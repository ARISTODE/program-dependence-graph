# SoK Paper Analysis Results Summary

Generated on: Mon 04 Aug 2025 12:46:30 AM EDT

## Executive Summary

- **Total Drivers Analyzed**: 450
- **Failed Analyses**: 24
- **Total Subsystems**: 11
- **Total Boundary Functions**: 6560
- **Total Shared Fields**: 6367
- **Total Risky APIs**: 12270

## Table 1: Driver Overview by Subsystem

| Subsystem | Driver Count | Avg Boundary Functions | Avg Shared Fields | Status |
|-----------|--------------|------------------------|-------------------|--------|
| arch_x86 | 2 | 18.0 | 7.0 | Complete |
| block | 26 | 29.1 | 25.2 | Complete |
| edac | 41 | 19.9 | 26.6 | Complete |
| foobar | 1 | 17.0 | 17.0 | Complete |
| gpu | 2 | 83.0 | 71.0 | Complete |
| hwmon | 199 | 6.8 | 4.3 | Complete |
| md | 6 | 13.7 | 15.5 | Complete |
| net_ethernet | 58 | 34.6 | 43.7 | Complete |
| sound | 9 | 5.0 | 3.0 | Complete |
| unknown | 13 | 19.8 | 26.0 | Complete |
| usb | 93 | 10.9 | 6.5 | Complete |


## Table 2: Risky Field Analysis Summary

| Field Type | Total Count | Drivers Affected | Percentage |
|------------|-------------|------------------|------------|
| Krdu Fields | 2048 | 82 | 18.2% |
| Ptr Fields | 3673 | 83 | 18.4% |
| Func Ptr Fields | 304 | 49 | 10.9% |
| Data Ptr Fields | 3357 | 77 | 17.1% |


## Table 3: Risky Boundary API Analysis

| API Class | Total Occurrences | Drivers Affected | Avg per Driver |
|-----------|------------------|------------------|----------------|
| concurrency | 3358 | 375 | 9.0 |
| memory | 2561 | 424 | 6.0 |
| bus | 1960 | 144 | 13.6 |
| timer | 1343 | 86 | 15.6 |
| refCount | 1316 | 238 | 5.5 |
| dma | 28 | 2 | 14.0 |
| ioPorts | 20 | 5 | 4.0 |


## Table 4: Overall Statistics Across All Analyzed Drivers

| Metric | Value | Notes |
|--------|-------|-------|
| Total Drivers Successfully Analyzed | 450 | Complete analysis with all JSON files |
| Total Failed Analyses | 24 | Missing or corrupted analysis files |
| Average Boundary Functions per Driver | 14.6 | Kernel functions called by drivers |
| Average Shared Fields per Driver | 14.1 | Fields accessible by both driver and kernel |
| Average Risky APIs per Driver | 27.3 | APIs with potential security implications |

## Detailed Driver-by-Driver Analysis

### ARCH_X86 Subsystem

#### msr

- **Boundary Functions**: 18
- **Shared Fields**: 7
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/arch_x86/msr/logs`

#### msr

- **Boundary Functions**: 18
- **Shared Fields**: 7
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: memory(6), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/arch_x86/msr/logs`

### BLOCK Subsystem

#### DAC960

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: refCount(4), concurrency(12), memory(8), bus(3), timer(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/DAC960/logs`

#### aoe

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 117
- **Taint Entries**: N/A
- **API Classes**: memory(17), concurrency(28), timer(55), refCount(13)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/aoe/logs`

#### aoe

- **Boundary Functions**: 94
- **Shared Fields**: 76
- **Risky APIs**: 97
- **Taint Entries**: N/A
- **API Classes**: memory(20), concurrency(48), refCount(17), timer(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/aoe/logs`

#### brd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 15
- **Taint Entries**: N/A
- **API Classes**: refCount(4), memory(3), concurrency(8)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/brd/logs`

#### brd

- **Boundary Functions**: 26
- **Shared Fields**: 18
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(10), refCount(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/brd/logs`

#### cciss

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 53
- **Taint Entries**: N/A
- **API Classes**: concurrency(18), refCount(15), memory(10), bus(5)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/cciss/logs`

#### cryptoloop

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/cryptoloop/logs`

#### loop

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 36
- **Taint Entries**: N/A
- **API Classes**: refCount(5), memory(12), concurrency(16)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/loop/logs`

#### loop

- **Boundary Functions**: 79
- **Shared Fields**: 90
- **Risky APIs**: 121
- **Taint Entries**: N/A
- **API Classes**: timer(59), memory(15), concurrency(28), refCount(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/loop/logs`

#### mtip32xx

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 151
- **Taint Entries**: N/A
- **API Classes**: memory(13), refCount(15), timer(37), dma(27), bus(21), concurrency(18)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/mtip32xx/logs`

#### nbd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 37
- **Taint Entries**: N/A
- **API Classes**: refCount(5), concurrency(18), timer(2), memory(9)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/nbd/logs`

#### nbd

- **Boundary Functions**: 92
- **Shared Fields**: 85
- **Risky APIs**: 155
- **Taint Entries**: N/A
- **API Classes**: concurrency(42), memory(22), refCount(17), timer(53)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/nbd/logs`

#### null_blk

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 31
- **Taint Entries**: N/A
- **API Classes**: concurrency(16), memory(9), refCount(5)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/null_blk/logs`

#### null_blk

- **Boundary Functions**: 75
- **Shared Fields**: 76
- **Risky APIs**: 84
- **Taint Entries**: N/A
- **API Classes**: concurrency(38), memory(23), timer(10), refCount(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/block/null_blk/logs`

#### null_blk

- **Boundary Functions**: 75
- **Shared Fields**: 76
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/null_blk/logs`

#### nvme

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 149
- **Taint Entries**: N/A
- **API Classes**: bus(36), memory(27), concurrency(24), refCount(17), timer(34)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/nvme/logs`

#### nvme-core

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 84
- **Taint Entries**: N/A
- **API Classes**: memory(14), refCount(22), concurrency(18), timer(25)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/nvme-core/logs`

#### nvme-core

- **Boundary Functions**: 155
- **Shared Fields**: 115
- **Risky APIs**: 403
- **Taint Entries**: N/A
- **API Classes**: memory(47), concurrency(92), timer(207), refCount(25)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/block/nvme-core/logs`

#### nvme-core

- **Boundary Functions**: 155
- **Shared Fields**: 115
- **Risky APIs**: 403
- **Taint Entries**: N/A
- **API Classes**: memory(47), concurrency(92), timer(207), refCount(25)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/nvme-core/logs`

#### nvmem-rmem

- **Boundary Functions**: 6
- **Shared Fields**: 3
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/nvmem-rmem/logs`

#### pktcdvd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 119
- **Taint Entries**: N/A
- **API Classes**: memory(31), refCount(33), concurrency(31)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/pktcdvd/logs`

#### rbd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 175
- **Taint Entries**: N/A
- **API Classes**: memory(31), refCount(28), concurrency(52), timer(13)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/rbd/logs`

#### rsxx

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 78
- **Taint Entries**: N/A
- **API Classes**: memory(17), refCount(11), concurrency(24), ioPorts(2), timer(8), bus(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/rsxx/logs`

#### skd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 64
- **Taint Entries**: N/A
- **API Classes**: bus(25), timer(9), refCount(5), memory(7), concurrency(16)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/skd/logs`

#### sx8

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(10), bus(6), refCount(4), timer(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/sx8/logs`

#### umem

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 27
- **Taint Entries**: N/A
- **API Classes**: memory(7), concurrency(8), timer(2), refCount(4), bus(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/block/umem/logs`

### EDAC Subsystem

#### e752x_edac

- **Boundary Functions**: 20
- **Shared Fields**: 23
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: bus(18), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/e752x_edac/logs`

#### e752x_edac

- **Boundary Functions**: 20
- **Shared Fields**: 23
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: bus(18), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/e752x_edac/logs`

#### e752x_edac

- **Boundary Functions**: 20
- **Shared Fields**: 23
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: bus(18), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/e752x_edac/logs`

#### i3000_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i3000_edac/logs`

#### i3000_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i3000_edac/logs`

#### i3000_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i3000_edac/logs`

#### i3200_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i3200_edac/logs`

#### i3200_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i3200_edac/logs`

#### i3200_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i3200_edac/logs`

#### i5000_edac

- **Boundary Functions**: 19
- **Shared Fields**: 25
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(6), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i5000_edac/logs`

#### i5000_edac

- **Boundary Functions**: 19
- **Shared Fields**: 25
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(6), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i5000_edac/logs`

#### i5000_edac

- **Boundary Functions**: 19
- **Shared Fields**: 25
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(6), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i5000_edac/logs`

#### i5100_edac

- **Boundary Functions**: 24
- **Shared Fields**: 30
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2), timer(2), bus(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i5100_edac/logs`

#### i5100_edac

- **Boundary Functions**: 24
- **Shared Fields**: 30
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2), timer(2), bus(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i5100_edac/logs`

#### i5100_edac

- **Boundary Functions**: 24
- **Shared Fields**: 30
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2), timer(2), bus(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i5100_edac/logs`

#### i5400_edac

- **Boundary Functions**: 19
- **Shared Fields**: 26
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i5400_edac/logs`

#### i5400_edac

- **Boundary Functions**: 19
- **Shared Fields**: 26
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i5400_edac/logs`

#### i5400_edac

- **Boundary Functions**: 19
- **Shared Fields**: 26
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i5400_edac/logs`

#### i7300_edac

- **Boundary Functions**: 19
- **Shared Fields**: 24
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i7300_edac/logs`

#### i7300_edac

- **Boundary Functions**: 19
- **Shared Fields**: 24
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i7300_edac/logs`

#### i7300_edac

- **Boundary Functions**: 19
- **Shared Fields**: 24
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i7300_edac/logs`

#### i7core_edac

- **Boundary Functions**: 26
- **Shared Fields**: 35
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(4), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i7core_edac/logs`

#### i7core_edac

- **Boundary Functions**: 26
- **Shared Fields**: 35
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(4), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i7core_edac/logs`

#### i7core_edac

- **Boundary Functions**: 26
- **Shared Fields**: 35
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(4), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i7core_edac/logs`

#### i82975x_edac

- **Boundary Functions**: 18
- **Shared Fields**: 23
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/i82975x_edac/logs`

#### i82975x_edac

- **Boundary Functions**: 18
- **Shared Fields**: 23
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/i82975x_edac/logs`

#### i82975x_edac

- **Boundary Functions**: 18
- **Shared Fields**: 23
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/i82975x_edac/logs`

#### ie31200_edac

- **Boundary Functions**: 17
- **Shared Fields**: 20
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/ie31200_edac/logs`

#### ie31200_edac

- **Boundary Functions**: 17
- **Shared Fields**: 20
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/ie31200_edac/logs`

#### ie31200_edac

- **Boundary Functions**: 17
- **Shared Fields**: 20
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/ie31200_edac/logs`

#### sb_edac

- **Boundary Functions**: 17
- **Shared Fields**: 39
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(1), bus(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/sb_edac/logs`

#### sb_edac

- **Boundary Functions**: 17
- **Shared Fields**: 39
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(1), bus(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/edac/sb_edac/logs`

#### sb_edac

- **Boundary Functions**: 17
- **Shared Fields**: 39
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(1), bus(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/sb_edac/logs`

#### sb_edac

- **Boundary Functions**: 17
- **Shared Fields**: 39
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(1), bus(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/sb_edac/logs`

#### skx_edac

- **Boundary Functions**: 25
- **Shared Fields**: 37
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), bus(3), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/skx_edac/logs`

#### skx_edac

- **Boundary Functions**: 25
- **Shared Fields**: 37
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), bus(3), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/edac/skx_edac/logs`

#### skx_edac

- **Boundary Functions**: 25
- **Shared Fields**: 37
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), bus(3), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/skx_edac/logs`

#### skx_edac

- **Boundary Functions**: 25
- **Shared Fields**: 37
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), bus(3), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/skx_edac/logs`

#### x38_edac

- **Boundary Functions**: 18
- **Shared Fields**: 18
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/edac/x38_edac/logs`

#### x38_edac

- **Boundary Functions**: 18
- **Shared Fields**: 18
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/edac/x38_edac/logs`

#### x38_edac

- **Boundary Functions**: 18
- **Shared Fields**: 18
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/edac/x38_edac/logs`

### FOOBAR Subsystem

#### foobar_dummy

- **Boundary Functions**: 17
- **Shared Fields**: 17
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/foobar/foobar_dummy/logs`

### GPU Subsystem

#### mgag200

- **Boundary Functions**: 83
- **Shared Fields**: 71
- **Risky APIs**: 155
- **Taint Entries**: N/A
- **API Classes**: memory(42), refCount(6), concurrency(29), ioPorts(4), bus(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/gpu/mgag200/logs`

#### mgag200

- **Boundary Functions**: 83
- **Shared Fields**: 71
- **Risky APIs**: 155
- **Taint Entries**: N/A
- **API Classes**: memory(42), refCount(6), concurrency(29), ioPorts(4), bus(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/gpu/mgag200/logs`

### HWMON Subsystem

#### abituguru

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 22
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(8), refCount(7)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/abituguru/logs`

#### abituguru

- **Boundary Functions**: 16
- **Shared Fields**: 6
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(9), memory(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/abituguru/logs`

#### abituguru

- **Boundary Functions**: 16
- **Shared Fields**: 6
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(9), memory(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/abituguru/logs`

#### abituguru3

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 22
- **Taint Entries**: N/A
- **API Classes**: refCount(7), concurrency(8), memory(5)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/abituguru3/logs`

#### abituguru3

- **Boundary Functions**: 15
- **Shared Fields**: 5
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(9), memory(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/abituguru3/logs`

#### abituguru3

- **Boundary Functions**: 15
- **Shared Fields**: 5
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(9), memory(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/abituguru3/logs`

#### acpi_power_meter

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), refCount(15), memory(3)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/acpi_power_meter/logs`

#### acpi_power_meter

- **Boundary Functions**: 24
- **Shared Fields**: 18
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: refCount(7), memory(7), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/hwmon/acpi_power_meter/logs`

#### acpi_power_meter

- **Boundary Functions**: 24
- **Shared Fields**: 18
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: refCount(7), memory(7), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/acpi_power_meter/logs`

#### acpi_power_meter

- **Boundary Functions**: 24
- **Shared Fields**: 18
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: refCount(7), memory(7), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/acpi_power_meter/logs`

#### ad7414

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ad7414/logs`

#### ad7414

- **Boundary Functions**: 8
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ad7414/logs`

#### ad7414

- **Boundary Functions**: 8
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ad7414/logs`

#### ad7418

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(6), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ad7418/logs`

#### ad7418

- **Boundary Functions**: 9
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ad7418/logs`

#### ad7418

- **Boundary Functions**: 9
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ad7418/logs`

#### adm1021

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adm1021/logs`

#### adm1021

- **Boundary Functions**: 8
- **Shared Fields**: 8
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adm1021/logs`

#### adm1021

- **Boundary Functions**: 8
- **Shared Fields**: 8
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adm1021/logs`

#### adm1025

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adm1025/logs`

#### adm1025

- **Boundary Functions**: 8
- **Shared Fields**: 7
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adm1025/logs`

#### adm1025

- **Boundary Functions**: 8
- **Shared Fields**: 7
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adm1025/logs`

#### adm1026

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adm1026/logs`

#### adm1026

- **Boundary Functions**: 9
- **Shared Fields**: 8
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adm1026/logs`

#### adm1026

- **Boundary Functions**: 9
- **Shared Fields**: 8
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adm1026/logs`

#### adm1029

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adm1029/logs`

#### adm1029

- **Boundary Functions**: 8
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adm1029/logs`

#### adm1029

- **Boundary Functions**: 8
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adm1029/logs`

#### adm1031

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adm1031/logs`

#### adm1031

- **Boundary Functions**: 8
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adm1031/logs`

#### adm1031

- **Boundary Functions**: 8
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adm1031/logs`

#### adm9240

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adm9240/logs`

#### adm9240

- **Boundary Functions**: 13
- **Shared Fields**: 8
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adm9240/logs`

#### adm9240

- **Boundary Functions**: 13
- **Shared Fields**: 8
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adm9240/logs`

#### adt7410

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 4
- **Taint Entries**: N/A
- **API Classes**: concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adt7410/logs`

#### adt7410

- **Boundary Functions**: 5
- **Shared Fields**: 3
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adt7410/logs`

#### adt7410

- **Boundary Functions**: 5
- **Shared Fields**: 3
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adt7410/logs`

#### adt7411

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adt7411/logs`

#### adt7411

- **Boundary Functions**: 6
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adt7411/logs`

#### adt7411

- **Boundary Functions**: 6
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adt7411/logs`

#### adt7462

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adt7462/logs`

#### adt7462

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adt7462/logs`

#### adt7462

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adt7462/logs`

#### adt7470

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adt7470/logs`

#### adt7470

- **Boundary Functions**: 13
- **Shared Fields**: 7
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adt7470/logs`

#### adt7470

- **Boundary Functions**: 13
- **Shared Fields**: 7
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adt7470/logs`

#### adt7475

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(8), refCount(3)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adt7475/logs`

#### adt7475

- **Boundary Functions**: 13
- **Shared Fields**: 10
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adt7475/logs`

#### adt7475

- **Boundary Functions**: 13
- **Shared Fields**: 10
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adt7475/logs`

#### adt7x10

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 15
- **Taint Entries**: N/A
- **API Classes**: memory(4), bus(2), concurrency(4), refCount(3)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/adt7x10/logs`

#### adt7x10

- **Boundary Functions**: 7
- **Shared Fields**: 1
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/adt7x10/logs`

#### adt7x10

- **Boundary Functions**: 7
- **Shared Fields**: 1
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/adt7x10/logs`

#### applesmc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 17
- **Taint Entries**: N/A
- **API Classes**: concurrency(7), memory(5), timer(3)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/applesmc/logs`

#### asb100

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 24
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(12), refCount(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/asb100/logs`

#### asb100

- **Boundary Functions**: 15
- **Shared Fields**: 7
- **Risky APIs**: 32
- **Taint Entries**: N/A
- **API Classes**: refCount(8), concurrency(12), memory(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/asb100/logs`

#### asb100

- **Boundary Functions**: 15
- **Shared Fields**: 7
- **Risky APIs**: 32
- **Taint Entries**: N/A
- **API Classes**: refCount(8), concurrency(12), memory(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/asb100/logs`

#### asc7621

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(3), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/asc7621/logs`

#### asc7621

- **Boundary Functions**: 10
- **Shared Fields**: 7
- **Risky APIs**: 20
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(5), refCount(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/asc7621/logs`

#### asc7621

- **Boundary Functions**: 10
- **Shared Fields**: 7
- **Risky APIs**: 20
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(5), refCount(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/asc7621/logs`

#### atxp1

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/atxp1/logs`

#### atxp1

- **Boundary Functions**: 10
- **Shared Fields**: 3
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/atxp1/logs`

#### atxp1

- **Boundary Functions**: 10
- **Shared Fields**: 3
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/atxp1/logs`

#### coretemp

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 20
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(8), refCount(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/coretemp/logs`

#### coretemp

- **Boundary Functions**: 21
- **Shared Fields**: 15
- **Risky APIs**: 32
- **Taint Entries**: N/A
- **API Classes**: memory(7), bus(1), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/coretemp/logs`

#### coretemp

- **Boundary Functions**: 21
- **Shared Fields**: 15
- **Risky APIs**: 32
- **Taint Entries**: N/A
- **API Classes**: memory(7), bus(1), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/coretemp/logs`

#### dell-smm-hwmon

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/dell-smm-hwmon/logs`

#### dell-smm-hwmon

- **Boundary Functions**: 18
- **Shared Fields**: 1
- **Risky APIs**: 21
- **Taint Entries**: N/A
- **API Classes**: memory(6), refCount(7), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/dell-smm-hwmon/logs`

#### dell-smm-hwmon

- **Boundary Functions**: 18
- **Shared Fields**: 1
- **Risky APIs**: 21
- **Taint Entries**: N/A
- **API Classes**: memory(6), refCount(7), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/dell-smm-hwmon/logs`

#### ds1621

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ds1621/logs`

#### ds1621

- **Boundary Functions**: 8
- **Shared Fields**: 4
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ds1621/logs`

#### ds1621

- **Boundary Functions**: 8
- **Shared Fields**: 4
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ds1621/logs`

#### ds620

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ds620/logs`

#### ds620

- **Boundary Functions**: 5
- **Shared Fields**: 4
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ds620/logs`

#### ds620

- **Boundary Functions**: 5
- **Shared Fields**: 4
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ds620/logs`

#### f71805f

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(7), memory(5), bus(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/f71805f/logs`

#### f71805f

- **Boundary Functions**: 22
- **Shared Fields**: 12
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: memory(9), bus(2), concurrency(8), refCount(9)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/f71805f/logs`

#### f71805f

- **Boundary Functions**: 22
- **Shared Fields**: 12
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: memory(9), bus(2), concurrency(8), refCount(9)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/f71805f/logs`

#### f71882fg

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 27
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(8), refCount(7), bus(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/f71882fg/logs`

#### f71882fg

- **Boundary Functions**: 21
- **Shared Fields**: 11
- **Risky APIs**: 31
- **Taint Entries**: N/A
- **API Classes**: memory(8), bus(1), concurrency(8), refCount(9)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/f71882fg/logs`

#### f71882fg

- **Boundary Functions**: 21
- **Shared Fields**: 11
- **Risky APIs**: 31
- **Taint Entries**: N/A
- **API Classes**: memory(8), bus(1), concurrency(8), refCount(9)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/f71882fg/logs`

#### f75375s

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(3), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/f75375s/logs`

#### f75375s

- **Boundary Functions**: 12
- **Shared Fields**: 7
- **Risky APIs**: 20
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(4), concurrency(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/f75375s/logs`

#### f75375s

- **Boundary Functions**: 12
- **Shared Fields**: 7
- **Risky APIs**: 20
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(4), concurrency(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/f75375s/logs`

#### fam15h_power

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: bus(2), memory(2), concurrency(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/fam15h_power/logs`

#### fam15h_power

- **Boundary Functions**: 14
- **Shared Fields**: 5
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(3), refCount(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/fam15h_power/logs`

#### fam15h_power

- **Boundary Functions**: 14
- **Shared Fields**: 5
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(3), refCount(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/fam15h_power/logs`

#### fschmd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), refCount(3), memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/fschmd/logs`

#### fschmd

- **Boundary Functions**: 17
- **Shared Fields**: 8
- **Risky APIs**: 25
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(10), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/fschmd/logs`

#### fschmd

- **Boundary Functions**: 17
- **Shared Fields**: 8
- **Risky APIs**: 25
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(10), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/fschmd/logs`

#### g760a

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/g760a/logs`

#### g760a

- **Boundary Functions**: 6
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/g760a/logs`

#### g760a

- **Boundary Functions**: 6
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/g760a/logs`

#### g762

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 25
- **Taint Entries**: N/A
- **API Classes**: concurrency(14), refCount(5), memory(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/g762/logs`

#### g762

- **Boundary Functions**: 11
- **Shared Fields**: 7
- **Risky APIs**: 27
- **Taint Entries**: N/A
- **API Classes**: memory(6), refCount(3), concurrency(12)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/g762/logs`

#### g762

- **Boundary Functions**: 11
- **Shared Fields**: 7
- **Risky APIs**: 27
- **Taint Entries**: N/A
- **API Classes**: memory(6), refCount(3), concurrency(12)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/g762/logs`

#### gl518sm

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/gl518sm/logs`

#### gl518sm

- **Boundary Functions**: 7
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/gl518sm/logs`

#### gl518sm

- **Boundary Functions**: 7
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/gl518sm/logs`

#### gl520sm

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(6), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/gl520sm/logs`

#### gl520sm

- **Boundary Functions**: 9
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/gl520sm/logs`

#### gl520sm

- **Boundary Functions**: 9
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/gl520sm/logs`

#### hih6130

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/hih6130/logs`

#### hih6130

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(2), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/hih6130/logs`

#### hih6130

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(2), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/hih6130/logs`

#### hwmon-vid

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/hwmon-vid/logs`

#### hwmon-vid

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/hwmon-vid/logs`

#### i5500_temp

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(2), refCount(2), bus(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/i5500_temp/logs`

#### i5500_temp

- **Boundary Functions**: 9
- **Shared Fields**: 2
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(4), memory(3), refCount(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/i5500_temp/logs`

#### i5500_temp

- **Boundary Functions**: 9
- **Shared Fields**: 2
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(4), memory(3), refCount(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/i5500_temp/logs`

#### i5k_amb

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(5), refCount(9), bus(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/i5k_amb/logs`

#### i5k_amb

- **Boundary Functions**: 20
- **Shared Fields**: 7
- **Risky APIs**: 36
- **Taint Entries**: N/A
- **API Classes**: memory(8), bus(4), refCount(11), concurrency(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/i5k_amb/logs`

#### i5k_amb

- **Boundary Functions**: 20
- **Shared Fields**: 7
- **Risky APIs**: 36
- **Taint Entries**: N/A
- **API Classes**: memory(8), bus(4), refCount(11), concurrency(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/i5k_amb/logs`

#### ibmaem

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 25
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(8), refCount(7)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ibmaem/logs`

#### ibmaem

- **Boundary Functions**: 20
- **Shared Fields**: 11
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: memory(7), concurrency(10), refCount(11)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ibmaem/logs`

#### ibmaem

- **Boundary Functions**: 20
- **Shared Fields**: 11
- **Risky APIs**: 34
- **Taint Entries**: N/A
- **API Classes**: memory(7), concurrency(10), refCount(11)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ibmaem/logs`

#### ibmpex

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), refCount(3), memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ibmpex/logs`

#### ibmpex

- **Boundary Functions**: 12
- **Shared Fields**: 4
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), refCount(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ibmpex/logs`

#### ibmpex

- **Boundary Functions**: 12
- **Shared Fields**: 4
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), refCount(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ibmpex/logs`

#### it87

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 27
- **Taint Entries**: N/A
- **API Classes**: bus(2), memory(7), concurrency(6), refCount(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/it87/logs`

#### it87

- **Boundary Functions**: 22
- **Shared Fields**: 11
- **Risky APIs**: 36
- **Taint Entries**: N/A
- **API Classes**: memory(8), bus(5), refCount(8), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/it87/logs`

#### it87

- **Boundary Functions**: 22
- **Shared Fields**: 11
- **Risky APIs**: 36
- **Taint Entries**: N/A
- **API Classes**: memory(8), bus(5), refCount(8), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/it87/logs`

#### jc42

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/jc42/logs`

#### jc42

- **Boundary Functions**: 9
- **Shared Fields**: 4
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/jc42/logs`

#### jc42

- **Boundary Functions**: 9
- **Shared Fields**: 4
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/jc42/logs`

#### k10temp

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: bus(2), memory(3), concurrency(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/k10temp/logs`

#### k10temp

- **Boundary Functions**: 9
- **Shared Fields**: 5
- **Risky APIs**: 17
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(3), refCount(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/k10temp/logs`

#### k10temp

- **Boundary Functions**: 9
- **Shared Fields**: 5
- **Risky APIs**: 17
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(3), refCount(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/k10temp/logs`

#### k8temp

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: refCount(3), concurrency(4), memory(3)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/k8temp/logs`

#### k8temp

- **Boundary Functions**: 8
- **Shared Fields**: 3
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(3), refCount(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/k8temp/logs`

#### k8temp

- **Boundary Functions**: 8
- **Shared Fields**: 3
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(3), refCount(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/k8temp/logs`

#### lineage-pem

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(6), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/lineage-pem/logs`

#### lineage-pem

- **Boundary Functions**: 7
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/lineage-pem/logs`

#### lineage-pem

- **Boundary Functions**: 7
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/lineage-pem/logs`

#### lm63

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/lm63/logs`

#### lm63

- **Boundary Functions**: 9
- **Shared Fields**: 11
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/lm63/logs`

#### lm63

- **Boundary Functions**: 9
- **Shared Fields**: 11
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/lm63/logs`

#### lm73

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/lm73/logs`

#### lm73

- **Boundary Functions**: 7
- **Shared Fields**: 6
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/lm73/logs`

#### lm73

- **Boundary Functions**: 7
- **Shared Fields**: 6
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/lm73/logs`

#### lm75

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(6), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/lm75/logs`

#### lm75

- **Boundary Functions**: 12
- **Shared Fields**: 10
- **Risky APIs**: 19
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/lm75/logs`

#### lm75

- **Boundary Functions**: 12
- **Shared Fields**: 10
- **Risky APIs**: 19
- **Taint Entries**: N/A
- **API Classes**: memory(5), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/lm75/logs`

#### ltc2945

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 15
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc2945/logs`

#### ltc2945

- **Boundary Functions**: 11
- **Shared Fields**: 3
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc2945/logs`

#### ltc2945

- **Boundary Functions**: 11
- **Shared Fields**: 3
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc2945/logs`

#### ltc2990

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc2990/logs`

#### ltc2990

- **Boundary Functions**: 9
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc2990/logs`

#### ltc2990

- **Boundary Functions**: 9
- **Shared Fields**: 6
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc2990/logs`

#### ltc4151

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc4151/logs`

#### ltc4151

- **Boundary Functions**: 6
- **Shared Fields**: 7
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc4151/logs`

#### ltc4151

- **Boundary Functions**: 6
- **Shared Fields**: 7
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc4151/logs`

#### ltc4215

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc4215/logs`

#### ltc4215

- **Boundary Functions**: 7
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc4215/logs`

#### ltc4215

- **Boundary Functions**: 7
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc4215/logs`

#### ltc4222

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(6), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc4222/logs`

#### ltc4222

- **Boundary Functions**: 9
- **Shared Fields**: 3
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: refCount(3), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc4222/logs`

#### ltc4222

- **Boundary Functions**: 9
- **Shared Fields**: 3
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: refCount(3), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc4222/logs`

#### ltc4245

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc4245/logs`

#### ltc4245

- **Boundary Functions**: 5
- **Shared Fields**: 8
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc4245/logs`

#### ltc4245

- **Boundary Functions**: 5
- **Shared Fields**: 8
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc4245/logs`

#### ltc4260

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(6), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc4260/logs`

#### ltc4260

- **Boundary Functions**: 8
- **Shared Fields**: 3
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: refCount(3), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc4260/logs`

#### ltc4260

- **Boundary Functions**: 8
- **Shared Fields**: 3
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: refCount(3), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc4260/logs`

#### ltc4261

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/ltc4261/logs`

#### ltc4261

- **Boundary Functions**: 8
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/ltc4261/logs`

#### ltc4261

- **Boundary Functions**: 8
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/ltc4261/logs`

#### max16065

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max16065/logs`

#### max16065

- **Boundary Functions**: 7
- **Shared Fields**: 7
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max16065/logs`

#### max16065

- **Boundary Functions**: 7
- **Shared Fields**: 7
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max16065/logs`

#### max1619

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max1619/logs`

#### max1619

- **Boundary Functions**: 7
- **Shared Fields**: 8
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max1619/logs`

#### max1619

- **Boundary Functions**: 7
- **Shared Fields**: 8
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max1619/logs`

#### max1668

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max1668/logs`

#### max1668

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max1668/logs`

#### max1668

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max1668/logs`

#### max197

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), refCount(3), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max197/logs`

#### max197

- **Boundary Functions**: 7
- **Shared Fields**: 6
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), refCount(4), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max197/logs`

#### max197

- **Boundary Functions**: 7
- **Shared Fields**: 6
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), refCount(4), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max197/logs`

#### max31790

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max31790/logs`

#### max31790

- **Boundary Functions**: 5
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max31790/logs`

#### max31790

- **Boundary Functions**: 5
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max31790/logs`

#### max6639

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max6639/logs`

#### max6639

- **Boundary Functions**: 7
- **Shared Fields**: 7
- **Risky APIs**: 17
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max6639/logs`

#### max6639

- **Boundary Functions**: 7
- **Shared Fields**: 7
- **Risky APIs**: 17
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max6639/logs`

#### max6642

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max6642/logs`

#### max6642

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max6642/logs`

#### max6642

- **Boundary Functions**: 6
- **Shared Fields**: 6
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max6642/logs`

#### max6650

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max6650/logs`

#### max6650

- **Boundary Functions**: 9
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max6650/logs`

#### max6650

- **Boundary Functions**: 9
- **Shared Fields**: 5
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(4), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max6650/logs`

#### max6697

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/max6697/logs`

#### max6697

- **Boundary Functions**: 7
- **Shared Fields**: 9
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/max6697/logs`

#### max6697

- **Boundary Functions**: 7
- **Shared Fields**: 9
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/max6697/logs`

#### mcp3021

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/mcp3021/logs`

#### mcp3021

- **Boundary Functions**: 4
- **Shared Fields**: 7
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/mcp3021/logs`

#### mcp3021

- **Boundary Functions**: 4
- **Shared Fields**: 7
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/mcp3021/logs`

#### powr1220

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/powr1220/logs`

#### powr1220

- **Boundary Functions**: 7
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/hwmon/powr1220/logs`

#### powr1220

- **Boundary Functions**: 7
- **Shared Fields**: 5
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/hwmon/powr1220/logs`

### MD Subsystem

#### dm-bufio

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 71
- **Taint Entries**: N/A
- **API Classes**: timer(33), memory(15), concurrency(17)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/md/dm-bufio/logs`

#### dm-crypt

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 52
- **Taint Entries**: N/A
- **API Classes**: memory(19), concurrency(12), timer(14)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/md/dm-crypt/logs`

#### dm-crypt

- **Boundary Functions**: 72
- **Shared Fields**: 89
- **Risky APIs**: 70
- **Taint Entries**: N/A
- **API Classes**: memory(21), concurrency(38), timer(2), refCount(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/md/dm-crypt/logs`

#### dm-zero

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/md/dm-zero/logs`

#### dm-zero

- **Boundary Functions**: 5
- **Shared Fields**: 2
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/md/dm-zero/logs`

#### dm-zero

- **Boundary Functions**: 5
- **Shared Fields**: 2
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/md/dm-zero/logs`

### NET_ETHERNET Subsystem

#### 8139cp

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 54
- **Taint Entries**: N/A
- **API Classes**: memory(13), refCount(2), concurrency(10), bus(21), timer(5)
- **Issues**: Missing RiskyDataStat.json, Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/8139cp/logs`

#### 8390

- **Boundary Functions**: 20
- **Shared Fields**: 17
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/8390/logs`

#### altera_tse

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 33
- **Taint Entries**: N/A
- **API Classes**: memory(11), refCount(3), concurrency(8), timer(3), bus(5)
- **Issues**: Missing RiskyDataStat.json, Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/altera_tse/logs`

#### alx

- **Boundary Functions**: 59
- **Shared Fields**: 89
- **Risky APIs**: 75
- **Taint Entries**: N/A
- **API Classes**: timer(7), memory(11), refCount(5), concurrency(11), bus(38)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/net_ethernet/alx/logs`

#### alx

- **Boundary Functions**: 59
- **Shared Fields**: 89
- **Risky APIs**: 75
- **Taint Entries**: N/A
- **API Classes**: timer(7), memory(11), refCount(5), concurrency(11), bus(38)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/alx/logs`

#### amd8111e

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 37
- **Taint Entries**: N/A
- **API Classes**: memory(10), refCount(2), concurrency(6), timer(10), bus(6)
- **Issues**: Missing RiskyDataStat.json, Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/amd8111e/logs`

#### bcm-phy-lib

- **Boundary Functions**: 2
- **Shared Fields**: 1
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/bcm-phy-lib/logs`

#### bcm7xxx

- **Boundary Functions**: 3
- **Shared Fields**: 1
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/bcm7xxx/logs`

#### cavium_ptp

- **Boundary Functions**: 16
- **Shared Fields**: 10
- **Risky APIs**: 10
- **Taint Entries**: 0
- **API Classes**: memory(6), concurrency(1), bus(2)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/cavium_ptp/logs`

#### dummy

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: concurrency(13), refCount(2), memory(6), timer(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/net_ethernet/dummy/logs`

#### dummy

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: concurrency(13), refCount(2), memory(6), timer(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/dummy/logs`

#### dwmac-generic

- **Boundary Functions**: 3
- **Shared Fields**: 4
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/dwmac-generic/logs`

#### dwmac-intel

- **Boundary Functions**: 26
- **Shared Fields**: 8
- **Risky APIs**: 19
- **Taint Entries**: 0
- **API Classes**: concurrency(6), memory(6), bus(4)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/dwmac-intel/logs`

#### encx24j600-regmap

- **Boundary Functions**: 4
- **Shared Fields**: 2
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/encx24j600-regmap/logs`

#### igb

- **Boundary Functions**: 136
- **Shared Fields**: 217
- **Risky APIs**: 366
- **Taint Entries**: N/A
- **API Classes**: concurrency(54), bus(184), memory(44), timer(44), refCount(9)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/igb/logs`

#### ixgbe

- **Boundary Functions**: 154
- **Shared Fields**: 222
- **Risky APIs**: 389
- **Taint Entries**: N/A
- **API Classes**: memory(48), concurrency(78), timer(75), refCount(13), bus(121)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/net_ethernet/ixgbe/logs`

#### ixgbe

- **Boundary Functions**: 154
- **Shared Fields**: 222
- **Risky APIs**: 389
- **Taint Entries**: N/A
- **API Classes**: memory(48), concurrency(78), timer(75), refCount(13), bus(121)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/ixgbe/logs`

#### jme

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 75
- **Taint Entries**: N/A
- **API Classes**: timer(6), memory(11), bus(46), concurrency(10)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/jme/logs`

#### ks8851_common

- **Boundary Functions**: 24
- **Shared Fields**: 32
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(8), bus(6), refCount(1), timer(3)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/ks8851_common/logs`

#### ks8851_par

- **Boundary Functions**: 12
- **Shared Fields**: 5
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/ks8851_par/logs`

#### ks8851_spi

- **Boundary Functions**: 9
- **Shared Fields**: 12
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/ks8851_spi/logs`

#### mdio

- **Boundary Functions**: 1
- **Shared Fields**: 19
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mdio/logs`

#### mdio-bcm-unimac

- **Boundary Functions**: 10
- **Shared Fields**: 9
- **Risky APIs**: 4
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(2)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mdio-bcm-unimac/logs`

#### mdio-cavium

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mdio-cavium/logs`

#### mdio-thunder

- **Boundary Functions**: 10
- **Shared Fields**: 4
- **Risky APIs**: 3
- **Taint Entries**: 0
- **API Classes**: memory(2), bus(1)
- **Issues**: Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mdio-thunder/logs`

#### micrel

- **Boundary Functions**: 15
- **Shared Fields**: 16
- **Risky APIs**: 7
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(2)
- **Issues**: Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/micrel/logs`

#### mii

- **Boundary Functions**: 5
- **Shared Fields**: 18
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: timer(1)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mii/logs`

#### mlx4_en

- **Boundary Functions**: 100
- **Shared Fields**: 186
- **Risky APIs**: 214
- **Taint Entries**: N/A
- **API Classes**: concurrency(74), timer(64), memory(48), refCount(15)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mlx4_en/logs`

#### mvmdio

- **Boundary Functions**: 19
- **Shared Fields**: 9
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(3)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/mvmdio/logs`

#### ne2k-pci

- **Boundary Functions**: 19
- **Shared Fields**: 12
- **Risky APIs**: 24
- **Taint Entries**: 0
- **API Classes**: memory(7), concurrency(6), bus(7), refCount(1)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/ne2k-pci/logs`

#### nicpf

- **Boundary Functions**: 18
- **Shared Fields**: 3
- **Risky APIs**: 17
- **Taint Entries**: 0
- **API Classes**: bus(9), memory(4), concurrency(4)
- **Issues**: Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/nicpf/logs`

#### nicvf

- **Boundary Functions**: 82
- **Shared Fields**: 111
- **Risky APIs**: 114
- **Taint Entries**: N/A
- **API Classes**: concurrency(38), memory(19), refCount(6), timer(7), bus(26)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/nicvf/logs`

#### nps_enet

- **Boundary Functions**: 23
- **Shared Fields**: 20
- **Risky APIs**: 28
- **Taint Entries**: N/A
- **API Classes**: timer(1), memory(10), refCount(3), concurrency(8), bus(4)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/nps_enet/logs`

#### pcs-altera-tse

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/pcs-altera-tse/logs`

#### pcs_xpcs

- **Boundary Functions**: 4
- **Shared Fields**: 0
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/pcs_xpcs/logs`

#### qede

- **Boundary Functions**: 92
- **Shared Fields**: 199
- **Risky APIs**: 117
- **Taint Entries**: N/A
- **API Classes**: memory(26), refCount(8), concurrency(46), timer(9), bus(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/qede/logs`

#### r6040

- **Boundary Functions**: 44
- **Shared Fields**: 31
- **Risky APIs**: 25
- **Taint Entries**: 0
- **API Classes**: memory(8), refCount(2), timer(1), concurrency(6), bus(6)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/r6040/logs`

#### realtek

- **Boundary Functions**: 4
- **Shared Fields**: 2
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/realtek/logs`

#### s2io

- **Boundary Functions**: 64
- **Shared Fields**: 73
- **Risky APIs**: 83
- **Taint Entries**: 0
- **API Classes**: timer(9), memory(12), refCount(7), concurrency(9), bus(44)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/s2io/logs`

#### samsung-sxgbe

- **Boundary Functions**: 51
- **Shared Fields**: 57
- **Risky APIs**: 38
- **Taint Entries**: N/A
- **API Classes**: memory(12), concurrency(12), refCount(3), timer(8)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/samsung-sxgbe/logs`

#### sfc

- **Boundary Functions**: 150
- **Shared Fields**: 223
- **Risky APIs**: 631
- **Taint Entries**: N/A
- **API Classes**: memory(64), concurrency(72), refCount(40), bus(253), timer(40)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/net_ethernet/sfc/logs`

#### sfc

- **Boundary Functions**: 150
- **Shared Fields**: 223
- **Risky APIs**: 631
- **Taint Entries**: N/A
- **API Classes**: memory(64), concurrency(72), refCount(40), bus(253), timer(40)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/sfc/logs`

#### sis190

- **Boundary Functions**: 57
- **Shared Fields**: 34
- **Risky APIs**: 73
- **Taint Entries**: 0
- **API Classes**: timer(23), refCount(7), concurrency(17), memory(11), bus(13)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/sis190/logs`

#### smsc

- **Boundary Functions**: 4
- **Shared Fields**: 2
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2)
- **Issues**: Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/smsc/logs`

#### smsc911x

- **Boundary Functions**: 49
- **Shared Fields**: 39
- **Risky APIs**: 41
- **Taint Entries**: N/A
- **API Classes**: memory(12), timer(7), concurrency(10), bus(6), refCount(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/smsc911x/logs`

#### stmmac-pci

- **Boundary Functions**: 14
- **Shared Fields**: 5
- **Risky APIs**: 13
- **Taint Entries**: 0
- **API Classes**: memory(5), bus(6), concurrency(2)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/stmmac-pci/logs`

#### stmmac-platform

- **Boundary Functions**: 15
- **Shared Fields**: 7
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(4), refCount(1)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/stmmac-platform/logs`

#### sundance

- **Boundary Functions**: 45
- **Shared Fields**: 36
- **Risky APIs**: 38
- **Taint Entries**: 0
- **API Classes**: timer(8), memory(8), refCount(2), concurrency(6), ioPorts(6), bus(5)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/sundance/logs`

#### sungem_phy

- **Boundary Functions**: 2
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/sungem_phy/logs`

#### sunhme

- **Boundary Functions**: 41
- **Shared Fields**: 47
- **Risky APIs**: 22
- **Taint Entries**: N/A
- **API Classes**: memory(7), bus(4), timer(4), concurrency(4), refCount(1)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/sunhme/logs`

#### thunder_bgx

- **Boundary Functions**: 27
- **Shared Fields**: 12
- **Risky APIs**: 28
- **Taint Entries**: 0
- **API Classes**: bus(3), memory(9), concurrency(6), refCount(6), timer(2)
- **Issues**: Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/thunder_bgx/logs`

#### thunder_xcv

- **Boundary Functions**: 11
- **Shared Fields**: 1
- **Risky APIs**: 5
- **Taint Entries**: 0
- **API Classes**: bus(2), memory(3)
- **Issues**: Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/thunder_xcv/logs`

#### vcan

- **Boundary Functions**: 5
- **Shared Fields**: 20
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: refCount(2), concurrency(4), memory(3)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/vcan/logs`

#### via-velocity

- **Boundary Functions**: 55
- **Shared Fields**: 62
- **Risky APIs**: 55
- **Taint Entries**: 0
- **API Classes**: memory(12), concurrency(14), bus(15), timer(9), refCount(2)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/via-velocity/logs`

#### w5100

- **Boundary Functions**: 35
- **Shared Fields**: 29
- **Risky APIs**: 42
- **Taint Entries**: N/A
- **API Classes**: memory(13), concurrency(14), timer(8), bus(4)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/w5100/logs`

#### w5100-spi

- **Boundary Functions**: 1
- **Shared Fields**: 3
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/w5100-spi/logs`

#### w5300

- **Boundary Functions**: 30
- **Shared Fields**: 25
- **Risky APIs**: 28
- **Taint Entries**: N/A
- **API Classes**: memory(10), timer(7), concurrency(8), bus(2)
- **Issues**: Missing BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/w5300/logs`

#### yellowfin

- **Boundary Functions**: 38
- **Shared Fields**: 28
- **Risky APIs**: 32
- **Taint Entries**: 0
- **API Classes**: memory(7), refCount(2), ioPorts(4), concurrency(6), timer(6), bus(5)
- **Issues**: Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/yellowfin/logs`

### SOUND Subsystem

#### snd-soc-rl6231

- **Boundary Functions**: 4
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/sound/snd-soc-rl6231/logs`

#### snd-soc-rt5640

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 36
- **Taint Entries**: N/A
- **API Classes**: concurrency(22), memory(10)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-rt5640/logs`

#### snd-soc-rt5640

- **Boundary Functions**: 41
- **Shared Fields**: 27
- **Risky APIs**: 58
- **Taint Entries**: N/A
- **API Classes**: memory(14), concurrency(32), timer(1), bus(2), refCount(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/sound/snd-soc-rt5640/logs`

#### snd-soc-sst-acpi

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(3), refCount(3), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-acpi/logs`

#### snd-soc-sst-firmware

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 7
- **Taint Entries**: N/A
- **API Classes**: memory(4), bus(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-firmware/logs`

#### snd-soc-sst-haswell

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-haswell/logs`

#### snd-soc-sst-haswell-pcm

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 91
- **Taint Entries**: N/A
- **API Classes**: memory(22), refCount(3), concurrency(46), timer(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-haswell-pcm/logs`

#### snd-soc-sst-ipc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-ipc/logs`

#### snd-soc-sst-match

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-match/logs`

### UNKNOWN Subsystem

#### e752x_edac

- **Boundary Functions**: 20
- **Shared Fields**: 23
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: bus(18), memory(3), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/e752x_edac/logs`

#### i3000_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i3000_edac/logs`

#### i3200_edac

- **Boundary Functions**: 18
- **Shared Fields**: 19
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i3200_edac/logs`

#### i5000_edac

- **Boundary Functions**: 19
- **Shared Fields**: 25
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(6), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i5000_edac/logs`

#### i5100_edac

- **Boundary Functions**: 24
- **Shared Fields**: 30
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(2), timer(2), bus(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i5100_edac/logs`

#### i5400_edac

- **Boundary Functions**: 19
- **Shared Fields**: 26
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i5400_edac/logs`

#### i7300_edac

- **Boundary Functions**: 19
- **Shared Fields**: 24
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i7300_edac/logs`

#### i7core_edac

- **Boundary Functions**: 26
- **Shared Fields**: 35
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: bus(6), memory(4), concurrency(8), refCount(10)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i7core_edac/logs`

#### i82975x_edac

- **Boundary Functions**: 18
- **Shared Fields**: 23
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/i82975x_edac/logs`

#### ie31200_edac

- **Boundary Functions**: 17
- **Shared Fields**: 20
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(3), bus(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/ie31200_edac/logs`

#### sb_edac

- **Boundary Functions**: 17
- **Shared Fields**: 39
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(1), bus(3), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/sb_edac/logs`

#### skx_edac

- **Boundary Functions**: 25
- **Shared Fields**: 37
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), bus(3), memory(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/skx_edac/logs`

#### x38_edac

- **Boundary Functions**: 18
- **Shared Fields**: 18
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(3), bus(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLogs/x38_edac/logs`

### USB Subsystem

#### amd5536udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 19
- **Taint Entries**: N/A
- **API Classes**: timer(2), memory(5), bus(11)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/amd5536udc/logs`

#### amd5536udc_pci

- **Boundary Functions**: 15
- **Shared Fields**: 3
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(2), bus(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/amd5536udc_pci/logs`

#### bdc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/bdc/logs`

#### bdc_pci

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 23
- **Taint Entries**: N/A
- **API Classes**: memory(5), bus(9), concurrency(4), refCount(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/bdc_pci/logs`

#### ci_hdrc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 39
- **Taint Entries**: N/A
- **API Classes**: concurrency(14), memory(14), refCount(7), timer(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/ci_hdrc/logs`

#### ci_hdrc_imx

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/ci_hdrc_imx/logs`

#### ci_hdrc_msm

- **Boundary Functions**: 11
- **Shared Fields**: 8
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/ci_hdrc_msm/logs`

#### ci_hdrc_tegra

- **Boundary Functions**: 10
- **Shared Fields**: 9
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: memory(2), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/ci_hdrc_tegra/logs`

#### ci_hdrc_usb2

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/ci_hdrc_usb2/logs`

#### ci_hdrc_usb2

- **Boundary Functions**: 7
- **Shared Fields**: 7
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/ci_hdrc_usb2/logs`

#### dwc2

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(6), timer(1), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/dwc2/logs`

#### dwc2

- **Boundary Functions**: 44
- **Shared Fields**: 21
- **Risky APIs**: 19
- **Taint Entries**: N/A
- **API Classes**: concurrency(10), memory(7), dma(1), timer(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/dwc2/logs`

#### dwc3

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 15
- **Taint Entries**: N/A
- **API Classes**: memory(7), concurrency(4), bus(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/dwc3/logs`

#### dwc3

- **Boundary Functions**: 49
- **Shared Fields**: 28
- **Risky APIs**: 44
- **Taint Entries**: N/A
- **API Classes**: concurrency(22), memory(14), timer(5), bus(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/dwc3/logs`

#### dwc3-haps

- **Boundary Functions**: 12
- **Shared Fields**: 4
- **Risky APIs**: 21
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), refCount(8), memory(6), bus(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/dwc3-haps/logs`

#### dwc3-of-simple

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(2), refCount(2), concurrency(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/dwc3-of-simple/logs`

#### dwc3-of-simple

- **Boundary Functions**: 8
- **Shared Fields**: 4
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/dwc3-of-simple/logs`

#### dwc3-pci

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: bus(5), memory(4), concurrency(4), refCount(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/dwc3-pci/logs`

#### fotg210-udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/fotg210-udc/logs`

#### fotg210-udc

- **Boundary Functions**: 16
- **Shared Fields**: 10
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(6)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/fotg210-udc/logs`

#### g_audio

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: 0
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_audio/logs`

#### g_ether

- **Boundary Functions**: 2
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: 0
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_ether/logs`

#### g_ffs

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_ffs/logs`

#### g_hid

- **Boundary Functions**: 5
- **Shared Fields**: 4
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_hid/logs`

#### g_mass_storage

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: 0
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_mass_storage/logs`

#### g_midi

- **Boundary Functions**: 1
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_midi/logs`

#### g_ncm

- **Boundary Functions**: 2
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: 0
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_ncm/logs`

#### g_printer

- **Boundary Functions**: 0
- **Shared Fields**: 0
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_printer/logs`

#### g_zero

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: timer(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_zero/logs`

#### g_zero

- **Boundary Functions**: 7
- **Shared Fields**: 0
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: timer(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/g_zero/logs`

#### gadgetfs

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/gadgetfs/logs`

#### gadgetfs

- **Boundary Functions**: 47
- **Shared Fields**: 45
- **Risky APIs**: 10
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/gadgetfs/logs`

#### goku_udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(7), memory(5)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/goku_udc/logs`

#### goku_udc

- **Boundary Functions**: 18
- **Shared Fields**: 7
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(2), bus(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/goku_udc/logs`

#### gr_udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/gr_udc/logs`

#### gr_udc

- **Boundary Functions**: 15
- **Shared Fields**: 6
- **Risky APIs**: 5
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/gr_udc/logs`

#### isp1760

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: bus(8), memory(6), timer(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/isp1760/logs`

#### isp1760

- **Boundary Functions**: 39
- **Shared Fields**: 12
- **Risky APIs**: 32
- **Taint Entries**: N/A
- **API Classes**: concurrency(4), memory(10), bus(11), timer(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/isp1760/logs`

#### libcomposite

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: refCount(4), memory(6), concurrency(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/libcomposite/logs`

#### libcomposite

- **Boundary Functions**: 28
- **Shared Fields**: 12
- **Risky APIs**: 15
- **Taint Entries**: N/A
- **API Classes**: memory(7), concurrency(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/libcomposite/logs`

#### m66592-udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: timer(1), memory(4), concurrency(4), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/m66592-udc/logs`

#### m66592-udc

- **Boundary Functions**: 26
- **Shared Fields**: 9
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(8), timer(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/m66592-udc/logs`

#### musb_hdrc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: timer(4), concurrency(6), memory(6), refCount(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/musb_hdrc/logs`

#### mv_u3d_core

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 11
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(4), refCount(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/mv_u3d_core/logs`

#### mv_udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(6), refCount(3), timer(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/mv_udc/logs`

#### mv_udc

- **Boundary Functions**: 23
- **Shared Fields**: 13
- **Risky APIs**: 17
- **Taint Entries**: N/A
- **API Classes**: memory(6), concurrency(4), refCount(4), timer(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/mv_udc/logs`

#### net2272

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: bus(7), memory(5)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/net2272/logs`

#### net2272

- **Boundary Functions**: 28
- **Shared Fields**: 12
- **Risky APIs**: 12
- **Taint Entries**: N/A
- **API Classes**: memory(6), bus(3), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/net2272/logs`

#### net2280

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 22
- **Taint Entries**: N/A
- **API Classes**: bus(15), memory(6)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/net2280/logs`

#### net2280

- **Boundary Functions**: 29
- **Shared Fields**: 9
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: bus(7), memory(8), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/net2280/logs`

#### pch_udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 15
- **Taint Entries**: N/A
- **API Classes**: memory(4), bus(11)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/pch_udc/logs`

#### pxa27x_udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 4
- **Taint Entries**: N/A
- **API Classes**: concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/pxa27x_udc/logs`

#### pxa27x_udc

- **Boundary Functions**: 17
- **Shared Fields**: 5
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/pxa27x_udc/logs`

#### r8a66597-udc

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: timer(1), memory(2)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/r8a66597-udc/logs`

#### r8a66597-udc

- **Boundary Functions**: 20
- **Shared Fields**: 9
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: timer(1), memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/r8a66597-udc/logs`

#### roles

- **Boundary Functions**: 16
- **Shared Fields**: 10
- **Risky APIs**: 23
- **Taint Entries**: N/A
- **API Classes**: concurrency(6), memory(5), refCount(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/roles/logs`

#### snps_udc_core

- **Boundary Functions**: 18
- **Shared Fields**: 6
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: timer(2), memory(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/snps_udc_core/logs`

#### u_audio

- **Boundary Functions**: 20
- **Shared Fields**: 37
- **Risky APIs**: 38
- **Taint Entries**: N/A
- **API Classes**: concurrency(16), memory(8), refCount(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/u_audio/logs`

#### u_ether

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 23
- **Taint Entries**: N/A
- **API Classes**: memory(7), refCount(5), timer(3), concurrency(7)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/u_ether/logs`

#### u_ether

- **Boundary Functions**: 29
- **Shared Fields**: 31
- **Risky APIs**: 21
- **Taint Entries**: N/A
- **API Classes**: memory(6), refCount(5), concurrency(7), timer(3)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/u_ether/logs`

#### udc-xilinx

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/udc-xilinx/logs`

#### udc-xilinx

- **Boundary Functions**: 23
- **Shared Fields**: 9
- **Risky APIs**: 6
- **Taint Entries**: N/A
- **API Classes**: memory(4), concurrency(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/udc-xilinx/logs`

#### ulpi

- **Boundary Functions**: 24
- **Shared Fields**: 13
- **Risky APIs**: 51
- **Taint Entries**: N/A
- **API Classes**: memory(10), refCount(19), concurrency(14)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/ulpi/logs`

#### usb_f_ecm

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: memory(2), refCount(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_ecm/logs`

#### usb_f_ecm

- **Boundary Functions**: 8
- **Shared Fields**: 0
- **Risky APIs**: 4
- **Taint Entries**: N/A
- **API Classes**: memory(3), refCount(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_ecm/logs`

#### usb_f_ecm_subset

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 3
- **Taint Entries**: N/A
- **API Classes**: memory(2), refCount(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_ecm_subset/logs`

#### usb_f_ecm_subset

- **Boundary Functions**: 5
- **Shared Fields**: 0
- **Risky APIs**: 4
- **Taint Entries**: N/A
- **API Classes**: memory(3), refCount(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_ecm_subset/logs`

#### usb_f_fs

- **Boundary Functions**: 68
- **Shared Fields**: 58
- **Risky APIs**: 37
- **Taint Entries**: N/A
- **API Classes**: memory(14), concurrency(14), timer(2), refCount(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/usb/usb_f_fs/logs`

#### usb_f_fs

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 14
- **Taint Entries**: N/A
- **API Classes**: refCount(4), memory(5), concurrency(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_fs/logs`

#### usb_f_fs

- **Boundary Functions**: 68
- **Shared Fields**: 58
- **Risky APIs**: 37
- **Taint Entries**: N/A
- **API Classes**: memory(14), concurrency(14), timer(2), refCount(4)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_fs/logs`

#### usb_f_hid

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: memory(7), refCount(8), concurrency(8)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_hid/logs`

#### usb_f_hid

- **Boundary Functions**: 27
- **Shared Fields**: 10
- **Risky APIs**: 29
- **Taint Entries**: N/A
- **API Classes**: memory(10), concurrency(8), refCount(7)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_hid/logs`

#### usb_f_mass_storage

- **Boundary Functions**: 48
- **Shared Fields**: 32
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(4), refCount(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/representative_drivers/usb/usb_f_mass_storage/logs`

#### usb_f_mass_storage

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 13
- **Taint Entries**: N/A
- **API Classes**: memory(3), concurrency(4), refCount(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_mass_storage/logs`

#### usb_f_mass_storage

- **Boundary Functions**: 48
- **Shared Fields**: 32
- **Risky APIs**: 16
- **Taint Entries**: N/A
- **API Classes**: memory(5), concurrency(4), refCount(5)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_mass_storage/logs`

#### usb_f_midi

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 23
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(5), refCount(5)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_midi/logs`

#### usb_f_ncm

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 4
- **Taint Entries**: N/A
- **API Classes**: memory(3), refCount(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_ncm/logs`

#### usb_f_ncm

- **Boundary Functions**: 19
- **Shared Fields**: 10
- **Risky APIs**: 5
- **Taint Entries**: N/A
- **API Classes**: memory(4), refCount(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_ncm/logs`

#### usb_f_printer

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 26
- **Taint Entries**: N/A
- **API Classes**: refCount(8), concurrency(8), memory(7)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_printer/logs`

#### usb_f_printer

- **Boundary Functions**: 34
- **Shared Fields**: 11
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(9), refCount(8)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_printer/logs`

#### usb_f_rndis

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 8
- **Taint Entries**: N/A
- **API Classes**: timer(1), memory(6), refCount(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_rndis/logs`

#### usb_f_rndis

- **Boundary Functions**: 23
- **Shared Fields**: 13
- **Risky APIs**: 9
- **Taint Entries**: N/A
- **API Classes**: memory(6), timer(1), refCount(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_rndis/logs`

#### usb_f_ss_lb

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_ss_lb/logs`

#### usb_f_ss_lb

- **Boundary Functions**: 4
- **Shared Fields**: 0
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_ss_lb/logs`

#### usb_f_uac2

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 30
- **Taint Entries**: N/A
- **API Classes**: concurrency(10), refCount(8), memory(7)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usb_f_uac2/logs`

#### usb_f_uac2

- **Boundary Functions**: 5
- **Shared Fields**: 0
- **Risky APIs**: 2
- **Taint Entries**: N/A
- **API Classes**: memory(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usb_f_uac2/logs`

#### usbmisc_imx

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 1
- **Taint Entries**: N/A
- **API Classes**: memory(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/usbmisc_imx/logs`

#### usbmisc_imx

- **Boundary Functions**: 8
- **Shared Fields**: 2
- **Risky APIs**: N/A
- **Taint Entries**: N/A
- **Issues**: Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/usbmisc_imx/logs`

#### xhci-hcd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: timer(4), memory(3), bus(7)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/xhci-hcd/logs`

#### xhci-pci

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 46
- **Taint Entries**: N/A
- **API Classes**: bus(25), concurrency(10), refCount(3), timer(2), memory(4)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/xhci-pci/logs`

#### xhci-pci

- **Boundary Functions**: 22
- **Shared Fields**: 19
- **Risky APIs**: 50
- **Taint Entries**: N/A
- **API Classes**: bus(26), concurrency(10), memory(7), timer(2)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/xhci-pci/logs`

#### xhci-plat-hcd

- **Boundary Functions**: N/A
- **Shared Fields**: N/A
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: concurrency(8), memory(3), timer(1)
- **Issues**: Missing RiskyDataStat.json, Missing BoundaryParamTaint.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/xhci-plat-hcd/logs`

#### xhci-plat-hcd

- **Boundary Functions**: 15
- **Shared Fields**: 18
- **Risky APIs**: 18
- **Taint Entries**: N/A
- **API Classes**: concurrency(10), memory(2), timer(1)
- **Issues**: Failed to load BoundaryParamTaint.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
- **Analysis Path**: `/home/yzh89/Documents/SoK_experiment/bc-files-12/usb/xhci-plat-hcd/logs`


## Failed Analyses

The following 24 drivers had incomplete or failed analyses:

- **.git** (unknown): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/.git/logs`

- **.git** (unknown): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/.git/logs`

- **hwmon-vid** (hwmon): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/hwmon/hwmon-vid/logs`

- **snd-soc-rl6231** (sound): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-rl6231/logs`

- **snd-soc-sst-dsp** (sound): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/sound/snd-soc-sst-dsp/logs`

- **ci_hdrc_msm** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/ci_hdrc_msm/logs`

- **ci_hdrc_zevio** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/ci_hdrc_zevio/logs`

- **g_audio** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_audio/logs`

- **g_ether** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_ether/logs`

- **g_ffs** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_ffs/logs`

- **g_hid** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_hid/logs`

- **g_mass_storage** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_mass_storage/logs`

- **g_midi** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_midi/logs`

- **g_ncm** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_ncm/logs`

- **g_printer** (usb): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Missing BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Missing UnclassifiedFields.json, Missing PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/TaintLog/usb/g_printer/logs`

- **rbd** (block): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/block/rbd/logs`

- **8139too** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/8139too/logs`

- **atl1** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/atl1/logs`

- **atl1c** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/atl1c/logs`

- **atl1e** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/atl1e/logs`

- **atl2** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/atl2/logs`

- **b44** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/b44/logs`

- **bcmsysport** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/bcmsysport/logs`

- **be2net** (net_ethernet): Missing RiskyDataStat.json, Missing RiskyBoundaryAPI.json, Failed to load BoundaryParamTaint.json, Missing BoundaryAPICounts.json, Failed to load UnclassifiedFields.json, Failed to load PerStructTaint.json
  - Path: `/home/yzh89/Documents/SoK_experiment/bc-files-12/net_ethernet/be2net/logs`


## Data Integrity Notes

- **Analysis Method**: Data extracted from existing JSON analysis results only
- **No Simulation**: All statistics represent actual analysis output
- **File Coverage**: Attempted to read RiskyDataStat.json, RiskyBoundaryAPI.json, BoundaryParamTaint.json, and other analysis files
- **Error Handling**: Failed file reads and parsing errors are documented above

## Raw Data Summary

Total analysis directories found: 474
- Successful analyses: 450
- Failed/incomplete analyses: 24

Subsystem distribution:
- arch_x86: 2 drivers
- block: 27 drivers
- edac: 41 drivers
- foobar: 1 drivers
- gpu: 2 drivers
- hwmon: 200 drivers
- md: 6 drivers
- net_ethernet: 66 drivers
- sound: 11 drivers
- unknown: 15 drivers
- usb: 103 drivers
