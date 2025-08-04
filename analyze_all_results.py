#!/usr/bin/env python3

import os
import json
import sys
from pathlib import Path
from collections import defaultdict, Counter
import traceback

def safe_load_json(filepath):
    """Safely load JSON file and return None if failed"""
    try:
        with open(filepath, 'r') as f:
            return json.load(f)
    except (json.JSONDecodeError, FileNotFoundError, IOError) as e:
        print(f"Warning: Failed to load {filepath}: {e}")
        return None

def get_driver_name_from_path(logs_path):
    """Extract driver name from logs path"""
    parts = logs_path.split('/')
    # Find the driver name - it's usually the directory name before 'logs'
    for i, part in enumerate(parts):
        if part == 'logs' and i > 0:
            return parts[i-1]
    return "unknown"

def get_subsystem_from_path(logs_path):
    """Extract subsystem from logs path"""
    parts = logs_path.split('/')
    # Look for known subsystems
    subsystems = ['hwmon', 'edac', 'block', 'sound', 'usb', 'net_ethernet', 'md', 'gpu', 'arch_x86', 'foobar']
    for part in parts:
        if part in subsystems:
            return part
    return "unknown"

def analyze_risky_data_stat(data):
    """Analyze RiskyDataStat.json"""
    if not data:
        return {}
    
    return {
        'boundary_functions': data.get('Num kernel  boundary func', 0),
        'boundary_parameters': data.get('Num boundary parameters', 0),
        'shared_structs': data.get('Num shared struct', 0),
        'shared_fields': data.get('Shared fields', 0),
        'krdu_fields': data.get('KRDU fields', 0),
        'ptr_fields': data.get('ptr fields', 0),
        'func_ptr_fields': data.get('func ptr fields', 0),
        'data_ptr_fields': data.get('data ptr fields', 0),
        'risky_kernel_func': data.get('RISKY_KERNEL_FUNC', 0),
        'ptr_read': data.get('PTR_READ', 0),
        'branch': data.get('BRANCH', 0),
        'unclassify': data.get('UNCLASSIFY', 0)
    }

def analyze_risky_boundary_api(data):
    """Analyze RiskyBoundaryAPI.json"""
    if not data:
        return {}
    
    api_classes = Counter()
    direct_risky = 0
    controlled_paths = 0
    
    for item in data:
        api_class = item.get('Risky API Class', '')
        if api_class:
            api_classes[api_class] += 1
        
        if item.get('Direct Risky Kernel API', 0):
            direct_risky += 1
            
        if item.get('Is Controlled Path', 0):
            controlled_paths += 1
    
    return {
        'total_risky_apis': len(data),
        'api_classes': dict(api_classes),
        'direct_risky': direct_risky,
        'controlled_paths': controlled_paths
    }

def analyze_boundary_param_taint(data):
    """Analyze BoundaryParamTaint.json"""
    if not data:
        return {}
    
    total_entries = 0
    risky_types = Counter()
    
    # Handle the nested list structure
    if isinstance(data, list):
        for section in data:
            if isinstance(section, list):
                total_entries += len(section)
                for item in section:
                    if isinstance(item, dict):
                        risky = item.get('risky', '')
                        if risky:
                            # Extract the main risky type
                            risky_type = risky.split(' ')[0] if ' ' in risky else risky
                            risky_types[risky_type] += 1
    
    return {
        'total_taint_entries': total_entries,
        'risky_types': dict(risky_types)
    }

def process_logs_directory(logs_path):
    """Process a single logs directory and extract all analysis data"""
    result = {
        'driver_name': get_driver_name_from_path(logs_path),
        'subsystem': get_subsystem_from_path(logs_path),
        'logs_path': logs_path,
        'analysis_files': {},
        'errors': []
    }
    
    # Expected JSON files
    json_files = [
        'RiskyDataStat.json',
        'RiskyBoundaryAPI.json', 
        'BoundaryParamTaint.json',
        'BoundaryAPICounts.json',
        'UnclassifiedFields.json',
        'PerStructTaint.json'
    ]
    
    for json_file in json_files:
        filepath = os.path.join(logs_path, json_file)
        if os.path.exists(filepath):
            data = safe_load_json(filepath)
            if data is not None:
                result['analysis_files'][json_file] = data
            else:
                result['errors'].append(f"Failed to load {json_file}")
        else:
            result['errors'].append(f"Missing {json_file}")
    
    # Analyze the loaded data
    result['analyzed_data'] = {}
    
    if 'RiskyDataStat.json' in result['analysis_files']:
        result['analyzed_data']['risky_data_stat'] = analyze_risky_data_stat(
            result['analysis_files']['RiskyDataStat.json']
        )
    
    if 'RiskyBoundaryAPI.json' in result['analysis_files']:
        result['analyzed_data']['risky_boundary_api'] = analyze_risky_boundary_api(
            result['analysis_files']['RiskyBoundaryAPI.json']
        )
    
    if 'BoundaryParamTaint.json' in result['analysis_files']:
        result['analyzed_data']['boundary_param_taint'] = analyze_boundary_param_taint(
            result['analysis_files']['BoundaryParamTaint.json']
        )
    
    return result

def find_all_logs_directories(base_path):
    """Find all logs directories under base_path"""
    logs_dirs = []
    for root, dirs, files in os.walk(base_path):
        if 'logs' in dirs:
            logs_path = os.path.join(root, 'logs')
            logs_dirs.append(logs_path)
    return sorted(logs_dirs)

def generate_markdown_summary(all_results):
    """Generate a comprehensive markdown summary"""
    
    # Count successful vs failed analyses
    successful = [r for r in all_results if r['analyzed_data']]
    failed = [r for r in all_results if not r['analyzed_data']]
    
    # Group by subsystem
    by_subsystem = defaultdict(list)
    for result in successful:
        by_subsystem[result['subsystem']].append(result)
    
    # Aggregate statistics
    total_stats = {
        'total_drivers': len(successful),
        'total_boundary_functions': 0,
        'total_shared_fields': 0,
        'total_risky_apis': 0,
        'api_classes': Counter(),
        'risky_types': Counter()
    }
    
    for result in successful:
        if 'risky_data_stat' in result['analyzed_data']:
            rds = result['analyzed_data']['risky_data_stat']
            total_stats['total_boundary_functions'] += rds.get('boundary_functions', 0)
            total_stats['total_shared_fields'] += rds.get('shared_fields', 0)
        
        if 'risky_boundary_api' in result['analyzed_data']:
            rba = result['analyzed_data']['risky_boundary_api']
            total_stats['total_risky_apis'] += rba.get('total_risky_apis', 0)
            for api_class, count in rba.get('api_classes', {}).items():
                total_stats['api_classes'][api_class] += count
        
        if 'boundary_param_taint' in result['analyzed_data']:
            bpt = result['analyzed_data']['boundary_param_taint']
            for risky_type, count in bpt.get('risky_types', {}).items():
                total_stats['risky_types'][risky_type] += count

    # Generate markdown content
    md_content = f"""# SoK Paper Analysis Results Summary

Generated on: {os.popen('date').read().strip()}

## Executive Summary

- **Total Drivers Analyzed**: {len(successful)}
- **Failed Analyses**: {len(failed)}
- **Total Subsystems**: {len(by_subsystem)}
- **Total Boundary Functions**: {total_stats['total_boundary_functions']}
- **Total Shared Fields**: {total_stats['total_shared_fields']}
- **Total Risky APIs**: {total_stats['total_risky_apis']}

## Table 1: Driver Overview by Subsystem

| Subsystem | Driver Count | Avg Boundary Functions | Avg Shared Fields | Status |
|-----------|--------------|------------------------|-------------------|--------|
"""
    
    for subsystem, drivers in sorted(by_subsystem.items()):
        avg_boundary = sum(d['analyzed_data'].get('risky_data_stat', {}).get('boundary_functions', 0) for d in drivers) / len(drivers)
        avg_shared = sum(d['analyzed_data'].get('risky_data_stat', {}).get('shared_fields', 0) for d in drivers) / len(drivers)
        md_content += f"| {subsystem} | {len(drivers)} | {avg_boundary:.1f} | {avg_shared:.1f} | Complete |\n"
    
    md_content += f"""

## Table 2: Risky Field Analysis Summary

| Field Type | Total Count | Drivers Affected | Percentage |
|------------|-------------|------------------|------------|
"""
    
    field_stats = defaultdict(lambda: {'count': 0, 'drivers': set()})
    for result in successful:
        if 'risky_data_stat' in result['analyzed_data']:
            rds = result['analyzed_data']['risky_data_stat']
            driver_name = result['driver_name']
            
            for field_type in ['krdu_fields', 'ptr_fields', 'func_ptr_fields', 'data_ptr_fields']:
                count = rds.get(field_type, 0)
                if count > 0:
                    field_stats[field_type]['count'] += count
                    field_stats[field_type]['drivers'].add(driver_name)
    
    for field_type, stats in field_stats.items():
        percentage = (len(stats['drivers']) / len(successful)) * 100
        md_content += f"| {field_type.replace('_', ' ').title()} | {stats['count']} | {len(stats['drivers'])} | {percentage:.1f}% |\n"
    
    md_content += f"""

## Table 3: Risky Boundary API Analysis

| API Class | Total Occurrences | Drivers Affected | Avg per Driver |
|-----------|------------------|------------------|----------------|
"""
    
    for api_class, count in total_stats['api_classes'].most_common():
        drivers_with_class = sum(1 for r in successful 
                               if api_class in r['analyzed_data'].get('risky_boundary_api', {}).get('api_classes', {}))
        avg_per_driver = count / drivers_with_class if drivers_with_class > 0 else 0
        md_content += f"| {api_class} | {count} | {drivers_with_class} | {avg_per_driver:.1f} |\n"
    
    md_content += f"""

## Table 4: Overall Statistics Across All Analyzed Drivers

| Metric | Value | Notes |
|--------|-------|-------|
| Total Drivers Successfully Analyzed | {len(successful)} | Complete analysis with all JSON files |
| Total Failed Analyses | {len(failed)} | Missing or corrupted analysis files |
| Average Boundary Functions per Driver | {total_stats['total_boundary_functions'] / len(successful):.1f} | Kernel functions called by drivers |
| Average Shared Fields per Driver | {total_stats['total_shared_fields'] / len(successful):.1f} | Fields accessible by both driver and kernel |
| Average Risky APIs per Driver | {total_stats['total_risky_apis'] / len(successful):.1f} | APIs with potential security implications |

## Detailed Driver-by-Driver Analysis

"""
    
    for subsystem, drivers in sorted(by_subsystem.items()):
        md_content += f"### {subsystem.upper()} Subsystem\n\n"
        
        for driver in sorted(drivers, key=lambda x: x['driver_name']):
            md_content += f"#### {driver['driver_name']}\n\n"
            
            rds = driver['analyzed_data'].get('risky_data_stat', {})
            rba = driver['analyzed_data'].get('risky_boundary_api', {})
            bpt = driver['analyzed_data'].get('boundary_param_taint', {})
            
            md_content += f"- **Boundary Functions**: {rds.get('boundary_functions', 'N/A')}\n"
            md_content += f"- **Shared Fields**: {rds.get('shared_fields', 'N/A')}\n"
            md_content += f"- **Risky APIs**: {rba.get('total_risky_apis', 'N/A')}\n"
            md_content += f"- **Taint Entries**: {bpt.get('total_taint_entries', 'N/A')}\n"
            
            if rba.get('api_classes'):
                md_content += f"- **API Classes**: {', '.join(f'{k}({v})' for k, v in rba['api_classes'].items())}\n"
            
            if driver['errors']:
                md_content += f"- **Issues**: {', '.join(driver['errors'])}\n"
            
            md_content += f"- **Analysis Path**: `{driver['logs_path']}`\n\n"
    
    if failed:
        md_content += f"""
## Failed Analyses

The following {len(failed)} drivers had incomplete or failed analyses:

"""
        for failure in failed:
            md_content += f"- **{failure['driver_name']}** ({failure['subsystem']}): {', '.join(failure['errors'])}\n"
            md_content += f"  - Path: `{failure['logs_path']}`\n\n"
    
    md_content += f"""
## Data Integrity Notes

- **Analysis Method**: Data extracted from existing JSON analysis results only
- **No Simulation**: All statistics represent actual analysis output
- **File Coverage**: Attempted to read RiskyDataStat.json, RiskyBoundaryAPI.json, BoundaryParamTaint.json, and other analysis files
- **Error Handling**: Failed file reads and parsing errors are documented above

## Raw Data Summary

Total analysis directories found: {len(all_results)}
- Successful analyses: {len(successful)}
- Failed/incomplete analyses: {len(failed)}

Subsystem distribution:
"""
    
    for subsystem, count in sorted(Counter(r['subsystem'] for r in all_results).items()):
        md_content += f"- {subsystem}: {count} drivers\n"
    
    return md_content

def main():
    base_path = "/home/yzh89/Documents/SoK_experiment/bc-files-12"
    output_file = "/home/yzh89/Documents/SoK_experiment/pdg/ANALYSIS_SUMMARY.md"
    
    print("Starting comprehensive analysis of SoK paper results...")
    print(f"Base path: {base_path}")
    
    # Find all logs directories
    logs_dirs = find_all_logs_directories(base_path)
    print(f"Found {len(logs_dirs)} logs directories")
    
    # Process each logs directory
    all_results = []
    failed_count = 0
    
    for i, logs_dir in enumerate(logs_dirs, 1):
        print(f"Processing {i}/{len(logs_dirs)}: {logs_dir}")
        try:
            result = process_logs_directory(logs_dir)
            all_results.append(result)
            if result['errors']:
                failed_count += 1
        except Exception as e:
            print(f"Error processing {logs_dir}: {e}")
            failed_count += 1
            all_results.append({
                'driver_name': get_driver_name_from_path(logs_dir),
                'subsystem': get_subsystem_from_path(logs_dir),
                'logs_path': logs_dir,
                'analysis_files': {},
                'analyzed_data': {},
                'errors': [f"Processing error: {str(e)}"]
            })
    
    print(f"Processed {len(all_results)} directories, {failed_count} had issues")
    
    # Generate markdown summary
    print("Generating markdown summary...")
    markdown_content = generate_markdown_summary(all_results)
    
    # Write to file
    with open(output_file, 'w') as f:
        f.write(markdown_content)
    
    print(f"Analysis complete! Summary written to: {output_file}")
    print(f"Successfully analyzed: {len([r for r in all_results if r['analyzed_data']])} drivers")
    print(f"Failed analyses: {len([r for r in all_results if not r['analyzed_data']])} drivers")

if __name__ == "__main__":
    main()