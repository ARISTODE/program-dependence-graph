; ModuleID = 'bzip2.c'
source_filename = "bzip2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.zzzz = type { i8*, %struct.zzzz* }
%struct.UInt64 = type { [8 x i8] }
%struct.utimbuf = type { i64, i64 }

@.str = private unnamed_addr constant [5 x i8] c".bz2\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c".bz\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c".tbz2\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c".tbz\00", align 1
@zSuffix = dso_local global [4 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0)], align 16, !dbg !0
@.str.4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.5 = private unnamed_addr constant [5 x i8] c".tar\00", align 1
@unzSuffix = dso_local global [4 x i8*] [i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0)], align 16, !dbg !45
@outputHandleJustInCase = common dso_local global %struct._IO_FILE* null, align 8, !dbg !95
@smallMode = common dso_local global i8 0, align 1, !dbg !56
@keepInputFiles = common dso_local global i8 0, align 1, !dbg !54
@forceOverwrite = common dso_local global i8 0, align 1, !dbg !60
@noisy = common dso_local global i8 0, align 1, !dbg !66
@verbosity = common dso_local global i32 0, align 4, !dbg !52
@blockSize100k = common dso_local global i32 0, align 4, !dbg !72
@testFailsExist = common dso_local global i8 0, align 1, !dbg !62
@unzFailsExist = common dso_local global i8 0, align 1, !dbg !64
@numFileNames = common dso_local global i32 0, align 4, !dbg !68
@numFilesProcessed = common dso_local global i32 0, align 4, !dbg !70
@workFactor = common dso_local global i32 0, align 4, !dbg !153
@deleteOutputOnInterrupt = common dso_local global i8 0, align 1, !dbg !58
@exitValue = common dso_local global i32 0, align 4, !dbg !74
@inName = common dso_local global [1034 x i8] zeroinitializer, align 16, !dbg !82
@.str.6 = private unnamed_addr constant [7 x i8] c"(none)\00", align 1
@outName = common dso_local global [1034 x i8] zeroinitializer, align 16, !dbg !87
@progNameReally = common dso_local global [1034 x i8] zeroinitializer, align 16, !dbg !93
@progName = common dso_local global i8* null, align 8, !dbg !91
@.str.7 = private unnamed_addr constant [6 x i8] c"BZIP2\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"BZIP\00", align 1
@longestFileName = common dso_local global i32 0, align 4, !dbg !80
@.str.9 = private unnamed_addr constant [3 x i8] c"--\00", align 1
@srcMode = common dso_local global i32 0, align 4, !dbg !78
@opMode = common dso_local global i32 0, align 4, !dbg !76
@.str.10 = private unnamed_addr constant [6 x i8] c"unzip\00", align 1
@.str.11 = private unnamed_addr constant [6 x i8] c"UNZIP\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"z2cat\00", align 1
@.str.13 = private unnamed_addr constant [6 x i8] c"Z2CAT\00", align 1
@.str.14 = private unnamed_addr constant [5 x i8] c"zcat\00", align 1
@.str.15 = private unnamed_addr constant [5 x i8] c"ZCAT\00", align 1
@stderr = external dso_local global %struct._IO_FILE*, align 8
@.str.16 = private unnamed_addr constant [19 x i8] c"%s: Bad flag `%s'\0A\00", align 1
@.str.17 = private unnamed_addr constant [9 x i8] c"--stdout\00", align 1
@.str.18 = private unnamed_addr constant [13 x i8] c"--decompress\00", align 1
@.str.19 = private unnamed_addr constant [11 x i8] c"--compress\00", align 1
@.str.20 = private unnamed_addr constant [8 x i8] c"--force\00", align 1
@.str.21 = private unnamed_addr constant [7 x i8] c"--test\00", align 1
@.str.22 = private unnamed_addr constant [7 x i8] c"--keep\00", align 1
@.str.23 = private unnamed_addr constant [8 x i8] c"--small\00", align 1
@.str.24 = private unnamed_addr constant [8 x i8] c"--quiet\00", align 1
@.str.25 = private unnamed_addr constant [10 x i8] c"--version\00", align 1
@.str.26 = private unnamed_addr constant [10 x i8] c"--license\00", align 1
@.str.27 = private unnamed_addr constant [14 x i8] c"--exponential\00", align 1
@.str.28 = private unnamed_addr constant [18 x i8] c"--repetitive-best\00", align 1
@.str.29 = private unnamed_addr constant [18 x i8] c"--repetitive-fast\00", align 1
@.str.30 = private unnamed_addr constant [7 x i8] c"--fast\00", align 1
@.str.31 = private unnamed_addr constant [7 x i8] c"--best\00", align 1
@.str.32 = private unnamed_addr constant [10 x i8] c"--verbose\00", align 1
@.str.33 = private unnamed_addr constant [7 x i8] c"--help\00", align 1
@.str.34 = private unnamed_addr constant [40 x i8] c"%s: -c and -t cannot be used together.\0A\00", align 1
@.str.35 = private unnamed_addr constant [113 x i8] c"\0AYou can use the `bzip2recover' program to attempt to recover\0Adata from undamaged sections of corrupted files.\0A\0A\00", align 1
@tmpName = common dso_local global [1034 x i8] zeroinitializer, align 16, !dbg !89
@.str.36 = private unnamed_addr constant [869 x i8] c"\0A%s: Caught a SIGSEGV or SIGBUS whilst compressing.\0A\0A   Possible causes are (most likely first):\0A   (1) This computer has unreliable memory or cache hardware\0A       (a surprisingly common problem; try a different machine.)\0A   (2) A bug in the compiler used to create this executable\0A       (unlikely, if you didn't compile bzip2 yourself.)\0A   (3) A real bug in bzip2 -- I hope this should never be the case.\0A   The user's manual, Section 4.3, has more info on (1) and (2).\0A   \0A   If you suspect this is a bug in bzip2, or are unsure about (1)\0A   or (2), feel free to report it to me at: jseward@bzip.org.\0A   Section 4.3 of the user's manual describes the info a useful\0A   bug report should have.  If the manual is available on your\0A   system, please try and read it before mailing me.  If you don't\0A   have the manual or can't be bothered to read it, mail me anyway.\0A\0A\00", align 1
@.str.37 = private unnamed_addr constant [996 x i8] c"\0A%s: Caught a SIGSEGV or SIGBUS whilst decompressing.\0A\0A   Possible causes are (most likely first):\0A   (1) The compressed data is corrupted, and bzip2's usual checks\0A       failed to detect this.  Try bzip2 -tvv my_file.bz2.\0A   (2) This computer has unreliable memory or cache hardware\0A       (a surprisingly common problem; try a different machine.)\0A   (3) A bug in the compiler used to create this executable\0A       (unlikely, if you didn't compile bzip2 yourself.)\0A   (4) A real bug in bzip2 -- I hope this should never be the case.\0A   The user's manual, Section 4.3, has more info on (2) and (3).\0A   \0A   If you suspect this is a bug in bzip2, or are unsure about (2)\0A   or (3), feel free to report it to me at: jseward@bzip.org.\0A   Section 4.3 of the user's manual describes the info a useful\0A   bug report should have.  If the manual is available on your\0A   system, please try and read it before mailing me.  If you don't\0A   have the manual or can't be bothered to read it, mail me anyway.\0A\0A\00", align 1
@.str.38 = private unnamed_addr constant [36 x i8] c"\09Input file = %s, output file = %s\0A\00", align 1
@.str.39 = private unnamed_addr constant [44 x i8] c"%s: Deleting output file %s, if it exists.\0A\00", align 1
@.str.40 = private unnamed_addr constant [59 x i8] c"%s: WARNING: deletion of output file (apparently) failed.\0A\00", align 1
@.str.41 = private unnamed_addr constant [49 x i8] c"%s: WARNING: deletion of output file suppressed\0A\00", align 1
@.str.42 = private unnamed_addr constant [56 x i8] c"%s:    since input file no longer exists.  Output file\0A\00", align 1
@.str.43 = private unnamed_addr constant [32 x i8] c"%s:    `%s' may be incomplete.\0A\00", align 1
@.str.44 = private unnamed_addr constant [61 x i8] c"%s:    I suggest doing an integrity test (bzip2 -tv) of it.\0A\00", align 1
@.str.45 = private unnamed_addr constant [110 x i8] c"%s: WARNING: some files have not been processed:\0A%s:    %d specified on command line, %d not processed yet.\0A\0A\00", align 1
@.str.46 = private unnamed_addr constant [241 x i8] c"\0AIt is possible that the compressed file(s) have become corrupted.\0AYou can use the -tvv option to test integrity of such files.\0A\0AYou can use the `bzip2recover' program to attempt to recover\0Adata from undamaged sections of corrupted files.\0A\0A\00", align 1
@.str.47 = private unnamed_addr constant [120 x i8] c"bzip2: file name\0A`%s'\0Ais suspiciously (more than %d chars) long.\0ATry using a reasonable file name instead.  Sorry! :-)\0A\00", align 1
@.str.48 = private unnamed_addr constant [38 x i8] c"\0A%s: couldn't allocate enough memory\0A\00", align 1
@.str.49 = private unnamed_addr constant [531 x i8] c"bzip2, a block-sorting file compressor.  Version %s.\0A   \0A   Copyright (C) 1996-2010 by Julian Seward.\0A   \0A   This program is free software; you can redistribute it and/or modify\0A   it under the terms set out in the LICENSE file, which is included\0A   in the bzip2-1.0.6 source distribution.\0A   \0A   This program is distributed in the hope that it will be useful,\0A   but WITHOUT ANY WARRANTY; without even the implied warranty of\0A   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\0A   LICENSE file for more details.\0A   \0A\00", align 1
@.str.50 = private unnamed_addr constant [1230 x i8] c"bzip2, a block-sorting file compressor.  Version %s.\0A\0A   usage: %s [flags and input files in any order]\0A\0A   -h --help           print this message\0A   -d --decompress     force decompression\0A   -z --compress       force compression\0A   -k --keep           keep (don't delete) input files\0A   -f --force          overwrite existing output files\0A   -t --test           test compressed file integrity\0A   -c --stdout         output to standard out\0A   -q --quiet          suppress noncritical error messages\0A   -v --verbose        be verbose (a 2nd -v gives more)\0A   -L --license        display software version & license\0A   -V --version        display software version & license\0A   -s --small          use less memory (at most 2500k)\0A   -1 .. -9            set block size to 100k .. 900k\0A   --fast              alias for -1\0A   --best              alias for -9\0A\0A   If invoked as `bzip2', default action is to compress.\0A              as `bunzip2',  default action is to decompress.\0A              as `bzcat', default action is to decompress to stdout.\0A\0A   If no file names are given, bzip2 compresses or decompresses\0A   from standard input to standard output.  You can combine\0A   short flags, so `-v -4' means the same as -v4 or -4v, &c.\0A\0A\00", align 1
@.str.51 = private unnamed_addr constant [49 x i8] c"%s: %s is redundant in versions 0.9.5 and above\0A\00", align 1
@.str.52 = private unnamed_addr constant [45 x i8] c"\0A%s: Control-C or similar caught, quitting.\0A\00", align 1
@.str.53 = private unnamed_addr constant [21 x i8] c"compress: bad modes\0A\00", align 1
@.str.54 = private unnamed_addr constant [8 x i8] c"(stdin)\00", align 1
@.str.55 = private unnamed_addr constant [9 x i8] c"(stdout)\00", align 1
@.str.56 = private unnamed_addr constant [39 x i8] c"%s: There are no files matching `%s'.\0A\00", align 1
@.str.57 = private unnamed_addr constant [35 x i8] c"%s: Can't open input file %s: %s.\0A\00", align 1
@.str.58 = private unnamed_addr constant [42 x i8] c"%s: Input file %s already has %s suffix.\0A\00", align 1
@.str.59 = private unnamed_addr constant [35 x i8] c"%s: Input file %s is a directory.\0A\00", align 1
@.str.60 = private unnamed_addr constant [41 x i8] c"%s: Input file %s is not a normal file.\0A\00", align 1
@.str.61 = private unnamed_addr constant [36 x i8] c"%s: Output file %s already exists.\0A\00", align 1
@.str.62 = private unnamed_addr constant [40 x i8] c"%s: Input file %s has %d other link%s.\0A\00", align 1
@.str.63 = private unnamed_addr constant [2 x i8] c"s\00", align 1
@stdin = external dso_local global %struct._IO_FILE*, align 8
@stdout = external dso_local global %struct._IO_FILE*, align 8
@.str.64 = private unnamed_addr constant [50 x i8] c"%s: I won't write compressed data to a terminal.\0A\00", align 1
@.str.65 = private unnamed_addr constant [34 x i8] c"%s: For help, type: `%s --help'.\0A\00", align 1
@.str.66 = private unnamed_addr constant [3 x i8] c"rb\00", align 1
@.str.67 = private unnamed_addr constant [3 x i8] c"wb\00", align 1
@.str.68 = private unnamed_addr constant [38 x i8] c"%s: Can't create output file %s: %s.\0A\00", align 1
@.str.69 = private unnamed_addr constant [22 x i8] c"compress: bad srcMode\00", align 1
@.str.70 = private unnamed_addr constant [7 x i8] c"  %s: \00", align 1
@.str.71 = private unnamed_addr constant [109 x i8] c"\0A%s: PANIC -- internal consistency error:\0A\09%s\0A\09This is a BUG.  Please report it to me at:\0A\09jseward@bzip.org\0A\00", align 1
@fileMetaInfo = internal global %struct.stat zeroinitializer, align 8, !dbg !155
@.str.72 = private unnamed_addr constant [2 x i8] c" \00", align 1
@.str.73 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.74 = private unnamed_addr constant [22 x i8] c" no data compressed.\0A\00", align 1
@.str.75 = private unnamed_addr constant [57 x i8] c"%6.3f:1, %6.3f bits/byte, %5.2f%% saved, %s in, %s out.\0A\00", align 1
@.str.76 = private unnamed_addr constant [26 x i8] c"compress:unexpected error\00", align 1
@.str.77 = private unnamed_addr constant [236 x i8] c"bzip2: I'm not configured correctly for this platform!\0A\09I require Int32, Int16 and Char to have sizes\0A\09of 4, 2 and 1 bytes to run properly, and they don't.\0A\09Probably you can fix this by defining them correctly,\0A\09and recompiling.  Bye!\0A\00", align 1
@.str.78 = private unnamed_addr constant [10 x i8] c"sensitive\00", section "llvm.metadata"
@.str.79 = private unnamed_addr constant [8 x i8] c"bzip2.c\00", section "llvm.metadata"
@.str.80 = private unnamed_addr constant [19 x i8] c"compress size: %d\0A\00", align 1
@.str.81 = private unnamed_addr constant [65 x i8] c"\0A%s: I/O or other error, bailing out.  Possible reason follows.\0A\00", align 1
@.str.82 = private unnamed_addr constant [23 x i8] c"uncompress: bad modes\0A\00", align 1
@.str.83 = private unnamed_addr constant [5 x i8] c".out\00", align 1
@.str.84 = private unnamed_addr constant [50 x i8] c"%s: Can't guess original name for %s -- using %s\0A\00", align 1
@.str.85 = private unnamed_addr constant [51 x i8] c"%s: I won't read compressed data from a terminal.\0A\00", align 1
@.str.86 = private unnamed_addr constant [34 x i8] c"%s: Can't open input file %s:%s.\0A\00", align 1
@.str.87 = private unnamed_addr constant [24 x i8] c"uncompress: bad srcMode\00", align 1
@.str.88 = private unnamed_addr constant [6 x i8] c"done\0A\00", align 1
@.str.89 = private unnamed_addr constant [19 x i8] c"not a bzip2 file.\0A\00", align 1
@.str.90 = private unnamed_addr constant [29 x i8] c"%s: %s is not a bzip2 file.\0A\00", align 1
@.str.91 = private unnamed_addr constant [27 x i8] c"decompress:bzReadGetUnused\00", align 1
@.str.92 = private unnamed_addr constant [6 x i8] c"\0A    \00", align 1
@.str.93 = private unnamed_addr constant [45 x i8] c"\0A%s: %s: trailing garbage after EOF ignored\0A\00", align 1
@.str.94 = private unnamed_addr constant [28 x i8] c"decompress:unexpected error\00", align 1
@.str.95 = private unnamed_addr constant [47 x i8] c"\0A%s: Data integrity error when decompressing.\0A\00", align 1
@.str.96 = private unnamed_addr constant [95 x i8] c"\0A%s: Compressed file ends unexpectedly;\0A\09perhaps it is corrupted?  *Possible* reason follows.\0A\00", align 1
@.str.97 = private unnamed_addr constant [18 x i8] c"testf: bad modes\0A\00", align 1
@.str.98 = private unnamed_addr constant [30 x i8] c"%s: Can't open input %s: %s.\0A\00", align 1
@.str.99 = private unnamed_addr constant [19 x i8] c"testf: bad srcMode\00", align 1
@.str.100 = private unnamed_addr constant [4 x i8] c"ok\0A\00", align 1
@.str.101 = private unnamed_addr constant [21 x i8] c"test:bzReadGetUnused\00", align 1
@.str.102 = private unnamed_addr constant [9 x i8] c"%s: %s: \00", align 1
@.str.103 = private unnamed_addr constant [36 x i8] c"data integrity (CRC) error in data\0A\00", align 1
@.str.104 = private unnamed_addr constant [24 x i8] c"file ends unexpectedly\0A\00", align 1
@.str.105 = private unnamed_addr constant [46 x i8] c"bad magic number (file not created by bzip2)\0A\00", align 1
@.str.106 = private unnamed_addr constant [36 x i8] c"trailing garbage after EOF ignored\0A\00", align 1
@.str.107 = private unnamed_addr constant [22 x i8] c"test:unexpected error\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !197 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca %struct.zzzz*, align 8
  %10 = alloca %struct.zzzz*, align 8
  %11 = alloca i8, align 1
  %12 = alloca %struct.zzzz*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !203, metadata !DIExpression()), !dbg !204
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !205, metadata !DIExpression()), !dbg !206
  call void @llvm.dbg.declare(metadata i32* %6, metadata !207, metadata !DIExpression()), !dbg !208
  call void @llvm.dbg.declare(metadata i32* %7, metadata !209, metadata !DIExpression()), !dbg !210
  call void @llvm.dbg.declare(metadata i8** %8, metadata !211, metadata !DIExpression()), !dbg !212
  call void @llvm.dbg.declare(metadata %struct.zzzz** %9, metadata !213, metadata !DIExpression()), !dbg !214
  call void @llvm.dbg.declare(metadata %struct.zzzz** %10, metadata !215, metadata !DIExpression()), !dbg !216
  call void @llvm.dbg.declare(metadata i8* %11, metadata !217, metadata !DIExpression()), !dbg !218
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !219
  store i8 0, i8* @smallMode, align 1, !dbg !220
  store i8 0, i8* @keepInputFiles, align 1, !dbg !221
  store i8 0, i8* @forceOverwrite, align 1, !dbg !222
  store i8 1, i8* @noisy, align 1, !dbg !223
  store i32 0, i32* @verbosity, align 4, !dbg !224
  store i32 9, i32* @blockSize100k, align 4, !dbg !225
  store i8 0, i8* @testFailsExist, align 1, !dbg !226
  store i8 0, i8* @unzFailsExist, align 1, !dbg !227
  store i32 0, i32* @numFileNames, align 4, !dbg !228
  store i32 0, i32* @numFilesProcessed, align 4, !dbg !229
  store i32 30, i32* @workFactor, align 4, !dbg !230
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !231
  store i32 0, i32* @exitValue, align 4, !dbg !232
  store i32 0, i32* %7, align 4, !dbg !233
  store i32 0, i32* %6, align 4, !dbg !234
  %13 = call void (i32)* @signal(i32 11, void (i32)* @mySIGSEGVorSIGBUScatcher) #10, !dbg !235
  %14 = call void (i32)* @signal(i32 7, void (i32)* @mySIGSEGVorSIGBUScatcher) #10, !dbg !236
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)), !dbg !237
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)), !dbg !238
  %15 = load i8**, i8*** %5, align 8, !dbg !239
  %16 = getelementptr inbounds i8*, i8** %15, i64 0, !dbg !239
  %17 = load i8*, i8** %16, align 8, !dbg !239
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @progNameReally, i64 0, i64 0), i8* %17), !dbg !240
  store i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @progNameReally, i64 0, i64 0), i8** @progName, align 8, !dbg !241
  store i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @progNameReally, i64 0, i64 0), i8** %8, align 8, !dbg !242
  br label %18, !dbg !244

18:                                               ; preds = %32, %2
  %19 = load i8*, i8** %8, align 8, !dbg !245
  %20 = load i8, i8* %19, align 1, !dbg !247
  %21 = sext i8 %20 to i32, !dbg !247
  %22 = icmp ne i32 %21, 0, !dbg !248
  br i1 %22, label %23, label %35, !dbg !249

23:                                               ; preds = %18
  %24 = load i8*, i8** %8, align 8, !dbg !250
  %25 = load i8, i8* %24, align 1, !dbg !252
  %26 = sext i8 %25 to i32, !dbg !252
  %27 = icmp eq i32 %26, 47, !dbg !253
  br i1 %27, label %28, label %31, !dbg !254

28:                                               ; preds = %23
  %29 = load i8*, i8** %8, align 8, !dbg !255
  %30 = getelementptr inbounds i8, i8* %29, i64 1, !dbg !256
  store i8* %30, i8** @progName, align 8, !dbg !257
  br label %31, !dbg !258

31:                                               ; preds = %28, %23
  br label %32, !dbg !259

32:                                               ; preds = %31
  %33 = load i8*, i8** %8, align 8, !dbg !260
  %34 = getelementptr inbounds i8, i8* %33, i32 1, !dbg !260
  store i8* %34, i8** %8, align 8, !dbg !260
  br label %18, !dbg !261, !llvm.loop !262

35:                                               ; preds = %18
  store %struct.zzzz* null, %struct.zzzz** %9, align 8, !dbg !264
  call void @addFlagsFromEnvVar(%struct.zzzz** %9, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.7, i64 0, i64 0)), !dbg !265
  call void @addFlagsFromEnvVar(%struct.zzzz** %9, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i64 0, i64 0)), !dbg !266
  store i32 1, i32* %6, align 4, !dbg !267
  br label %36, !dbg !269

36:                                               ; preds = %49, %35
  %37 = load i32, i32* %6, align 4, !dbg !270
  %38 = load i32, i32* %4, align 4, !dbg !272
  %39 = sub nsw i32 %38, 1, !dbg !273
  %40 = icmp sle i32 %37, %39, !dbg !274
  br i1 %40, label %41, label %52, !dbg !275

41:                                               ; preds = %36
  %42 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !276
  %43 = load i8**, i8*** %5, align 8, !dbg !276
  %44 = load i32, i32* %6, align 4, !dbg !276
  %45 = sext i32 %44 to i64, !dbg !276
  %46 = getelementptr inbounds i8*, i8** %43, i64 %45, !dbg !276
  %47 = load i8*, i8** %46, align 8, !dbg !276
  %48 = call %struct.zzzz* @snocString(%struct.zzzz* %42, i8* %47), !dbg !276
  store %struct.zzzz* %48, %struct.zzzz** %9, align 8, !dbg !276
  br label %49, !dbg !276

49:                                               ; preds = %41
  %50 = load i32, i32* %6, align 4, !dbg !277
  %51 = add nsw i32 %50, 1, !dbg !277
  store i32 %51, i32* %6, align 4, !dbg !277
  br label %36, !dbg !278, !llvm.loop !279

52:                                               ; preds = %36
  store i32 7, i32* @longestFileName, align 4, !dbg !281
  store i32 0, i32* @numFileNames, align 4, !dbg !282
  store i8 1, i8* %11, align 1, !dbg !283
  %53 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !284
  store %struct.zzzz* %53, %struct.zzzz** %10, align 8, !dbg !286
  br label %54, !dbg !287

54:                                               ; preds = %94, %52
  %55 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !288
  %56 = icmp ne %struct.zzzz* %55, null, !dbg !290
  br i1 %56, label %57, label %98, !dbg !291

57:                                               ; preds = %54
  %58 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !292
  %59 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %58, i32 0, i32 0, !dbg !292
  %60 = load i8*, i8** %59, align 8, !dbg !292
  %61 = call i32 @strcmp(i8* %60, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0)) #11, !dbg !292
  %62 = icmp eq i32 %61, 0, !dbg !292
  br i1 %62, label %63, label %64, !dbg !295

63:                                               ; preds = %57
  store i8 0, i8* %11, align 1, !dbg !296
  br label %94, !dbg !298

64:                                               ; preds = %57
  %65 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !299
  %66 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %65, i32 0, i32 0, !dbg !301
  %67 = load i8*, i8** %66, align 8, !dbg !301
  %68 = getelementptr inbounds i8, i8* %67, i64 0, !dbg !299
  %69 = load i8, i8* %68, align 1, !dbg !299
  %70 = sext i8 %69 to i32, !dbg !299
  %71 = icmp eq i32 %70, 45, !dbg !302
  br i1 %71, label %72, label %77, !dbg !303

72:                                               ; preds = %64
  %73 = load i8, i8* %11, align 1, !dbg !304
  %74 = zext i8 %73 to i32, !dbg !304
  %75 = icmp ne i32 %74, 0, !dbg !304
  br i1 %75, label %76, label %77, !dbg !305

76:                                               ; preds = %72
  br label %94, !dbg !306

77:                                               ; preds = %72, %64
  %78 = load i32, i32* @numFileNames, align 4, !dbg !307
  %79 = add nsw i32 %78, 1, !dbg !307
  store i32 %79, i32* @numFileNames, align 4, !dbg !307
  %80 = load i32, i32* @longestFileName, align 4, !dbg !308
  %81 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !310
  %82 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %81, i32 0, i32 0, !dbg !311
  %83 = load i8*, i8** %82, align 8, !dbg !311
  %84 = call i64 @strlen(i8* %83) #11, !dbg !312
  %85 = trunc i64 %84 to i32, !dbg !313
  %86 = icmp slt i32 %80, %85, !dbg !314
  br i1 %86, label %87, label %93, !dbg !315

87:                                               ; preds = %77
  %88 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !316
  %89 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %88, i32 0, i32 0, !dbg !317
  %90 = load i8*, i8** %89, align 8, !dbg !317
  %91 = call i64 @strlen(i8* %90) #11, !dbg !318
  %92 = trunc i64 %91 to i32, !dbg !319
  store i32 %92, i32* @longestFileName, align 4, !dbg !320
  br label %93, !dbg !321

93:                                               ; preds = %87, %77
  br label %94, !dbg !322

94:                                               ; preds = %93, %76, %63
  %95 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !323
  %96 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %95, i32 0, i32 1, !dbg !324
  %97 = load %struct.zzzz*, %struct.zzzz** %96, align 8, !dbg !324
  store %struct.zzzz* %97, %struct.zzzz** %10, align 8, !dbg !325
  br label %54, !dbg !326, !llvm.loop !327

98:                                               ; preds = %54
  %99 = load i32, i32* @numFileNames, align 4, !dbg !329
  %100 = icmp eq i32 %99, 0, !dbg !331
  br i1 %100, label %101, label %102, !dbg !332

101:                                              ; preds = %98
  store i32 1, i32* @srcMode, align 4, !dbg !333
  br label %103, !dbg !334

102:                                              ; preds = %98
  store i32 3, i32* @srcMode, align 4, !dbg !335
  br label %103

103:                                              ; preds = %102, %101
  store i32 1, i32* @opMode, align 4, !dbg !336
  %104 = load i8*, i8** @progName, align 8, !dbg !337
  %105 = call i8* @strstr(i8* %104, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i64 0, i64 0)) #11, !dbg !339
  %106 = icmp ne i8* %105, null, !dbg !340
  br i1 %106, label %111, label %107, !dbg !341

107:                                              ; preds = %103
  %108 = load i8*, i8** @progName, align 8, !dbg !342
  %109 = call i8* @strstr(i8* %108, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.11, i64 0, i64 0)) #11, !dbg !343
  %110 = icmp ne i8* %109, null, !dbg !344
  br i1 %110, label %111, label %112, !dbg !345

111:                                              ; preds = %107, %103
  store i32 2, i32* @opMode, align 4, !dbg !346
  br label %112, !dbg !347

112:                                              ; preds = %111, %107
  %113 = load i8*, i8** @progName, align 8, !dbg !348
  %114 = call i8* @strstr(i8* %113, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i64 0, i64 0)) #11, !dbg !350
  %115 = icmp ne i8* %114, null, !dbg !351
  br i1 %115, label %128, label %116, !dbg !352

116:                                              ; preds = %112
  %117 = load i8*, i8** @progName, align 8, !dbg !353
  %118 = call i8* @strstr(i8* %117, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.13, i64 0, i64 0)) #11, !dbg !354
  %119 = icmp ne i8* %118, null, !dbg !355
  br i1 %119, label %128, label %120, !dbg !356

120:                                              ; preds = %116
  %121 = load i8*, i8** @progName, align 8, !dbg !357
  %122 = call i8* @strstr(i8* %121, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i64 0, i64 0)) #11, !dbg !358
  %123 = icmp ne i8* %122, null, !dbg !359
  br i1 %123, label %128, label %124, !dbg !360

124:                                              ; preds = %120
  %125 = load i8*, i8** @progName, align 8, !dbg !361
  %126 = call i8* @strstr(i8* %125, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.15, i64 0, i64 0)) #11, !dbg !362
  %127 = icmp ne i8* %126, null, !dbg !363
  br i1 %127, label %128, label %133, !dbg !364

128:                                              ; preds = %124, %120, %116, %112
  store i32 2, i32* @opMode, align 4, !dbg !365
  %129 = load i32, i32* @numFileNames, align 4, !dbg !367
  %130 = icmp eq i32 %129, 0, !dbg !368
  %131 = zext i1 %130 to i64, !dbg !369
  %132 = select i1 %130, i32 1, i32 2, !dbg !369
  store i32 %132, i32* @srcMode, align 4, !dbg !370
  br label %133, !dbg !371

133:                                              ; preds = %128, %124
  %134 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !372
  store %struct.zzzz* %134, %struct.zzzz** %10, align 8, !dbg !374
  br label %135, !dbg !375

135:                                              ; preds = %218, %133
  %136 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !376
  %137 = icmp ne %struct.zzzz* %136, null, !dbg !378
  br i1 %137, label %138, label %222, !dbg !379

138:                                              ; preds = %135
  %139 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !380
  %140 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %139, i32 0, i32 0, !dbg !380
  %141 = load i8*, i8** %140, align 8, !dbg !380
  %142 = call i32 @strcmp(i8* %141, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0)) #11, !dbg !380
  %143 = icmp eq i32 %142, 0, !dbg !380
  br i1 %143, label %144, label %145, !dbg !383

144:                                              ; preds = %138
  br label %222, !dbg !384

145:                                              ; preds = %138
  %146 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !385
  %147 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %146, i32 0, i32 0, !dbg !387
  %148 = load i8*, i8** %147, align 8, !dbg !387
  %149 = getelementptr inbounds i8, i8* %148, i64 0, !dbg !385
  %150 = load i8, i8* %149, align 1, !dbg !385
  %151 = sext i8 %150 to i32, !dbg !385
  %152 = icmp eq i32 %151, 45, !dbg !388
  br i1 %152, label %153, label %217, !dbg !389

153:                                              ; preds = %145
  %154 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !390
  %155 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %154, i32 0, i32 0, !dbg !391
  %156 = load i8*, i8** %155, align 8, !dbg !391
  %157 = getelementptr inbounds i8, i8* %156, i64 1, !dbg !390
  %158 = load i8, i8* %157, align 1, !dbg !390
  %159 = sext i8 %158 to i32, !dbg !390
  %160 = icmp ne i32 %159, 45, !dbg !392
  br i1 %160, label %161, label %217, !dbg !393

161:                                              ; preds = %153
  store i32 1, i32* %7, align 4, !dbg !394
  br label %162, !dbg !397

162:                                              ; preds = %213, %161
  %163 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !398
  %164 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %163, i32 0, i32 0, !dbg !400
  %165 = load i8*, i8** %164, align 8, !dbg !400
  %166 = load i32, i32* %7, align 4, !dbg !401
  %167 = sext i32 %166 to i64, !dbg !398
  %168 = getelementptr inbounds i8, i8* %165, i64 %167, !dbg !398
  %169 = load i8, i8* %168, align 1, !dbg !398
  %170 = sext i8 %169 to i32, !dbg !398
  %171 = icmp ne i32 %170, 0, !dbg !402
  br i1 %171, label %172, label %216, !dbg !403

172:                                              ; preds = %162
  %173 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !404
  %174 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %173, i32 0, i32 0, !dbg !406
  %175 = load i8*, i8** %174, align 8, !dbg !406
  %176 = load i32, i32* %7, align 4, !dbg !407
  %177 = sext i32 %176 to i64, !dbg !404
  %178 = getelementptr inbounds i8, i8* %175, i64 %177, !dbg !404
  %179 = load i8, i8* %178, align 1, !dbg !404
  %180 = sext i8 %179 to i32, !dbg !404
  switch i32 %180, label %204 [
    i32 99, label %181
    i32 100, label %182
    i32 122, label %183
    i32 102, label %184
    i32 116, label %185
    i32 107, label %186
    i32 115, label %187
    i32 113, label %188
    i32 49, label %189
    i32 50, label %190
    i32 51, label %191
    i32 52, label %192
    i32 53, label %193
    i32 54, label %194
    i32 55, label %195
    i32 56, label %196
    i32 57, label %197
    i32 86, label %198
    i32 76, label %198
    i32 118, label %199
    i32 104, label %202
  ], !dbg !408

181:                                              ; preds = %172
  store i32 2, i32* @srcMode, align 4, !dbg !409
  br label %212, !dbg !411

182:                                              ; preds = %172
  store i32 2, i32* @opMode, align 4, !dbg !412
  br label %212, !dbg !413

183:                                              ; preds = %172
  store i32 1, i32* @opMode, align 4, !dbg !414
  br label %212, !dbg !415

184:                                              ; preds = %172
  store i8 1, i8* @forceOverwrite, align 1, !dbg !416
  br label %212, !dbg !417

185:                                              ; preds = %172
  store i32 3, i32* @opMode, align 4, !dbg !418
  br label %212, !dbg !419

186:                                              ; preds = %172
  store i8 1, i8* @keepInputFiles, align 1, !dbg !420
  br label %212, !dbg !421

187:                                              ; preds = %172
  store i8 1, i8* @smallMode, align 1, !dbg !422
  br label %212, !dbg !423

188:                                              ; preds = %172
  store i8 0, i8* @noisy, align 1, !dbg !424
  br label %212, !dbg !425

189:                                              ; preds = %172
  store i32 1, i32* @blockSize100k, align 4, !dbg !426
  br label %212, !dbg !427

190:                                              ; preds = %172
  store i32 2, i32* @blockSize100k, align 4, !dbg !428
  br label %212, !dbg !429

191:                                              ; preds = %172
  store i32 3, i32* @blockSize100k, align 4, !dbg !430
  br label %212, !dbg !431

192:                                              ; preds = %172
  store i32 4, i32* @blockSize100k, align 4, !dbg !432
  br label %212, !dbg !433

193:                                              ; preds = %172
  store i32 5, i32* @blockSize100k, align 4, !dbg !434
  br label %212, !dbg !435

194:                                              ; preds = %172
  store i32 6, i32* @blockSize100k, align 4, !dbg !436
  br label %212, !dbg !437

195:                                              ; preds = %172
  store i32 7, i32* @blockSize100k, align 4, !dbg !438
  br label %212, !dbg !439

196:                                              ; preds = %172
  store i32 8, i32* @blockSize100k, align 4, !dbg !440
  br label %212, !dbg !441

197:                                              ; preds = %172
  store i32 9, i32* @blockSize100k, align 4, !dbg !442
  br label %212, !dbg !443

198:                                              ; preds = %172, %172
  call void @license(), !dbg !444
  br label %212, !dbg !445

199:                                              ; preds = %172
  %200 = load i32, i32* @verbosity, align 4, !dbg !446
  %201 = add nsw i32 %200, 1, !dbg !446
  store i32 %201, i32* @verbosity, align 4, !dbg !446
  br label %212, !dbg !447

202:                                              ; preds = %172
  %203 = load i8*, i8** @progName, align 8, !dbg !448
  call void @usage(i8* %203), !dbg !449
  call void @exit(i32 0) #12, !dbg !450
  unreachable, !dbg !450

204:                                              ; preds = %172
  %205 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !451
  %206 = load i8*, i8** @progName, align 8, !dbg !452
  %207 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !453
  %208 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %207, i32 0, i32 0, !dbg !454
  %209 = load i8*, i8** %208, align 8, !dbg !454
  %210 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %205, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.16, i64 0, i64 0), i8* %206, i8* %209), !dbg !455
  %211 = load i8*, i8** @progName, align 8, !dbg !456
  call void @usage(i8* %211), !dbg !457
  call void @exit(i32 1) #12, !dbg !458
  unreachable, !dbg !458

212:                                              ; preds = %199, %198, %197, %196, %195, %194, %193, %192, %191, %190, %189, %188, %187, %186, %185, %184, %183, %182, %181
  br label %213, !dbg !459

213:                                              ; preds = %212
  %214 = load i32, i32* %7, align 4, !dbg !460
  %215 = add nsw i32 %214, 1, !dbg !460
  store i32 %215, i32* %7, align 4, !dbg !460
  br label %162, !dbg !461, !llvm.loop !462

216:                                              ; preds = %162
  br label %217, !dbg !464

217:                                              ; preds = %216, %153, %145
  br label %218, !dbg !465

218:                                              ; preds = %217
  %219 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !466
  %220 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %219, i32 0, i32 1, !dbg !467
  %221 = load %struct.zzzz*, %struct.zzzz** %220, align 8, !dbg !467
  store %struct.zzzz* %221, %struct.zzzz** %10, align 8, !dbg !468
  br label %135, !dbg !469, !llvm.loop !470

222:                                              ; preds = %144, %135
  %223 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !472
  store %struct.zzzz* %223, %struct.zzzz** %10, align 8, !dbg !474
  br label %224, !dbg !475

224:                                              ; preds = %394, %222
  %225 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !476
  %226 = icmp ne %struct.zzzz* %225, null, !dbg !478
  br i1 %226, label %227, label %398, !dbg !479

227:                                              ; preds = %224
  %228 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !480
  %229 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %228, i32 0, i32 0, !dbg !480
  %230 = load i8*, i8** %229, align 8, !dbg !480
  %231 = call i32 @strcmp(i8* %230, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0)) #11, !dbg !480
  %232 = icmp eq i32 %231, 0, !dbg !480
  br i1 %232, label %233, label %234, !dbg !483

233:                                              ; preds = %227
  br label %398, !dbg !484

234:                                              ; preds = %227
  %235 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !485
  %236 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %235, i32 0, i32 0, !dbg !485
  %237 = load i8*, i8** %236, align 8, !dbg !485
  %238 = call i32 @strcmp(i8* %237, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.17, i64 0, i64 0)) #11, !dbg !485
  %239 = icmp eq i32 %238, 0, !dbg !485
  br i1 %239, label %240, label %241, !dbg !487

240:                                              ; preds = %234
  store i32 2, i32* @srcMode, align 4, !dbg !488
  br label %393, !dbg !489

241:                                              ; preds = %234
  %242 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !490
  %243 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %242, i32 0, i32 0, !dbg !490
  %244 = load i8*, i8** %243, align 8, !dbg !490
  %245 = call i32 @strcmp(i8* %244, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.18, i64 0, i64 0)) #11, !dbg !490
  %246 = icmp eq i32 %245, 0, !dbg !490
  br i1 %246, label %247, label %248, !dbg !492

247:                                              ; preds = %241
  store i32 2, i32* @opMode, align 4, !dbg !493
  br label %392, !dbg !494

248:                                              ; preds = %241
  %249 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !495
  %250 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %249, i32 0, i32 0, !dbg !495
  %251 = load i8*, i8** %250, align 8, !dbg !495
  %252 = call i32 @strcmp(i8* %251, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.19, i64 0, i64 0)) #11, !dbg !495
  %253 = icmp eq i32 %252, 0, !dbg !495
  br i1 %253, label %254, label %255, !dbg !497

254:                                              ; preds = %248
  store i32 1, i32* @opMode, align 4, !dbg !498
  br label %391, !dbg !499

255:                                              ; preds = %248
  %256 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !500
  %257 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %256, i32 0, i32 0, !dbg !500
  %258 = load i8*, i8** %257, align 8, !dbg !500
  %259 = call i32 @strcmp(i8* %258, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.20, i64 0, i64 0)) #11, !dbg !500
  %260 = icmp eq i32 %259, 0, !dbg !500
  br i1 %260, label %261, label %262, !dbg !502

261:                                              ; preds = %255
  store i8 1, i8* @forceOverwrite, align 1, !dbg !503
  br label %390, !dbg !504

262:                                              ; preds = %255
  %263 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !505
  %264 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %263, i32 0, i32 0, !dbg !505
  %265 = load i8*, i8** %264, align 8, !dbg !505
  %266 = call i32 @strcmp(i8* %265, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.21, i64 0, i64 0)) #11, !dbg !505
  %267 = icmp eq i32 %266, 0, !dbg !505
  br i1 %267, label %268, label %269, !dbg !507

268:                                              ; preds = %262
  store i32 3, i32* @opMode, align 4, !dbg !508
  br label %389, !dbg !509

269:                                              ; preds = %262
  %270 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !510
  %271 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %270, i32 0, i32 0, !dbg !510
  %272 = load i8*, i8** %271, align 8, !dbg !510
  %273 = call i32 @strcmp(i8* %272, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.22, i64 0, i64 0)) #11, !dbg !510
  %274 = icmp eq i32 %273, 0, !dbg !510
  br i1 %274, label %275, label %276, !dbg !512

275:                                              ; preds = %269
  store i8 1, i8* @keepInputFiles, align 1, !dbg !513
  br label %388, !dbg !514

276:                                              ; preds = %269
  %277 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !515
  %278 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %277, i32 0, i32 0, !dbg !515
  %279 = load i8*, i8** %278, align 8, !dbg !515
  %280 = call i32 @strcmp(i8* %279, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.23, i64 0, i64 0)) #11, !dbg !515
  %281 = icmp eq i32 %280, 0, !dbg !515
  br i1 %281, label %282, label %283, !dbg !517

282:                                              ; preds = %276
  store i8 1, i8* @smallMode, align 1, !dbg !518
  br label %387, !dbg !519

283:                                              ; preds = %276
  %284 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !520
  %285 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %284, i32 0, i32 0, !dbg !520
  %286 = load i8*, i8** %285, align 8, !dbg !520
  %287 = call i32 @strcmp(i8* %286, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.24, i64 0, i64 0)) #11, !dbg !520
  %288 = icmp eq i32 %287, 0, !dbg !520
  br i1 %288, label %289, label %290, !dbg !522

289:                                              ; preds = %283
  store i8 0, i8* @noisy, align 1, !dbg !523
  br label %386, !dbg !524

290:                                              ; preds = %283
  %291 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !525
  %292 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %291, i32 0, i32 0, !dbg !525
  %293 = load i8*, i8** %292, align 8, !dbg !525
  %294 = call i32 @strcmp(i8* %293, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.25, i64 0, i64 0)) #11, !dbg !525
  %295 = icmp eq i32 %294, 0, !dbg !525
  br i1 %295, label %296, label %297, !dbg !527

296:                                              ; preds = %290
  call void @license(), !dbg !528
  br label %385, !dbg !528

297:                                              ; preds = %290
  %298 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !529
  %299 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %298, i32 0, i32 0, !dbg !529
  %300 = load i8*, i8** %299, align 8, !dbg !529
  %301 = call i32 @strcmp(i8* %300, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.26, i64 0, i64 0)) #11, !dbg !529
  %302 = icmp eq i32 %301, 0, !dbg !529
  br i1 %302, label %303, label %304, !dbg !531

303:                                              ; preds = %297
  call void @license(), !dbg !532
  br label %384, !dbg !532

304:                                              ; preds = %297
  %305 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !533
  %306 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %305, i32 0, i32 0, !dbg !533
  %307 = load i8*, i8** %306, align 8, !dbg !533
  %308 = call i32 @strcmp(i8* %307, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.27, i64 0, i64 0)) #11, !dbg !533
  %309 = icmp eq i32 %308, 0, !dbg !533
  br i1 %309, label %310, label %311, !dbg !535

310:                                              ; preds = %304
  store i32 1, i32* @workFactor, align 4, !dbg !536
  br label %383, !dbg !537

311:                                              ; preds = %304
  %312 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !538
  %313 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %312, i32 0, i32 0, !dbg !538
  %314 = load i8*, i8** %313, align 8, !dbg !538
  %315 = call i32 @strcmp(i8* %314, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.28, i64 0, i64 0)) #11, !dbg !538
  %316 = icmp eq i32 %315, 0, !dbg !538
  br i1 %316, label %317, label %321, !dbg !540

317:                                              ; preds = %311
  %318 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !541
  %319 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %318, i32 0, i32 0, !dbg !542
  %320 = load i8*, i8** %319, align 8, !dbg !542
  call void @redundant(i8* %320), !dbg !543
  br label %382, !dbg !543

321:                                              ; preds = %311
  %322 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !544
  %323 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %322, i32 0, i32 0, !dbg !544
  %324 = load i8*, i8** %323, align 8, !dbg !544
  %325 = call i32 @strcmp(i8* %324, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.29, i64 0, i64 0)) #11, !dbg !544
  %326 = icmp eq i32 %325, 0, !dbg !544
  br i1 %326, label %327, label %331, !dbg !546

327:                                              ; preds = %321
  %328 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !547
  %329 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %328, i32 0, i32 0, !dbg !548
  %330 = load i8*, i8** %329, align 8, !dbg !548
  call void @redundant(i8* %330), !dbg !549
  br label %381, !dbg !549

331:                                              ; preds = %321
  %332 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !550
  %333 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %332, i32 0, i32 0, !dbg !550
  %334 = load i8*, i8** %333, align 8, !dbg !550
  %335 = call i32 @strcmp(i8* %334, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.30, i64 0, i64 0)) #11, !dbg !550
  %336 = icmp eq i32 %335, 0, !dbg !550
  br i1 %336, label %337, label %338, !dbg !552

337:                                              ; preds = %331
  store i32 1, i32* @blockSize100k, align 4, !dbg !553
  br label %380, !dbg !554

338:                                              ; preds = %331
  %339 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !555
  %340 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %339, i32 0, i32 0, !dbg !555
  %341 = load i8*, i8** %340, align 8, !dbg !555
  %342 = call i32 @strcmp(i8* %341, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i64 0, i64 0)) #11, !dbg !555
  %343 = icmp eq i32 %342, 0, !dbg !555
  br i1 %343, label %344, label %345, !dbg !557

344:                                              ; preds = %338
  store i32 9, i32* @blockSize100k, align 4, !dbg !558
  br label %379, !dbg !559

345:                                              ; preds = %338
  %346 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !560
  %347 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %346, i32 0, i32 0, !dbg !560
  %348 = load i8*, i8** %347, align 8, !dbg !560
  %349 = call i32 @strcmp(i8* %348, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.32, i64 0, i64 0)) #11, !dbg !560
  %350 = icmp eq i32 %349, 0, !dbg !560
  br i1 %350, label %351, label %354, !dbg !562

351:                                              ; preds = %345
  %352 = load i32, i32* @verbosity, align 4, !dbg !563
  %353 = add nsw i32 %352, 1, !dbg !563
  store i32 %353, i32* @verbosity, align 4, !dbg !563
  br label %378, !dbg !564

354:                                              ; preds = %345
  %355 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !565
  %356 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %355, i32 0, i32 0, !dbg !565
  %357 = load i8*, i8** %356, align 8, !dbg !565
  %358 = call i32 @strcmp(i8* %357, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i64 0, i64 0)) #11, !dbg !565
  %359 = icmp eq i32 %358, 0, !dbg !565
  br i1 %359, label %360, label %362, !dbg !567

360:                                              ; preds = %354
  %361 = load i8*, i8** @progName, align 8, !dbg !568
  call void @usage(i8* %361), !dbg !570
  call void @exit(i32 0) #12, !dbg !571
  unreachable, !dbg !571

362:                                              ; preds = %354
  %363 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !572
  %364 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %363, i32 0, i32 0, !dbg !574
  %365 = load i8*, i8** %364, align 8, !dbg !574
  %366 = call i32 @strncmp(i8* %365, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0), i64 2) #11, !dbg !575
  %367 = icmp eq i32 %366, 0, !dbg !576
  br i1 %367, label %368, label %376, !dbg !577

368:                                              ; preds = %362
  %369 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !578
  %370 = load i8*, i8** @progName, align 8, !dbg !580
  %371 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !581
  %372 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %371, i32 0, i32 0, !dbg !582
  %373 = load i8*, i8** %372, align 8, !dbg !582
  %374 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %369, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.16, i64 0, i64 0), i8* %370, i8* %373), !dbg !583
  %375 = load i8*, i8** @progName, align 8, !dbg !584
  call void @usage(i8* %375), !dbg !585
  call void @exit(i32 1) #12, !dbg !586
  unreachable, !dbg !586

376:                                              ; preds = %362
  br label %377

377:                                              ; preds = %376
  br label %378

378:                                              ; preds = %377, %351
  br label %379

379:                                              ; preds = %378, %344
  br label %380

380:                                              ; preds = %379, %337
  br label %381

381:                                              ; preds = %380, %327
  br label %382

382:                                              ; preds = %381, %317
  br label %383

383:                                              ; preds = %382, %310
  br label %384

384:                                              ; preds = %383, %303
  br label %385

385:                                              ; preds = %384, %296
  br label %386

386:                                              ; preds = %385, %289
  br label %387

387:                                              ; preds = %386, %282
  br label %388

388:                                              ; preds = %387, %275
  br label %389

389:                                              ; preds = %388, %268
  br label %390

390:                                              ; preds = %389, %261
  br label %391

391:                                              ; preds = %390, %254
  br label %392

392:                                              ; preds = %391, %247
  br label %393

393:                                              ; preds = %392, %240
  br label %394, !dbg !587

394:                                              ; preds = %393
  %395 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !588
  %396 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %395, i32 0, i32 1, !dbg !589
  %397 = load %struct.zzzz*, %struct.zzzz** %396, align 8, !dbg !589
  store %struct.zzzz* %397, %struct.zzzz** %10, align 8, !dbg !590
  br label %224, !dbg !591, !llvm.loop !592

398:                                              ; preds = %233, %224
  %399 = load i32, i32* @verbosity, align 4, !dbg !594
  %400 = icmp sgt i32 %399, 4, !dbg !596
  br i1 %400, label %401, label %402, !dbg !597

401:                                              ; preds = %398
  store i32 4, i32* @verbosity, align 4, !dbg !598
  br label %402, !dbg !599

402:                                              ; preds = %401, %398
  %403 = load i32, i32* @opMode, align 4, !dbg !600
  %404 = icmp eq i32 %403, 1, !dbg !602
  br i1 %404, label %405, label %413, !dbg !603

405:                                              ; preds = %402
  %406 = load i8, i8* @smallMode, align 1, !dbg !604
  %407 = zext i8 %406 to i32, !dbg !604
  %408 = icmp ne i32 %407, 0, !dbg !604
  br i1 %408, label %409, label %413, !dbg !605

409:                                              ; preds = %405
  %410 = load i32, i32* @blockSize100k, align 4, !dbg !606
  %411 = icmp sgt i32 %410, 2, !dbg !607
  br i1 %411, label %412, label %413, !dbg !608

412:                                              ; preds = %409
  store i32 2, i32* @blockSize100k, align 4, !dbg !609
  br label %413, !dbg !610

413:                                              ; preds = %412, %409, %405, %402
  %414 = load i32, i32* @opMode, align 4, !dbg !611
  %415 = icmp eq i32 %414, 3, !dbg !613
  br i1 %415, label %416, label %423, !dbg !614

416:                                              ; preds = %413
  %417 = load i32, i32* @srcMode, align 4, !dbg !615
  %418 = icmp eq i32 %417, 2, !dbg !616
  br i1 %418, label %419, label %423, !dbg !617

419:                                              ; preds = %416
  %420 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !618
  %421 = load i8*, i8** @progName, align 8, !dbg !620
  %422 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %420, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.34, i64 0, i64 0), i8* %421), !dbg !621
  call void @exit(i32 1) #12, !dbg !622
  unreachable, !dbg !622

423:                                              ; preds = %416, %413
  %424 = load i32, i32* @srcMode, align 4, !dbg !623
  %425 = icmp eq i32 %424, 2, !dbg !625
  br i1 %425, label %426, label %430, !dbg !626

426:                                              ; preds = %423
  %427 = load i32, i32* @numFileNames, align 4, !dbg !627
  %428 = icmp eq i32 %427, 0, !dbg !628
  br i1 %428, label %429, label %430, !dbg !629

429:                                              ; preds = %426
  store i32 1, i32* @srcMode, align 4, !dbg !630
  br label %430, !dbg !631

430:                                              ; preds = %429, %426, %423
  %431 = load i32, i32* @opMode, align 4, !dbg !632
  %432 = icmp ne i32 %431, 1, !dbg !634
  br i1 %432, label %433, label %434, !dbg !635

433:                                              ; preds = %430
  store i32 0, i32* @blockSize100k, align 4, !dbg !636
  br label %434, !dbg !637

434:                                              ; preds = %433, %430
  %435 = load i32, i32* @srcMode, align 4, !dbg !638
  %436 = icmp eq i32 %435, 3, !dbg !640
  br i1 %436, label %437, label %441, !dbg !641

437:                                              ; preds = %434
  %438 = call void (i32)* @signal(i32 2, void (i32)* @mySignalCatcher) #10, !dbg !642
  %439 = call void (i32)* @signal(i32 15, void (i32)* @mySignalCatcher) #10, !dbg !644
  %440 = call void (i32)* @signal(i32 1, void (i32)* @mySignalCatcher) #10, !dbg !645
  br label %441, !dbg !646

441:                                              ; preds = %437, %434
  %442 = load i32, i32* @opMode, align 4, !dbg !647
  %443 = icmp eq i32 %442, 1, !dbg !649
  br i1 %443, label %444, label %485, !dbg !650

444:                                              ; preds = %441
  %445 = load i32, i32* @srcMode, align 4, !dbg !651
  %446 = icmp eq i32 %445, 1, !dbg !654
  br i1 %446, label %447, label %448, !dbg !655

447:                                              ; preds = %444
  call void @compress(i8* null), !dbg !656
  br label %484, !dbg !658

448:                                              ; preds = %444
  store i8 1, i8* %11, align 1, !dbg !659
  %449 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !661
  store %struct.zzzz* %449, %struct.zzzz** %10, align 8, !dbg !663
  br label %450, !dbg !664

450:                                              ; preds = %479, %448
  %451 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !665
  %452 = icmp ne %struct.zzzz* %451, null, !dbg !667
  br i1 %452, label %453, label %483, !dbg !668

453:                                              ; preds = %450
  %454 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !669
  %455 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %454, i32 0, i32 0, !dbg !669
  %456 = load i8*, i8** %455, align 8, !dbg !669
  %457 = call i32 @strcmp(i8* %456, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0)) #11, !dbg !669
  %458 = icmp eq i32 %457, 0, !dbg !669
  br i1 %458, label %459, label %460, !dbg !672

459:                                              ; preds = %453
  store i8 0, i8* %11, align 1, !dbg !673
  br label %479, !dbg !675

460:                                              ; preds = %453
  %461 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !676
  %462 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %461, i32 0, i32 0, !dbg !678
  %463 = load i8*, i8** %462, align 8, !dbg !678
  %464 = getelementptr inbounds i8, i8* %463, i64 0, !dbg !676
  %465 = load i8, i8* %464, align 1, !dbg !676
  %466 = sext i8 %465 to i32, !dbg !676
  %467 = icmp eq i32 %466, 45, !dbg !679
  br i1 %467, label %468, label %473, !dbg !680

468:                                              ; preds = %460
  %469 = load i8, i8* %11, align 1, !dbg !681
  %470 = zext i8 %469 to i32, !dbg !681
  %471 = icmp ne i32 %470, 0, !dbg !681
  br i1 %471, label %472, label %473, !dbg !682

472:                                              ; preds = %468
  br label %479, !dbg !683

473:                                              ; preds = %468, %460
  %474 = load i32, i32* @numFilesProcessed, align 4, !dbg !684
  %475 = add nsw i32 %474, 1, !dbg !684
  store i32 %475, i32* @numFilesProcessed, align 4, !dbg !684
  %476 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !685
  %477 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %476, i32 0, i32 0, !dbg !686
  %478 = load i8*, i8** %477, align 8, !dbg !686
  call void @compress(i8* %478), !dbg !687
  br label %479, !dbg !688

479:                                              ; preds = %473, %472, %459
  %480 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !689
  %481 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %480, i32 0, i32 1, !dbg !690
  %482 = load %struct.zzzz*, %struct.zzzz** %481, align 8, !dbg !690
  store %struct.zzzz* %482, %struct.zzzz** %10, align 8, !dbg !691
  br label %450, !dbg !692, !llvm.loop !693

483:                                              ; preds = %450
  br label %484

484:                                              ; preds = %483, %447
  br label %588, !dbg !695

485:                                              ; preds = %441
  %486 = load i32, i32* @opMode, align 4, !dbg !696
  %487 = icmp eq i32 %486, 2, !dbg !698
  br i1 %487, label %488, label %534, !dbg !699

488:                                              ; preds = %485
  store i8 0, i8* @unzFailsExist, align 1, !dbg !700
  %489 = load i32, i32* @srcMode, align 4, !dbg !702
  %490 = icmp eq i32 %489, 1, !dbg !704
  br i1 %490, label %491, label %492, !dbg !705

491:                                              ; preds = %488
  call void @uncompress(i8* null), !dbg !706
  br label %528, !dbg !708

492:                                              ; preds = %488
  store i8 1, i8* %11, align 1, !dbg !709
  %493 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !711
  store %struct.zzzz* %493, %struct.zzzz** %10, align 8, !dbg !713
  br label %494, !dbg !714

494:                                              ; preds = %523, %492
  %495 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !715
  %496 = icmp ne %struct.zzzz* %495, null, !dbg !717
  br i1 %496, label %497, label %527, !dbg !718

497:                                              ; preds = %494
  %498 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !719
  %499 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %498, i32 0, i32 0, !dbg !719
  %500 = load i8*, i8** %499, align 8, !dbg !719
  %501 = call i32 @strcmp(i8* %500, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0)) #11, !dbg !719
  %502 = icmp eq i32 %501, 0, !dbg !719
  br i1 %502, label %503, label %504, !dbg !722

503:                                              ; preds = %497
  store i8 0, i8* %11, align 1, !dbg !723
  br label %523, !dbg !725

504:                                              ; preds = %497
  %505 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !726
  %506 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %505, i32 0, i32 0, !dbg !728
  %507 = load i8*, i8** %506, align 8, !dbg !728
  %508 = getelementptr inbounds i8, i8* %507, i64 0, !dbg !726
  %509 = load i8, i8* %508, align 1, !dbg !726
  %510 = sext i8 %509 to i32, !dbg !726
  %511 = icmp eq i32 %510, 45, !dbg !729
  br i1 %511, label %512, label %517, !dbg !730

512:                                              ; preds = %504
  %513 = load i8, i8* %11, align 1, !dbg !731
  %514 = zext i8 %513 to i32, !dbg !731
  %515 = icmp ne i32 %514, 0, !dbg !731
  br i1 %515, label %516, label %517, !dbg !732

516:                                              ; preds = %512
  br label %523, !dbg !733

517:                                              ; preds = %512, %504
  %518 = load i32, i32* @numFilesProcessed, align 4, !dbg !734
  %519 = add nsw i32 %518, 1, !dbg !734
  store i32 %519, i32* @numFilesProcessed, align 4, !dbg !734
  %520 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !735
  %521 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %520, i32 0, i32 0, !dbg !736
  %522 = load i8*, i8** %521, align 8, !dbg !736
  call void @uncompress(i8* %522), !dbg !737
  br label %523, !dbg !738

523:                                              ; preds = %517, %516, %503
  %524 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !739
  %525 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %524, i32 0, i32 1, !dbg !740
  %526 = load %struct.zzzz*, %struct.zzzz** %525, align 8, !dbg !740
  store %struct.zzzz* %526, %struct.zzzz** %10, align 8, !dbg !741
  br label %494, !dbg !742, !llvm.loop !743

527:                                              ; preds = %494
  br label %528

528:                                              ; preds = %527, %491
  %529 = load i8, i8* @unzFailsExist, align 1, !dbg !745
  %530 = icmp ne i8 %529, 0, !dbg !745
  br i1 %530, label %531, label %533, !dbg !747

531:                                              ; preds = %528
  call void @setExit(i32 2), !dbg !748
  %532 = load i32, i32* @exitValue, align 4, !dbg !750
  call void @exit(i32 %532) #12, !dbg !751
  unreachable, !dbg !751

533:                                              ; preds = %528
  br label %587, !dbg !752

534:                                              ; preds = %485
  store i8 0, i8* @testFailsExist, align 1, !dbg !753
  %535 = load i32, i32* @srcMode, align 4, !dbg !755
  %536 = icmp eq i32 %535, 1, !dbg !757
  br i1 %536, label %537, label %538, !dbg !758

537:                                              ; preds = %534
  call void @testf(i8* null), !dbg !759
  br label %574, !dbg !761

538:                                              ; preds = %534
  store i8 1, i8* %11, align 1, !dbg !762
  %539 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !764
  store %struct.zzzz* %539, %struct.zzzz** %10, align 8, !dbg !766
  br label %540, !dbg !767

540:                                              ; preds = %569, %538
  %541 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !768
  %542 = icmp ne %struct.zzzz* %541, null, !dbg !770
  br i1 %542, label %543, label %573, !dbg !771

543:                                              ; preds = %540
  %544 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !772
  %545 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %544, i32 0, i32 0, !dbg !772
  %546 = load i8*, i8** %545, align 8, !dbg !772
  %547 = call i32 @strcmp(i8* %546, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i64 0, i64 0)) #11, !dbg !772
  %548 = icmp eq i32 %547, 0, !dbg !772
  br i1 %548, label %549, label %550, !dbg !775

549:                                              ; preds = %543
  store i8 0, i8* %11, align 1, !dbg !776
  br label %569, !dbg !778

550:                                              ; preds = %543
  %551 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !779
  %552 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %551, i32 0, i32 0, !dbg !781
  %553 = load i8*, i8** %552, align 8, !dbg !781
  %554 = getelementptr inbounds i8, i8* %553, i64 0, !dbg !779
  %555 = load i8, i8* %554, align 1, !dbg !779
  %556 = sext i8 %555 to i32, !dbg !779
  %557 = icmp eq i32 %556, 45, !dbg !782
  br i1 %557, label %558, label %563, !dbg !783

558:                                              ; preds = %550
  %559 = load i8, i8* %11, align 1, !dbg !784
  %560 = zext i8 %559 to i32, !dbg !784
  %561 = icmp ne i32 %560, 0, !dbg !784
  br i1 %561, label %562, label %563, !dbg !785

562:                                              ; preds = %558
  br label %569, !dbg !786

563:                                              ; preds = %558, %550
  %564 = load i32, i32* @numFilesProcessed, align 4, !dbg !787
  %565 = add nsw i32 %564, 1, !dbg !787
  store i32 %565, i32* @numFilesProcessed, align 4, !dbg !787
  %566 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !788
  %567 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %566, i32 0, i32 0, !dbg !789
  %568 = load i8*, i8** %567, align 8, !dbg !789
  call void @testf(i8* %568), !dbg !790
  br label %569, !dbg !791

569:                                              ; preds = %563, %562, %549
  %570 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !792
  %571 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %570, i32 0, i32 1, !dbg !793
  %572 = load %struct.zzzz*, %struct.zzzz** %571, align 8, !dbg !793
  store %struct.zzzz* %572, %struct.zzzz** %10, align 8, !dbg !794
  br label %540, !dbg !795, !llvm.loop !796

573:                                              ; preds = %540
  br label %574

574:                                              ; preds = %573, %537
  %575 = load i8, i8* @testFailsExist, align 1, !dbg !798
  %576 = zext i8 %575 to i32, !dbg !798
  %577 = icmp ne i32 %576, 0, !dbg !798
  br i1 %577, label %578, label %586, !dbg !800

578:                                              ; preds = %574
  %579 = load i8, i8* @noisy, align 1, !dbg !801
  %580 = zext i8 %579 to i32, !dbg !801
  %581 = icmp ne i32 %580, 0, !dbg !801
  br i1 %581, label %582, label %586, !dbg !802

582:                                              ; preds = %578
  %583 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !803
  %584 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %583, i8* getelementptr inbounds ([113 x i8], [113 x i8]* @.str.35, i64 0, i64 0)), !dbg !805
  call void @setExit(i32 2), !dbg !806
  %585 = load i32, i32* @exitValue, align 4, !dbg !807
  call void @exit(i32 %585) #12, !dbg !808
  unreachable, !dbg !808

586:                                              ; preds = %578, %574
  br label %587

587:                                              ; preds = %586, %533
  br label %588

588:                                              ; preds = %587, %484
  %589 = load %struct.zzzz*, %struct.zzzz** %9, align 8, !dbg !809
  store %struct.zzzz* %589, %struct.zzzz** %10, align 8, !dbg !810
  br label %590, !dbg !811

590:                                              ; preds = %605, %588
  %591 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !812
  %592 = icmp ne %struct.zzzz* %591, null, !dbg !813
  br i1 %592, label %593, label %609, !dbg !811

593:                                              ; preds = %590
  call void @llvm.dbg.declare(metadata %struct.zzzz** %12, metadata !814, metadata !DIExpression()), !dbg !816
  %594 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !817
  %595 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %594, i32 0, i32 1, !dbg !818
  %596 = load %struct.zzzz*, %struct.zzzz** %595, align 8, !dbg !818
  store %struct.zzzz* %596, %struct.zzzz** %12, align 8, !dbg !816
  %597 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !819
  %598 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %597, i32 0, i32 0, !dbg !821
  %599 = load i8*, i8** %598, align 8, !dbg !821
  %600 = icmp ne i8* %599, null, !dbg !822
  br i1 %600, label %601, label %605, !dbg !823

601:                                              ; preds = %593
  %602 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !824
  %603 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %602, i32 0, i32 0, !dbg !825
  %604 = load i8*, i8** %603, align 8, !dbg !825
  call void @free(i8* %604) #10, !dbg !826
  br label %605, !dbg !826

605:                                              ; preds = %601, %593
  %606 = load %struct.zzzz*, %struct.zzzz** %10, align 8, !dbg !827
  %607 = bitcast %struct.zzzz* %606 to i8*, !dbg !827
  call void @free(i8* %607) #10, !dbg !828
  %608 = load %struct.zzzz*, %struct.zzzz** %12, align 8, !dbg !829
  store %struct.zzzz* %608, %struct.zzzz** %10, align 8, !dbg !830
  br label %590, !dbg !811, !llvm.loop !831

609:                                              ; preds = %590
  %610 = load i32, i32* @exitValue, align 4, !dbg !833
  ret i32 %610, !dbg !834
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare dso_local void (i32)* @signal(i32, void (i32)*) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal void @mySIGSEGVorSIGBUScatcher(i32 %0) #0 !dbg !835 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !838, metadata !DIExpression()), !dbg !839
  %3 = load i32, i32* @opMode, align 4, !dbg !840
  %4 = icmp eq i32 %3, 1, !dbg !842
  br i1 %4, label %5, label %9, !dbg !843

5:                                                ; preds = %1
  %6 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !844
  %7 = load i8*, i8** @progName, align 8, !dbg !845
  %8 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %6, i8* getelementptr inbounds ([869 x i8], [869 x i8]* @.str.36, i64 0, i64 0), i8* %7), !dbg !846
  br label %13, !dbg !846

9:                                                ; preds = %1
  %10 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !847
  %11 = load i8*, i8** @progName, align 8, !dbg !848
  %12 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %10, i8* getelementptr inbounds ([996 x i8], [996 x i8]* @.str.37, i64 0, i64 0), i8* %11), !dbg !849
  br label %13

13:                                               ; preds = %9, %5
  call void @showFileNames(), !dbg !850
  %14 = load i32, i32* @opMode, align 4, !dbg !851
  %15 = icmp eq i32 %14, 1, !dbg !853
  br i1 %15, label %16, label %17, !dbg !854

16:                                               ; preds = %13
  call void @cleanUpAndFail(i32 3) #13, !dbg !855
  unreachable, !dbg !855

17:                                               ; preds = %13
  call void @cadvise(), !dbg !856
  call void @cleanUpAndFail(i32 2) #13, !dbg !858
  unreachable, !dbg !858
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @copyFileName(i8* %0, i8* %1) #0 !dbg !859 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !862, metadata !DIExpression()), !dbg !863
  store i8* %1, i8** %4, align 8
  call void @llvm.dbg.declare(metadata i8** %4, metadata !864, metadata !DIExpression()), !dbg !865
  %5 = load i8*, i8** %4, align 8, !dbg !866
  %6 = call i64 @strlen(i8* %5) #11, !dbg !868
  %7 = icmp ugt i64 %6, 1024, !dbg !869
  br i1 %7, label %8, label %13, !dbg !870

8:                                                ; preds = %2
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !871
  %10 = load i8*, i8** %4, align 8, !dbg !873
  %11 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %9, i8* getelementptr inbounds ([120 x i8], [120 x i8]* @.str.47, i64 0, i64 0), i8* %10, i32 1024), !dbg !874
  call void @setExit(i32 1), !dbg !875
  %12 = load i32, i32* @exitValue, align 4, !dbg !876
  call void @exit(i32 %12) #12, !dbg !877
  unreachable, !dbg !877

13:                                               ; preds = %2
  %14 = load i8*, i8** %3, align 8, !dbg !878
  %15 = load i8*, i8** %4, align 8, !dbg !879
  %16 = call i8* @strncpy(i8* %14, i8* %15, i64 1024) #10, !dbg !880
  %17 = load i8*, i8** %3, align 8, !dbg !881
  %18 = getelementptr inbounds i8, i8* %17, i64 1024, !dbg !881
  store i8 0, i8* %18, align 1, !dbg !882
  ret void, !dbg !883
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @addFlagsFromEnvVar(%struct.zzzz** %0, i8* %1) #0 !dbg !884 {
  %3 = alloca %struct.zzzz**, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  store %struct.zzzz** %0, %struct.zzzz*** %3, align 8
  call void @llvm.dbg.declare(metadata %struct.zzzz*** %3, metadata !888, metadata !DIExpression()), !dbg !889
  store i8* %1, i8** %4, align 8
  call void @llvm.dbg.declare(metadata i8** %4, metadata !890, metadata !DIExpression()), !dbg !891
  call void @llvm.dbg.declare(metadata i32* %5, metadata !892, metadata !DIExpression()), !dbg !893
  call void @llvm.dbg.declare(metadata i32* %6, metadata !894, metadata !DIExpression()), !dbg !895
  call void @llvm.dbg.declare(metadata i32* %7, metadata !896, metadata !DIExpression()), !dbg !897
  call void @llvm.dbg.declare(metadata i8** %8, metadata !898, metadata !DIExpression()), !dbg !899
  call void @llvm.dbg.declare(metadata i8** %9, metadata !900, metadata !DIExpression()), !dbg !901
  %10 = load i8*, i8** %4, align 8, !dbg !902
  %11 = call i8* @getenv(i8* %10) #10, !dbg !903
  store i8* %11, i8** %8, align 8, !dbg !904
  %12 = load i8*, i8** %8, align 8, !dbg !905
  %13 = icmp ne i8* %12, null, !dbg !907
  br i1 %13, label %14, label %111, !dbg !908

14:                                               ; preds = %2
  %15 = load i8*, i8** %8, align 8, !dbg !909
  store i8* %15, i8** %9, align 8, !dbg !911
  store i32 0, i32* %5, align 4, !dbg !912
  br label %16, !dbg !913

16:                                               ; preds = %14, %109
  %17 = load i8*, i8** %9, align 8, !dbg !914
  %18 = load i32, i32* %5, align 4, !dbg !917
  %19 = sext i32 %18 to i64, !dbg !914
  %20 = getelementptr inbounds i8, i8* %17, i64 %19, !dbg !914
  %21 = load i8, i8* %20, align 1, !dbg !914
  %22 = sext i8 %21 to i32, !dbg !914
  %23 = icmp eq i32 %22, 0, !dbg !918
  br i1 %23, label %24, label %25, !dbg !919

24:                                               ; preds = %16
  br label %110, !dbg !920

25:                                               ; preds = %16
  %26 = load i32, i32* %5, align 4, !dbg !921
  %27 = load i8*, i8** %9, align 8, !dbg !922
  %28 = sext i32 %26 to i64, !dbg !922
  %29 = getelementptr inbounds i8, i8* %27, i64 %28, !dbg !922
  store i8* %29, i8** %9, align 8, !dbg !922
  store i32 0, i32* %5, align 4, !dbg !923
  br label %30, !dbg !924

30:                                               ; preds = %43, %25
  %31 = call i16** @__ctype_b_loc() #14, !dbg !925
  %32 = load i16*, i16** %31, align 8, !dbg !925
  %33 = load i8*, i8** %9, align 8, !dbg !925
  %34 = getelementptr inbounds i8, i8* %33, i64 0, !dbg !925
  %35 = load i8, i8* %34, align 1, !dbg !925
  %36 = sext i8 %35 to i32, !dbg !925
  %37 = sext i32 %36 to i64, !dbg !925
  %38 = getelementptr inbounds i16, i16* %32, i64 %37, !dbg !925
  %39 = load i16, i16* %38, align 2, !dbg !925
  %40 = zext i16 %39 to i32, !dbg !925
  %41 = and i32 %40, 8192, !dbg !925
  %42 = icmp ne i32 %41, 0, !dbg !924
  br i1 %42, label %43, label %46, !dbg !924

43:                                               ; preds = %30
  %44 = load i8*, i8** %9, align 8, !dbg !926
  %45 = getelementptr inbounds i8, i8* %44, i32 1, !dbg !926
  store i8* %45, i8** %9, align 8, !dbg !926
  br label %30, !dbg !924, !llvm.loop !927

46:                                               ; preds = %30
  br label %47, !dbg !928

47:                                               ; preds = %73, %46
  %48 = load i8*, i8** %9, align 8, !dbg !929
  %49 = load i32, i32* %5, align 4, !dbg !930
  %50 = sext i32 %49 to i64, !dbg !929
  %51 = getelementptr inbounds i8, i8* %48, i64 %50, !dbg !929
  %52 = load i8, i8* %51, align 1, !dbg !929
  %53 = sext i8 %52 to i32, !dbg !929
  %54 = icmp ne i32 %53, 0, !dbg !931
  br i1 %54, label %55, label %71, !dbg !932

55:                                               ; preds = %47
  %56 = call i16** @__ctype_b_loc() #14, !dbg !933
  %57 = load i16*, i16** %56, align 8, !dbg !933
  %58 = load i8*, i8** %9, align 8, !dbg !933
  %59 = load i32, i32* %5, align 4, !dbg !933
  %60 = sext i32 %59 to i64, !dbg !933
  %61 = getelementptr inbounds i8, i8* %58, i64 %60, !dbg !933
  %62 = load i8, i8* %61, align 1, !dbg !933
  %63 = sext i8 %62 to i32, !dbg !933
  %64 = sext i32 %63 to i64, !dbg !933
  %65 = getelementptr inbounds i16, i16* %57, i64 %64, !dbg !933
  %66 = load i16, i16* %65, align 2, !dbg !933
  %67 = zext i16 %66 to i32, !dbg !933
  %68 = and i32 %67, 8192, !dbg !933
  %69 = icmp ne i32 %68, 0, !dbg !934
  %70 = xor i1 %69, true, !dbg !934
  br label %71

71:                                               ; preds = %55, %47
  %72 = phi i1 [ false, %47 ], [ %70, %55 ], !dbg !935
  br i1 %72, label %73, label %76, !dbg !928

73:                                               ; preds = %71
  %74 = load i32, i32* %5, align 4, !dbg !936
  %75 = add nsw i32 %74, 1, !dbg !936
  store i32 %75, i32* %5, align 4, !dbg !936
  br label %47, !dbg !928, !llvm.loop !937

76:                                               ; preds = %71
  %77 = load i32, i32* %5, align 4, !dbg !938
  %78 = icmp sgt i32 %77, 0, !dbg !940
  br i1 %78, label %79, label %109, !dbg !941

79:                                               ; preds = %76
  %80 = load i32, i32* %5, align 4, !dbg !942
  store i32 %80, i32* %7, align 4, !dbg !944
  %81 = load i32, i32* %7, align 4, !dbg !945
  %82 = icmp sgt i32 %81, 1024, !dbg !947
  br i1 %82, label %83, label %84, !dbg !948

83:                                               ; preds = %79
  store i32 1024, i32* %7, align 4, !dbg !949
  br label %84, !dbg !950

84:                                               ; preds = %83, %79
  store i32 0, i32* %6, align 4, !dbg !951
  br label %85, !dbg !953

85:                                               ; preds = %98, %84
  %86 = load i32, i32* %6, align 4, !dbg !954
  %87 = load i32, i32* %7, align 4, !dbg !956
  %88 = icmp slt i32 %86, %87, !dbg !957
  br i1 %88, label %89, label %101, !dbg !958

89:                                               ; preds = %85
  %90 = load i8*, i8** %9, align 8, !dbg !959
  %91 = load i32, i32* %6, align 4, !dbg !960
  %92 = sext i32 %91 to i64, !dbg !959
  %93 = getelementptr inbounds i8, i8* %90, i64 %92, !dbg !959
  %94 = load i8, i8* %93, align 1, !dbg !959
  %95 = load i32, i32* %6, align 4, !dbg !961
  %96 = sext i32 %95 to i64, !dbg !962
  %97 = getelementptr inbounds [1034 x i8], [1034 x i8]* @tmpName, i64 0, i64 %96, !dbg !962
  store i8 %94, i8* %97, align 1, !dbg !963
  br label %98, !dbg !962

98:                                               ; preds = %89
  %99 = load i32, i32* %6, align 4, !dbg !964
  %100 = add nsw i32 %99, 1, !dbg !964
  store i32 %100, i32* %6, align 4, !dbg !964
  br label %85, !dbg !965, !llvm.loop !966

101:                                              ; preds = %85
  %102 = load i32, i32* %7, align 4, !dbg !968
  %103 = sext i32 %102 to i64, !dbg !969
  %104 = getelementptr inbounds [1034 x i8], [1034 x i8]* @tmpName, i64 0, i64 %103, !dbg !969
  store i8 0, i8* %104, align 1, !dbg !970
  %105 = load %struct.zzzz**, %struct.zzzz*** %3, align 8, !dbg !971
  %106 = load %struct.zzzz*, %struct.zzzz** %105, align 8, !dbg !971
  %107 = call %struct.zzzz* @snocString(%struct.zzzz* %106, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @tmpName, i64 0, i64 0)), !dbg !971
  %108 = load %struct.zzzz**, %struct.zzzz*** %3, align 8, !dbg !971
  store %struct.zzzz* %107, %struct.zzzz** %108, align 8, !dbg !971
  br label %109, !dbg !972

109:                                              ; preds = %101, %76
  br label %16, !dbg !913, !llvm.loop !973

110:                                              ; preds = %24
  br label %111, !dbg !975

111:                                              ; preds = %110, %2
  ret void, !dbg !976
}

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.zzzz* @snocString(%struct.zzzz* %0, i8* %1) #0 !dbg !977 {
  %3 = alloca %struct.zzzz*, align 8
  %4 = alloca %struct.zzzz*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct.zzzz*, align 8
  %7 = alloca %struct.zzzz*, align 8
  store %struct.zzzz* %0, %struct.zzzz** %4, align 8
  call void @llvm.dbg.declare(metadata %struct.zzzz** %4, metadata !980, metadata !DIExpression()), !dbg !981
  store i8* %1, i8** %5, align 8
  call void @llvm.dbg.declare(metadata i8** %5, metadata !982, metadata !DIExpression()), !dbg !983
  %8 = load %struct.zzzz*, %struct.zzzz** %4, align 8, !dbg !984
  %9 = icmp eq %struct.zzzz* %8, null, !dbg !986
  br i1 %9, label %10, label %25, !dbg !987

10:                                               ; preds = %2
  call void @llvm.dbg.declare(metadata %struct.zzzz** %6, metadata !988, metadata !DIExpression()), !dbg !990
  %11 = call %struct.zzzz* @mkCell(), !dbg !991
  store %struct.zzzz* %11, %struct.zzzz** %6, align 8, !dbg !990
  %12 = load i8*, i8** %5, align 8, !dbg !992
  %13 = call i64 @strlen(i8* %12) #11, !dbg !993
  %14 = add i64 5, %13, !dbg !994
  %15 = trunc i64 %14 to i32, !dbg !995
  %16 = call i8* @myMalloc(i32 %15), !dbg !996
  %17 = load %struct.zzzz*, %struct.zzzz** %6, align 8, !dbg !997
  %18 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %17, i32 0, i32 0, !dbg !998
  store i8* %16, i8** %18, align 8, !dbg !999
  %19 = load %struct.zzzz*, %struct.zzzz** %6, align 8, !dbg !1000
  %20 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %19, i32 0, i32 0, !dbg !1001
  %21 = load i8*, i8** %20, align 8, !dbg !1001
  %22 = load i8*, i8** %5, align 8, !dbg !1002
  %23 = call i8* @strcpy(i8* %21, i8* %22) #10, !dbg !1003
  %24 = load %struct.zzzz*, %struct.zzzz** %6, align 8, !dbg !1004
  store %struct.zzzz* %24, %struct.zzzz** %3, align 8, !dbg !1005
  br label %45, !dbg !1005

25:                                               ; preds = %2
  call void @llvm.dbg.declare(metadata %struct.zzzz** %7, metadata !1006, metadata !DIExpression()), !dbg !1008
  %26 = load %struct.zzzz*, %struct.zzzz** %4, align 8, !dbg !1009
  store %struct.zzzz* %26, %struct.zzzz** %7, align 8, !dbg !1008
  br label %27, !dbg !1010

27:                                               ; preds = %32, %25
  %28 = load %struct.zzzz*, %struct.zzzz** %7, align 8, !dbg !1011
  %29 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %28, i32 0, i32 1, !dbg !1012
  %30 = load %struct.zzzz*, %struct.zzzz** %29, align 8, !dbg !1012
  %31 = icmp ne %struct.zzzz* %30, null, !dbg !1013
  br i1 %31, label %32, label %36, !dbg !1010

32:                                               ; preds = %27
  %33 = load %struct.zzzz*, %struct.zzzz** %7, align 8, !dbg !1014
  %34 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %33, i32 0, i32 1, !dbg !1015
  %35 = load %struct.zzzz*, %struct.zzzz** %34, align 8, !dbg !1015
  store %struct.zzzz* %35, %struct.zzzz** %7, align 8, !dbg !1016
  br label %27, !dbg !1010, !llvm.loop !1017

36:                                               ; preds = %27
  %37 = load %struct.zzzz*, %struct.zzzz** %7, align 8, !dbg !1018
  %38 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %37, i32 0, i32 1, !dbg !1019
  %39 = load %struct.zzzz*, %struct.zzzz** %38, align 8, !dbg !1019
  %40 = load i8*, i8** %5, align 8, !dbg !1020
  %41 = call %struct.zzzz* @snocString(%struct.zzzz* %39, i8* %40), !dbg !1021
  %42 = load %struct.zzzz*, %struct.zzzz** %7, align 8, !dbg !1022
  %43 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %42, i32 0, i32 1, !dbg !1023
  store %struct.zzzz* %41, %struct.zzzz** %43, align 8, !dbg !1024
  %44 = load %struct.zzzz*, %struct.zzzz** %4, align 8, !dbg !1025
  store %struct.zzzz* %44, %struct.zzzz** %3, align 8, !dbg !1026
  br label %45, !dbg !1026

45:                                               ; preds = %36, %10
  %46 = load %struct.zzzz*, %struct.zzzz** %3, align 8, !dbg !1027
  ret %struct.zzzz* %46, !dbg !1027
}

; Function Attrs: nounwind readonly
declare dso_local i32 @strcmp(i8*, i8*) #3

; Function Attrs: nounwind readonly
declare dso_local i64 @strlen(i8*) #3

; Function Attrs: nounwind readonly
declare dso_local i8* @strstr(i8*, i8*) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal void @license() #0 !dbg !1028 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1031
  %2 = call i8* @BZ2_bzlibVersion(), !dbg !1032
  %3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([531 x i8], [531 x i8]* @.str.49, i64 0, i64 0), i8* %2), !dbg !1033
  ret void, !dbg !1034
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @usage(i8* %0) #0 !dbg !1035 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !1038, metadata !DIExpression()), !dbg !1039
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1040
  %4 = call i8* @BZ2_bzlibVersion(), !dbg !1041
  %5 = load i8*, i8** %2, align 8, !dbg !1042
  %6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([1230 x i8], [1230 x i8]* @.str.50, i64 0, i64 0), i8* %4, i8* %5), !dbg !1043
  ret void, !dbg !1044
}

; Function Attrs: noreturn nounwind
declare dso_local void @exit(i32) #4

declare dso_local i32 @fprintf(%struct._IO_FILE*, i8*, ...) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal void @redundant(i8* %0) #0 !dbg !1045 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !1046, metadata !DIExpression()), !dbg !1047
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1048
  %4 = load i8*, i8** @progName, align 8, !dbg !1049
  %5 = load i8*, i8** %2, align 8, !dbg !1050
  %6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.51, i64 0, i64 0), i8* %4, i8* %5), !dbg !1051
  ret void, !dbg !1052
}

; Function Attrs: nounwind readonly
declare dso_local i32 @strncmp(i8*, i8*, i64) #3

; Function Attrs: noinline nounwind optnone uwtable
define internal void @mySignalCatcher(i32 %0) #0 !dbg !1053 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !1054, metadata !DIExpression()), !dbg !1055
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1056
  %4 = load i8*, i8** @progName, align 8, !dbg !1057
  %5 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.52, i64 0, i64 0), i8* %4), !dbg !1058
  call void @cleanUpAndFail(i32 1) #13, !dbg !1059
  unreachable, !dbg !1059
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @compress(i8* %0) #0 !dbg !1060 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca %struct.stat, align 8
  %8 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !1061, metadata !DIExpression()), !dbg !1062
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !1063, metadata !DIExpression()), !dbg !1064
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %4, metadata !1065, metadata !DIExpression()), !dbg !1066
  call void @llvm.dbg.declare(metadata i32* %5, metadata !1067, metadata !DIExpression()), !dbg !1068
  call void @llvm.dbg.declare(metadata i32* %6, metadata !1069, metadata !DIExpression()), !dbg !1070
  call void @llvm.dbg.declare(metadata %struct.stat* %7, metadata !1071, metadata !DIExpression()), !dbg !1072
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1073
  %9 = load i8*, i8** %2, align 8, !dbg !1074
  %10 = icmp eq i8* %9, null, !dbg !1076
  br i1 %10, label %11, label %15, !dbg !1077

11:                                               ; preds = %1
  %12 = load i32, i32* @srcMode, align 4, !dbg !1078
  %13 = icmp ne i32 %12, 1, !dbg !1079
  br i1 %13, label %14, label %15, !dbg !1080

14:                                               ; preds = %11
  call void @panic(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.53, i64 0, i64 0)) #13, !dbg !1081
  unreachable, !dbg !1081

15:                                               ; preds = %11, %1
  %16 = load i32, i32* @srcMode, align 4, !dbg !1082
  switch i32 %16, label %24 [
    i32 1, label %17
    i32 3, label %18
    i32 2, label %22
  ], !dbg !1083

17:                                               ; preds = %15
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.54, i64 0, i64 0)), !dbg !1084
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i64 0, i64 0)), !dbg !1086
  br label %24, !dbg !1087

18:                                               ; preds = %15
  %19 = load i8*, i8** %2, align 8, !dbg !1088
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %19), !dbg !1089
  %20 = load i8*, i8** %2, align 8, !dbg !1090
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* %20), !dbg !1091
  %21 = call i8* @strcat(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0)) #10, !dbg !1092
  br label %24, !dbg !1093

22:                                               ; preds = %15
  %23 = load i8*, i8** %2, align 8, !dbg !1094
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %23), !dbg !1095
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i64 0, i64 0)), !dbg !1096
  br label %24, !dbg !1097

24:                                               ; preds = %15, %22, %18, %17
  %25 = load i32, i32* @srcMode, align 4, !dbg !1098
  %26 = icmp ne i32 %25, 1, !dbg !1100
  br i1 %26, label %27, label %39, !dbg !1101

27:                                               ; preds = %24
  %28 = call zeroext i8 @containsDubiousChars(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1102
  %29 = zext i8 %28 to i32, !dbg !1102
  %30 = icmp ne i32 %29, 0, !dbg !1102
  br i1 %30, label %31, label %39, !dbg !1103

31:                                               ; preds = %27
  %32 = load i8, i8* @noisy, align 1, !dbg !1104
  %33 = icmp ne i8 %32, 0, !dbg !1104
  br i1 %33, label %34, label %38, !dbg !1107

34:                                               ; preds = %31
  %35 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1108
  %36 = load i8*, i8** @progName, align 8, !dbg !1109
  %37 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %35, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.56, i64 0, i64 0), i8* %36, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1110
  br label %38, !dbg !1110

38:                                               ; preds = %34, %31
  call void @setExit(i32 1), !dbg !1111
  br label %268, !dbg !1112

39:                                               ; preds = %27, %24
  %40 = load i32, i32* @srcMode, align 4, !dbg !1113
  %41 = icmp ne i32 %40, 1, !dbg !1115
  br i1 %41, label %42, label %52, !dbg !1116

42:                                               ; preds = %39
  %43 = call zeroext i8 @fileExists(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1117
  %44 = icmp ne i8 %43, 0, !dbg !1117
  br i1 %44, label %52, label %45, !dbg !1118

45:                                               ; preds = %42
  %46 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1119
  %47 = load i8*, i8** @progName, align 8, !dbg !1121
  %48 = call i32* @__errno_location() #14, !dbg !1122
  %49 = load i32, i32* %48, align 4, !dbg !1122
  %50 = call i8* @strerror(i32 %49) #10, !dbg !1123
  %51 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %46, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.57, i64 0, i64 0), i8* %47, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %50), !dbg !1124
  call void @setExit(i32 1), !dbg !1125
  br label %268, !dbg !1126

52:                                               ; preds = %42, %39
  store i32 0, i32* %6, align 4, !dbg !1127
  br label %53, !dbg !1129

53:                                               ; preds = %76, %52
  %54 = load i32, i32* %6, align 4, !dbg !1130
  %55 = icmp slt i32 %54, 4, !dbg !1132
  br i1 %55, label %56, label %79, !dbg !1133

56:                                               ; preds = %53
  %57 = load i32, i32* %6, align 4, !dbg !1134
  %58 = sext i32 %57 to i64, !dbg !1137
  %59 = getelementptr inbounds [4 x i8*], [4 x i8*]* @zSuffix, i64 0, i64 %58, !dbg !1137
  %60 = load i8*, i8** %59, align 8, !dbg !1137
  %61 = call zeroext i8 @hasSuffix(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %60), !dbg !1138
  %62 = icmp ne i8 %61, 0, !dbg !1138
  br i1 %62, label %63, label %75, !dbg !1139

63:                                               ; preds = %56
  %64 = load i8, i8* @noisy, align 1, !dbg !1140
  %65 = icmp ne i8 %64, 0, !dbg !1140
  br i1 %65, label %66, label %74, !dbg !1143

66:                                               ; preds = %63
  %67 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1144
  %68 = load i8*, i8** @progName, align 8, !dbg !1145
  %69 = load i32, i32* %6, align 4, !dbg !1146
  %70 = sext i32 %69 to i64, !dbg !1147
  %71 = getelementptr inbounds [4 x i8*], [4 x i8*]* @zSuffix, i64 0, i64 %70, !dbg !1147
  %72 = load i8*, i8** %71, align 8, !dbg !1147
  %73 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %67, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.58, i64 0, i64 0), i8* %68, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %72), !dbg !1148
  br label %74, !dbg !1148

74:                                               ; preds = %66, %63
  call void @setExit(i32 1), !dbg !1149
  br label %268, !dbg !1150

75:                                               ; preds = %56
  br label %76, !dbg !1151

76:                                               ; preds = %75
  %77 = load i32, i32* %6, align 4, !dbg !1152
  %78 = add nsw i32 %77, 1, !dbg !1152
  store i32 %78, i32* %6, align 4, !dbg !1152
  br label %53, !dbg !1153, !llvm.loop !1154

79:                                               ; preds = %53
  %80 = load i32, i32* @srcMode, align 4, !dbg !1156
  %81 = icmp eq i32 %80, 3, !dbg !1158
  br i1 %81, label %85, label %82, !dbg !1159

82:                                               ; preds = %79
  %83 = load i32, i32* @srcMode, align 4, !dbg !1160
  %84 = icmp eq i32 %83, 2, !dbg !1161
  br i1 %84, label %85, label %96, !dbg !1162

85:                                               ; preds = %82, %79
  %86 = call i32 @stat(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), %struct.stat* %7) #10, !dbg !1163
  %87 = getelementptr inbounds %struct.stat, %struct.stat* %7, i32 0, i32 3, !dbg !1165
  %88 = load i32, i32* %87, align 8, !dbg !1165
  %89 = and i32 %88, 61440, !dbg !1165
  %90 = icmp eq i32 %89, 16384, !dbg !1165
  br i1 %90, label %91, label %95, !dbg !1167

91:                                               ; preds = %85
  %92 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1168
  %93 = load i8*, i8** @progName, align 8, !dbg !1170
  %94 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %92, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.59, i64 0, i64 0), i8* %93, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1171
  call void @setExit(i32 1), !dbg !1172
  br label %268, !dbg !1173

95:                                               ; preds = %85
  br label %96, !dbg !1174

96:                                               ; preds = %95, %82
  %97 = load i32, i32* @srcMode, align 4, !dbg !1175
  %98 = icmp eq i32 %97, 3, !dbg !1177
  br i1 %98, label %99, label %114, !dbg !1178

99:                                               ; preds = %96
  %100 = load i8, i8* @forceOverwrite, align 1, !dbg !1179
  %101 = icmp ne i8 %100, 0, !dbg !1179
  br i1 %101, label %114, label %102, !dbg !1180

102:                                              ; preds = %99
  %103 = call zeroext i8 @notAStandardFile(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1181
  %104 = zext i8 %103 to i32, !dbg !1181
  %105 = icmp ne i32 %104, 0, !dbg !1181
  br i1 %105, label %106, label %114, !dbg !1182

106:                                              ; preds = %102
  %107 = load i8, i8* @noisy, align 1, !dbg !1183
  %108 = icmp ne i8 %107, 0, !dbg !1183
  br i1 %108, label %109, label %113, !dbg !1186

109:                                              ; preds = %106
  %110 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1187
  %111 = load i8*, i8** @progName, align 8, !dbg !1188
  %112 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %110, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.60, i64 0, i64 0), i8* %111, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1189
  br label %113, !dbg !1189

113:                                              ; preds = %109, %106
  call void @setExit(i32 1), !dbg !1190
  br label %268, !dbg !1191

114:                                              ; preds = %102, %99, %96
  %115 = load i32, i32* @srcMode, align 4, !dbg !1192
  %116 = icmp eq i32 %115, 3, !dbg !1194
  br i1 %116, label %117, label %131, !dbg !1195

117:                                              ; preds = %114
  %118 = call zeroext i8 @fileExists(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1196
  %119 = zext i8 %118 to i32, !dbg !1196
  %120 = icmp ne i32 %119, 0, !dbg !1196
  br i1 %120, label %121, label %131, !dbg !1197

121:                                              ; preds = %117
  %122 = load i8, i8* @forceOverwrite, align 1, !dbg !1198
  %123 = icmp ne i8 %122, 0, !dbg !1198
  br i1 %123, label %124, label %126, !dbg !1201

124:                                              ; preds = %121
  %125 = call i32 @remove(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)) #10, !dbg !1202
  br label %130, !dbg !1204

126:                                              ; preds = %121
  %127 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1205
  %128 = load i8*, i8** @progName, align 8, !dbg !1207
  %129 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %127, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.61, i64 0, i64 0), i8* %128, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1208
  call void @setExit(i32 1), !dbg !1209
  br label %268, !dbg !1210

130:                                              ; preds = %124
  br label %131, !dbg !1211

131:                                              ; preds = %130, %117, %114
  %132 = load i32, i32* @srcMode, align 4, !dbg !1212
  %133 = icmp eq i32 %132, 3, !dbg !1214
  br i1 %133, label %134, label %149, !dbg !1215

134:                                              ; preds = %131
  %135 = load i8, i8* @forceOverwrite, align 1, !dbg !1216
  %136 = icmp ne i8 %135, 0, !dbg !1216
  br i1 %136, label %149, label %137, !dbg !1217

137:                                              ; preds = %134
  %138 = call i32 @countHardLinks(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1218
  store i32 %138, i32* %5, align 4, !dbg !1219
  %139 = icmp sgt i32 %138, 0, !dbg !1220
  br i1 %139, label %140, label %149, !dbg !1221

140:                                              ; preds = %137
  %141 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1222
  %142 = load i8*, i8** @progName, align 8, !dbg !1224
  %143 = load i32, i32* %5, align 4, !dbg !1225
  %144 = load i32, i32* %5, align 4, !dbg !1226
  %145 = icmp sgt i32 %144, 1, !dbg !1227
  %146 = zext i1 %145 to i64, !dbg !1226
  %147 = select i1 %145, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.63, i64 0, i64 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.4, i64 0, i64 0), !dbg !1226
  %148 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %141, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.62, i64 0, i64 0), i8* %142, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i32 %143, i8* %147), !dbg !1228
  call void @setExit(i32 1), !dbg !1229
  br label %268, !dbg !1230

149:                                              ; preds = %137, %134, %131
  %150 = load i32, i32* @srcMode, align 4, !dbg !1231
  %151 = icmp eq i32 %150, 3, !dbg !1233
  br i1 %151, label %152, label %153, !dbg !1234

152:                                              ; preds = %149
  call void @saveInputFileMetaInfo(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1235
  br label %153, !dbg !1237

153:                                              ; preds = %152, %149
  %154 = load i32, i32* @srcMode, align 4, !dbg !1238
  switch i32 %154, label %238 [
    i32 1, label %155
    i32 2, label %171
    i32 3, label %203
  ], !dbg !1239

155:                                              ; preds = %153
  %156 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1240
  store %struct._IO_FILE* %156, %struct._IO_FILE** %3, align 8, !dbg !1242
  %157 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1243
  store %struct._IO_FILE* %157, %struct._IO_FILE** %4, align 8, !dbg !1244
  %158 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1245
  %159 = call i32 @fileno(%struct._IO_FILE* %158) #10, !dbg !1247
  %160 = call i32 @isatty(i32 %159) #10, !dbg !1248
  %161 = icmp ne i32 %160, 0, !dbg !1248
  br i1 %161, label %162, label %170, !dbg !1249

162:                                              ; preds = %155
  %163 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1250
  %164 = load i8*, i8** @progName, align 8, !dbg !1252
  %165 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %163, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.64, i64 0, i64 0), i8* %164), !dbg !1253
  %166 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1254
  %167 = load i8*, i8** @progName, align 8, !dbg !1255
  %168 = load i8*, i8** @progName, align 8, !dbg !1256
  %169 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %166, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.65, i64 0, i64 0), i8* %167, i8* %168), !dbg !1257
  call void @setExit(i32 1), !dbg !1258
  br label %268, !dbg !1259

170:                                              ; preds = %155
  br label %239, !dbg !1260

171:                                              ; preds = %153
  %172 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !1261
  store %struct._IO_FILE* %172, %struct._IO_FILE** %3, align 8, !dbg !1262
  %173 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1263
  store %struct._IO_FILE* %173, %struct._IO_FILE** %4, align 8, !dbg !1264
  %174 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1265
  %175 = call i32 @fileno(%struct._IO_FILE* %174) #10, !dbg !1267
  %176 = call i32 @isatty(i32 %175) #10, !dbg !1268
  %177 = icmp ne i32 %176, 0, !dbg !1268
  br i1 %177, label %178, label %192, !dbg !1269

178:                                              ; preds = %171
  %179 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1270
  %180 = load i8*, i8** @progName, align 8, !dbg !1272
  %181 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %179, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.64, i64 0, i64 0), i8* %180), !dbg !1273
  %182 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1274
  %183 = load i8*, i8** @progName, align 8, !dbg !1275
  %184 = load i8*, i8** @progName, align 8, !dbg !1276
  %185 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %182, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.65, i64 0, i64 0), i8* %183, i8* %184), !dbg !1277
  %186 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1278
  %187 = icmp ne %struct._IO_FILE* %186, null, !dbg !1280
  br i1 %187, label %188, label %191, !dbg !1281

188:                                              ; preds = %178
  %189 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1282
  %190 = call i32 @fclose(%struct._IO_FILE* %189), !dbg !1283
  br label %191, !dbg !1283

191:                                              ; preds = %188, %178
  call void @setExit(i32 1), !dbg !1284
  br label %268, !dbg !1285

192:                                              ; preds = %171
  %193 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1286
  %194 = icmp eq %struct._IO_FILE* %193, null, !dbg !1288
  br i1 %194, label %195, label %202, !dbg !1289

195:                                              ; preds = %192
  %196 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1290
  %197 = load i8*, i8** @progName, align 8, !dbg !1292
  %198 = call i32* @__errno_location() #14, !dbg !1293
  %199 = load i32, i32* %198, align 4, !dbg !1293
  %200 = call i8* @strerror(i32 %199) #10, !dbg !1294
  %201 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %196, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.57, i64 0, i64 0), i8* %197, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %200), !dbg !1295
  call void @setExit(i32 1), !dbg !1296
  br label %268, !dbg !1297

202:                                              ; preds = %192
  br label %239, !dbg !1298

203:                                              ; preds = %153
  %204 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !1299
  store %struct._IO_FILE* %204, %struct._IO_FILE** %3, align 8, !dbg !1300
  %205 = call %struct._IO_FILE* @fopen_output_safely(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.67, i64 0, i64 0)), !dbg !1301
  store %struct._IO_FILE* %205, %struct._IO_FILE** %4, align 8, !dbg !1302
  %206 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1303
  %207 = icmp eq %struct._IO_FILE* %206, null, !dbg !1305
  br i1 %207, label %208, label %221, !dbg !1306

208:                                              ; preds = %203
  %209 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1307
  %210 = load i8*, i8** @progName, align 8, !dbg !1309
  %211 = call i32* @__errno_location() #14, !dbg !1310
  %212 = load i32, i32* %211, align 4, !dbg !1310
  %213 = call i8* @strerror(i32 %212) #10, !dbg !1311
  %214 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %209, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.68, i64 0, i64 0), i8* %210, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* %213), !dbg !1312
  %215 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1313
  %216 = icmp ne %struct._IO_FILE* %215, null, !dbg !1315
  br i1 %216, label %217, label %220, !dbg !1316

217:                                              ; preds = %208
  %218 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1317
  %219 = call i32 @fclose(%struct._IO_FILE* %218), !dbg !1318
  br label %220, !dbg !1318

220:                                              ; preds = %217, %208
  call void @setExit(i32 1), !dbg !1319
  br label %268, !dbg !1320

221:                                              ; preds = %203
  %222 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1321
  %223 = icmp eq %struct._IO_FILE* %222, null, !dbg !1323
  br i1 %223, label %224, label %237, !dbg !1324

224:                                              ; preds = %221
  %225 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1325
  %226 = load i8*, i8** @progName, align 8, !dbg !1327
  %227 = call i32* @__errno_location() #14, !dbg !1328
  %228 = load i32, i32* %227, align 4, !dbg !1328
  %229 = call i8* @strerror(i32 %228) #10, !dbg !1329
  %230 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %225, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.57, i64 0, i64 0), i8* %226, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %229), !dbg !1330
  %231 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1331
  %232 = icmp ne %struct._IO_FILE* %231, null, !dbg !1333
  br i1 %232, label %233, label %236, !dbg !1334

233:                                              ; preds = %224
  %234 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1335
  %235 = call i32 @fclose(%struct._IO_FILE* %234), !dbg !1336
  br label %236, !dbg !1336

236:                                              ; preds = %233, %224
  call void @setExit(i32 1), !dbg !1337
  br label %268, !dbg !1338

237:                                              ; preds = %221
  br label %239, !dbg !1339

238:                                              ; preds = %153
  call void @panic(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.69, i64 0, i64 0)) #13, !dbg !1340
  unreachable, !dbg !1340

239:                                              ; preds = %237, %202, %170
  %240 = load i32, i32* @verbosity, align 4, !dbg !1341
  %241 = icmp sge i32 %240, 1, !dbg !1343
  br i1 %241, label %242, label %247, !dbg !1344

242:                                              ; preds = %239
  %243 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1345
  %244 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %243, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.70, i64 0, i64 0), i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1347
  call void @pad(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1348
  %245 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1349
  %246 = call i32 @fflush(%struct._IO_FILE* %245), !dbg !1350
  br label %247, !dbg !1351

247:                                              ; preds = %242, %239
  %248 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1352
  store %struct._IO_FILE* %248, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1353
  store i8 1, i8* @deleteOutputOnInterrupt, align 1, !dbg !1354
  %249 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1355
  %250 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1356
  call void @compressStream(%struct._IO_FILE* %249, %struct._IO_FILE* %250), !dbg !1357
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1358
  %251 = load i32, i32* @srcMode, align 4, !dbg !1359
  %252 = icmp eq i32 %251, 3, !dbg !1361
  br i1 %252, label %253, label %267, !dbg !1362

253:                                              ; preds = %247
  call void @applySavedTimeInfoToOutputFile(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1363
  %254 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1365
  %255 = icmp ne %struct._IO_FILE* %254, null, !dbg !1367
  br i1 %255, label %256, label %257, !dbg !1368

256:                                              ; preds = %253
  call void @logCompressSize(i32 1034), !dbg !1369
  br label %257, !dbg !1371

257:                                              ; preds = %256, %253
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1372
  %258 = load i8, i8* @keepInputFiles, align 1, !dbg !1373
  %259 = icmp ne i8 %258, 0, !dbg !1373
  br i1 %259, label %266, label %260, !dbg !1375

260:                                              ; preds = %257
  call void @llvm.dbg.declare(metadata i32* %8, metadata !1376, metadata !DIExpression()), !dbg !1378
  %261 = call i32 @remove(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)) #10, !dbg !1379
  store i32 %261, i32* %8, align 4, !dbg !1378
  %262 = load i32, i32* %8, align 4, !dbg !1380
  %263 = icmp ne i32 %262, 0, !dbg !1380
  br i1 %263, label %264, label %265, !dbg !1383

264:                                              ; preds = %260
  call void @ioError() #13, !dbg !1380
  unreachable, !dbg !1380

265:                                              ; preds = %260
  br label %266, !dbg !1384

266:                                              ; preds = %265, %257
  br label %267, !dbg !1385

267:                                              ; preds = %266, %247
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1386
  br label %268, !dbg !1387

268:                                              ; preds = %267, %236, %220, %195, %191, %162, %140, %126, %113, %91, %74, %45, %38
  ret void, !dbg !1387
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @uncompress(i8* %0) #0 !dbg !1388 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i8, align 1
  %8 = alloca i8, align 1
  %9 = alloca %struct.stat, align 8
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !1389, metadata !DIExpression()), !dbg !1390
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !1391, metadata !DIExpression()), !dbg !1392
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %4, metadata !1393, metadata !DIExpression()), !dbg !1394
  call void @llvm.dbg.declare(metadata i32* %5, metadata !1395, metadata !DIExpression()), !dbg !1396
  call void @llvm.dbg.declare(metadata i32* %6, metadata !1397, metadata !DIExpression()), !dbg !1398
  call void @llvm.dbg.declare(metadata i8* %7, metadata !1399, metadata !DIExpression()), !dbg !1400
  call void @llvm.dbg.declare(metadata i8* %8, metadata !1401, metadata !DIExpression()), !dbg !1402
  call void @llvm.dbg.declare(metadata %struct.stat* %9, metadata !1403, metadata !DIExpression()), !dbg !1404
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1405
  %12 = load i8*, i8** %2, align 8, !dbg !1406
  %13 = icmp eq i8* %12, null, !dbg !1408
  br i1 %13, label %14, label %18, !dbg !1409

14:                                               ; preds = %1
  %15 = load i32, i32* @srcMode, align 4, !dbg !1410
  %16 = icmp ne i32 %15, 1, !dbg !1411
  br i1 %16, label %17, label %18, !dbg !1412

17:                                               ; preds = %14
  call void @panic(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.82, i64 0, i64 0)) #13, !dbg !1413
  unreachable, !dbg !1413

18:                                               ; preds = %14, %1
  store i8 0, i8* %8, align 1, !dbg !1414
  %19 = load i32, i32* @srcMode, align 4, !dbg !1415
  switch i32 %19, label %47 [
    i32 1, label %20
    i32 3, label %21
    i32 2, label %45
  ], !dbg !1416

20:                                               ; preds = %18
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.54, i64 0, i64 0)), !dbg !1417
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i64 0, i64 0)), !dbg !1419
  br label %47, !dbg !1420

21:                                               ; preds = %18
  %22 = load i8*, i8** %2, align 8, !dbg !1421
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %22), !dbg !1422
  %23 = load i8*, i8** %2, align 8, !dbg !1423
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* %23), !dbg !1424
  store i32 0, i32* %6, align 4, !dbg !1425
  br label %24, !dbg !1427

24:                                               ; preds = %40, %21
  %25 = load i32, i32* %6, align 4, !dbg !1428
  %26 = icmp slt i32 %25, 4, !dbg !1430
  br i1 %26, label %27, label %43, !dbg !1431

27:                                               ; preds = %24
  %28 = load i32, i32* %6, align 4, !dbg !1432
  %29 = sext i32 %28 to i64, !dbg !1434
  %30 = getelementptr inbounds [4 x i8*], [4 x i8*]* @zSuffix, i64 0, i64 %29, !dbg !1434
  %31 = load i8*, i8** %30, align 8, !dbg !1434
  %32 = load i32, i32* %6, align 4, !dbg !1435
  %33 = sext i32 %32 to i64, !dbg !1436
  %34 = getelementptr inbounds [4 x i8*], [4 x i8*]* @unzSuffix, i64 0, i64 %33, !dbg !1436
  %35 = load i8*, i8** %34, align 8, !dbg !1436
  %36 = call zeroext i8 @mapSuffix(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* %31, i8* %35), !dbg !1437
  %37 = icmp ne i8 %36, 0, !dbg !1437
  br i1 %37, label %38, label %39, !dbg !1438

38:                                               ; preds = %27
  br label %48, !dbg !1439

39:                                               ; preds = %27
  br label %40, !dbg !1440

40:                                               ; preds = %39
  %41 = load i32, i32* %6, align 4, !dbg !1441
  %42 = add nsw i32 %41, 1, !dbg !1441
  store i32 %42, i32* %6, align 4, !dbg !1441
  br label %24, !dbg !1442, !llvm.loop !1443

43:                                               ; preds = %24
  store i8 1, i8* %8, align 1, !dbg !1445
  %44 = call i8* @strcat(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.83, i64 0, i64 0)) #10, !dbg !1446
  br label %47, !dbg !1447

45:                                               ; preds = %18
  %46 = load i8*, i8** %2, align 8, !dbg !1448
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %46), !dbg !1449
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.55, i64 0, i64 0)), !dbg !1450
  br label %47, !dbg !1451

47:                                               ; preds = %18, %45, %43, %20
  br label %48, !dbg !1452

48:                                               ; preds = %47, %38
  call void @llvm.dbg.label(metadata !1453), !dbg !1454
  %49 = load i32, i32* @srcMode, align 4, !dbg !1455
  %50 = icmp ne i32 %49, 1, !dbg !1457
  br i1 %50, label %51, label %63, !dbg !1458

51:                                               ; preds = %48
  %52 = call zeroext i8 @containsDubiousChars(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1459
  %53 = zext i8 %52 to i32, !dbg !1459
  %54 = icmp ne i32 %53, 0, !dbg !1459
  br i1 %54, label %55, label %63, !dbg !1460

55:                                               ; preds = %51
  %56 = load i8, i8* @noisy, align 1, !dbg !1461
  %57 = icmp ne i8 %56, 0, !dbg !1461
  br i1 %57, label %58, label %62, !dbg !1464

58:                                               ; preds = %55
  %59 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1465
  %60 = load i8*, i8** @progName, align 8, !dbg !1466
  %61 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %59, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.56, i64 0, i64 0), i8* %60, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1467
  br label %62, !dbg !1467

62:                                               ; preds = %58, %55
  call void @setExit(i32 1), !dbg !1468
  br label %294, !dbg !1469

63:                                               ; preds = %51, %48
  %64 = load i32, i32* @srcMode, align 4, !dbg !1470
  %65 = icmp ne i32 %64, 1, !dbg !1472
  br i1 %65, label %66, label %76, !dbg !1473

66:                                               ; preds = %63
  %67 = call zeroext i8 @fileExists(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1474
  %68 = icmp ne i8 %67, 0, !dbg !1474
  br i1 %68, label %76, label %69, !dbg !1475

69:                                               ; preds = %66
  %70 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1476
  %71 = load i8*, i8** @progName, align 8, !dbg !1478
  %72 = call i32* @__errno_location() #14, !dbg !1479
  %73 = load i32, i32* %72, align 4, !dbg !1479
  %74 = call i8* @strerror(i32 %73) #10, !dbg !1480
  %75 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %70, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.57, i64 0, i64 0), i8* %71, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %74), !dbg !1481
  call void @setExit(i32 1), !dbg !1482
  br label %294, !dbg !1483

76:                                               ; preds = %66, %63
  %77 = load i32, i32* @srcMode, align 4, !dbg !1484
  %78 = icmp eq i32 %77, 3, !dbg !1486
  br i1 %78, label %82, label %79, !dbg !1487

79:                                               ; preds = %76
  %80 = load i32, i32* @srcMode, align 4, !dbg !1488
  %81 = icmp eq i32 %80, 2, !dbg !1489
  br i1 %81, label %82, label %93, !dbg !1490

82:                                               ; preds = %79, %76
  %83 = call i32 @stat(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), %struct.stat* %9) #10, !dbg !1491
  %84 = getelementptr inbounds %struct.stat, %struct.stat* %9, i32 0, i32 3, !dbg !1493
  %85 = load i32, i32* %84, align 8, !dbg !1493
  %86 = and i32 %85, 61440, !dbg !1493
  %87 = icmp eq i32 %86, 16384, !dbg !1493
  br i1 %87, label %88, label %92, !dbg !1495

88:                                               ; preds = %82
  %89 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1496
  %90 = load i8*, i8** @progName, align 8, !dbg !1498
  %91 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %89, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.59, i64 0, i64 0), i8* %90, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1499
  call void @setExit(i32 1), !dbg !1500
  br label %294, !dbg !1501

92:                                               ; preds = %82
  br label %93, !dbg !1502

93:                                               ; preds = %92, %79
  %94 = load i32, i32* @srcMode, align 4, !dbg !1503
  %95 = icmp eq i32 %94, 3, !dbg !1505
  br i1 %95, label %96, label %111, !dbg !1506

96:                                               ; preds = %93
  %97 = load i8, i8* @forceOverwrite, align 1, !dbg !1507
  %98 = icmp ne i8 %97, 0, !dbg !1507
  br i1 %98, label %111, label %99, !dbg !1508

99:                                               ; preds = %96
  %100 = call zeroext i8 @notAStandardFile(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1509
  %101 = zext i8 %100 to i32, !dbg !1509
  %102 = icmp ne i32 %101, 0, !dbg !1509
  br i1 %102, label %103, label %111, !dbg !1510

103:                                              ; preds = %99
  %104 = load i8, i8* @noisy, align 1, !dbg !1511
  %105 = icmp ne i8 %104, 0, !dbg !1511
  br i1 %105, label %106, label %110, !dbg !1514

106:                                              ; preds = %103
  %107 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1515
  %108 = load i8*, i8** @progName, align 8, !dbg !1516
  %109 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %107, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.60, i64 0, i64 0), i8* %108, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1517
  br label %110, !dbg !1517

110:                                              ; preds = %106, %103
  call void @setExit(i32 1), !dbg !1518
  br label %294, !dbg !1519

111:                                              ; preds = %99, %96, %93
  %112 = load i8, i8* %8, align 1, !dbg !1520
  %113 = icmp ne i8 %112, 0, !dbg !1520
  br i1 %113, label %114, label %122, !dbg !1522

114:                                              ; preds = %111
  %115 = load i8, i8* @noisy, align 1, !dbg !1523
  %116 = icmp ne i8 %115, 0, !dbg !1523
  br i1 %116, label %117, label %121, !dbg !1526

117:                                              ; preds = %114
  %118 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1527
  %119 = load i8*, i8** @progName, align 8, !dbg !1528
  %120 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %118, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.84, i64 0, i64 0), i8* %119, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1529
  br label %121, !dbg !1529

121:                                              ; preds = %117, %114
  br label %122, !dbg !1530

122:                                              ; preds = %121, %111
  %123 = load i32, i32* @srcMode, align 4, !dbg !1531
  %124 = icmp eq i32 %123, 3, !dbg !1533
  br i1 %124, label %125, label %139, !dbg !1534

125:                                              ; preds = %122
  %126 = call zeroext i8 @fileExists(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1535
  %127 = zext i8 %126 to i32, !dbg !1535
  %128 = icmp ne i32 %127, 0, !dbg !1535
  br i1 %128, label %129, label %139, !dbg !1536

129:                                              ; preds = %125
  %130 = load i8, i8* @forceOverwrite, align 1, !dbg !1537
  %131 = icmp ne i8 %130, 0, !dbg !1537
  br i1 %131, label %132, label %134, !dbg !1540

132:                                              ; preds = %129
  %133 = call i32 @remove(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)) #10, !dbg !1541
  br label %138, !dbg !1543

134:                                              ; preds = %129
  %135 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1544
  %136 = load i8*, i8** @progName, align 8, !dbg !1546
  %137 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %135, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.61, i64 0, i64 0), i8* %136, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1547
  call void @setExit(i32 1), !dbg !1548
  br label %294, !dbg !1549

138:                                              ; preds = %132
  br label %139, !dbg !1550

139:                                              ; preds = %138, %125, %122
  %140 = load i32, i32* @srcMode, align 4, !dbg !1551
  %141 = icmp eq i32 %140, 3, !dbg !1553
  br i1 %141, label %142, label %157, !dbg !1554

142:                                              ; preds = %139
  %143 = load i8, i8* @forceOverwrite, align 1, !dbg !1555
  %144 = icmp ne i8 %143, 0, !dbg !1555
  br i1 %144, label %157, label %145, !dbg !1556

145:                                              ; preds = %142
  %146 = call i32 @countHardLinks(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1557
  store i32 %146, i32* %5, align 4, !dbg !1558
  %147 = icmp sgt i32 %146, 0, !dbg !1559
  br i1 %147, label %148, label %157, !dbg !1560

148:                                              ; preds = %145
  %149 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1561
  %150 = load i8*, i8** @progName, align 8, !dbg !1563
  %151 = load i32, i32* %5, align 4, !dbg !1564
  %152 = load i32, i32* %5, align 4, !dbg !1565
  %153 = icmp sgt i32 %152, 1, !dbg !1566
  %154 = zext i1 %153 to i64, !dbg !1565
  %155 = select i1 %153, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.63, i64 0, i64 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.4, i64 0, i64 0), !dbg !1565
  %156 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %149, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.62, i64 0, i64 0), i8* %150, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i32 %151, i8* %155), !dbg !1567
  call void @setExit(i32 1), !dbg !1568
  br label %294, !dbg !1569

157:                                              ; preds = %145, %142, %139
  %158 = load i32, i32* @srcMode, align 4, !dbg !1570
  %159 = icmp eq i32 %158, 3, !dbg !1572
  br i1 %159, label %160, label %161, !dbg !1573

160:                                              ; preds = %157
  call void @saveInputFileMetaInfo(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1574
  br label %161, !dbg !1576

161:                                              ; preds = %160, %157
  %162 = load i32, i32* @srcMode, align 4, !dbg !1577
  switch i32 %162, label %233 [
    i32 1, label %163
    i32 2, label %179
    i32 3, label %198
  ], !dbg !1578

163:                                              ; preds = %161
  %164 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1579
  store %struct._IO_FILE* %164, %struct._IO_FILE** %3, align 8, !dbg !1581
  %165 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1582
  store %struct._IO_FILE* %165, %struct._IO_FILE** %4, align 8, !dbg !1583
  %166 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1584
  %167 = call i32 @fileno(%struct._IO_FILE* %166) #10, !dbg !1586
  %168 = call i32 @isatty(i32 %167) #10, !dbg !1587
  %169 = icmp ne i32 %168, 0, !dbg !1587
  br i1 %169, label %170, label %178, !dbg !1588

170:                                              ; preds = %163
  %171 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1589
  %172 = load i8*, i8** @progName, align 8, !dbg !1591
  %173 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %171, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.85, i64 0, i64 0), i8* %172), !dbg !1592
  %174 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1593
  %175 = load i8*, i8** @progName, align 8, !dbg !1594
  %176 = load i8*, i8** @progName, align 8, !dbg !1595
  %177 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %174, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.65, i64 0, i64 0), i8* %175, i8* %176), !dbg !1596
  call void @setExit(i32 1), !dbg !1597
  br label %294, !dbg !1598

178:                                              ; preds = %163
  br label %234, !dbg !1599

179:                                              ; preds = %161
  %180 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !1600
  store %struct._IO_FILE* %180, %struct._IO_FILE** %3, align 8, !dbg !1601
  %181 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1602
  store %struct._IO_FILE* %181, %struct._IO_FILE** %4, align 8, !dbg !1603
  %182 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1604
  %183 = icmp eq %struct._IO_FILE* %182, null, !dbg !1606
  br i1 %183, label %184, label %197, !dbg !1607

184:                                              ; preds = %179
  %185 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1608
  %186 = load i8*, i8** @progName, align 8, !dbg !1610
  %187 = call i32* @__errno_location() #14, !dbg !1611
  %188 = load i32, i32* %187, align 4, !dbg !1611
  %189 = call i8* @strerror(i32 %188) #10, !dbg !1612
  %190 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %185, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.86, i64 0, i64 0), i8* %186, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %189), !dbg !1613
  %191 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1614
  %192 = icmp ne %struct._IO_FILE* %191, null, !dbg !1616
  br i1 %192, label %193, label %196, !dbg !1617

193:                                              ; preds = %184
  %194 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1618
  %195 = call i32 @fclose(%struct._IO_FILE* %194), !dbg !1619
  br label %196, !dbg !1619

196:                                              ; preds = %193, %184
  call void @setExit(i32 1), !dbg !1620
  br label %294, !dbg !1621

197:                                              ; preds = %179
  br label %234, !dbg !1622

198:                                              ; preds = %161
  %199 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !1623
  store %struct._IO_FILE* %199, %struct._IO_FILE** %3, align 8, !dbg !1624
  %200 = call %struct._IO_FILE* @fopen_output_safely(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.67, i64 0, i64 0)), !dbg !1625
  store %struct._IO_FILE* %200, %struct._IO_FILE** %4, align 8, !dbg !1626
  %201 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1627
  %202 = icmp eq %struct._IO_FILE* %201, null, !dbg !1629
  br i1 %202, label %203, label %216, !dbg !1630

203:                                              ; preds = %198
  %204 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1631
  %205 = load i8*, i8** @progName, align 8, !dbg !1633
  %206 = call i32* @__errno_location() #14, !dbg !1634
  %207 = load i32, i32* %206, align 4, !dbg !1634
  %208 = call i8* @strerror(i32 %207) #10, !dbg !1635
  %209 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %204, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.68, i64 0, i64 0), i8* %205, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* %208), !dbg !1636
  %210 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1637
  %211 = icmp ne %struct._IO_FILE* %210, null, !dbg !1639
  br i1 %211, label %212, label %215, !dbg !1640

212:                                              ; preds = %203
  %213 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1641
  %214 = call i32 @fclose(%struct._IO_FILE* %213), !dbg !1642
  br label %215, !dbg !1642

215:                                              ; preds = %212, %203
  call void @setExit(i32 1), !dbg !1643
  br label %294, !dbg !1644

216:                                              ; preds = %198
  %217 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1645
  %218 = icmp eq %struct._IO_FILE* %217, null, !dbg !1647
  br i1 %218, label %219, label %232, !dbg !1648

219:                                              ; preds = %216
  %220 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1649
  %221 = load i8*, i8** @progName, align 8, !dbg !1651
  %222 = call i32* @__errno_location() #14, !dbg !1652
  %223 = load i32, i32* %222, align 4, !dbg !1652
  %224 = call i8* @strerror(i32 %223) #10, !dbg !1653
  %225 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %220, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.57, i64 0, i64 0), i8* %221, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %224), !dbg !1654
  %226 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1655
  %227 = icmp ne %struct._IO_FILE* %226, null, !dbg !1657
  br i1 %227, label %228, label %231, !dbg !1658

228:                                              ; preds = %219
  %229 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1659
  %230 = call i32 @fclose(%struct._IO_FILE* %229), !dbg !1660
  br label %231, !dbg !1660

231:                                              ; preds = %228, %219
  call void @setExit(i32 1), !dbg !1661
  br label %294, !dbg !1662

232:                                              ; preds = %216
  br label %234, !dbg !1663

233:                                              ; preds = %161
  call void @panic(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.87, i64 0, i64 0)) #13, !dbg !1664
  unreachable, !dbg !1664

234:                                              ; preds = %232, %197, %178
  %235 = load i32, i32* @verbosity, align 4, !dbg !1665
  %236 = icmp sge i32 %235, 1, !dbg !1667
  br i1 %236, label %237, label %242, !dbg !1668

237:                                              ; preds = %234
  %238 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1669
  %239 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %238, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.70, i64 0, i64 0), i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1671
  call void @pad(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1672
  %240 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1673
  %241 = call i32 @fflush(%struct._IO_FILE* %240), !dbg !1674
  br label %242, !dbg !1675

242:                                              ; preds = %237, %234
  %243 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1676
  store %struct._IO_FILE* %243, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1677
  store i8 1, i8* @deleteOutputOnInterrupt, align 1, !dbg !1678
  %244 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1679
  %245 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !1680
  %246 = call zeroext i8 @uncompressStream(%struct._IO_FILE* %244, %struct._IO_FILE* %245), !dbg !1681
  store i8 %246, i8* %7, align 1, !dbg !1682
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1683
  %247 = load i8, i8* %7, align 1, !dbg !1684
  %248 = icmp ne i8 %247, 0, !dbg !1684
  br i1 %248, label %249, label %263, !dbg !1686

249:                                              ; preds = %242
  %250 = load i32, i32* @srcMode, align 4, !dbg !1687
  %251 = icmp eq i32 %250, 3, !dbg !1690
  br i1 %251, label %252, label %262, !dbg !1691

252:                                              ; preds = %249
  call void @applySavedTimeInfoToOutputFile(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1692
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1694
  %253 = load i8, i8* @keepInputFiles, align 1, !dbg !1695
  %254 = icmp ne i8 %253, 0, !dbg !1695
  br i1 %254, label %261, label %255, !dbg !1697

255:                                              ; preds = %252
  call void @llvm.dbg.declare(metadata i32* %10, metadata !1698, metadata !DIExpression()), !dbg !1700
  %256 = call i32 @remove(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)) #10, !dbg !1701
  store i32 %256, i32* %10, align 4, !dbg !1700
  %257 = load i32, i32* %10, align 4, !dbg !1702
  %258 = icmp ne i32 %257, 0, !dbg !1702
  br i1 %258, label %259, label %260, !dbg !1705

259:                                              ; preds = %255
  call void @ioError() #13, !dbg !1702
  unreachable, !dbg !1702

260:                                              ; preds = %255
  br label %261, !dbg !1706

261:                                              ; preds = %260, %252
  br label %262, !dbg !1707

262:                                              ; preds = %261, %249
  br label %273, !dbg !1708

263:                                              ; preds = %242
  store i8 1, i8* @unzFailsExist, align 1, !dbg !1709
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1711
  %264 = load i32, i32* @srcMode, align 4, !dbg !1712
  %265 = icmp eq i32 %264, 3, !dbg !1714
  br i1 %265, label %266, label %272, !dbg !1715

266:                                              ; preds = %263
  call void @llvm.dbg.declare(metadata i32* %11, metadata !1716, metadata !DIExpression()), !dbg !1718
  %267 = call i32 @remove(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)) #10, !dbg !1719
  store i32 %267, i32* %11, align 4, !dbg !1718
  %268 = load i32, i32* %11, align 4, !dbg !1720
  %269 = icmp ne i32 %268, 0, !dbg !1720
  br i1 %269, label %270, label %271, !dbg !1723

270:                                              ; preds = %266
  call void @ioError() #13, !dbg !1720
  unreachable, !dbg !1720

271:                                              ; preds = %266
  br label %272, !dbg !1724

272:                                              ; preds = %271, %263
  br label %273

273:                                              ; preds = %272, %262
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1725
  %274 = load i8, i8* %7, align 1, !dbg !1726
  %275 = icmp ne i8 %274, 0, !dbg !1726
  br i1 %275, label %276, label %283, !dbg !1728

276:                                              ; preds = %273
  %277 = load i32, i32* @verbosity, align 4, !dbg !1729
  %278 = icmp sge i32 %277, 1, !dbg !1732
  br i1 %278, label %279, label %282, !dbg !1733

279:                                              ; preds = %276
  %280 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1734
  %281 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %280, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.88, i64 0, i64 0)), !dbg !1735
  br label %282, !dbg !1735

282:                                              ; preds = %279, %276
  br label %294, !dbg !1736

283:                                              ; preds = %273
  call void @setExit(i32 2), !dbg !1737
  %284 = load i32, i32* @verbosity, align 4, !dbg !1739
  %285 = icmp sge i32 %284, 1, !dbg !1741
  br i1 %285, label %286, label %289, !dbg !1742

286:                                              ; preds = %283
  %287 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1743
  %288 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %287, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.89, i64 0, i64 0)), !dbg !1744
  br label %293, !dbg !1744

289:                                              ; preds = %283
  %290 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1745
  %291 = load i8*, i8** @progName, align 8, !dbg !1746
  %292 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %290, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.90, i64 0, i64 0), i8* %291, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1747
  br label %293

293:                                              ; preds = %289, %286
  br label %294

294:                                              ; preds = %62, %69, %88, %110, %134, %148, %170, %196, %215, %231, %293, %282
  ret void, !dbg !1748
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @setExit(i32 %0) #0 !dbg !1749 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !1752, metadata !DIExpression()), !dbg !1753
  %3 = load i32, i32* %2, align 4, !dbg !1754
  %4 = load i32, i32* @exitValue, align 4, !dbg !1756
  %5 = icmp sgt i32 %3, %4, !dbg !1757
  br i1 %5, label %6, label %8, !dbg !1758

6:                                                ; preds = %1
  %7 = load i32, i32* %2, align 4, !dbg !1759
  store i32 %7, i32* @exitValue, align 4, !dbg !1760
  br label %8, !dbg !1761

8:                                                ; preds = %6, %1
  ret void, !dbg !1762
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @testf(i8* %0) #0 !dbg !1763 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca i8, align 1
  %5 = alloca %struct.stat, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !1764, metadata !DIExpression()), !dbg !1765
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !1766, metadata !DIExpression()), !dbg !1767
  call void @llvm.dbg.declare(metadata i8* %4, metadata !1768, metadata !DIExpression()), !dbg !1769
  call void @llvm.dbg.declare(metadata %struct.stat* %5, metadata !1770, metadata !DIExpression()), !dbg !1771
  store i8 0, i8* @deleteOutputOnInterrupt, align 1, !dbg !1772
  %6 = load i8*, i8** %2, align 8, !dbg !1773
  %7 = icmp eq i8* %6, null, !dbg !1775
  br i1 %7, label %8, label %12, !dbg !1776

8:                                                ; preds = %1
  %9 = load i32, i32* @srcMode, align 4, !dbg !1777
  %10 = icmp ne i32 %9, 1, !dbg !1778
  br i1 %10, label %11, label %12, !dbg !1779

11:                                               ; preds = %8
  call void @panic(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.97, i64 0, i64 0)) #13, !dbg !1780
  unreachable, !dbg !1780

12:                                               ; preds = %8, %1
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0)), !dbg !1781
  %13 = load i32, i32* @srcMode, align 4, !dbg !1782
  switch i32 %13, label %19 [
    i32 1, label %14
    i32 3, label %15
    i32 2, label %17
  ], !dbg !1783

14:                                               ; preds = %12
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.54, i64 0, i64 0)), !dbg !1784
  br label %19, !dbg !1786

15:                                               ; preds = %12
  %16 = load i8*, i8** %2, align 8, !dbg !1787
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %16), !dbg !1788
  br label %19, !dbg !1789

17:                                               ; preds = %12
  %18 = load i8*, i8** %2, align 8, !dbg !1790
  call void @copyFileName(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %18), !dbg !1791
  br label %19, !dbg !1792

19:                                               ; preds = %12, %17, %15, %14
  %20 = load i32, i32* @srcMode, align 4, !dbg !1793
  %21 = icmp ne i32 %20, 1, !dbg !1795
  br i1 %21, label %22, label %34, !dbg !1796

22:                                               ; preds = %19
  %23 = call zeroext i8 @containsDubiousChars(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1797
  %24 = zext i8 %23 to i32, !dbg !1797
  %25 = icmp ne i32 %24, 0, !dbg !1797
  br i1 %25, label %26, label %34, !dbg !1798

26:                                               ; preds = %22
  %27 = load i8, i8* @noisy, align 1, !dbg !1799
  %28 = icmp ne i8 %27, 0, !dbg !1799
  br i1 %28, label %29, label %33, !dbg !1802

29:                                               ; preds = %26
  %30 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1803
  %31 = load i8*, i8** @progName, align 8, !dbg !1804
  %32 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %30, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.56, i64 0, i64 0), i8* %31, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1805
  br label %33, !dbg !1805

33:                                               ; preds = %29, %26
  call void @setExit(i32 1), !dbg !1806
  br label %115, !dbg !1807

34:                                               ; preds = %22, %19
  %35 = load i32, i32* @srcMode, align 4, !dbg !1808
  %36 = icmp ne i32 %35, 1, !dbg !1810
  br i1 %36, label %37, label %47, !dbg !1811

37:                                               ; preds = %34
  %38 = call zeroext i8 @fileExists(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1812
  %39 = icmp ne i8 %38, 0, !dbg !1812
  br i1 %39, label %47, label %40, !dbg !1813

40:                                               ; preds = %37
  %41 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1814
  %42 = load i8*, i8** @progName, align 8, !dbg !1816
  %43 = call i32* @__errno_location() #14, !dbg !1817
  %44 = load i32, i32* %43, align 4, !dbg !1817
  %45 = call i8* @strerror(i32 %44) #10, !dbg !1818
  %46 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %41, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.98, i64 0, i64 0), i8* %42, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %45), !dbg !1819
  call void @setExit(i32 1), !dbg !1820
  br label %115, !dbg !1821

47:                                               ; preds = %37, %34
  %48 = load i32, i32* @srcMode, align 4, !dbg !1822
  %49 = icmp ne i32 %48, 1, !dbg !1824
  br i1 %49, label %50, label %61, !dbg !1825

50:                                               ; preds = %47
  %51 = call i32 @stat(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), %struct.stat* %5) #10, !dbg !1826
  %52 = getelementptr inbounds %struct.stat, %struct.stat* %5, i32 0, i32 3, !dbg !1828
  %53 = load i32, i32* %52, align 8, !dbg !1828
  %54 = and i32 %53, 61440, !dbg !1828
  %55 = icmp eq i32 %54, 16384, !dbg !1828
  br i1 %55, label %56, label %60, !dbg !1830

56:                                               ; preds = %50
  %57 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1831
  %58 = load i8*, i8** @progName, align 8, !dbg !1833
  %59 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %57, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.59, i64 0, i64 0), i8* %58, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1834
  call void @setExit(i32 1), !dbg !1835
  br label %115, !dbg !1836

60:                                               ; preds = %50
  br label %61, !dbg !1837

61:                                               ; preds = %60, %47
  %62 = load i32, i32* @srcMode, align 4, !dbg !1838
  switch i32 %62, label %90 [
    i32 1, label %63
    i32 2, label %78
    i32 3, label %78
  ], !dbg !1839

63:                                               ; preds = %61
  %64 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1840
  %65 = call i32 @fileno(%struct._IO_FILE* %64) #10, !dbg !1843
  %66 = call i32 @isatty(i32 %65) #10, !dbg !1844
  %67 = icmp ne i32 %66, 0, !dbg !1844
  br i1 %67, label %68, label %76, !dbg !1845

68:                                               ; preds = %63
  %69 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1846
  %70 = load i8*, i8** @progName, align 8, !dbg !1848
  %71 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %69, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.85, i64 0, i64 0), i8* %70), !dbg !1849
  %72 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1850
  %73 = load i8*, i8** @progName, align 8, !dbg !1851
  %74 = load i8*, i8** @progName, align 8, !dbg !1852
  %75 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %72, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.65, i64 0, i64 0), i8* %73, i8* %74), !dbg !1853
  call void @setExit(i32 1), !dbg !1854
  br label %115, !dbg !1855

76:                                               ; preds = %63
  %77 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !1856
  store %struct._IO_FILE* %77, %struct._IO_FILE** %3, align 8, !dbg !1857
  br label %91, !dbg !1858

78:                                               ; preds = %61, %61
  %79 = call %struct._IO_FILE* @fopen(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !1859
  store %struct._IO_FILE* %79, %struct._IO_FILE** %3, align 8, !dbg !1860
  %80 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1861
  %81 = icmp eq %struct._IO_FILE* %80, null, !dbg !1863
  br i1 %81, label %82, label %89, !dbg !1864

82:                                               ; preds = %78
  %83 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1865
  %84 = load i8*, i8** @progName, align 8, !dbg !1867
  %85 = call i32* @__errno_location() #14, !dbg !1868
  %86 = load i32, i32* %85, align 4, !dbg !1868
  %87 = call i8* @strerror(i32 %86) #10, !dbg !1869
  %88 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %83, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.86, i64 0, i64 0), i8* %84, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* %87), !dbg !1870
  call void @setExit(i32 1), !dbg !1871
  br label %115, !dbg !1872

89:                                               ; preds = %78
  br label %91, !dbg !1873

90:                                               ; preds = %61
  call void @panic(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.99, i64 0, i64 0)) #13, !dbg !1874
  unreachable, !dbg !1874

91:                                               ; preds = %89, %76
  %92 = load i32, i32* @verbosity, align 4, !dbg !1875
  %93 = icmp sge i32 %92, 1, !dbg !1877
  br i1 %93, label %94, label %99, !dbg !1878

94:                                               ; preds = %91
  %95 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1879
  %96 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %95, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.70, i64 0, i64 0), i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1881
  call void @pad(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !1882
  %97 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1883
  %98 = call i32 @fflush(%struct._IO_FILE* %97), !dbg !1884
  br label %99, !dbg !1885

99:                                               ; preds = %94, %91
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1886
  %100 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !1887
  %101 = call zeroext i8 @testStream(%struct._IO_FILE* %100), !dbg !1888
  store i8 %101, i8* %4, align 1, !dbg !1889
  %102 = load i8, i8* %4, align 1, !dbg !1890
  %103 = zext i8 %102 to i32, !dbg !1890
  %104 = icmp ne i32 %103, 0, !dbg !1890
  br i1 %104, label %105, label %111, !dbg !1892

105:                                              ; preds = %99
  %106 = load i32, i32* @verbosity, align 4, !dbg !1893
  %107 = icmp sge i32 %106, 1, !dbg !1894
  br i1 %107, label %108, label %111, !dbg !1895

108:                                              ; preds = %105
  %109 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1896
  %110 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %109, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.100, i64 0, i64 0)), !dbg !1897
  br label %111, !dbg !1897

111:                                              ; preds = %108, %105, %99
  %112 = load i8, i8* %4, align 1, !dbg !1898
  %113 = icmp ne i8 %112, 0, !dbg !1898
  br i1 %113, label %115, label %114, !dbg !1900

114:                                              ; preds = %111
  store i8 1, i8* @testFailsExist, align 1, !dbg !1901
  br label %115, !dbg !1902

115:                                              ; preds = %33, %40, %56, %68, %82, %114, %111
  ret void, !dbg !1903
}

; Function Attrs: nounwind
declare dso_local void @free(i8*) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal void @showFileNames() #0 !dbg !1904 {
  %1 = load i8, i8* @noisy, align 1, !dbg !1905
  %2 = icmp ne i8 %1, 0, !dbg !1905
  br i1 %2, label %3, label %6, !dbg !1907

3:                                                ; preds = %0
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1908
  %5 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %4, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.38, i64 0, i64 0), i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1909
  br label %6, !dbg !1909

6:                                                ; preds = %3, %0
  ret void, !dbg !1910
}

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @cleanUpAndFail(i32 %0) #6 !dbg !1911 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca %struct.stat, align 8
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !1912, metadata !DIExpression()), !dbg !1913
  call void @llvm.dbg.declare(metadata i32* %3, metadata !1914, metadata !DIExpression()), !dbg !1915
  call void @llvm.dbg.declare(metadata %struct.stat* %4, metadata !1916, metadata !DIExpression()), !dbg !1917
  %5 = load i32, i32* @srcMode, align 4, !dbg !1918
  %6 = icmp eq i32 %5, 3, !dbg !1920
  br i1 %6, label %7, label %54, !dbg !1921

7:                                                ; preds = %1
  %8 = load i32, i32* @opMode, align 4, !dbg !1922
  %9 = icmp ne i32 %8, 3, !dbg !1923
  br i1 %9, label %10, label %54, !dbg !1924

10:                                               ; preds = %7
  %11 = load i8, i8* @deleteOutputOnInterrupt, align 1, !dbg !1925
  %12 = zext i8 %11 to i32, !dbg !1925
  %13 = icmp ne i32 %12, 0, !dbg !1925
  br i1 %13, label %14, label %54, !dbg !1926

14:                                               ; preds = %10
  %15 = call i32 @stat(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0), %struct.stat* %4) #10, !dbg !1927
  store i32 %15, i32* %3, align 4, !dbg !1929
  %16 = load i32, i32* %3, align 4, !dbg !1930
  %17 = icmp eq i32 %16, 0, !dbg !1932
  br i1 %17, label %18, label %40, !dbg !1933

18:                                               ; preds = %14
  %19 = load i8, i8* @noisy, align 1, !dbg !1934
  %20 = icmp ne i8 %19, 0, !dbg !1934
  br i1 %20, label %21, label %25, !dbg !1937

21:                                               ; preds = %18
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1938
  %23 = load i8*, i8** @progName, align 8, !dbg !1939
  %24 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %22, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.39, i64 0, i64 0), i8* %23, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1940
  br label %25, !dbg !1940

25:                                               ; preds = %21, %18
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1941
  %27 = icmp ne %struct._IO_FILE* %26, null, !dbg !1943
  br i1 %27, label %28, label %31, !dbg !1944

28:                                               ; preds = %25
  %29 = load %struct._IO_FILE*, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !1945
  %30 = call i32 @fclose(%struct._IO_FILE* %29), !dbg !1946
  br label %31, !dbg !1946

31:                                               ; preds = %28, %25
  %32 = call i32 @remove(i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)) #10, !dbg !1947
  store i32 %32, i32* %3, align 4, !dbg !1948
  %33 = load i32, i32* %3, align 4, !dbg !1949
  %34 = icmp ne i32 %33, 0, !dbg !1951
  br i1 %34, label %35, label %39, !dbg !1952

35:                                               ; preds = %31
  %36 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1953
  %37 = load i8*, i8** @progName, align 8, !dbg !1954
  %38 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %36, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @.str.40, i64 0, i64 0), i8* %37), !dbg !1955
  br label %39, !dbg !1955

39:                                               ; preds = %35, %31
  br label %53, !dbg !1956

40:                                               ; preds = %14
  %41 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1957
  %42 = load i8*, i8** @progName, align 8, !dbg !1959
  %43 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %41, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.41, i64 0, i64 0), i8* %42), !dbg !1960
  %44 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1961
  %45 = load i8*, i8** @progName, align 8, !dbg !1962
  %46 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %44, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.42, i64 0, i64 0), i8* %45), !dbg !1963
  %47 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1964
  %48 = load i8*, i8** @progName, align 8, !dbg !1965
  %49 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %47, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.43, i64 0, i64 0), i8* %48, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @outName, i64 0, i64 0)), !dbg !1966
  %50 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1967
  %51 = load i8*, i8** @progName, align 8, !dbg !1968
  %52 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %50, i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.44, i64 0, i64 0), i8* %51), !dbg !1969
  br label %53

53:                                               ; preds = %40, %39
  br label %54, !dbg !1970

54:                                               ; preds = %53, %10, %7, %1
  %55 = load i8, i8* @noisy, align 1, !dbg !1971
  %56 = zext i8 %55 to i32, !dbg !1971
  %57 = icmp ne i32 %56, 0, !dbg !1971
  br i1 %57, label %58, label %74, !dbg !1973

58:                                               ; preds = %54
  %59 = load i32, i32* @numFileNames, align 4, !dbg !1974
  %60 = icmp sgt i32 %59, 0, !dbg !1975
  br i1 %60, label %61, label %74, !dbg !1976

61:                                               ; preds = %58
  %62 = load i32, i32* @numFilesProcessed, align 4, !dbg !1977
  %63 = load i32, i32* @numFileNames, align 4, !dbg !1978
  %64 = icmp slt i32 %62, %63, !dbg !1979
  br i1 %64, label %65, label %74, !dbg !1980

65:                                               ; preds = %61
  %66 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1981
  %67 = load i8*, i8** @progName, align 8, !dbg !1983
  %68 = load i8*, i8** @progName, align 8, !dbg !1984
  %69 = load i32, i32* @numFileNames, align 4, !dbg !1985
  %70 = load i32, i32* @numFileNames, align 4, !dbg !1986
  %71 = load i32, i32* @numFilesProcessed, align 4, !dbg !1987
  %72 = sub nsw i32 %70, %71, !dbg !1988
  %73 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %66, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.45, i64 0, i64 0), i8* %67, i8* %68, i32 %69, i32 %72), !dbg !1989
  br label %74, !dbg !1990

74:                                               ; preds = %65, %61, %58, %54
  %75 = load i32, i32* %2, align 4, !dbg !1991
  call void @setExit(i32 %75), !dbg !1992
  %76 = load i32, i32* @exitValue, align 4, !dbg !1993
  call void @exit(i32 %76) #12, !dbg !1994
  unreachable, !dbg !1994
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @cadvise() #0 !dbg !1995 {
  %1 = load i8, i8* @noisy, align 1, !dbg !1996
  %2 = icmp ne i8 %1, 0, !dbg !1996
  br i1 %2, label %3, label %6, !dbg !1998

3:                                                ; preds = %0
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1999
  %5 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %4, i8* getelementptr inbounds ([241 x i8], [241 x i8]* @.str.46, i64 0, i64 0)), !dbg !2000
  br label %6, !dbg !2000

6:                                                ; preds = %3, %0
  ret void, !dbg !2001
}

; Function Attrs: nounwind
declare dso_local i32 @stat(i8*, %struct.stat*) #2

declare dso_local i32 @fclose(%struct._IO_FILE*) #5

; Function Attrs: nounwind
declare dso_local i32 @remove(i8*) #2

; Function Attrs: nounwind
declare dso_local i8* @strncpy(i8*, i8*, i64) #2

; Function Attrs: nounwind
declare dso_local i8* @getenv(i8*) #2

; Function Attrs: nounwind readnone
declare dso_local i16** @__ctype_b_loc() #7

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct.zzzz* @mkCell() #0 !dbg !2002 {
  %1 = alloca %struct.zzzz*, align 8
  call void @llvm.dbg.declare(metadata %struct.zzzz** %1, metadata !2005, metadata !DIExpression()), !dbg !2006
  %2 = call i8* @myMalloc(i32 16), !dbg !2007
  %3 = bitcast i8* %2 to %struct.zzzz*, !dbg !2008
  store %struct.zzzz* %3, %struct.zzzz** %1, align 8, !dbg !2009
  %4 = load %struct.zzzz*, %struct.zzzz** %1, align 8, !dbg !2010
  %5 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %4, i32 0, i32 0, !dbg !2011
  store i8* null, i8** %5, align 8, !dbg !2012
  %6 = load %struct.zzzz*, %struct.zzzz** %1, align 8, !dbg !2013
  %7 = getelementptr inbounds %struct.zzzz, %struct.zzzz* %6, i32 0, i32 1, !dbg !2014
  store %struct.zzzz* null, %struct.zzzz** %7, align 8, !dbg !2015
  %8 = load %struct.zzzz*, %struct.zzzz** %1, align 8, !dbg !2016
  ret %struct.zzzz* %8, !dbg !2017
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i8* @myMalloc(i32 %0) #0 !dbg !2018 {
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !2021, metadata !DIExpression()), !dbg !2022
  call void @llvm.dbg.declare(metadata i8** %3, metadata !2023, metadata !DIExpression()), !dbg !2024
  %4 = load i32, i32* %2, align 4, !dbg !2025
  %5 = sext i32 %4 to i64, !dbg !2026
  %6 = call noalias i8* @malloc(i64 %5) #10, !dbg !2027
  store i8* %6, i8** %3, align 8, !dbg !2028
  %7 = load i8*, i8** %3, align 8, !dbg !2029
  %8 = icmp eq i8* %7, null, !dbg !2031
  br i1 %8, label %9, label %10, !dbg !2032

9:                                                ; preds = %1
  call void @outOfMemory() #13, !dbg !2033
  unreachable, !dbg !2033

10:                                               ; preds = %1
  %11 = load i8*, i8** %3, align 8, !dbg !2034
  ret i8* %11, !dbg !2035
}

; Function Attrs: nounwind
declare dso_local i8* @strcpy(i8*, i8*) #2

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #2

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @outOfMemory() #6 !dbg !2036 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2037
  %2 = load i8*, i8** @progName, align 8, !dbg !2038
  %3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.48, i64 0, i64 0), i8* %2), !dbg !2039
  call void @showFileNames(), !dbg !2040
  call void @cleanUpAndFail(i32 1) #13, !dbg !2041
  unreachable, !dbg !2041
}

declare dso_local i8* @BZ2_bzlibVersion() #5

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @panic(i8* %0) #6 !dbg !2042 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !2045, metadata !DIExpression()), !dbg !2046
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2047
  %4 = load i8*, i8** @progName, align 8, !dbg !2048
  %5 = load i8*, i8** %2, align 8, !dbg !2049
  %6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([109 x i8], [109 x i8]* @.str.71, i64 0, i64 0), i8* %4, i8* %5), !dbg !2050
  call void @showFileNames(), !dbg !2051
  call void @cleanUpAndFail(i32 3) #13, !dbg !2052
  unreachable, !dbg !2052
}

; Function Attrs: nounwind
declare dso_local i8* @strcat(i8*, i8*) #2

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @containsDubiousChars(i8* %0) #0 !dbg !2053 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !2056, metadata !DIExpression()), !dbg !2057
  ret i8 0, !dbg !2058
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @fileExists(i8* %0) #0 !dbg !2059 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca i8, align 1
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !2060, metadata !DIExpression()), !dbg !2061
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !2062, metadata !DIExpression()), !dbg !2063
  %5 = load i8*, i8** %2, align 8, !dbg !2064
  %6 = call %struct._IO_FILE* @fopen(i8* %5, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !2065
  store %struct._IO_FILE* %6, %struct._IO_FILE** %3, align 8, !dbg !2063
  call void @llvm.dbg.declare(metadata i8* %4, metadata !2066, metadata !DIExpression()), !dbg !2067
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2068
  %8 = icmp ne %struct._IO_FILE* %7, null, !dbg !2069
  %9 = zext i1 %8 to i32, !dbg !2069
  %10 = trunc i32 %9 to i8, !dbg !2070
  store i8 %10, i8* %4, align 1, !dbg !2067
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2071
  %12 = icmp ne %struct._IO_FILE* %11, null, !dbg !2073
  br i1 %12, label %13, label %16, !dbg !2074

13:                                               ; preds = %1
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2075
  %15 = call i32 @fclose(%struct._IO_FILE* %14), !dbg !2076
  br label %16, !dbg !2076

16:                                               ; preds = %13, %1
  %17 = load i8, i8* %4, align 1, !dbg !2077
  ret i8 %17, !dbg !2078
}

; Function Attrs: nounwind
declare dso_local i8* @strerror(i32) #2

; Function Attrs: nounwind readnone
declare dso_local i32* @__errno_location() #7

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @hasSuffix(i8* %0, i8* %1) #0 !dbg !2079 {
  %3 = alloca i8, align 1
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  call void @llvm.dbg.declare(metadata i8** %4, metadata !2082, metadata !DIExpression()), !dbg !2083
  store i8* %1, i8** %5, align 8
  call void @llvm.dbg.declare(metadata i8** %5, metadata !2084, metadata !DIExpression()), !dbg !2085
  call void @llvm.dbg.declare(metadata i32* %6, metadata !2086, metadata !DIExpression()), !dbg !2087
  %8 = load i8*, i8** %4, align 8, !dbg !2088
  %9 = call i64 @strlen(i8* %8) #11, !dbg !2089
  %10 = trunc i64 %9 to i32, !dbg !2089
  store i32 %10, i32* %6, align 4, !dbg !2087
  call void @llvm.dbg.declare(metadata i32* %7, metadata !2090, metadata !DIExpression()), !dbg !2091
  %11 = load i8*, i8** %5, align 8, !dbg !2092
  %12 = call i64 @strlen(i8* %11) #11, !dbg !2093
  %13 = trunc i64 %12 to i32, !dbg !2093
  store i32 %13, i32* %7, align 4, !dbg !2091
  %14 = load i32, i32* %6, align 4, !dbg !2094
  %15 = load i32, i32* %7, align 4, !dbg !2096
  %16 = icmp slt i32 %14, %15, !dbg !2097
  br i1 %16, label %17, label %18, !dbg !2098

17:                                               ; preds = %2
  store i8 0, i8* %3, align 1, !dbg !2099
  br label %32, !dbg !2099

18:                                               ; preds = %2
  %19 = load i8*, i8** %4, align 8, !dbg !2100
  %20 = load i32, i32* %6, align 4, !dbg !2102
  %21 = sext i32 %20 to i64, !dbg !2103
  %22 = getelementptr inbounds i8, i8* %19, i64 %21, !dbg !2103
  %23 = load i32, i32* %7, align 4, !dbg !2104
  %24 = sext i32 %23 to i64, !dbg !2105
  %25 = sub i64 0, %24, !dbg !2105
  %26 = getelementptr inbounds i8, i8* %22, i64 %25, !dbg !2105
  %27 = load i8*, i8** %5, align 8, !dbg !2106
  %28 = call i32 @strcmp(i8* %26, i8* %27) #11, !dbg !2107
  %29 = icmp eq i32 %28, 0, !dbg !2108
  br i1 %29, label %30, label %31, !dbg !2109

30:                                               ; preds = %18
  store i8 1, i8* %3, align 1, !dbg !2110
  br label %32, !dbg !2110

31:                                               ; preds = %18
  store i8 0, i8* %3, align 1, !dbg !2111
  br label %32, !dbg !2111

32:                                               ; preds = %31, %30, %17
  %33 = load i8, i8* %3, align 1, !dbg !2112
  ret i8 %33, !dbg !2112
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @notAStandardFile(i8* %0) #0 !dbg !2113 {
  %2 = alloca i8, align 1
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca %struct.stat, align 8
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !2114, metadata !DIExpression()), !dbg !2115
  call void @llvm.dbg.declare(metadata i32* %4, metadata !2116, metadata !DIExpression()), !dbg !2117
  call void @llvm.dbg.declare(metadata %struct.stat* %5, metadata !2118, metadata !DIExpression()), !dbg !2119
  %6 = load i8*, i8** %3, align 8, !dbg !2120
  %7 = call i32 @lstat(i8* %6, %struct.stat* %5) #10, !dbg !2121
  store i32 %7, i32* %4, align 4, !dbg !2122
  %8 = load i32, i32* %4, align 4, !dbg !2123
  %9 = icmp ne i32 %8, 0, !dbg !2125
  br i1 %9, label %10, label %11, !dbg !2126

10:                                               ; preds = %1
  store i8 1, i8* %2, align 1, !dbg !2127
  br label %18, !dbg !2127

11:                                               ; preds = %1
  %12 = getelementptr inbounds %struct.stat, %struct.stat* %5, i32 0, i32 3, !dbg !2128
  %13 = load i32, i32* %12, align 8, !dbg !2128
  %14 = and i32 %13, 61440, !dbg !2128
  %15 = icmp eq i32 %14, 32768, !dbg !2128
  br i1 %15, label %16, label %17, !dbg !2130

16:                                               ; preds = %11
  store i8 0, i8* %2, align 1, !dbg !2131
  br label %18, !dbg !2131

17:                                               ; preds = %11
  store i8 1, i8* %2, align 1, !dbg !2132
  br label %18, !dbg !2132

18:                                               ; preds = %17, %16, %10
  %19 = load i8, i8* %2, align 1, !dbg !2133
  ret i8 %19, !dbg !2133
}

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @countHardLinks(i8* %0) #0 !dbg !2134 {
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca %struct.stat, align 8
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !2137, metadata !DIExpression()), !dbg !2138
  call void @llvm.dbg.declare(metadata i32* %4, metadata !2139, metadata !DIExpression()), !dbg !2140
  call void @llvm.dbg.declare(metadata %struct.stat* %5, metadata !2141, metadata !DIExpression()), !dbg !2142
  %6 = load i8*, i8** %3, align 8, !dbg !2143
  %7 = call i32 @lstat(i8* %6, %struct.stat* %5) #10, !dbg !2144
  store i32 %7, i32* %4, align 4, !dbg !2145
  %8 = load i32, i32* %4, align 4, !dbg !2146
  %9 = icmp ne i32 %8, 0, !dbg !2148
  br i1 %9, label %10, label %11, !dbg !2149

10:                                               ; preds = %1
  store i32 0, i32* %2, align 4, !dbg !2150
  br label %16, !dbg !2150

11:                                               ; preds = %1
  %12 = getelementptr inbounds %struct.stat, %struct.stat* %5, i32 0, i32 2, !dbg !2151
  %13 = load i64, i64* %12, align 8, !dbg !2151
  %14 = sub i64 %13, 1, !dbg !2152
  %15 = trunc i64 %14 to i32, !dbg !2153
  store i32 %15, i32* %2, align 4, !dbg !2154
  br label %16, !dbg !2154

16:                                               ; preds = %11, %10
  %17 = load i32, i32* %2, align 4, !dbg !2155
  ret i32 %17, !dbg !2155
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @saveInputFileMetaInfo(i8* %0) #0 !dbg !2156 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !2157, metadata !DIExpression()), !dbg !2158
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2159, metadata !DIExpression()), !dbg !2160
  %4 = load i8*, i8** %2, align 8, !dbg !2161
  %5 = call i32 @stat(i8* %4, %struct.stat* @fileMetaInfo) #10, !dbg !2162
  store i32 %5, i32* %3, align 4, !dbg !2163
  %6 = load i32, i32* %3, align 4, !dbg !2164
  %7 = icmp ne i32 %6, 0, !dbg !2164
  br i1 %7, label %8, label %9, !dbg !2167

8:                                                ; preds = %1
  call void @ioError() #13, !dbg !2164
  unreachable, !dbg !2164

9:                                                ; preds = %1
  ret void, !dbg !2168
}

; Function Attrs: nounwind
declare dso_local i32 @isatty(i32) #2

; Function Attrs: nounwind
declare dso_local i32 @fileno(%struct._IO_FILE*) #2

declare dso_local %struct._IO_FILE* @fopen(i8*, i8*) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal %struct._IO_FILE* @fopen_output_safely(i8* %0, i8* %1) #0 !dbg !2169 {
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca %struct._IO_FILE*, align 8
  %7 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  call void @llvm.dbg.declare(metadata i8** %4, metadata !2174, metadata !DIExpression()), !dbg !2175
  store i8* %1, i8** %5, align 8
  call void @llvm.dbg.declare(metadata i8** %5, metadata !2176, metadata !DIExpression()), !dbg !2177
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %6, metadata !2178, metadata !DIExpression()), !dbg !2179
  call void @llvm.dbg.declare(metadata i32* %7, metadata !2180, metadata !DIExpression()), !dbg !2181
  %8 = load i8*, i8** %4, align 8, !dbg !2182
  %9 = call i32 (i8*, i32, ...) @open(i8* %8, i32 193, i32 384), !dbg !2183
  store i32 %9, i32* %7, align 4, !dbg !2184
  %10 = load i32, i32* %7, align 4, !dbg !2185
  %11 = icmp eq i32 %10, -1, !dbg !2187
  br i1 %11, label %12, label %13, !dbg !2188

12:                                               ; preds = %2
  store %struct._IO_FILE* null, %struct._IO_FILE** %3, align 8, !dbg !2189
  br label %24, !dbg !2189

13:                                               ; preds = %2
  %14 = load i32, i32* %7, align 4, !dbg !2190
  %15 = load i8*, i8** %5, align 8, !dbg !2191
  %16 = call %struct._IO_FILE* @fdopen(i32 %14, i8* %15) #10, !dbg !2192
  store %struct._IO_FILE* %16, %struct._IO_FILE** %6, align 8, !dbg !2193
  %17 = load %struct._IO_FILE*, %struct._IO_FILE** %6, align 8, !dbg !2194
  %18 = icmp eq %struct._IO_FILE* %17, null, !dbg !2196
  br i1 %18, label %19, label %22, !dbg !2197

19:                                               ; preds = %13
  %20 = load i32, i32* %7, align 4, !dbg !2198
  %21 = call i32 @close(i32 %20), !dbg !2199
  br label %22, !dbg !2199

22:                                               ; preds = %19, %13
  %23 = load %struct._IO_FILE*, %struct._IO_FILE** %6, align 8, !dbg !2200
  store %struct._IO_FILE* %23, %struct._IO_FILE** %3, align 8, !dbg !2201
  br label %24, !dbg !2201

24:                                               ; preds = %22, %12
  %25 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2202
  ret %struct._IO_FILE* %25, !dbg !2202
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @pad(i8* %0) #0 !dbg !2203 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !2204, metadata !DIExpression()), !dbg !2205
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2206, metadata !DIExpression()), !dbg !2207
  %4 = load i8*, i8** %2, align 8, !dbg !2208
  %5 = call i64 @strlen(i8* %4) #11, !dbg !2210
  %6 = trunc i64 %5 to i32, !dbg !2211
  %7 = load i32, i32* @longestFileName, align 4, !dbg !2212
  %8 = icmp sge i32 %6, %7, !dbg !2213
  br i1 %8, label %9, label %10, !dbg !2214

9:                                                ; preds = %1
  br label %25, !dbg !2215

10:                                               ; preds = %1
  store i32 1, i32* %3, align 4, !dbg !2216
  br label %11, !dbg !2218

11:                                               ; preds = %22, %10
  %12 = load i32, i32* %3, align 4, !dbg !2219
  %13 = load i32, i32* @longestFileName, align 4, !dbg !2221
  %14 = load i8*, i8** %2, align 8, !dbg !2222
  %15 = call i64 @strlen(i8* %14) #11, !dbg !2223
  %16 = trunc i64 %15 to i32, !dbg !2224
  %17 = sub nsw i32 %13, %16, !dbg !2225
  %18 = icmp sle i32 %12, %17, !dbg !2226
  br i1 %18, label %19, label %25, !dbg !2227

19:                                               ; preds = %11
  %20 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2228
  %21 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %20, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.72, i64 0, i64 0)), !dbg !2229
  br label %22, !dbg !2229

22:                                               ; preds = %19
  %23 = load i32, i32* %3, align 4, !dbg !2230
  %24 = add nsw i32 %23, 1, !dbg !2230
  store i32 %24, i32* %3, align 4, !dbg !2230
  br label %11, !dbg !2231, !llvm.loop !2232

25:                                               ; preds = %9, %11
  ret void, !dbg !2234
}

declare dso_local i32 @fflush(%struct._IO_FILE*) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal void @compressStream(%struct._IO_FILE* %0, %struct._IO_FILE* %1) #0 !dbg !2235 {
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca [5000 x i8], align 16
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca [32 x i8], align 16
  %17 = alloca [32 x i8], align 16
  %18 = alloca %struct.UInt64, align 1
  %19 = alloca %struct.UInt64, align 1
  %20 = alloca double, align 8
  %21 = alloca double, align 8
  store %struct._IO_FILE* %0, %struct._IO_FILE** %3, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !2238, metadata !DIExpression()), !dbg !2239
  store %struct._IO_FILE* %1, %struct._IO_FILE** %4, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %4, metadata !2240, metadata !DIExpression()), !dbg !2241
  call void @llvm.dbg.declare(metadata i8** %5, metadata !2242, metadata !DIExpression()), !dbg !2246
  store i8* null, i8** %5, align 8, !dbg !2246
  call void @llvm.dbg.declare(metadata [5000 x i8]* %6, metadata !2247, metadata !DIExpression()), !dbg !2251
  call void @llvm.dbg.declare(metadata i32* %7, metadata !2252, metadata !DIExpression()), !dbg !2253
  call void @llvm.dbg.declare(metadata i32* %8, metadata !2254, metadata !DIExpression()), !dbg !2256
  call void @llvm.dbg.declare(metadata i32* %9, metadata !2257, metadata !DIExpression()), !dbg !2258
  call void @llvm.dbg.declare(metadata i32* %10, metadata !2259, metadata !DIExpression()), !dbg !2260
  call void @llvm.dbg.declare(metadata i32* %11, metadata !2261, metadata !DIExpression()), !dbg !2262
  call void @llvm.dbg.declare(metadata i32* %12, metadata !2263, metadata !DIExpression()), !dbg !2264
  call void @llvm.dbg.declare(metadata i32* %13, metadata !2265, metadata !DIExpression()), !dbg !2266
  call void @llvm.dbg.declare(metadata i32* %14, metadata !2267, metadata !DIExpression()), !dbg !2268
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2269
  %23 = call i32 @ferror(%struct._IO_FILE* %22) #10, !dbg !2271
  %24 = icmp ne i32 %23, 0, !dbg !2271
  br i1 %24, label %25, label %26, !dbg !2272

25:                                               ; preds = %2
  br label %163, !dbg !2273

26:                                               ; preds = %2
  %27 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2274
  %28 = call i32 @ferror(%struct._IO_FILE* %27) #10, !dbg !2276
  %29 = icmp ne i32 %28, 0, !dbg !2276
  br i1 %29, label %30, label %31, !dbg !2277

30:                                               ; preds = %26
  br label %163, !dbg !2278

31:                                               ; preds = %26
  %32 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2279
  %33 = load i32, i32* @blockSize100k, align 4, !dbg !2280
  %34 = load i32, i32* @verbosity, align 4, !dbg !2281
  %35 = load i32, i32* @workFactor, align 4, !dbg !2282
  %36 = call i8* @BZ2_bzWriteOpen(i32* %12, %struct._IO_FILE* %32, i32 %33, i32 %34, i32 %35), !dbg !2283
  store i8* %36, i8** %5, align 8, !dbg !2284
  %37 = load i32, i32* %12, align 4, !dbg !2285
  %38 = icmp ne i32 %37, 0, !dbg !2287
  br i1 %38, label %39, label %40, !dbg !2288

39:                                               ; preds = %31
  br label %157, !dbg !2289

40:                                               ; preds = %31
  %41 = load i32, i32* @verbosity, align 4, !dbg !2290
  %42 = icmp sge i32 %41, 2, !dbg !2292
  br i1 %42, label %43, label %46, !dbg !2293

43:                                               ; preds = %40
  %44 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2294
  %45 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %44, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.73, i64 0, i64 0)), !dbg !2295
  br label %46, !dbg !2295

46:                                               ; preds = %43, %40
  br label %47, !dbg !2296

47:                                               ; preds = %46, %72
  %48 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2297
  %49 = call zeroext i8 @myfeof(%struct._IO_FILE* %48), !dbg !2300
  %50 = icmp ne i8 %49, 0, !dbg !2300
  br i1 %50, label %51, label %52, !dbg !2301

51:                                               ; preds = %47
  br label %73, !dbg !2302

52:                                               ; preds = %47
  %53 = getelementptr inbounds [5000 x i8], [5000 x i8]* %6, i64 0, i64 0, !dbg !2303
  %54 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2304
  %55 = call i64 @fread(i8* %53, i64 1, i64 5000, %struct._IO_FILE* %54), !dbg !2305
  %56 = trunc i64 %55 to i32, !dbg !2305
  store i32 %56, i32* %7, align 4, !dbg !2306
  %57 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2307
  %58 = call i32 @ferror(%struct._IO_FILE* %57) #10, !dbg !2309
  %59 = icmp ne i32 %58, 0, !dbg !2309
  br i1 %59, label %60, label %61, !dbg !2310

60:                                               ; preds = %52
  br label %163, !dbg !2311

61:                                               ; preds = %52
  %62 = load i32, i32* %7, align 4, !dbg !2312
  %63 = icmp sgt i32 %62, 0, !dbg !2314
  br i1 %63, label %64, label %68, !dbg !2315

64:                                               ; preds = %61
  %65 = load i8*, i8** %5, align 8, !dbg !2316
  %66 = getelementptr inbounds [5000 x i8], [5000 x i8]* %6, i64 0, i64 0, !dbg !2317
  %67 = load i32, i32* %7, align 4, !dbg !2318
  call void @BZ2_bzWrite(i32* %12, i8* %65, i8* %66, i32 %67), !dbg !2319
  br label %68, !dbg !2319

68:                                               ; preds = %64, %61
  %69 = load i32, i32* %12, align 4, !dbg !2320
  %70 = icmp ne i32 %69, 0, !dbg !2322
  br i1 %70, label %71, label %72, !dbg !2323

71:                                               ; preds = %68
  br label %157, !dbg !2324

72:                                               ; preds = %68
  br label %47, !dbg !2296, !llvm.loop !2325

73:                                               ; preds = %51
  %74 = load i8*, i8** %5, align 8, !dbg !2327
  call void @BZ2_bzWriteClose64(i32* %12, i8* %74, i32 0, i32* %8, i32* %9, i32* %10, i32* %11), !dbg !2328
  %75 = load i32, i32* %12, align 4, !dbg !2329
  %76 = icmp ne i32 %75, 0, !dbg !2331
  br i1 %76, label %77, label %78, !dbg !2332

77:                                               ; preds = %73
  br label %157, !dbg !2333

78:                                               ; preds = %73
  %79 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2334
  %80 = call i32 @ferror(%struct._IO_FILE* %79) #10, !dbg !2336
  %81 = icmp ne i32 %80, 0, !dbg !2336
  br i1 %81, label %82, label %83, !dbg !2337

82:                                               ; preds = %78
  br label %163, !dbg !2338

83:                                               ; preds = %78
  %84 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2339
  %85 = call i32 @fflush(%struct._IO_FILE* %84), !dbg !2340
  store i32 %85, i32* %14, align 4, !dbg !2341
  %86 = load i32, i32* %14, align 4, !dbg !2342
  %87 = icmp eq i32 %86, -1, !dbg !2344
  br i1 %87, label %88, label %89, !dbg !2345

88:                                               ; preds = %83
  br label %163, !dbg !2346

89:                                               ; preds = %83
  %90 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2347
  %91 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !2349
  %92 = icmp ne %struct._IO_FILE* %90, %91, !dbg !2350
  br i1 %92, label %93, label %107, !dbg !2351

93:                                               ; preds = %89
  call void @llvm.dbg.declare(metadata i32* %15, metadata !2352, metadata !DIExpression()), !dbg !2354
  %94 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2355
  %95 = call i32 @fileno(%struct._IO_FILE* %94) #10, !dbg !2356
  store i32 %95, i32* %15, align 4, !dbg !2354
  %96 = load i32, i32* %15, align 4, !dbg !2357
  %97 = icmp slt i32 %96, 0, !dbg !2359
  br i1 %97, label %98, label %99, !dbg !2360

98:                                               ; preds = %93
  br label %163, !dbg !2361

99:                                               ; preds = %93
  %100 = load i32, i32* %15, align 4, !dbg !2362
  call void @applySavedFileAttrToOutputFile(i32 %100), !dbg !2363
  %101 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2364
  %102 = call i32 @fclose(%struct._IO_FILE* %101), !dbg !2365
  store i32 %102, i32* %14, align 4, !dbg !2366
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !2367
  %103 = load i32, i32* %14, align 4, !dbg !2368
  %104 = icmp eq i32 %103, -1, !dbg !2370
  br i1 %104, label %105, label %106, !dbg !2371

105:                                              ; preds = %99
  br label %163, !dbg !2372

106:                                              ; preds = %99
  br label %107, !dbg !2373

107:                                              ; preds = %106, %89
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !2374
  %108 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2375
  %109 = call i32 @ferror(%struct._IO_FILE* %108) #10, !dbg !2377
  %110 = icmp ne i32 %109, 0, !dbg !2377
  br i1 %110, label %111, label %112, !dbg !2378

111:                                              ; preds = %107
  br label %163, !dbg !2379

112:                                              ; preds = %107
  %113 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2380
  %114 = call i32 @fclose(%struct._IO_FILE* %113), !dbg !2381
  store i32 %114, i32* %14, align 4, !dbg !2382
  %115 = load i32, i32* %14, align 4, !dbg !2383
  %116 = icmp eq i32 %115, -1, !dbg !2385
  br i1 %116, label %117, label %118, !dbg !2386

117:                                              ; preds = %112
  br label %163, !dbg !2387

118:                                              ; preds = %112
  %119 = load i32, i32* @verbosity, align 4, !dbg !2388
  %120 = icmp sge i32 %119, 1, !dbg !2390
  br i1 %120, label %121, label %156, !dbg !2391

121:                                              ; preds = %118
  %122 = load i32, i32* %8, align 4, !dbg !2392
  %123 = icmp eq i32 %122, 0, !dbg !2395
  br i1 %123, label %124, label %130, !dbg !2396

124:                                              ; preds = %121
  %125 = load i32, i32* %9, align 4, !dbg !2397
  %126 = icmp eq i32 %125, 0, !dbg !2398
  br i1 %126, label %127, label %130, !dbg !2399

127:                                              ; preds = %124
  %128 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2400
  %129 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %128, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.74, i64 0, i64 0)), !dbg !2402
  br label %155, !dbg !2403

130:                                              ; preds = %124, %121
  call void @llvm.dbg.declare(metadata [32 x i8]* %16, metadata !2404, metadata !DIExpression()), !dbg !2409
  call void @llvm.dbg.declare(metadata [32 x i8]* %17, metadata !2410, metadata !DIExpression()), !dbg !2411
  call void @llvm.dbg.declare(metadata %struct.UInt64* %18, metadata !2412, metadata !DIExpression()), !dbg !2420
  call void @llvm.dbg.declare(metadata %struct.UInt64* %19, metadata !2421, metadata !DIExpression()), !dbg !2422
  call void @llvm.dbg.declare(metadata double* %20, metadata !2423, metadata !DIExpression()), !dbg !2424
  call void @llvm.dbg.declare(metadata double* %21, metadata !2425, metadata !DIExpression()), !dbg !2426
  %131 = load i32, i32* %8, align 4, !dbg !2427
  %132 = load i32, i32* %9, align 4, !dbg !2428
  call void @uInt64_from_UInt32s(%struct.UInt64* %18, i32 %131, i32 %132), !dbg !2429
  %133 = load i32, i32* %10, align 4, !dbg !2430
  %134 = load i32, i32* %11, align 4, !dbg !2431
  call void @uInt64_from_UInt32s(%struct.UInt64* %19, i32 %133, i32 %134), !dbg !2432
  %135 = call double @uInt64_to_double(%struct.UInt64* %18), !dbg !2433
  store double %135, double* %20, align 8, !dbg !2434
  %136 = call double @uInt64_to_double(%struct.UInt64* %19), !dbg !2435
  store double %136, double* %21, align 8, !dbg !2436
  %137 = getelementptr inbounds [32 x i8], [32 x i8]* %16, i64 0, i64 0, !dbg !2437
  call void @uInt64_toAscii(i8* %137, %struct.UInt64* %18), !dbg !2438
  %138 = getelementptr inbounds [32 x i8], [32 x i8]* %17, i64 0, i64 0, !dbg !2439
  call void @uInt64_toAscii(i8* %138, %struct.UInt64* %19), !dbg !2440
  %139 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2441
  %140 = load double, double* %20, align 8, !dbg !2442
  %141 = load double, double* %21, align 8, !dbg !2443
  %142 = fdiv double %140, %141, !dbg !2444
  %143 = load double, double* %21, align 8, !dbg !2445
  %144 = fmul double 8.000000e+00, %143, !dbg !2446
  %145 = load double, double* %20, align 8, !dbg !2447
  %146 = fdiv double %144, %145, !dbg !2448
  %147 = load double, double* %21, align 8, !dbg !2449
  %148 = load double, double* %20, align 8, !dbg !2450
  %149 = fdiv double %147, %148, !dbg !2451
  %150 = fsub double 1.000000e+00, %149, !dbg !2452
  %151 = fmul double 1.000000e+02, %150, !dbg !2453
  %152 = getelementptr inbounds [32 x i8], [32 x i8]* %16, i64 0, i64 0, !dbg !2454
  %153 = getelementptr inbounds [32 x i8], [32 x i8]* %17, i64 0, i64 0, !dbg !2455
  %154 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %139, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.75, i64 0, i64 0), double %142, double %146, double %151, i8* %152, i8* %153), !dbg !2456
  br label %155

155:                                              ; preds = %130, %127
  br label %156, !dbg !2457

156:                                              ; preds = %155, %118
  ret void, !dbg !2458

157:                                              ; preds = %77, %71, %39
  call void @llvm.dbg.label(metadata !2459), !dbg !2460
  %158 = load i8*, i8** %5, align 8, !dbg !2461
  call void @BZ2_bzWriteClose64(i32* %13, i8* %158, i32 1, i32* %8, i32* %9, i32* %10, i32* %11), !dbg !2462
  %159 = load i32, i32* %12, align 4, !dbg !2463
  switch i32 %159, label %164 [
    i32 -9, label %160
    i32 -3, label %161
    i32 -6, label %162
  ], !dbg !2464

160:                                              ; preds = %157
  call void @configError() #13, !dbg !2465
  unreachable, !dbg !2465

161:                                              ; preds = %157
  call void @outOfMemory() #13, !dbg !2467
  unreachable, !dbg !2467

162:                                              ; preds = %157
  br label %163, !dbg !2467

163:                                              ; preds = %162, %117, %111, %105, %98, %88, %82, %60, %30, %25
  call void @llvm.dbg.label(metadata !2468), !dbg !2469
  call void @ioError() #13, !dbg !2470
  unreachable, !dbg !2470

164:                                              ; preds = %157
  call void @panic(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.76, i64 0, i64 0)) #13, !dbg !2471
  unreachable, !dbg !2471
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @applySavedTimeInfoToOutputFile(i8* %0) #0 !dbg !2472 {
  %2 = alloca i8*, align 8
  %3 = alloca i32, align 4
  %4 = alloca %struct.utimbuf, align 8
  store i8* %0, i8** %2, align 8
  call void @llvm.dbg.declare(metadata i8** %2, metadata !2473, metadata !DIExpression()), !dbg !2474
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2475, metadata !DIExpression()), !dbg !2476
  call void @llvm.dbg.declare(metadata %struct.utimbuf* %4, metadata !2477, metadata !DIExpression()), !dbg !2483
  %5 = load i64, i64* getelementptr inbounds (%struct.stat, %struct.stat* @fileMetaInfo, i32 0, i32 11, i32 0), align 8, !dbg !2484
  %6 = getelementptr inbounds %struct.utimbuf, %struct.utimbuf* %4, i32 0, i32 0, !dbg !2485
  store i64 %5, i64* %6, align 8, !dbg !2486
  %7 = load i64, i64* getelementptr inbounds (%struct.stat, %struct.stat* @fileMetaInfo, i32 0, i32 12, i32 0), align 8, !dbg !2487
  %8 = getelementptr inbounds %struct.utimbuf, %struct.utimbuf* %4, i32 0, i32 1, !dbg !2488
  store i64 %7, i64* %8, align 8, !dbg !2489
  %9 = load i8*, i8** %2, align 8, !dbg !2490
  %10 = call i32 @utime(i8* %9, %struct.utimbuf* %4) #10, !dbg !2491
  store i32 %10, i32* %3, align 4, !dbg !2492
  %11 = load i32, i32* %3, align 4, !dbg !2493
  %12 = icmp ne i32 %11, 0, !dbg !2493
  br i1 %12, label %13, label %14, !dbg !2496

13:                                               ; preds = %1
  call void @ioError() #13, !dbg !2493
  unreachable, !dbg !2493

14:                                               ; preds = %1
  ret void, !dbg !2497
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @logCompressSize(i32 %0) #0 !dbg !2498 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !2501, metadata !DIExpression()), !dbg !2502
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2503, metadata !DIExpression()), !dbg !2504
  %4 = bitcast i32* %3 to i8*, !dbg !2505
  call void @llvm.var.annotation(i8* %4, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.78, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.79, i32 0, i32 0), i32 793), !dbg !2505
  %5 = load i32, i32* %2, align 4, !dbg !2506
  store i32 %5, i32* %3, align 4, !dbg !2504
  %6 = load i32, i32* %3, align 4, !dbg !2507
  %7 = icmp sgt i32 %6, 0, !dbg !2509
  br i1 %7, label %8, label %12, !dbg !2510

8:                                                ; preds = %1
  %9 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !2511
  %10 = load i32, i32* %3, align 4, !dbg !2512
  %11 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %9, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.80, i64 0, i64 0), i32 %10), !dbg !2513
  br label %12, !dbg !2513

12:                                               ; preds = %8, %1
  ret void, !dbg !2514
}

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @ioError() #6 !dbg !2515 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2516
  %2 = load i8*, i8** @progName, align 8, !dbg !2517
  %3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([65 x i8], [65 x i8]* @.str.81, i64 0, i64 0), i8* %2), !dbg !2518
  %4 = load i8*, i8** @progName, align 8, !dbg !2519
  call void @perror(i8* %4), !dbg !2520
  call void @showFileNames(), !dbg !2521
  call void @cleanUpAndFail(i32 1) #13, !dbg !2522
  unreachable, !dbg !2522
}

; Function Attrs: nounwind
declare dso_local i32 @lstat(i8*, %struct.stat*) #2

declare dso_local i32 @open(i8*, i32, ...) #5

; Function Attrs: nounwind
declare dso_local %struct._IO_FILE* @fdopen(i32, i8*) #2

declare dso_local i32 @close(i32) #5

; Function Attrs: nounwind
declare dso_local i32 @ferror(%struct._IO_FILE*) #2

declare dso_local i8* @BZ2_bzWriteOpen(i32*, %struct._IO_FILE*, i32, i32, i32) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @myfeof(%struct._IO_FILE* %0) #0 !dbg !2523 {
  %2 = alloca i8, align 1
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca i32, align 4
  store %struct._IO_FILE* %0, %struct._IO_FILE** %3, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !2526, metadata !DIExpression()), !dbg !2527
  call void @llvm.dbg.declare(metadata i32* %4, metadata !2528, metadata !DIExpression()), !dbg !2529
  %5 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2530
  %6 = call i32 @fgetc(%struct._IO_FILE* %5), !dbg !2531
  store i32 %6, i32* %4, align 4, !dbg !2529
  %7 = load i32, i32* %4, align 4, !dbg !2532
  %8 = icmp eq i32 %7, -1, !dbg !2534
  br i1 %8, label %9, label %10, !dbg !2535

9:                                                ; preds = %1
  store i8 1, i8* %2, align 1, !dbg !2536
  br label %14, !dbg !2536

10:                                               ; preds = %1
  %11 = load i32, i32* %4, align 4, !dbg !2537
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !2538
  %13 = call i32 @ungetc(i32 %11, %struct._IO_FILE* %12), !dbg !2539
  store i8 0, i8* %2, align 1, !dbg !2540
  br label %14, !dbg !2540

14:                                               ; preds = %10, %9
  %15 = load i8, i8* %2, align 1, !dbg !2541
  ret i8 %15, !dbg !2541
}

declare dso_local i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #5

declare dso_local void @BZ2_bzWrite(i32*, i8*, i8*, i32) #5

declare dso_local void @BZ2_bzWriteClose64(i32*, i8*, i32, i32*, i32*, i32*, i32*) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal void @applySavedFileAttrToOutputFile(i32 %0) #0 !dbg !2542 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !2543, metadata !DIExpression()), !dbg !2544
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2545, metadata !DIExpression()), !dbg !2546
  %4 = load i32, i32* %2, align 4, !dbg !2547
  %5 = load i32, i32* getelementptr inbounds (%struct.stat, %struct.stat* @fileMetaInfo, i32 0, i32 3), align 8, !dbg !2548
  %6 = call i32 @fchmod(i32 %4, i32 %5) #10, !dbg !2549
  store i32 %6, i32* %3, align 4, !dbg !2550
  %7 = load i32, i32* %3, align 4, !dbg !2551
  %8 = icmp ne i32 %7, 0, !dbg !2551
  br i1 %8, label %9, label %10, !dbg !2554

9:                                                ; preds = %1
  call void @ioError() #13, !dbg !2551
  unreachable, !dbg !2551

10:                                               ; preds = %1
  %11 = load i32, i32* %2, align 4, !dbg !2555
  %12 = load i32, i32* getelementptr inbounds (%struct.stat, %struct.stat* @fileMetaInfo, i32 0, i32 4), align 4, !dbg !2556
  %13 = load i32, i32* getelementptr inbounds (%struct.stat, %struct.stat* @fileMetaInfo, i32 0, i32 5), align 8, !dbg !2557
  %14 = call i32 @fchown(i32 %11, i32 %12, i32 %13) #10, !dbg !2558
  ret void, !dbg !2559
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @uInt64_from_UInt32s(%struct.UInt64* %0, i32 %1, i32 %2) #0 !dbg !2560 {
  %4 = alloca %struct.UInt64*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store %struct.UInt64* %0, %struct.UInt64** %4, align 8
  call void @llvm.dbg.declare(metadata %struct.UInt64** %4, metadata !2564, metadata !DIExpression()), !dbg !2565
  store i32 %1, i32* %5, align 4
  call void @llvm.dbg.declare(metadata i32* %5, metadata !2566, metadata !DIExpression()), !dbg !2567
  store i32 %2, i32* %6, align 4
  call void @llvm.dbg.declare(metadata i32* %6, metadata !2568, metadata !DIExpression()), !dbg !2569
  %7 = load i32, i32* %6, align 4, !dbg !2570
  %8 = lshr i32 %7, 24, !dbg !2571
  %9 = and i32 %8, 255, !dbg !2572
  %10 = trunc i32 %9 to i8, !dbg !2573
  %11 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2574
  %12 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %11, i32 0, i32 0, !dbg !2575
  %13 = getelementptr inbounds [8 x i8], [8 x i8]* %12, i64 0, i64 7, !dbg !2574
  store i8 %10, i8* %13, align 1, !dbg !2576
  %14 = load i32, i32* %6, align 4, !dbg !2577
  %15 = lshr i32 %14, 16, !dbg !2578
  %16 = and i32 %15, 255, !dbg !2579
  %17 = trunc i32 %16 to i8, !dbg !2580
  %18 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2581
  %19 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %18, i32 0, i32 0, !dbg !2582
  %20 = getelementptr inbounds [8 x i8], [8 x i8]* %19, i64 0, i64 6, !dbg !2581
  store i8 %17, i8* %20, align 1, !dbg !2583
  %21 = load i32, i32* %6, align 4, !dbg !2584
  %22 = lshr i32 %21, 8, !dbg !2585
  %23 = and i32 %22, 255, !dbg !2586
  %24 = trunc i32 %23 to i8, !dbg !2587
  %25 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2588
  %26 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %25, i32 0, i32 0, !dbg !2589
  %27 = getelementptr inbounds [8 x i8], [8 x i8]* %26, i64 0, i64 5, !dbg !2588
  store i8 %24, i8* %27, align 1, !dbg !2590
  %28 = load i32, i32* %6, align 4, !dbg !2591
  %29 = and i32 %28, 255, !dbg !2592
  %30 = trunc i32 %29 to i8, !dbg !2593
  %31 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2594
  %32 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %31, i32 0, i32 0, !dbg !2595
  %33 = getelementptr inbounds [8 x i8], [8 x i8]* %32, i64 0, i64 4, !dbg !2594
  store i8 %30, i8* %33, align 1, !dbg !2596
  %34 = load i32, i32* %5, align 4, !dbg !2597
  %35 = lshr i32 %34, 24, !dbg !2598
  %36 = and i32 %35, 255, !dbg !2599
  %37 = trunc i32 %36 to i8, !dbg !2600
  %38 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2601
  %39 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %38, i32 0, i32 0, !dbg !2602
  %40 = getelementptr inbounds [8 x i8], [8 x i8]* %39, i64 0, i64 3, !dbg !2601
  store i8 %37, i8* %40, align 1, !dbg !2603
  %41 = load i32, i32* %5, align 4, !dbg !2604
  %42 = lshr i32 %41, 16, !dbg !2605
  %43 = and i32 %42, 255, !dbg !2606
  %44 = trunc i32 %43 to i8, !dbg !2607
  %45 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2608
  %46 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %45, i32 0, i32 0, !dbg !2609
  %47 = getelementptr inbounds [8 x i8], [8 x i8]* %46, i64 0, i64 2, !dbg !2608
  store i8 %44, i8* %47, align 1, !dbg !2610
  %48 = load i32, i32* %5, align 4, !dbg !2611
  %49 = lshr i32 %48, 8, !dbg !2612
  %50 = and i32 %49, 255, !dbg !2613
  %51 = trunc i32 %50 to i8, !dbg !2614
  %52 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2615
  %53 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %52, i32 0, i32 0, !dbg !2616
  %54 = getelementptr inbounds [8 x i8], [8 x i8]* %53, i64 0, i64 1, !dbg !2615
  store i8 %51, i8* %54, align 1, !dbg !2617
  %55 = load i32, i32* %5, align 4, !dbg !2618
  %56 = and i32 %55, 255, !dbg !2619
  %57 = trunc i32 %56 to i8, !dbg !2620
  %58 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2621
  %59 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %58, i32 0, i32 0, !dbg !2622
  %60 = getelementptr inbounds [8 x i8], [8 x i8]* %59, i64 0, i64 0, !dbg !2621
  store i8 %57, i8* %60, align 1, !dbg !2623
  ret void, !dbg !2624
}

; Function Attrs: noinline nounwind optnone uwtable
define internal double @uInt64_to_double(%struct.UInt64* %0) #0 !dbg !2625 {
  %2 = alloca %struct.UInt64*, align 8
  %3 = alloca i32, align 4
  %4 = alloca double, align 8
  %5 = alloca double, align 8
  store %struct.UInt64* %0, %struct.UInt64** %2, align 8
  call void @llvm.dbg.declare(metadata %struct.UInt64** %2, metadata !2628, metadata !DIExpression()), !dbg !2629
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2630, metadata !DIExpression()), !dbg !2631
  call void @llvm.dbg.declare(metadata double* %4, metadata !2632, metadata !DIExpression()), !dbg !2633
  store double 1.000000e+00, double* %4, align 8, !dbg !2633
  call void @llvm.dbg.declare(metadata double* %5, metadata !2634, metadata !DIExpression()), !dbg !2635
  store double 0.000000e+00, double* %5, align 8, !dbg !2635
  store i32 0, i32* %3, align 4, !dbg !2636
  br label %6, !dbg !2638

6:                                                ; preds = %23, %1
  %7 = load i32, i32* %3, align 4, !dbg !2639
  %8 = icmp slt i32 %7, 8, !dbg !2641
  br i1 %8, label %9, label %26, !dbg !2642

9:                                                ; preds = %6
  %10 = load double, double* %4, align 8, !dbg !2643
  %11 = load %struct.UInt64*, %struct.UInt64** %2, align 8, !dbg !2645
  %12 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %11, i32 0, i32 0, !dbg !2646
  %13 = load i32, i32* %3, align 4, !dbg !2647
  %14 = sext i32 %13 to i64, !dbg !2645
  %15 = getelementptr inbounds [8 x i8], [8 x i8]* %12, i64 0, i64 %14, !dbg !2645
  %16 = load i8, i8* %15, align 1, !dbg !2645
  %17 = uitofp i8 %16 to double, !dbg !2648
  %18 = fmul double %10, %17, !dbg !2649
  %19 = load double, double* %5, align 8, !dbg !2650
  %20 = fadd double %19, %18, !dbg !2650
  store double %20, double* %5, align 8, !dbg !2650
  %21 = load double, double* %4, align 8, !dbg !2651
  %22 = fmul double %21, 2.560000e+02, !dbg !2651
  store double %22, double* %4, align 8, !dbg !2651
  br label %23, !dbg !2652

23:                                               ; preds = %9
  %24 = load i32, i32* %3, align 4, !dbg !2653
  %25 = add nsw i32 %24, 1, !dbg !2653
  store i32 %25, i32* %3, align 4, !dbg !2653
  br label %6, !dbg !2654, !llvm.loop !2655

26:                                               ; preds = %6
  %27 = load double, double* %5, align 8, !dbg !2657
  ret double %27, !dbg !2658
}

; Function Attrs: noinline nounwind optnone uwtable
define internal void @uInt64_toAscii(i8* %0, %struct.UInt64* %1) #0 !dbg !2659 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.UInt64*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca [32 x i8], align 16
  %8 = alloca i32, align 4
  %9 = alloca %struct.UInt64, align 1
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !2662, metadata !DIExpression()), !dbg !2663
  store %struct.UInt64* %1, %struct.UInt64** %4, align 8
  call void @llvm.dbg.declare(metadata %struct.UInt64** %4, metadata !2664, metadata !DIExpression()), !dbg !2665
  call void @llvm.dbg.declare(metadata i32* %5, metadata !2666, metadata !DIExpression()), !dbg !2667
  call void @llvm.dbg.declare(metadata i32* %6, metadata !2668, metadata !DIExpression()), !dbg !2669
  call void @llvm.dbg.declare(metadata [32 x i8]* %7, metadata !2670, metadata !DIExpression()), !dbg !2672
  call void @llvm.dbg.declare(metadata i32* %8, metadata !2673, metadata !DIExpression()), !dbg !2674
  store i32 0, i32* %8, align 4, !dbg !2674
  call void @llvm.dbg.declare(metadata %struct.UInt64* %9, metadata !2675, metadata !DIExpression()), !dbg !2676
  %10 = load %struct.UInt64*, %struct.UInt64** %4, align 8, !dbg !2677
  %11 = bitcast %struct.UInt64* %9 to i8*, !dbg !2678
  %12 = bitcast %struct.UInt64* %10 to i8*, !dbg !2678
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %11, i8* align 1 %12, i64 8, i1 false), !dbg !2678
  br label %13, !dbg !2679

13:                                               ; preds = %23, %2
  %14 = call i32 @uInt64_qrm10(%struct.UInt64* %9), !dbg !2680
  store i32 %14, i32* %6, align 4, !dbg !2682
  %15 = load i32, i32* %6, align 4, !dbg !2683
  %16 = add nsw i32 %15, 48, !dbg !2684
  %17 = trunc i32 %16 to i8, !dbg !2683
  %18 = load i32, i32* %8, align 4, !dbg !2685
  %19 = sext i32 %18 to i64, !dbg !2686
  %20 = getelementptr inbounds [32 x i8], [32 x i8]* %7, i64 0, i64 %19, !dbg !2686
  store i8 %17, i8* %20, align 1, !dbg !2687
  %21 = load i32, i32* %8, align 4, !dbg !2688
  %22 = add nsw i32 %21, 1, !dbg !2688
  store i32 %22, i32* %8, align 4, !dbg !2688
  br label %23, !dbg !2689

23:                                               ; preds = %13
  %24 = call zeroext i8 @uInt64_isZero(%struct.UInt64* %9), !dbg !2690
  %25 = icmp ne i8 %24, 0, !dbg !2691
  %26 = xor i1 %25, true, !dbg !2691
  br i1 %26, label %13, label %27, !dbg !2689, !llvm.loop !2692

27:                                               ; preds = %23
  %28 = load i8*, i8** %3, align 8, !dbg !2694
  %29 = load i32, i32* %8, align 4, !dbg !2695
  %30 = sext i32 %29 to i64, !dbg !2694
  %31 = getelementptr inbounds i8, i8* %28, i64 %30, !dbg !2694
  store i8 0, i8* %31, align 1, !dbg !2696
  store i32 0, i32* %5, align 4, !dbg !2697
  br label %32, !dbg !2699

32:                                               ; preds = %48, %27
  %33 = load i32, i32* %5, align 4, !dbg !2700
  %34 = load i32, i32* %8, align 4, !dbg !2702
  %35 = icmp slt i32 %33, %34, !dbg !2703
  br i1 %35, label %36, label %51, !dbg !2704

36:                                               ; preds = %32
  %37 = load i32, i32* %8, align 4, !dbg !2705
  %38 = load i32, i32* %5, align 4, !dbg !2706
  %39 = sub nsw i32 %37, %38, !dbg !2707
  %40 = sub nsw i32 %39, 1, !dbg !2708
  %41 = sext i32 %40 to i64, !dbg !2709
  %42 = getelementptr inbounds [32 x i8], [32 x i8]* %7, i64 0, i64 %41, !dbg !2709
  %43 = load i8, i8* %42, align 1, !dbg !2709
  %44 = load i8*, i8** %3, align 8, !dbg !2710
  %45 = load i32, i32* %5, align 4, !dbg !2711
  %46 = sext i32 %45 to i64, !dbg !2710
  %47 = getelementptr inbounds i8, i8* %44, i64 %46, !dbg !2710
  store i8 %43, i8* %47, align 1, !dbg !2712
  br label %48, !dbg !2710

48:                                               ; preds = %36
  %49 = load i32, i32* %5, align 4, !dbg !2713
  %50 = add nsw i32 %49, 1, !dbg !2713
  store i32 %50, i32* %5, align 4, !dbg !2713
  br label %32, !dbg !2714, !llvm.loop !2715

51:                                               ; preds = %32
  ret void, !dbg !2717
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.label(metadata) #1

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @configError() #6 !dbg !2718 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !2719
  %2 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([236 x i8], [236 x i8]* @.str.77, i64 0, i64 0)), !dbg !2720
  call void @setExit(i32 3), !dbg !2721
  %3 = load i32, i32* @exitValue, align 4, !dbg !2722
  call void @exit(i32 %3) #12, !dbg !2723
  unreachable, !dbg !2723
}

declare dso_local i32 @fgetc(%struct._IO_FILE*) #5

declare dso_local i32 @ungetc(i32, %struct._IO_FILE*) #5

; Function Attrs: nounwind
declare dso_local i32 @fchmod(i32, i32) #2

; Function Attrs: nounwind
declare dso_local i32 @fchown(i32, i32, i32) #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #8

; Function Attrs: noinline nounwind optnone uwtable
define internal i32 @uInt64_qrm10(%struct.UInt64* %0) #0 !dbg !2724 {
  %2 = alloca %struct.UInt64*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store %struct.UInt64* %0, %struct.UInt64** %2, align 8
  call void @llvm.dbg.declare(metadata %struct.UInt64** %2, metadata !2727, metadata !DIExpression()), !dbg !2728
  call void @llvm.dbg.declare(metadata i32* %3, metadata !2729, metadata !DIExpression()), !dbg !2730
  call void @llvm.dbg.declare(metadata i32* %4, metadata !2731, metadata !DIExpression()), !dbg !2732
  call void @llvm.dbg.declare(metadata i32* %5, metadata !2733, metadata !DIExpression()), !dbg !2734
  store i32 0, i32* %3, align 4, !dbg !2735
  store i32 7, i32* %5, align 4, !dbg !2736
  br label %6, !dbg !2738

6:                                                ; preds = %30, %1
  %7 = load i32, i32* %5, align 4, !dbg !2739
  %8 = icmp sge i32 %7, 0, !dbg !2741
  br i1 %8, label %9, label %33, !dbg !2742

9:                                                ; preds = %6
  %10 = load i32, i32* %3, align 4, !dbg !2743
  %11 = mul i32 %10, 256, !dbg !2745
  %12 = load %struct.UInt64*, %struct.UInt64** %2, align 8, !dbg !2746
  %13 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %12, i32 0, i32 0, !dbg !2747
  %14 = load i32, i32* %5, align 4, !dbg !2748
  %15 = sext i32 %14 to i64, !dbg !2746
  %16 = getelementptr inbounds [8 x i8], [8 x i8]* %13, i64 0, i64 %15, !dbg !2746
  %17 = load i8, i8* %16, align 1, !dbg !2746
  %18 = zext i8 %17 to i32, !dbg !2746
  %19 = add i32 %11, %18, !dbg !2749
  store i32 %19, i32* %4, align 4, !dbg !2750
  %20 = load i32, i32* %4, align 4, !dbg !2751
  %21 = udiv i32 %20, 10, !dbg !2752
  %22 = trunc i32 %21 to i8, !dbg !2751
  %23 = load %struct.UInt64*, %struct.UInt64** %2, align 8, !dbg !2753
  %24 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %23, i32 0, i32 0, !dbg !2754
  %25 = load i32, i32* %5, align 4, !dbg !2755
  %26 = sext i32 %25 to i64, !dbg !2753
  %27 = getelementptr inbounds [8 x i8], [8 x i8]* %24, i64 0, i64 %26, !dbg !2753
  store i8 %22, i8* %27, align 1, !dbg !2756
  %28 = load i32, i32* %4, align 4, !dbg !2757
  %29 = urem i32 %28, 10, !dbg !2758
  store i32 %29, i32* %3, align 4, !dbg !2759
  br label %30, !dbg !2760

30:                                               ; preds = %9
  %31 = load i32, i32* %5, align 4, !dbg !2761
  %32 = add nsw i32 %31, -1, !dbg !2761
  store i32 %32, i32* %5, align 4, !dbg !2761
  br label %6, !dbg !2762, !llvm.loop !2763

33:                                               ; preds = %6
  %34 = load i32, i32* %3, align 4, !dbg !2765
  ret i32 %34, !dbg !2766
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @uInt64_isZero(%struct.UInt64* %0) #0 !dbg !2767 {
  %2 = alloca i8, align 1
  %3 = alloca %struct.UInt64*, align 8
  %4 = alloca i32, align 4
  store %struct.UInt64* %0, %struct.UInt64** %3, align 8
  call void @llvm.dbg.declare(metadata %struct.UInt64** %3, metadata !2770, metadata !DIExpression()), !dbg !2771
  call void @llvm.dbg.declare(metadata i32* %4, metadata !2772, metadata !DIExpression()), !dbg !2773
  store i32 0, i32* %4, align 4, !dbg !2774
  br label %5, !dbg !2776

5:                                                ; preds = %19, %1
  %6 = load i32, i32* %4, align 4, !dbg !2777
  %7 = icmp slt i32 %6, 8, !dbg !2779
  br i1 %7, label %8, label %22, !dbg !2780

8:                                                ; preds = %5
  %9 = load %struct.UInt64*, %struct.UInt64** %3, align 8, !dbg !2781
  %10 = getelementptr inbounds %struct.UInt64, %struct.UInt64* %9, i32 0, i32 0, !dbg !2783
  %11 = load i32, i32* %4, align 4, !dbg !2784
  %12 = sext i32 %11 to i64, !dbg !2781
  %13 = getelementptr inbounds [8 x i8], [8 x i8]* %10, i64 0, i64 %12, !dbg !2781
  %14 = load i8, i8* %13, align 1, !dbg !2781
  %15 = zext i8 %14 to i32, !dbg !2781
  %16 = icmp ne i32 %15, 0, !dbg !2785
  br i1 %16, label %17, label %18, !dbg !2786

17:                                               ; preds = %8
  store i8 0, i8* %2, align 1, !dbg !2787
  br label %23, !dbg !2787

18:                                               ; preds = %8
  br label %19, !dbg !2788

19:                                               ; preds = %18
  %20 = load i32, i32* %4, align 4, !dbg !2789
  %21 = add nsw i32 %20, 1, !dbg !2789
  store i32 %21, i32* %4, align 4, !dbg !2789
  br label %5, !dbg !2790, !llvm.loop !2791

22:                                               ; preds = %5
  store i8 1, i8* %2, align 1, !dbg !2793
  br label %23, !dbg !2793

23:                                               ; preds = %22, %17
  %24 = load i8, i8* %2, align 1, !dbg !2794
  ret i8 %24, !dbg !2794
}

; Function Attrs: nounwind
declare dso_local i32 @utime(i8*, %struct.utimbuf*) #2

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #9

declare dso_local void @perror(i8*) #5

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @mapSuffix(i8* %0, i8* %1, i8* %2) #0 !dbg !2795 {
  %4 = alloca i8, align 1
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i8*, align 8
  store i8* %0, i8** %5, align 8
  call void @llvm.dbg.declare(metadata i8** %5, metadata !2798, metadata !DIExpression()), !dbg !2799
  store i8* %1, i8** %6, align 8
  call void @llvm.dbg.declare(metadata i8** %6, metadata !2800, metadata !DIExpression()), !dbg !2801
  store i8* %2, i8** %7, align 8
  call void @llvm.dbg.declare(metadata i8** %7, metadata !2802, metadata !DIExpression()), !dbg !2803
  %8 = load i8*, i8** %5, align 8, !dbg !2804
  %9 = load i8*, i8** %6, align 8, !dbg !2806
  %10 = call zeroext i8 @hasSuffix(i8* %8, i8* %9), !dbg !2807
  %11 = icmp ne i8 %10, 0, !dbg !2807
  br i1 %11, label %13, label %12, !dbg !2808

12:                                               ; preds = %3
  store i8 0, i8* %4, align 1, !dbg !2809
  br label %24, !dbg !2809

13:                                               ; preds = %3
  %14 = load i8*, i8** %5, align 8, !dbg !2810
  %15 = load i8*, i8** %5, align 8, !dbg !2811
  %16 = call i64 @strlen(i8* %15) #11, !dbg !2812
  %17 = load i8*, i8** %6, align 8, !dbg !2813
  %18 = call i64 @strlen(i8* %17) #11, !dbg !2814
  %19 = sub i64 %16, %18, !dbg !2815
  %20 = getelementptr inbounds i8, i8* %14, i64 %19, !dbg !2810
  store i8 0, i8* %20, align 1, !dbg !2816
  %21 = load i8*, i8** %5, align 8, !dbg !2817
  %22 = load i8*, i8** %7, align 8, !dbg !2818
  %23 = call i8* @strcat(i8* %21, i8* %22) #10, !dbg !2819
  store i8 1, i8* %4, align 1, !dbg !2820
  br label %24, !dbg !2820

24:                                               ; preds = %13, %12
  %25 = load i8, i8* %4, align 1, !dbg !2821
  ret i8 %25, !dbg !2821
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @uncompressStream(%struct._IO_FILE* %0, %struct._IO_FILE* %1) #0 !dbg !2822 {
  %3 = alloca i8, align 1
  %4 = alloca %struct._IO_FILE*, align 8
  %5 = alloca %struct._IO_FILE*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca [5000 x i8], align 16
  %14 = alloca [5000 x i8], align 16
  %15 = alloca i32, align 4
  %16 = alloca i8*, align 8
  %17 = alloca i8*, align 8
  %18 = alloca i32, align 4
  store %struct._IO_FILE* %0, %struct._IO_FILE** %4, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %4, metadata !2825, metadata !DIExpression()), !dbg !2826
  store %struct._IO_FILE* %1, %struct._IO_FILE** %5, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %5, metadata !2827, metadata !DIExpression()), !dbg !2828
  call void @llvm.dbg.declare(metadata i8** %6, metadata !2829, metadata !DIExpression()), !dbg !2830
  store i8* null, i8** %6, align 8, !dbg !2830
  call void @llvm.dbg.declare(metadata i32* %7, metadata !2831, metadata !DIExpression()), !dbg !2832
  call void @llvm.dbg.declare(metadata i32* %8, metadata !2833, metadata !DIExpression()), !dbg !2834
  call void @llvm.dbg.declare(metadata i32* %9, metadata !2835, metadata !DIExpression()), !dbg !2836
  call void @llvm.dbg.declare(metadata i32* %10, metadata !2837, metadata !DIExpression()), !dbg !2838
  call void @llvm.dbg.declare(metadata i32* %11, metadata !2839, metadata !DIExpression()), !dbg !2840
  call void @llvm.dbg.declare(metadata i32* %12, metadata !2841, metadata !DIExpression()), !dbg !2842
  call void @llvm.dbg.declare(metadata [5000 x i8]* %13, metadata !2843, metadata !DIExpression()), !dbg !2844
  call void @llvm.dbg.declare(metadata [5000 x i8]* %14, metadata !2845, metadata !DIExpression()), !dbg !2846
  call void @llvm.dbg.declare(metadata i32* %15, metadata !2847, metadata !DIExpression()), !dbg !2848
  call void @llvm.dbg.declare(metadata i8** %16, metadata !2849, metadata !DIExpression()), !dbg !2850
  call void @llvm.dbg.declare(metadata i8** %17, metadata !2851, metadata !DIExpression()), !dbg !2852
  store i32 0, i32* %15, align 4, !dbg !2853
  store i32 0, i32* %11, align 4, !dbg !2854
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !2855
  %20 = call i32 @ferror(%struct._IO_FILE* %19) #10, !dbg !2857
  %21 = icmp ne i32 %20, 0, !dbg !2857
  br i1 %21, label %22, label %23, !dbg !2858

22:                                               ; preds = %2
  br label %213, !dbg !2859

23:                                               ; preds = %2
  %24 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2860
  %25 = call i32 @ferror(%struct._IO_FILE* %24) #10, !dbg !2862
  %26 = icmp ne i32 %25, 0, !dbg !2862
  br i1 %26, label %27, label %28, !dbg !2863

27:                                               ; preds = %23
  br label %213, !dbg !2864

28:                                               ; preds = %23
  br label %29, !dbg !2865

29:                                               ; preds = %28, %118
  %30 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2866
  %31 = load i32, i32* @verbosity, align 4, !dbg !2868
  %32 = load i8, i8* @smallMode, align 1, !dbg !2869
  %33 = zext i8 %32 to i32, !dbg !2870
  %34 = getelementptr inbounds [5000 x i8], [5000 x i8]* %14, i64 0, i64 0, !dbg !2871
  %35 = load i32, i32* %15, align 4, !dbg !2872
  %36 = call i8* @BZ2_bzReadOpen(i32* %7, %struct._IO_FILE* %30, i32 %31, i32 %33, i8* %34, i32 %35), !dbg !2873
  store i8* %36, i8** %6, align 8, !dbg !2874
  %37 = load i8*, i8** %6, align 8, !dbg !2875
  %38 = icmp eq i8* %37, null, !dbg !2877
  br i1 %38, label %42, label %39, !dbg !2878

39:                                               ; preds = %29
  %40 = load i32, i32* %7, align 4, !dbg !2879
  %41 = icmp ne i32 %40, 0, !dbg !2880
  br i1 %41, label %42, label %43, !dbg !2881

42:                                               ; preds = %39, %29
  br label %208, !dbg !2882

43:                                               ; preds = %39
  %44 = load i32, i32* %11, align 4, !dbg !2883
  %45 = add nsw i32 %44, 1, !dbg !2883
  store i32 %45, i32* %11, align 4, !dbg !2883
  br label %46, !dbg !2884

46:                                               ; preds = %76, %43
  %47 = load i32, i32* %7, align 4, !dbg !2885
  %48 = icmp eq i32 %47, 0, !dbg !2886
  br i1 %48, label %49, label %77, !dbg !2884

49:                                               ; preds = %46
  %50 = load i8*, i8** %6, align 8, !dbg !2887
  %51 = getelementptr inbounds [5000 x i8], [5000 x i8]* %13, i64 0, i64 0, !dbg !2889
  %52 = call i32 @BZ2_bzRead(i32* %7, i8* %50, i8* %51, i32 5000), !dbg !2890
  store i32 %52, i32* %10, align 4, !dbg !2891
  %53 = load i32, i32* %7, align 4, !dbg !2892
  %54 = icmp eq i32 %53, -5, !dbg !2894
  br i1 %54, label %55, label %56, !dbg !2895

55:                                               ; preds = %49
  br label %172, !dbg !2896

56:                                               ; preds = %49
  %57 = load i32, i32* %7, align 4, !dbg !2897
  %58 = icmp eq i32 %57, 0, !dbg !2899
  br i1 %58, label %62, label %59, !dbg !2900

59:                                               ; preds = %56
  %60 = load i32, i32* %7, align 4, !dbg !2901
  %61 = icmp eq i32 %60, 4, !dbg !2902
  br i1 %61, label %62, label %71, !dbg !2903

62:                                               ; preds = %59, %56
  %63 = load i32, i32* %10, align 4, !dbg !2904
  %64 = icmp sgt i32 %63, 0, !dbg !2905
  br i1 %64, label %65, label %71, !dbg !2906

65:                                               ; preds = %62
  %66 = getelementptr inbounds [5000 x i8], [5000 x i8]* %13, i64 0, i64 0, !dbg !2907
  %67 = load i32, i32* %10, align 4, !dbg !2908
  %68 = sext i32 %67 to i64, !dbg !2908
  %69 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !2909
  %70 = call i64 @fwrite(i8* %66, i64 1, i64 %68, %struct._IO_FILE* %69), !dbg !2910
  br label %71, !dbg !2910

71:                                               ; preds = %65, %62, %59
  %72 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !2911
  %73 = call i32 @ferror(%struct._IO_FILE* %72) #10, !dbg !2913
  %74 = icmp ne i32 %73, 0, !dbg !2913
  br i1 %74, label %75, label %76, !dbg !2914

75:                                               ; preds = %71
  br label %213, !dbg !2915

76:                                               ; preds = %71
  br label %46, !dbg !2884, !llvm.loop !2916

77:                                               ; preds = %46
  %78 = load i32, i32* %7, align 4, !dbg !2918
  %79 = icmp ne i32 %78, 4, !dbg !2920
  br i1 %79, label %80, label %81, !dbg !2921

80:                                               ; preds = %77
  br label %208, !dbg !2922

81:                                               ; preds = %77
  %82 = load i8*, i8** %6, align 8, !dbg !2923
  call void @BZ2_bzReadGetUnused(i32* %7, i8* %82, i8** %16, i32* %15), !dbg !2924
  %83 = load i32, i32* %7, align 4, !dbg !2925
  %84 = icmp ne i32 %83, 0, !dbg !2927
  br i1 %84, label %85, label %86, !dbg !2928

85:                                               ; preds = %81
  call void @panic(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.91, i64 0, i64 0)) #13, !dbg !2929
  unreachable, !dbg !2929

86:                                               ; preds = %81
  %87 = load i8*, i8** %16, align 8, !dbg !2930
  store i8* %87, i8** %17, align 8, !dbg !2931
  store i32 0, i32* %12, align 4, !dbg !2932
  br label %88, !dbg !2934

88:                                               ; preds = %101, %86
  %89 = load i32, i32* %12, align 4, !dbg !2935
  %90 = load i32, i32* %15, align 4, !dbg !2937
  %91 = icmp slt i32 %89, %90, !dbg !2938
  br i1 %91, label %92, label %104, !dbg !2939

92:                                               ; preds = %88
  %93 = load i8*, i8** %17, align 8, !dbg !2940
  %94 = load i32, i32* %12, align 4, !dbg !2941
  %95 = sext i32 %94 to i64, !dbg !2940
  %96 = getelementptr inbounds i8, i8* %93, i64 %95, !dbg !2940
  %97 = load i8, i8* %96, align 1, !dbg !2940
  %98 = load i32, i32* %12, align 4, !dbg !2942
  %99 = sext i32 %98 to i64, !dbg !2943
  %100 = getelementptr inbounds [5000 x i8], [5000 x i8]* %14, i64 0, i64 %99, !dbg !2943
  store i8 %97, i8* %100, align 1, !dbg !2944
  br label %101, !dbg !2943

101:                                              ; preds = %92
  %102 = load i32, i32* %12, align 4, !dbg !2945
  %103 = add nsw i32 %102, 1, !dbg !2945
  store i32 %103, i32* %12, align 4, !dbg !2945
  br label %88, !dbg !2946, !llvm.loop !2947

104:                                              ; preds = %88
  %105 = load i8*, i8** %6, align 8, !dbg !2949
  call void @BZ2_bzReadClose(i32* %7, i8* %105), !dbg !2950
  %106 = load i32, i32* %7, align 4, !dbg !2951
  %107 = icmp ne i32 %106, 0, !dbg !2953
  br i1 %107, label %108, label %109, !dbg !2954

108:                                              ; preds = %104
  call void @panic(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.91, i64 0, i64 0)) #13, !dbg !2955
  unreachable, !dbg !2955

109:                                              ; preds = %104
  %110 = load i32, i32* %15, align 4, !dbg !2956
  %111 = icmp eq i32 %110, 0, !dbg !2958
  br i1 %111, label %112, label %118, !dbg !2959

112:                                              ; preds = %109
  %113 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2960
  %114 = call zeroext i8 @myfeof(%struct._IO_FILE* %113), !dbg !2961
  %115 = zext i8 %114 to i32, !dbg !2961
  %116 = icmp ne i32 %115, 0, !dbg !2961
  br i1 %116, label %117, label %118, !dbg !2962

117:                                              ; preds = %112
  br label %119, !dbg !2963

118:                                              ; preds = %112, %109
  br label %29, !dbg !2865, !llvm.loop !2964

119:                                              ; preds = %117
  br label %120, !dbg !2865

120:                                              ; preds = %206, %119
  call void @llvm.dbg.label(metadata !2966), !dbg !2967
  %121 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2968
  %122 = call i32 @ferror(%struct._IO_FILE* %121) #10, !dbg !2970
  %123 = icmp ne i32 %122, 0, !dbg !2970
  br i1 %123, label %124, label %125, !dbg !2971

124:                                              ; preds = %120
  br label %213, !dbg !2972

125:                                              ; preds = %120
  %126 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !2973
  %127 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !2975
  %128 = icmp ne %struct._IO_FILE* %126, %127, !dbg !2976
  br i1 %128, label %129, label %137, !dbg !2977

129:                                              ; preds = %125
  call void @llvm.dbg.declare(metadata i32* %18, metadata !2978, metadata !DIExpression()), !dbg !2980
  %130 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !2981
  %131 = call i32 @fileno(%struct._IO_FILE* %130) #10, !dbg !2982
  store i32 %131, i32* %18, align 4, !dbg !2980
  %132 = load i32, i32* %18, align 4, !dbg !2983
  %133 = icmp slt i32 %132, 0, !dbg !2985
  br i1 %133, label %134, label %135, !dbg !2986

134:                                              ; preds = %129
  br label %213, !dbg !2987

135:                                              ; preds = %129
  %136 = load i32, i32* %18, align 4, !dbg !2988
  call void @applySavedFileAttrToOutputFile(i32 %136), !dbg !2989
  br label %137, !dbg !2990

137:                                              ; preds = %135, %125
  %138 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !2991
  %139 = call i32 @fclose(%struct._IO_FILE* %138), !dbg !2992
  store i32 %139, i32* %9, align 4, !dbg !2993
  %140 = load i32, i32* %9, align 4, !dbg !2994
  %141 = icmp eq i32 %140, -1, !dbg !2996
  br i1 %141, label %142, label %143, !dbg !2997

142:                                              ; preds = %137
  br label %213, !dbg !2998

143:                                              ; preds = %137
  %144 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !2999
  %145 = call i32 @ferror(%struct._IO_FILE* %144) #10, !dbg !3001
  %146 = icmp ne i32 %145, 0, !dbg !3001
  br i1 %146, label %147, label %148, !dbg !3002

147:                                              ; preds = %143
  br label %213, !dbg !3003

148:                                              ; preds = %143
  %149 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3004
  %150 = call i32 @fflush(%struct._IO_FILE* %149), !dbg !3005
  store i32 %150, i32* %9, align 4, !dbg !3006
  %151 = load i32, i32* %9, align 4, !dbg !3007
  %152 = icmp ne i32 %151, 0, !dbg !3009
  br i1 %152, label %153, label %154, !dbg !3010

153:                                              ; preds = %148
  br label %213, !dbg !3011

154:                                              ; preds = %148
  %155 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3012
  %156 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !3014
  %157 = icmp ne %struct._IO_FILE* %155, %156, !dbg !3015
  br i1 %157, label %158, label %165, !dbg !3016

158:                                              ; preds = %154
  %159 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3017
  %160 = call i32 @fclose(%struct._IO_FILE* %159), !dbg !3019
  store i32 %160, i32* %9, align 4, !dbg !3020
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !3021
  %161 = load i32, i32* %9, align 4, !dbg !3022
  %162 = icmp eq i32 %161, -1, !dbg !3024
  br i1 %162, label %163, label %164, !dbg !3025

163:                                              ; preds = %158
  br label %213, !dbg !3026

164:                                              ; preds = %158
  br label %165, !dbg !3027

165:                                              ; preds = %164, %154
  store %struct._IO_FILE* null, %struct._IO_FILE** @outputHandleJustInCase, align 8, !dbg !3028
  %166 = load i32, i32* @verbosity, align 4, !dbg !3029
  %167 = icmp sge i32 %166, 2, !dbg !3031
  br i1 %167, label %168, label %171, !dbg !3032

168:                                              ; preds = %165
  %169 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3033
  %170 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %169, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.92, i64 0, i64 0)), !dbg !3034
  br label %171, !dbg !3034

171:                                              ; preds = %168, %165
  store i8 1, i8* %3, align 1, !dbg !3035
  br label %244, !dbg !3035

172:                                              ; preds = %55
  call void @llvm.dbg.label(metadata !3036), !dbg !3037
  %173 = load i8, i8* @forceOverwrite, align 1, !dbg !3038
  %174 = icmp ne i8 %173, 0, !dbg !3038
  br i1 %174, label %175, label %207, !dbg !3040

175:                                              ; preds = %172
  %176 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !3041
  call void @rewind(%struct._IO_FILE* %176), !dbg !3043
  br label %177, !dbg !3044

177:                                              ; preds = %175, %205
  %178 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !3045
  %179 = call zeroext i8 @myfeof(%struct._IO_FILE* %178), !dbg !3048
  %180 = icmp ne i8 %179, 0, !dbg !3048
  br i1 %180, label %181, label %182, !dbg !3049

181:                                              ; preds = %177
  br label %206, !dbg !3050

182:                                              ; preds = %177
  %183 = getelementptr inbounds [5000 x i8], [5000 x i8]* %13, i64 0, i64 0, !dbg !3051
  %184 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !3052
  %185 = call i64 @fread(i8* %183, i64 1, i64 5000, %struct._IO_FILE* %184), !dbg !3053
  %186 = trunc i64 %185 to i32, !dbg !3053
  store i32 %186, i32* %10, align 4, !dbg !3054
  %187 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !3055
  %188 = call i32 @ferror(%struct._IO_FILE* %187) #10, !dbg !3057
  %189 = icmp ne i32 %188, 0, !dbg !3057
  br i1 %189, label %190, label %191, !dbg !3058

190:                                              ; preds = %182
  br label %213, !dbg !3059

191:                                              ; preds = %182
  %192 = load i32, i32* %10, align 4, !dbg !3060
  %193 = icmp sgt i32 %192, 0, !dbg !3062
  br i1 %193, label %194, label %200, !dbg !3063

194:                                              ; preds = %191
  %195 = getelementptr inbounds [5000 x i8], [5000 x i8]* %13, i64 0, i64 0, !dbg !3064
  %196 = load i32, i32* %10, align 4, !dbg !3065
  %197 = sext i32 %196 to i64, !dbg !3065
  %198 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3066
  %199 = call i64 @fwrite(i8* %195, i64 1, i64 %197, %struct._IO_FILE* %198), !dbg !3067
  br label %200, !dbg !3067

200:                                              ; preds = %194, %191
  %201 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3068
  %202 = call i32 @ferror(%struct._IO_FILE* %201) #10, !dbg !3070
  %203 = icmp ne i32 %202, 0, !dbg !3070
  br i1 %203, label %204, label %205, !dbg !3071

204:                                              ; preds = %200
  br label %213, !dbg !3072

205:                                              ; preds = %200
  br label %177, !dbg !3044, !llvm.loop !3073

206:                                              ; preds = %181
  br label %120, !dbg !3075

207:                                              ; preds = %172
  br label %208, !dbg !3038

208:                                              ; preds = %207, %80, %42
  call void @llvm.dbg.label(metadata !3076), !dbg !3077
  %209 = load i8*, i8** %6, align 8, !dbg !3078
  call void @BZ2_bzReadClose(i32* %8, i8* %209), !dbg !3079
  %210 = load i32, i32* %7, align 4, !dbg !3080
  switch i32 %210, label %243 [
    i32 -9, label %211
    i32 -6, label %212
    i32 -4, label %214
    i32 -3, label %215
    i32 -7, label %216
    i32 -5, label %217
  ], !dbg !3081

211:                                              ; preds = %208
  call void @configError() #13, !dbg !3082
  unreachable, !dbg !3082

212:                                              ; preds = %208
  br label %213, !dbg !3082

213:                                              ; preds = %212, %204, %190, %163, %153, %147, %142, %134, %124, %75, %27, %22
  call void @llvm.dbg.label(metadata !3084), !dbg !3085
  call void @ioError() #13, !dbg !3086
  unreachable, !dbg !3086

214:                                              ; preds = %208
  call void @crcError() #13, !dbg !3087
  unreachable, !dbg !3087

215:                                              ; preds = %208
  call void @outOfMemory() #13, !dbg !3088
  unreachable, !dbg !3088

216:                                              ; preds = %208
  call void @compressedStreamEOF() #13, !dbg !3089
  unreachable, !dbg !3089

217:                                              ; preds = %208
  %218 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !3090
  %219 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !3092
  %220 = icmp ne %struct._IO_FILE* %218, %219, !dbg !3093
  br i1 %220, label %221, label %224, !dbg !3094

221:                                              ; preds = %217
  %222 = load %struct._IO_FILE*, %struct._IO_FILE** %4, align 8, !dbg !3095
  %223 = call i32 @fclose(%struct._IO_FILE* %222), !dbg !3096
  br label %224, !dbg !3096

224:                                              ; preds = %221, %217
  %225 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3097
  %226 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !3099
  %227 = icmp ne %struct._IO_FILE* %225, %226, !dbg !3100
  br i1 %227, label %228, label %231, !dbg !3101

228:                                              ; preds = %224
  %229 = load %struct._IO_FILE*, %struct._IO_FILE** %5, align 8, !dbg !3102
  %230 = call i32 @fclose(%struct._IO_FILE* %229), !dbg !3103
  br label %231, !dbg !3103

231:                                              ; preds = %228, %224
  %232 = load i32, i32* %11, align 4, !dbg !3104
  %233 = icmp eq i32 %232, 1, !dbg !3106
  br i1 %233, label %234, label %235, !dbg !3107

234:                                              ; preds = %231
  store i8 0, i8* %3, align 1, !dbg !3108
  br label %244, !dbg !3108

235:                                              ; preds = %231
  %236 = load i8, i8* @noisy, align 1, !dbg !3110
  %237 = icmp ne i8 %236, 0, !dbg !3110
  br i1 %237, label %238, label %242, !dbg !3113

238:                                              ; preds = %235
  %239 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3114
  %240 = load i8*, i8** @progName, align 8, !dbg !3115
  %241 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %239, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.93, i64 0, i64 0), i8* %240, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !3116
  br label %242, !dbg !3116

242:                                              ; preds = %238, %235
  store i8 1, i8* %3, align 1, !dbg !3117
  br label %244, !dbg !3117

243:                                              ; preds = %208
  call void @panic(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.94, i64 0, i64 0)) #13, !dbg !3118
  unreachable, !dbg !3118

244:                                              ; preds = %242, %234, %171
  %245 = load i8, i8* %3, align 1, !dbg !3119
  ret i8 %245, !dbg !3119
}

declare dso_local i8* @BZ2_bzReadOpen(i32*, %struct._IO_FILE*, i32, i32, i8*, i32) #5

declare dso_local i32 @BZ2_bzRead(i32*, i8*, i8*, i32) #5

declare dso_local i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #5

declare dso_local void @BZ2_bzReadGetUnused(i32*, i8*, i8**, i32*) #5

declare dso_local void @BZ2_bzReadClose(i32*, i8*) #5

declare dso_local void @rewind(%struct._IO_FILE*) #5

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @crcError() #6 !dbg !3120 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3121
  %2 = load i8*, i8** @progName, align 8, !dbg !3122
  %3 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.95, i64 0, i64 0), i8* %2), !dbg !3123
  call void @showFileNames(), !dbg !3124
  call void @cadvise(), !dbg !3125
  call void @cleanUpAndFail(i32 2) #13, !dbg !3126
  unreachable, !dbg !3126
}

; Function Attrs: noinline noreturn nounwind optnone uwtable
define internal void @compressedStreamEOF() #6 !dbg !3127 {
  %1 = load i8, i8* @noisy, align 1, !dbg !3128
  %2 = icmp ne i8 %1, 0, !dbg !3128
  br i1 %2, label %3, label %8, !dbg !3130

3:                                                ; preds = %0
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3131
  %5 = load i8*, i8** @progName, align 8, !dbg !3133
  %6 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %4, i8* getelementptr inbounds ([95 x i8], [95 x i8]* @.str.96, i64 0, i64 0), i8* %5), !dbg !3134
  %7 = load i8*, i8** @progName, align 8, !dbg !3135
  call void @perror(i8* %7), !dbg !3136
  call void @showFileNames(), !dbg !3137
  call void @cadvise(), !dbg !3138
  br label %8, !dbg !3139

8:                                                ; preds = %3, %0
  call void @cleanUpAndFail(i32 2) #13, !dbg !3140
  unreachable, !dbg !3140
}

; Function Attrs: noinline nounwind optnone uwtable
define internal zeroext i8 @testStream(%struct._IO_FILE* %0) #0 !dbg !3141 {
  %2 = alloca i8, align 1
  %3 = alloca %struct._IO_FILE*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca [5000 x i8], align 16
  %12 = alloca [5000 x i8], align 16
  %13 = alloca i32, align 4
  %14 = alloca i8*, align 8
  %15 = alloca i8*, align 8
  store %struct._IO_FILE* %0, %struct._IO_FILE** %3, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %3, metadata !3142, metadata !DIExpression()), !dbg !3143
  call void @llvm.dbg.declare(metadata i8** %4, metadata !3144, metadata !DIExpression()), !dbg !3145
  store i8* null, i8** %4, align 8, !dbg !3145
  call void @llvm.dbg.declare(metadata i32* %5, metadata !3146, metadata !DIExpression()), !dbg !3147
  call void @llvm.dbg.declare(metadata i32* %6, metadata !3148, metadata !DIExpression()), !dbg !3149
  call void @llvm.dbg.declare(metadata i32* %7, metadata !3150, metadata !DIExpression()), !dbg !3151
  call void @llvm.dbg.declare(metadata i32* %8, metadata !3152, metadata !DIExpression()), !dbg !3153
  call void @llvm.dbg.declare(metadata i32* %9, metadata !3154, metadata !DIExpression()), !dbg !3155
  call void @llvm.dbg.declare(metadata i32* %10, metadata !3156, metadata !DIExpression()), !dbg !3157
  call void @llvm.dbg.declare(metadata [5000 x i8]* %11, metadata !3158, metadata !DIExpression()), !dbg !3159
  call void @llvm.dbg.declare(metadata [5000 x i8]* %12, metadata !3160, metadata !DIExpression()), !dbg !3161
  call void @llvm.dbg.declare(metadata i32* %13, metadata !3162, metadata !DIExpression()), !dbg !3163
  call void @llvm.dbg.declare(metadata i8** %14, metadata !3164, metadata !DIExpression()), !dbg !3165
  call void @llvm.dbg.declare(metadata i8** %15, metadata !3166, metadata !DIExpression()), !dbg !3167
  store i32 0, i32* %13, align 4, !dbg !3168
  store i32 0, i32* %9, align 4, !dbg !3169
  %16 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3170
  %17 = call i32 @ferror(%struct._IO_FILE* %16) #10, !dbg !3172
  %18 = icmp ne i32 %17, 0, !dbg !3172
  br i1 %18, label %19, label %20, !dbg !3173

19:                                               ; preds = %1
  br label %121, !dbg !3174

20:                                               ; preds = %1
  br label %21, !dbg !3175

21:                                               ; preds = %20, %90
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3176
  %23 = load i32, i32* @verbosity, align 4, !dbg !3178
  %24 = load i8, i8* @smallMode, align 1, !dbg !3179
  %25 = zext i8 %24 to i32, !dbg !3180
  %26 = getelementptr inbounds [5000 x i8], [5000 x i8]* %12, i64 0, i64 0, !dbg !3181
  %27 = load i32, i32* %13, align 4, !dbg !3182
  %28 = call i8* @BZ2_bzReadOpen(i32* %5, %struct._IO_FILE* %22, i32 %23, i32 %25, i8* %26, i32 %27), !dbg !3183
  store i8* %28, i8** %4, align 8, !dbg !3184
  %29 = load i8*, i8** %4, align 8, !dbg !3185
  %30 = icmp eq i8* %29, null, !dbg !3187
  br i1 %30, label %34, label %31, !dbg !3188

31:                                               ; preds = %21
  %32 = load i32, i32* %5, align 4, !dbg !3189
  %33 = icmp ne i32 %32, 0, !dbg !3190
  br i1 %33, label %34, label %35, !dbg !3191

34:                                               ; preds = %31, %21
  br label %109, !dbg !3192

35:                                               ; preds = %31
  %36 = load i32, i32* %9, align 4, !dbg !3193
  %37 = add nsw i32 %36, 1, !dbg !3193
  store i32 %37, i32* %9, align 4, !dbg !3193
  br label %38, !dbg !3194

38:                                               ; preds = %48, %35
  %39 = load i32, i32* %5, align 4, !dbg !3195
  %40 = icmp eq i32 %39, 0, !dbg !3196
  br i1 %40, label %41, label %49, !dbg !3194

41:                                               ; preds = %38
  %42 = load i8*, i8** %4, align 8, !dbg !3197
  %43 = getelementptr inbounds [5000 x i8], [5000 x i8]* %11, i64 0, i64 0, !dbg !3199
  %44 = call i32 @BZ2_bzRead(i32* %5, i8* %42, i8* %43, i32 5000), !dbg !3200
  store i32 %44, i32* %8, align 4, !dbg !3201
  %45 = load i32, i32* %5, align 4, !dbg !3202
  %46 = icmp eq i32 %45, -5, !dbg !3204
  br i1 %46, label %47, label %48, !dbg !3205

47:                                               ; preds = %41
  br label %109, !dbg !3206

48:                                               ; preds = %41
  br label %38, !dbg !3194, !llvm.loop !3207

49:                                               ; preds = %38
  %50 = load i32, i32* %5, align 4, !dbg !3209
  %51 = icmp ne i32 %50, 4, !dbg !3211
  br i1 %51, label %52, label %53, !dbg !3212

52:                                               ; preds = %49
  br label %109, !dbg !3213

53:                                               ; preds = %49
  %54 = load i8*, i8** %4, align 8, !dbg !3214
  call void @BZ2_bzReadGetUnused(i32* %5, i8* %54, i8** %14, i32* %13), !dbg !3215
  %55 = load i32, i32* %5, align 4, !dbg !3216
  %56 = icmp ne i32 %55, 0, !dbg !3218
  br i1 %56, label %57, label %58, !dbg !3219

57:                                               ; preds = %53
  call void @panic(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.101, i64 0, i64 0)) #13, !dbg !3220
  unreachable, !dbg !3220

58:                                               ; preds = %53
  %59 = load i8*, i8** %14, align 8, !dbg !3221
  store i8* %59, i8** %15, align 8, !dbg !3222
  store i32 0, i32* %10, align 4, !dbg !3223
  br label %60, !dbg !3225

60:                                               ; preds = %73, %58
  %61 = load i32, i32* %10, align 4, !dbg !3226
  %62 = load i32, i32* %13, align 4, !dbg !3228
  %63 = icmp slt i32 %61, %62, !dbg !3229
  br i1 %63, label %64, label %76, !dbg !3230

64:                                               ; preds = %60
  %65 = load i8*, i8** %15, align 8, !dbg !3231
  %66 = load i32, i32* %10, align 4, !dbg !3232
  %67 = sext i32 %66 to i64, !dbg !3231
  %68 = getelementptr inbounds i8, i8* %65, i64 %67, !dbg !3231
  %69 = load i8, i8* %68, align 1, !dbg !3231
  %70 = load i32, i32* %10, align 4, !dbg !3233
  %71 = sext i32 %70 to i64, !dbg !3234
  %72 = getelementptr inbounds [5000 x i8], [5000 x i8]* %12, i64 0, i64 %71, !dbg !3234
  store i8 %69, i8* %72, align 1, !dbg !3235
  br label %73, !dbg !3234

73:                                               ; preds = %64
  %74 = load i32, i32* %10, align 4, !dbg !3236
  %75 = add nsw i32 %74, 1, !dbg !3236
  store i32 %75, i32* %10, align 4, !dbg !3236
  br label %60, !dbg !3237, !llvm.loop !3238

76:                                               ; preds = %60
  %77 = load i8*, i8** %4, align 8, !dbg !3240
  call void @BZ2_bzReadClose(i32* %5, i8* %77), !dbg !3241
  %78 = load i32, i32* %5, align 4, !dbg !3242
  %79 = icmp ne i32 %78, 0, !dbg !3244
  br i1 %79, label %80, label %81, !dbg !3245

80:                                               ; preds = %76
  call void @panic(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.101, i64 0, i64 0)) #13, !dbg !3246
  unreachable, !dbg !3246

81:                                               ; preds = %76
  %82 = load i32, i32* %13, align 4, !dbg !3247
  %83 = icmp eq i32 %82, 0, !dbg !3249
  br i1 %83, label %84, label %90, !dbg !3250

84:                                               ; preds = %81
  %85 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3251
  %86 = call zeroext i8 @myfeof(%struct._IO_FILE* %85), !dbg !3252
  %87 = zext i8 %86 to i32, !dbg !3252
  %88 = icmp ne i32 %87, 0, !dbg !3252
  br i1 %88, label %89, label %90, !dbg !3253

89:                                               ; preds = %84
  br label %91, !dbg !3254

90:                                               ; preds = %84, %81
  br label %21, !dbg !3175, !llvm.loop !3255

91:                                               ; preds = %89
  %92 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3257
  %93 = call i32 @ferror(%struct._IO_FILE* %92) #10, !dbg !3259
  %94 = icmp ne i32 %93, 0, !dbg !3259
  br i1 %94, label %95, label %96, !dbg !3260

95:                                               ; preds = %91
  br label %121, !dbg !3261

96:                                               ; preds = %91
  %97 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3262
  %98 = call i32 @fclose(%struct._IO_FILE* %97), !dbg !3263
  store i32 %98, i32* %7, align 4, !dbg !3264
  %99 = load i32, i32* %7, align 4, !dbg !3265
  %100 = icmp eq i32 %99, -1, !dbg !3267
  br i1 %100, label %101, label %102, !dbg !3268

101:                                              ; preds = %96
  br label %121, !dbg !3269

102:                                              ; preds = %96
  %103 = load i32, i32* @verbosity, align 4, !dbg !3270
  %104 = icmp sge i32 %103, 2, !dbg !3272
  br i1 %104, label %105, label %108, !dbg !3273

105:                                              ; preds = %102
  %106 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3274
  %107 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %106, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.92, i64 0, i64 0)), !dbg !3275
  br label %108, !dbg !3275

108:                                              ; preds = %105, %102
  store i8 1, i8* %2, align 1, !dbg !3276
  br label %150, !dbg !3276

109:                                              ; preds = %52, %47, %34
  call void @llvm.dbg.label(metadata !3277), !dbg !3278
  %110 = load i8*, i8** %4, align 8, !dbg !3279
  call void @BZ2_bzReadClose(i32* %6, i8* %110), !dbg !3280
  %111 = load i32, i32* @verbosity, align 4, !dbg !3281
  %112 = icmp eq i32 %111, 0, !dbg !3283
  br i1 %112, label %113, label %117, !dbg !3284

113:                                              ; preds = %109
  %114 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3285
  %115 = load i8*, i8** @progName, align 8, !dbg !3286
  %116 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %114, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.102, i64 0, i64 0), i8* %115, i8* getelementptr inbounds ([1034 x i8], [1034 x i8]* @inName, i64 0, i64 0)), !dbg !3287
  br label %117, !dbg !3287

117:                                              ; preds = %113, %109
  %118 = load i32, i32* %5, align 4, !dbg !3288
  switch i32 %118, label %149 [
    i32 -9, label %119
    i32 -6, label %120
    i32 -4, label %122
    i32 -3, label %125
    i32 -7, label %126
    i32 -5, label %129
  ], !dbg !3289

119:                                              ; preds = %117
  call void @configError() #13, !dbg !3290
  unreachable, !dbg !3290

120:                                              ; preds = %117
  br label %121, !dbg !3290

121:                                              ; preds = %120, %101, %95, %19
  call void @llvm.dbg.label(metadata !3292), !dbg !3293
  call void @ioError() #13, !dbg !3294
  unreachable, !dbg !3294

122:                                              ; preds = %117
  %123 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3295
  %124 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %123, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.103, i64 0, i64 0)), !dbg !3296
  store i8 0, i8* %2, align 1, !dbg !3297
  br label %150, !dbg !3297

125:                                              ; preds = %117
  call void @outOfMemory() #13, !dbg !3298
  unreachable, !dbg !3298

126:                                              ; preds = %117
  %127 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3299
  %128 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %127, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.104, i64 0, i64 0)), !dbg !3300
  store i8 0, i8* %2, align 1, !dbg !3301
  br label %150, !dbg !3301

129:                                              ; preds = %117
  %130 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3302
  %131 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !3304
  %132 = icmp ne %struct._IO_FILE* %130, %131, !dbg !3305
  br i1 %132, label %133, label %136, !dbg !3306

133:                                              ; preds = %129
  %134 = load %struct._IO_FILE*, %struct._IO_FILE** %3, align 8, !dbg !3307
  %135 = call i32 @fclose(%struct._IO_FILE* %134), !dbg !3308
  br label %136, !dbg !3308

136:                                              ; preds = %133, %129
  %137 = load i32, i32* %9, align 4, !dbg !3309
  %138 = icmp eq i32 %137, 1, !dbg !3311
  br i1 %138, label %139, label %142, !dbg !3312

139:                                              ; preds = %136
  %140 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3313
  %141 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %140, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.105, i64 0, i64 0)), !dbg !3315
  store i8 0, i8* %2, align 1, !dbg !3316
  br label %150, !dbg !3316

142:                                              ; preds = %136
  %143 = load i8, i8* @noisy, align 1, !dbg !3317
  %144 = icmp ne i8 %143, 0, !dbg !3317
  br i1 %144, label %145, label %148, !dbg !3320

145:                                              ; preds = %142
  %146 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !3321
  %147 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %146, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.106, i64 0, i64 0)), !dbg !3322
  br label %148, !dbg !3322

148:                                              ; preds = %145, %142
  store i8 1, i8* %2, align 1, !dbg !3323
  br label %150, !dbg !3323

149:                                              ; preds = %117
  call void @panic(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.107, i64 0, i64 0)) #13, !dbg !3324
  unreachable, !dbg !3324

150:                                              ; preds = %148, %139, %126, %122, %108
  %151 = load i8, i8* %2, align 1, !dbg !3325
  ret i8 %151, !dbg !3325
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noinline noreturn nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { argmemonly nounwind willreturn }
attributes #9 = { nounwind willreturn }
attributes #10 = { nounwind }
attributes #11 = { nounwind readonly }
attributes #12 = { noreturn nounwind }
attributes #13 = { noreturn }
attributes #14 = { nounwind readnone }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!193, !194, !195}
!llvm.ident = !{!196}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "zSuffix", scope: !2, file: !3, line: 1113, type: !47, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "Ubuntu clang version 10.0.1-++20210327122936+ef32c611aa21-1~exp1~20210327113535.195", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !21, globals: !44, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "bzip2.c", directory: "/home/yongzhe/Documents/grpc/examples/cpp/bzip2")
!4 = !{!5}
!5 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !6, line: 46, baseType: !7, size: 32, elements: !8)
!6 = !DIFile(filename: "/usr/include/ctype.h", directory: "")
!7 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!8 = !{!9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20}
!9 = !DIEnumerator(name: "_ISupper", value: 256, isUnsigned: true)
!10 = !DIEnumerator(name: "_ISlower", value: 512, isUnsigned: true)
!11 = !DIEnumerator(name: "_ISalpha", value: 1024, isUnsigned: true)
!12 = !DIEnumerator(name: "_ISdigit", value: 2048, isUnsigned: true)
!13 = !DIEnumerator(name: "_ISxdigit", value: 4096, isUnsigned: true)
!14 = !DIEnumerator(name: "_ISspace", value: 8192, isUnsigned: true)
!15 = !DIEnumerator(name: "_ISprint", value: 16384, isUnsigned: true)
!16 = !DIEnumerator(name: "_ISgraph", value: 32768, isUnsigned: true)
!17 = !DIEnumerator(name: "_ISblank", value: 1, isUnsigned: true)
!18 = !DIEnumerator(name: "_IScntrl", value: 2, isUnsigned: true)
!19 = !DIEnumerator(name: "_ISpunct", value: 4, isUnsigned: true)
!20 = !DIEnumerator(name: "_ISalnum", value: 8, isUnsigned: true)
!21 = !{!22, !24, !27, !28, !29, !30, !31, !38, !41, !42, !43}
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bool", file: !3, line: 163, baseType: !23)
!23 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "Char", file: !3, line: 162, baseType: !26)
!26 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "Int32", file: !3, line: 165, baseType: !29)
!29 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!30 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "Cell", file: !3, line: 1712, baseType: !33)
!33 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "zzzz", file: !3, line: 1708, size: 128, elements: !34)
!34 = !{!35, !36}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !33, file: !3, line: 1709, baseType: !24, size: 64)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "link", scope: !33, file: !3, line: 1710, baseType: !37, size: 64, offset: 64)
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !39, line: 46, baseType: !40)
!39 = !DIFile(filename: "/usr/lib/llvm-10/lib/clang/10.0.1/include/stddef.h", directory: "")
!40 = !DIBasicType(name: "long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "UChar", file: !3, line: 164, baseType: !23)
!42 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64)
!44 = !{!0, !45, !52, !54, !56, !58, !60, !62, !64, !66, !68, !70, !72, !74, !76, !78, !80, !82, !87, !89, !91, !93, !95, !153, !155}
!45 = !DIGlobalVariableExpression(var: !46, expr: !DIExpression())
!46 = distinct !DIGlobalVariable(name: "unzSuffix", scope: !2, file: !3, line: 1115, type: !47, isLocal: false, isDefinition: true)
!47 = !DICompositeType(tag: DW_TAG_array_type, baseType: !48, size: 256, elements: !50)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64)
!49 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !25)
!50 = !{!51}
!51 = !DISubrange(count: 4)
!52 = !DIGlobalVariableExpression(var: !53, expr: !DIExpression())
!53 = distinct !DIGlobalVariable(name: "verbosity", scope: !2, file: !3, line: 184, type: !28, isLocal: false, isDefinition: true)
!54 = !DIGlobalVariableExpression(var: !55, expr: !DIExpression())
!55 = distinct !DIGlobalVariable(name: "keepInputFiles", scope: !2, file: !3, line: 185, type: !22, isLocal: false, isDefinition: true)
!56 = !DIGlobalVariableExpression(var: !57, expr: !DIExpression())
!57 = distinct !DIGlobalVariable(name: "smallMode", scope: !2, file: !3, line: 185, type: !22, isLocal: false, isDefinition: true)
!58 = !DIGlobalVariableExpression(var: !59, expr: !DIExpression())
!59 = distinct !DIGlobalVariable(name: "deleteOutputOnInterrupt", scope: !2, file: !3, line: 185, type: !22, isLocal: false, isDefinition: true)
!60 = !DIGlobalVariableExpression(var: !61, expr: !DIExpression())
!61 = distinct !DIGlobalVariable(name: "forceOverwrite", scope: !2, file: !3, line: 186, type: !22, isLocal: false, isDefinition: true)
!62 = !DIGlobalVariableExpression(var: !63, expr: !DIExpression())
!63 = distinct !DIGlobalVariable(name: "testFailsExist", scope: !2, file: !3, line: 186, type: !22, isLocal: false, isDefinition: true)
!64 = !DIGlobalVariableExpression(var: !65, expr: !DIExpression())
!65 = distinct !DIGlobalVariable(name: "unzFailsExist", scope: !2, file: !3, line: 186, type: !22, isLocal: false, isDefinition: true)
!66 = !DIGlobalVariableExpression(var: !67, expr: !DIExpression())
!67 = distinct !DIGlobalVariable(name: "noisy", scope: !2, file: !3, line: 186, type: !22, isLocal: false, isDefinition: true)
!68 = !DIGlobalVariableExpression(var: !69, expr: !DIExpression())
!69 = distinct !DIGlobalVariable(name: "numFileNames", scope: !2, file: !3, line: 187, type: !28, isLocal: false, isDefinition: true)
!70 = !DIGlobalVariableExpression(var: !71, expr: !DIExpression())
!71 = distinct !DIGlobalVariable(name: "numFilesProcessed", scope: !2, file: !3, line: 187, type: !28, isLocal: false, isDefinition: true)
!72 = !DIGlobalVariableExpression(var: !73, expr: !DIExpression())
!73 = distinct !DIGlobalVariable(name: "blockSize100k", scope: !2, file: !3, line: 187, type: !28, isLocal: false, isDefinition: true)
!74 = !DIGlobalVariableExpression(var: !75, expr: !DIExpression())
!75 = distinct !DIGlobalVariable(name: "exitValue", scope: !2, file: !3, line: 188, type: !28, isLocal: false, isDefinition: true)
!76 = !DIGlobalVariableExpression(var: !77, expr: !DIExpression())
!77 = distinct !DIGlobalVariable(name: "opMode", scope: !2, file: !3, line: 200, type: !28, isLocal: false, isDefinition: true)
!78 = !DIGlobalVariableExpression(var: !79, expr: !DIExpression())
!79 = distinct !DIGlobalVariable(name: "srcMode", scope: !2, file: !3, line: 201, type: !28, isLocal: false, isDefinition: true)
!80 = !DIGlobalVariableExpression(var: !81, expr: !DIExpression())
!81 = distinct !DIGlobalVariable(name: "longestFileName", scope: !2, file: !3, line: 205, type: !28, isLocal: false, isDefinition: true)
!82 = !DIGlobalVariableExpression(var: !83, expr: !DIExpression())
!83 = distinct !DIGlobalVariable(name: "inName", scope: !2, file: !3, line: 206, type: !84, isLocal: false, isDefinition: true)
!84 = !DICompositeType(tag: DW_TAG_array_type, baseType: !25, size: 8272, elements: !85)
!85 = !{!86}
!86 = !DISubrange(count: 1034)
!87 = !DIGlobalVariableExpression(var: !88, expr: !DIExpression())
!88 = distinct !DIGlobalVariable(name: "outName", scope: !2, file: !3, line: 207, type: !84, isLocal: false, isDefinition: true)
!89 = !DIGlobalVariableExpression(var: !90, expr: !DIExpression())
!90 = distinct !DIGlobalVariable(name: "tmpName", scope: !2, file: !3, line: 208, type: !84, isLocal: false, isDefinition: true)
!91 = !DIGlobalVariableExpression(var: !92, expr: !DIExpression())
!92 = distinct !DIGlobalVariable(name: "progName", scope: !2, file: !3, line: 209, type: !24, isLocal: false, isDefinition: true)
!93 = !DIGlobalVariableExpression(var: !94, expr: !DIExpression())
!94 = distinct !DIGlobalVariable(name: "progNameReally", scope: !2, file: !3, line: 210, type: !84, isLocal: false, isDefinition: true)
!95 = !DIGlobalVariableExpression(var: !96, expr: !DIExpression())
!96 = distinct !DIGlobalVariable(name: "outputHandleJustInCase", scope: !2, file: !3, line: 211, type: !97, isLocal: false, isDefinition: true)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64)
!98 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !99, line: 48, baseType: !100)
!99 = !DIFile(filename: "/usr/include/stdio.h", directory: "")
!100 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !101, line: 241, size: 1728, elements: !102)
!101 = !DIFile(filename: "/usr/include/libio.h", directory: "")
!102 = !{!103, !104, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !124, !125, !126, !127, !131, !132, !134, !138, !141, !143, !144, !145, !146, !147, !148, !149}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !100, file: !101, line: 242, baseType: !29, size: 32)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !100, file: !101, line: 247, baseType: !105, size: 64, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !100, file: !101, line: 248, baseType: !105, size: 64, offset: 128)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !100, file: !101, line: 249, baseType: !105, size: 64, offset: 192)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !100, file: !101, line: 250, baseType: !105, size: 64, offset: 256)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !100, file: !101, line: 251, baseType: !105, size: 64, offset: 320)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !100, file: !101, line: 252, baseType: !105, size: 64, offset: 384)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !100, file: !101, line: 253, baseType: !105, size: 64, offset: 448)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !100, file: !101, line: 254, baseType: !105, size: 64, offset: 512)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !100, file: !101, line: 256, baseType: !105, size: 64, offset: 576)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !100, file: !101, line: 257, baseType: !105, size: 64, offset: 640)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !100, file: !101, line: 258, baseType: !105, size: 64, offset: 704)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !100, file: !101, line: 260, baseType: !117, size: 64, offset: 768)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64)
!118 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !101, line: 156, size: 192, elements: !119)
!119 = !{!120, !121, !123}
!120 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !118, file: !101, line: 157, baseType: !117, size: 64)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !118, file: !101, line: 158, baseType: !122, size: 64, offset: 64)
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !118, file: !101, line: 162, baseType: !29, size: 32, offset: 128)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !100, file: !101, line: 262, baseType: !122, size: 64, offset: 832)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !100, file: !101, line: 264, baseType: !29, size: 32, offset: 896)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !100, file: !101, line: 268, baseType: !29, size: 32, offset: 928)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !100, file: !101, line: 270, baseType: !128, size: 64, offset: 960)
!128 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !129, line: 131, baseType: !130)
!129 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "")
!130 = !DIBasicType(name: "long int", size: 64, encoding: DW_ATE_signed)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !100, file: !101, line: 274, baseType: !30, size: 16, offset: 1024)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !100, file: !101, line: 275, baseType: !133, size: 8, offset: 1040)
!133 = !DIBasicType(name: "signed char", size: 8, encoding: DW_ATE_signed_char)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !100, file: !101, line: 276, baseType: !135, size: 8, offset: 1048)
!135 = !DICompositeType(tag: DW_TAG_array_type, baseType: !26, size: 8, elements: !136)
!136 = !{!137}
!137 = !DISubrange(count: 1)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !100, file: !101, line: 280, baseType: !139, size: 64, offset: 1088)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64)
!140 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !101, line: 150, baseType: null)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !100, file: !101, line: 289, baseType: !142, size: 64, offset: 1152)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !129, line: 132, baseType: !130)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !100, file: !101, line: 297, baseType: !27, size: 64, offset: 1216)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !100, file: !101, line: 298, baseType: !27, size: 64, offset: 1280)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !100, file: !101, line: 299, baseType: !27, size: 64, offset: 1344)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !100, file: !101, line: 300, baseType: !27, size: 64, offset: 1408)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !100, file: !101, line: 302, baseType: !38, size: 64, offset: 1472)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !100, file: !101, line: 303, baseType: !29, size: 32, offset: 1536)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !100, file: !101, line: 305, baseType: !150, size: 160, offset: 1568)
!150 = !DICompositeType(tag: DW_TAG_array_type, baseType: !26, size: 160, elements: !151)
!151 = !{!152}
!152 = !DISubrange(count: 20)
!153 = !DIGlobalVariableExpression(var: !154, expr: !DIExpression())
!154 = distinct !DIGlobalVariable(name: "workFactor", scope: !2, file: !3, line: 212, type: !28, isLocal: false, isDefinition: true)
!155 = !DIGlobalVariableExpression(var: !156, expr: !DIExpression())
!156 = distinct !DIGlobalVariable(name: "fileMetaInfo", scope: !2, file: !3, line: 1043, type: !157, isLocal: true, isDefinition: true)
!157 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !158, line: 46, size: 1152, elements: !159)
!158 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "")
!159 = !{!160, !162, !164, !166, !168, !170, !172, !173, !174, !175, !177, !179, !187, !188, !189}
!160 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !157, file: !158, line: 48, baseType: !161, size: 64)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !129, line: 124, baseType: !40)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !157, file: !158, line: 53, baseType: !163, size: 64, offset: 64)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !129, line: 127, baseType: !40)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !157, file: !158, line: 61, baseType: !165, size: 64, offset: 128)
!165 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !129, line: 130, baseType: !40)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !157, file: !158, line: 62, baseType: !167, size: 32, offset: 192)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !129, line: 129, baseType: !7)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !157, file: !158, line: 64, baseType: !169, size: 32, offset: 224)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !129, line: 125, baseType: !7)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !157, file: !158, line: 65, baseType: !171, size: 32, offset: 256)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !129, line: 126, baseType: !7)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !157, file: !158, line: 67, baseType: !29, size: 32, offset: 288)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !157, file: !158, line: 69, baseType: !161, size: 64, offset: 320)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !157, file: !158, line: 74, baseType: !128, size: 64, offset: 384)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !157, file: !158, line: 78, baseType: !176, size: 64, offset: 448)
!176 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !129, line: 153, baseType: !130)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !157, file: !158, line: 80, baseType: !178, size: 64, offset: 512)
!178 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !129, line: 158, baseType: !130)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !157, file: !158, line: 91, baseType: !180, size: 128, offset: 576)
!180 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !181, line: 120, size: 128, elements: !182)
!181 = !DIFile(filename: "/usr/include/time.h", directory: "")
!182 = !{!183, !185}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !180, file: !181, line: 122, baseType: !184, size: 64)
!184 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !129, line: 139, baseType: !130)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !180, file: !181, line: 123, baseType: !186, size: 64, offset: 64)
!186 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !129, line: 175, baseType: !130)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !157, file: !158, line: 92, baseType: !180, size: 128, offset: 704)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !157, file: !158, line: 93, baseType: !180, size: 128, offset: 832)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !157, file: !158, line: 106, baseType: !190, size: 192, offset: 960)
!190 = !DICompositeType(tag: DW_TAG_array_type, baseType: !186, size: 192, elements: !191)
!191 = !{!192}
!192 = !DISubrange(count: 3)
!193 = !{i32 7, !"Dwarf Version", i32 4}
!194 = !{i32 2, !"Debug Info Version", i32 3}
!195 = !{i32 1, !"wchar_size", i32 4}
!196 = !{!"Ubuntu clang version 10.0.1-++20210327122936+ef32c611aa21-1~exp1~20210327113535.195"}
!197 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 1789, type: !198, scopeLine: 1790, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !202)
!198 = !DISubroutineType(types: !199)
!199 = !{!200, !200, !201}
!200 = !DIDerivedType(tag: DW_TAG_typedef, name: "IntNative", file: !3, line: 177, baseType: !29)
!201 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64)
!202 = !{}
!203 = !DILocalVariable(name: "argc", arg: 1, scope: !197, file: !3, line: 1789, type: !200)
!204 = !DILocation(line: 1789, column: 28, scope: !197)
!205 = !DILocalVariable(name: "argv", arg: 2, scope: !197, file: !3, line: 1789, type: !201)
!206 = !DILocation(line: 1789, column: 40, scope: !197)
!207 = !DILocalVariable(name: "i", scope: !197, file: !3, line: 1791, type: !28)
!208 = !DILocation(line: 1791, column: 11, scope: !197)
!209 = !DILocalVariable(name: "j", scope: !197, file: !3, line: 1791, type: !28)
!210 = !DILocation(line: 1791, column: 14, scope: !197)
!211 = !DILocalVariable(name: "tmp", scope: !197, file: !3, line: 1792, type: !24)
!212 = !DILocation(line: 1792, column: 12, scope: !197)
!213 = !DILocalVariable(name: "argList", scope: !197, file: !3, line: 1793, type: !31)
!214 = !DILocation(line: 1793, column: 12, scope: !197)
!215 = !DILocalVariable(name: "aa", scope: !197, file: !3, line: 1794, type: !31)
!216 = !DILocation(line: 1794, column: 12, scope: !197)
!217 = !DILocalVariable(name: "decode", scope: !197, file: !3, line: 1795, type: !22)
!218 = !DILocation(line: 1795, column: 11, scope: !197)
!219 = !DILocation(line: 1804, column: 28, scope: !197)
!220 = !DILocation(line: 1805, column: 28, scope: !197)
!221 = !DILocation(line: 1806, column: 28, scope: !197)
!222 = !DILocation(line: 1807, column: 28, scope: !197)
!223 = !DILocation(line: 1808, column: 28, scope: !197)
!224 = !DILocation(line: 1809, column: 28, scope: !197)
!225 = !DILocation(line: 1810, column: 28, scope: !197)
!226 = !DILocation(line: 1811, column: 28, scope: !197)
!227 = !DILocation(line: 1812, column: 28, scope: !197)
!228 = !DILocation(line: 1813, column: 28, scope: !197)
!229 = !DILocation(line: 1814, column: 28, scope: !197)
!230 = !DILocation(line: 1815, column: 28, scope: !197)
!231 = !DILocation(line: 1816, column: 28, scope: !197)
!232 = !DILocation(line: 1817, column: 28, scope: !197)
!233 = !DILocation(line: 1818, column: 10, scope: !197)
!234 = !DILocation(line: 1818, column: 6, scope: !197)
!235 = !DILocation(line: 1821, column: 4, scope: !197)
!236 = !DILocation(line: 1824, column: 4, scope: !197)
!237 = !DILocation(line: 1828, column: 4, scope: !197)
!238 = !DILocation(line: 1829, column: 4, scope: !197)
!239 = !DILocation(line: 1831, column: 35, scope: !197)
!240 = !DILocation(line: 1831, column: 4, scope: !197)
!241 = !DILocation(line: 1832, column: 13, scope: !197)
!242 = !DILocation(line: 1833, column: 13, scope: !243)
!243 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1833, column: 4)
!244 = !DILocation(line: 1833, column: 9, scope: !243)
!245 = !DILocation(line: 1833, column: 36, scope: !246)
!246 = distinct !DILexicalBlock(scope: !243, file: !3, line: 1833, column: 4)
!247 = !DILocation(line: 1833, column: 35, scope: !246)
!248 = !DILocation(line: 1833, column: 40, scope: !246)
!249 = !DILocation(line: 1833, column: 4, scope: !243)
!250 = !DILocation(line: 1834, column: 12, scope: !251)
!251 = distinct !DILexicalBlock(scope: !246, file: !3, line: 1834, column: 11)
!252 = !DILocation(line: 1834, column: 11, scope: !251)
!253 = !DILocation(line: 1834, column: 16, scope: !251)
!254 = !DILocation(line: 1834, column: 11, scope: !246)
!255 = !DILocation(line: 1834, column: 40, scope: !251)
!256 = !DILocation(line: 1834, column: 44, scope: !251)
!257 = !DILocation(line: 1834, column: 38, scope: !251)
!258 = !DILocation(line: 1834, column: 29, scope: !251)
!259 = !DILocation(line: 1834, column: 19, scope: !251)
!260 = !DILocation(line: 1833, column: 52, scope: !246)
!261 = !DILocation(line: 1833, column: 4, scope: !246)
!262 = distinct !{!262, !249, !263}
!263 = !DILocation(line: 1834, column: 46, scope: !243)
!264 = !DILocation(line: 1840, column: 12, scope: !197)
!265 = !DILocation(line: 1841, column: 4, scope: !197)
!266 = !DILocation(line: 1842, column: 4, scope: !197)
!267 = !DILocation(line: 1843, column: 11, scope: !268)
!268 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1843, column: 4)
!269 = !DILocation(line: 1843, column: 9, scope: !268)
!270 = !DILocation(line: 1843, column: 16, scope: !271)
!271 = distinct !DILexicalBlock(scope: !268, file: !3, line: 1843, column: 4)
!272 = !DILocation(line: 1843, column: 21, scope: !271)
!273 = !DILocation(line: 1843, column: 25, scope: !271)
!274 = !DILocation(line: 1843, column: 18, scope: !271)
!275 = !DILocation(line: 1843, column: 4, scope: !268)
!276 = !DILocation(line: 1844, column: 7, scope: !271)
!277 = !DILocation(line: 1843, column: 30, scope: !271)
!278 = !DILocation(line: 1843, column: 4, scope: !271)
!279 = distinct !{!279, !275, !280}
!280 = !DILocation(line: 1844, column: 7, scope: !268)
!281 = !DILocation(line: 1848, column: 20, scope: !197)
!282 = !DILocation(line: 1849, column: 20, scope: !197)
!283 = !DILocation(line: 1850, column: 20, scope: !197)
!284 = !DILocation(line: 1851, column: 14, scope: !285)
!285 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1851, column: 4)
!286 = !DILocation(line: 1851, column: 12, scope: !285)
!287 = !DILocation(line: 1851, column: 9, scope: !285)
!288 = !DILocation(line: 1851, column: 23, scope: !289)
!289 = distinct !DILexicalBlock(scope: !285, file: !3, line: 1851, column: 4)
!290 = !DILocation(line: 1851, column: 26, scope: !289)
!291 = !DILocation(line: 1851, column: 4, scope: !285)
!292 = !DILocation(line: 1852, column: 11, scope: !293)
!293 = distinct !DILexicalBlock(scope: !294, file: !3, line: 1852, column: 11)
!294 = distinct !DILexicalBlock(scope: !289, file: !3, line: 1851, column: 50)
!295 = !DILocation(line: 1852, column: 11, scope: !294)
!296 = !DILocation(line: 1852, column: 34, scope: !297)
!297 = distinct !DILexicalBlock(scope: !293, file: !3, line: 1852, column: 25)
!298 = !DILocation(line: 1852, column: 43, scope: !297)
!299 = !DILocation(line: 1853, column: 11, scope: !300)
!300 = distinct !DILexicalBlock(scope: !294, file: !3, line: 1853, column: 11)
!301 = !DILocation(line: 1853, column: 15, scope: !300)
!302 = !DILocation(line: 1853, column: 23, scope: !300)
!303 = !DILocation(line: 1853, column: 30, scope: !300)
!304 = !DILocation(line: 1853, column: 33, scope: !300)
!305 = !DILocation(line: 1853, column: 11, scope: !294)
!306 = !DILocation(line: 1853, column: 41, scope: !300)
!307 = !DILocation(line: 1854, column: 19, scope: !294)
!308 = !DILocation(line: 1855, column: 11, scope: !309)
!309 = distinct !DILexicalBlock(scope: !294, file: !3, line: 1855, column: 11)
!310 = !DILocation(line: 1855, column: 43, scope: !309)
!311 = !DILocation(line: 1855, column: 47, scope: !309)
!312 = !DILocation(line: 1855, column: 36, scope: !309)
!313 = !DILocation(line: 1855, column: 29, scope: !309)
!314 = !DILocation(line: 1855, column: 27, scope: !309)
!315 = !DILocation(line: 1855, column: 11, scope: !294)
!316 = !DILocation(line: 1856, column: 42, scope: !309)
!317 = !DILocation(line: 1856, column: 46, scope: !309)
!318 = !DILocation(line: 1856, column: 35, scope: !309)
!319 = !DILocation(line: 1856, column: 28, scope: !309)
!320 = !DILocation(line: 1856, column: 26, scope: !309)
!321 = !DILocation(line: 1856, column: 10, scope: !309)
!322 = !DILocation(line: 1857, column: 4, scope: !294)
!323 = !DILocation(line: 1851, column: 40, scope: !289)
!324 = !DILocation(line: 1851, column: 44, scope: !289)
!325 = !DILocation(line: 1851, column: 38, scope: !289)
!326 = !DILocation(line: 1851, column: 4, scope: !289)
!327 = distinct !{!327, !291, !328}
!328 = !DILocation(line: 1857, column: 4, scope: !285)
!329 = !DILocation(line: 1861, column: 8, scope: !330)
!330 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1861, column: 8)
!331 = !DILocation(line: 1861, column: 21, scope: !330)
!332 = !DILocation(line: 1861, column: 8, scope: !197)
!333 = !DILocation(line: 1862, column: 15, scope: !330)
!334 = !DILocation(line: 1862, column: 7, scope: !330)
!335 = !DILocation(line: 1862, column: 38, scope: !330)
!336 = !DILocation(line: 1867, column: 11, scope: !197)
!337 = !DILocation(line: 1869, column: 19, scope: !338)
!338 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1869, column: 9)
!339 = !DILocation(line: 1869, column: 10, scope: !338)
!340 = !DILocation(line: 1869, column: 39, scope: !338)
!341 = !DILocation(line: 1869, column: 45, scope: !338)
!342 = !DILocation(line: 1870, column: 19, scope: !338)
!343 = !DILocation(line: 1870, column: 10, scope: !338)
!344 = !DILocation(line: 1870, column: 39, scope: !338)
!345 = !DILocation(line: 1869, column: 9, scope: !197)
!346 = !DILocation(line: 1871, column: 14, scope: !338)
!347 = !DILocation(line: 1871, column: 7, scope: !338)
!348 = !DILocation(line: 1873, column: 19, scope: !349)
!349 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1873, column: 9)
!350 = !DILocation(line: 1873, column: 10, scope: !349)
!351 = !DILocation(line: 1873, column: 39, scope: !349)
!352 = !DILocation(line: 1873, column: 45, scope: !349)
!353 = !DILocation(line: 1874, column: 19, scope: !349)
!354 = !DILocation(line: 1874, column: 10, scope: !349)
!355 = !DILocation(line: 1874, column: 39, scope: !349)
!356 = !DILocation(line: 1874, column: 45, scope: !349)
!357 = !DILocation(line: 1875, column: 19, scope: !349)
!358 = !DILocation(line: 1875, column: 10, scope: !349)
!359 = !DILocation(line: 1875, column: 38, scope: !349)
!360 = !DILocation(line: 1875, column: 45, scope: !349)
!361 = !DILocation(line: 1876, column: 19, scope: !349)
!362 = !DILocation(line: 1876, column: 10, scope: !349)
!363 = !DILocation(line: 1876, column: 38, scope: !349)
!364 = !DILocation(line: 1873, column: 9, scope: !197)
!365 = !DILocation(line: 1877, column: 14, scope: !366)
!366 = distinct !DILexicalBlock(scope: !349, file: !3, line: 1876, column: 47)
!367 = !DILocation(line: 1878, column: 18, scope: !366)
!368 = !DILocation(line: 1878, column: 31, scope: !366)
!369 = !DILocation(line: 1878, column: 17, scope: !366)
!370 = !DILocation(line: 1878, column: 15, scope: !366)
!371 = !DILocation(line: 1879, column: 4, scope: !366)
!372 = !DILocation(line: 1883, column: 14, scope: !373)
!373 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1883, column: 4)
!374 = !DILocation(line: 1883, column: 12, scope: !373)
!375 = !DILocation(line: 1883, column: 9, scope: !373)
!376 = !DILocation(line: 1883, column: 23, scope: !377)
!377 = distinct !DILexicalBlock(scope: !373, file: !3, line: 1883, column: 4)
!378 = !DILocation(line: 1883, column: 26, scope: !377)
!379 = !DILocation(line: 1883, column: 4, scope: !373)
!380 = !DILocation(line: 1884, column: 11, scope: !381)
!381 = distinct !DILexicalBlock(scope: !382, file: !3, line: 1884, column: 11)
!382 = distinct !DILexicalBlock(scope: !377, file: !3, line: 1883, column: 50)
!383 = !DILocation(line: 1884, column: 11, scope: !382)
!384 = !DILocation(line: 1884, column: 25, scope: !381)
!385 = !DILocation(line: 1885, column: 11, scope: !386)
!386 = distinct !DILexicalBlock(scope: !382, file: !3, line: 1885, column: 11)
!387 = !DILocation(line: 1885, column: 15, scope: !386)
!388 = !DILocation(line: 1885, column: 23, scope: !386)
!389 = !DILocation(line: 1885, column: 30, scope: !386)
!390 = !DILocation(line: 1885, column: 33, scope: !386)
!391 = !DILocation(line: 1885, column: 37, scope: !386)
!392 = !DILocation(line: 1885, column: 45, scope: !386)
!393 = !DILocation(line: 1885, column: 11, scope: !382)
!394 = !DILocation(line: 1886, column: 17, scope: !395)
!395 = distinct !DILexicalBlock(scope: !396, file: !3, line: 1886, column: 10)
!396 = distinct !DILexicalBlock(scope: !386, file: !3, line: 1885, column: 53)
!397 = !DILocation(line: 1886, column: 15, scope: !395)
!398 = !DILocation(line: 1886, column: 22, scope: !399)
!399 = distinct !DILexicalBlock(scope: !395, file: !3, line: 1886, column: 10)
!400 = !DILocation(line: 1886, column: 26, scope: !399)
!401 = !DILocation(line: 1886, column: 31, scope: !399)
!402 = !DILocation(line: 1886, column: 34, scope: !399)
!403 = !DILocation(line: 1886, column: 10, scope: !395)
!404 = !DILocation(line: 1887, column: 21, scope: !405)
!405 = distinct !DILexicalBlock(scope: !399, file: !3, line: 1886, column: 48)
!406 = !DILocation(line: 1887, column: 25, scope: !405)
!407 = !DILocation(line: 1887, column: 30, scope: !405)
!408 = !DILocation(line: 1887, column: 13, scope: !405)
!409 = !DILocation(line: 1888, column: 43, scope: !410)
!410 = distinct !DILexicalBlock(scope: !405, file: !3, line: 1887, column: 34)
!411 = !DILocation(line: 1888, column: 53, scope: !410)
!412 = !DILocation(line: 1889, column: 43, scope: !410)
!413 = !DILocation(line: 1889, column: 53, scope: !410)
!414 = !DILocation(line: 1890, column: 43, scope: !410)
!415 = !DILocation(line: 1890, column: 51, scope: !410)
!416 = !DILocation(line: 1891, column: 43, scope: !410)
!417 = !DILocation(line: 1891, column: 51, scope: !410)
!418 = !DILocation(line: 1892, column: 43, scope: !410)
!419 = !DILocation(line: 1892, column: 54, scope: !410)
!420 = !DILocation(line: 1893, column: 43, scope: !410)
!421 = !DILocation(line: 1893, column: 51, scope: !410)
!422 = !DILocation(line: 1894, column: 43, scope: !410)
!423 = !DILocation(line: 1894, column: 51, scope: !410)
!424 = !DILocation(line: 1895, column: 43, scope: !410)
!425 = !DILocation(line: 1895, column: 52, scope: !410)
!426 = !DILocation(line: 1896, column: 43, scope: !410)
!427 = !DILocation(line: 1896, column: 48, scope: !410)
!428 = !DILocation(line: 1897, column: 43, scope: !410)
!429 = !DILocation(line: 1897, column: 48, scope: !410)
!430 = !DILocation(line: 1898, column: 43, scope: !410)
!431 = !DILocation(line: 1898, column: 48, scope: !410)
!432 = !DILocation(line: 1899, column: 43, scope: !410)
!433 = !DILocation(line: 1899, column: 48, scope: !410)
!434 = !DILocation(line: 1900, column: 43, scope: !410)
!435 = !DILocation(line: 1900, column: 48, scope: !410)
!436 = !DILocation(line: 1901, column: 43, scope: !410)
!437 = !DILocation(line: 1901, column: 48, scope: !410)
!438 = !DILocation(line: 1902, column: 43, scope: !410)
!439 = !DILocation(line: 1902, column: 48, scope: !410)
!440 = !DILocation(line: 1903, column: 43, scope: !410)
!441 = !DILocation(line: 1903, column: 48, scope: !410)
!442 = !DILocation(line: 1904, column: 43, scope: !410)
!443 = !DILocation(line: 1904, column: 48, scope: !410)
!444 = !DILocation(line: 1906, column: 26, scope: !410)
!445 = !DILocation(line: 1906, column: 48, scope: !410)
!446 = !DILocation(line: 1907, column: 35, scope: !410)
!447 = !DILocation(line: 1907, column: 39, scope: !410)
!448 = !DILocation(line: 1908, column: 34, scope: !410)
!449 = !DILocation(line: 1908, column: 26, scope: !410)
!450 = !DILocation(line: 1909, column: 26, scope: !410)
!451 = !DILocation(line: 1911, column: 36, scope: !410)
!452 = !DILocation(line: 1912, column: 36, scope: !410)
!453 = !DILocation(line: 1912, column: 46, scope: !410)
!454 = !DILocation(line: 1912, column: 50, scope: !410)
!455 = !DILocation(line: 1911, column: 26, scope: !410)
!456 = !DILocation(line: 1913, column: 34, scope: !410)
!457 = !DILocation(line: 1913, column: 26, scope: !410)
!458 = !DILocation(line: 1914, column: 26, scope: !410)
!459 = !DILocation(line: 1917, column: 10, scope: !405)
!460 = !DILocation(line: 1886, column: 44, scope: !399)
!461 = !DILocation(line: 1886, column: 10, scope: !399)
!462 = distinct !{!462, !403, !463}
!463 = !DILocation(line: 1917, column: 10, scope: !395)
!464 = !DILocation(line: 1918, column: 7, scope: !396)
!465 = !DILocation(line: 1919, column: 4, scope: !382)
!466 = !DILocation(line: 1883, column: 40, scope: !377)
!467 = !DILocation(line: 1883, column: 44, scope: !377)
!468 = !DILocation(line: 1883, column: 38, scope: !377)
!469 = !DILocation(line: 1883, column: 4, scope: !377)
!470 = distinct !{!470, !379, !471}
!471 = !DILocation(line: 1919, column: 4, scope: !373)
!472 = !DILocation(line: 1922, column: 14, scope: !473)
!473 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1922, column: 4)
!474 = !DILocation(line: 1922, column: 12, scope: !473)
!475 = !DILocation(line: 1922, column: 9, scope: !473)
!476 = !DILocation(line: 1922, column: 23, scope: !477)
!477 = distinct !DILexicalBlock(scope: !473, file: !3, line: 1922, column: 4)
!478 = !DILocation(line: 1922, column: 26, scope: !477)
!479 = !DILocation(line: 1922, column: 4, scope: !473)
!480 = !DILocation(line: 1923, column: 11, scope: !481)
!481 = distinct !DILexicalBlock(scope: !482, file: !3, line: 1923, column: 11)
!482 = distinct !DILexicalBlock(scope: !477, file: !3, line: 1922, column: 50)
!483 = !DILocation(line: 1923, column: 11, scope: !482)
!484 = !DILocation(line: 1923, column: 25, scope: !481)
!485 = !DILocation(line: 1924, column: 11, scope: !486)
!486 = distinct !DILexicalBlock(scope: !482, file: !3, line: 1924, column: 11)
!487 = !DILocation(line: 1924, column: 11, scope: !482)
!488 = !DILocation(line: 1924, column: 59, scope: !486)
!489 = !DILocation(line: 1924, column: 42, scope: !486)
!490 = !DILocation(line: 1925, column: 11, scope: !491)
!491 = distinct !DILexicalBlock(scope: !486, file: !3, line: 1925, column: 11)
!492 = !DILocation(line: 1925, column: 11, scope: !486)
!493 = !DILocation(line: 1925, column: 59, scope: !491)
!494 = !DILocation(line: 1925, column: 42, scope: !491)
!495 = !DILocation(line: 1926, column: 11, scope: !496)
!496 = distinct !DILexicalBlock(scope: !491, file: !3, line: 1926, column: 11)
!497 = !DILocation(line: 1926, column: 11, scope: !491)
!498 = !DILocation(line: 1926, column: 59, scope: !496)
!499 = !DILocation(line: 1926, column: 42, scope: !496)
!500 = !DILocation(line: 1927, column: 11, scope: !501)
!501 = distinct !DILexicalBlock(scope: !496, file: !3, line: 1927, column: 11)
!502 = !DILocation(line: 1927, column: 11, scope: !496)
!503 = !DILocation(line: 1927, column: 59, scope: !501)
!504 = !DILocation(line: 1927, column: 42, scope: !501)
!505 = !DILocation(line: 1928, column: 11, scope: !506)
!506 = distinct !DILexicalBlock(scope: !501, file: !3, line: 1928, column: 11)
!507 = !DILocation(line: 1928, column: 11, scope: !501)
!508 = !DILocation(line: 1928, column: 59, scope: !506)
!509 = !DILocation(line: 1928, column: 42, scope: !506)
!510 = !DILocation(line: 1929, column: 11, scope: !511)
!511 = distinct !DILexicalBlock(scope: !506, file: !3, line: 1929, column: 11)
!512 = !DILocation(line: 1929, column: 11, scope: !506)
!513 = !DILocation(line: 1929, column: 59, scope: !511)
!514 = !DILocation(line: 1929, column: 42, scope: !511)
!515 = !DILocation(line: 1930, column: 11, scope: !516)
!516 = distinct !DILexicalBlock(scope: !511, file: !3, line: 1930, column: 11)
!517 = !DILocation(line: 1930, column: 11, scope: !511)
!518 = !DILocation(line: 1930, column: 59, scope: !516)
!519 = !DILocation(line: 1930, column: 42, scope: !516)
!520 = !DILocation(line: 1931, column: 11, scope: !521)
!521 = distinct !DILexicalBlock(scope: !516, file: !3, line: 1931, column: 11)
!522 = !DILocation(line: 1931, column: 11, scope: !516)
!523 = !DILocation(line: 1931, column: 59, scope: !521)
!524 = !DILocation(line: 1931, column: 42, scope: !521)
!525 = !DILocation(line: 1932, column: 11, scope: !526)
!526 = distinct !DILexicalBlock(scope: !521, file: !3, line: 1932, column: 11)
!527 = !DILocation(line: 1932, column: 11, scope: !521)
!528 = !DILocation(line: 1932, column: 42, scope: !526)
!529 = !DILocation(line: 1933, column: 11, scope: !530)
!530 = distinct !DILexicalBlock(scope: !526, file: !3, line: 1933, column: 11)
!531 = !DILocation(line: 1933, column: 11, scope: !526)
!532 = !DILocation(line: 1933, column: 42, scope: !530)
!533 = !DILocation(line: 1934, column: 11, scope: !534)
!534 = distinct !DILexicalBlock(scope: !530, file: !3, line: 1934, column: 11)
!535 = !DILocation(line: 1934, column: 11, scope: !530)
!536 = !DILocation(line: 1934, column: 53, scope: !534)
!537 = !DILocation(line: 1934, column: 42, scope: !534)
!538 = !DILocation(line: 1935, column: 11, scope: !539)
!539 = distinct !DILexicalBlock(scope: !534, file: !3, line: 1935, column: 11)
!540 = !DILocation(line: 1935, column: 11, scope: !534)
!541 = !DILocation(line: 1935, column: 52, scope: !539)
!542 = !DILocation(line: 1935, column: 56, scope: !539)
!543 = !DILocation(line: 1935, column: 42, scope: !539)
!544 = !DILocation(line: 1936, column: 11, scope: !545)
!545 = distinct !DILexicalBlock(scope: !539, file: !3, line: 1936, column: 11)
!546 = !DILocation(line: 1936, column: 11, scope: !539)
!547 = !DILocation(line: 1936, column: 52, scope: !545)
!548 = !DILocation(line: 1936, column: 56, scope: !545)
!549 = !DILocation(line: 1936, column: 42, scope: !545)
!550 = !DILocation(line: 1937, column: 11, scope: !551)
!551 = distinct !DILexicalBlock(scope: !545, file: !3, line: 1937, column: 11)
!552 = !DILocation(line: 1937, column: 11, scope: !545)
!553 = !DILocation(line: 1937, column: 56, scope: !551)
!554 = !DILocation(line: 1937, column: 42, scope: !551)
!555 = !DILocation(line: 1938, column: 11, scope: !556)
!556 = distinct !DILexicalBlock(scope: !551, file: !3, line: 1938, column: 11)
!557 = !DILocation(line: 1938, column: 11, scope: !551)
!558 = !DILocation(line: 1938, column: 56, scope: !556)
!559 = !DILocation(line: 1938, column: 42, scope: !556)
!560 = !DILocation(line: 1939, column: 11, scope: !561)
!561 = distinct !DILexicalBlock(scope: !556, file: !3, line: 1939, column: 11)
!562 = !DILocation(line: 1939, column: 11, scope: !556)
!563 = !DILocation(line: 1939, column: 51, scope: !561)
!564 = !DILocation(line: 1939, column: 42, scope: !561)
!565 = !DILocation(line: 1940, column: 11, scope: !566)
!566 = distinct !DILexicalBlock(scope: !561, file: !3, line: 1940, column: 11)
!567 = !DILocation(line: 1940, column: 11, scope: !561)
!568 = !DILocation(line: 1940, column: 52, scope: !569)
!569 = distinct !DILexicalBlock(scope: !566, file: !3, line: 1940, column: 42)
!570 = !DILocation(line: 1940, column: 44, scope: !569)
!571 = !DILocation(line: 1940, column: 64, scope: !569)
!572 = !DILocation(line: 1942, column: 24, scope: !573)
!573 = distinct !DILexicalBlock(scope: !566, file: !3, line: 1942, column: 14)
!574 = !DILocation(line: 1942, column: 28, scope: !573)
!575 = !DILocation(line: 1942, column: 14, scope: !573)
!576 = !DILocation(line: 1942, column: 43, scope: !573)
!577 = !DILocation(line: 1942, column: 14, scope: !566)
!578 = !DILocation(line: 1943, column: 23, scope: !579)
!579 = distinct !DILexicalBlock(scope: !573, file: !3, line: 1942, column: 49)
!580 = !DILocation(line: 1943, column: 54, scope: !579)
!581 = !DILocation(line: 1943, column: 64, scope: !579)
!582 = !DILocation(line: 1943, column: 68, scope: !579)
!583 = !DILocation(line: 1943, column: 13, scope: !579)
!584 = !DILocation(line: 1944, column: 21, scope: !579)
!585 = !DILocation(line: 1944, column: 13, scope: !579)
!586 = !DILocation(line: 1945, column: 13, scope: !579)
!587 = !DILocation(line: 1947, column: 4, scope: !482)
!588 = !DILocation(line: 1922, column: 40, scope: !477)
!589 = !DILocation(line: 1922, column: 44, scope: !477)
!590 = !DILocation(line: 1922, column: 38, scope: !477)
!591 = !DILocation(line: 1922, column: 4, scope: !477)
!592 = distinct !{!592, !479, !593}
!593 = !DILocation(line: 1947, column: 4, scope: !473)
!594 = !DILocation(line: 1949, column: 8, scope: !595)
!595 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1949, column: 8)
!596 = !DILocation(line: 1949, column: 18, scope: !595)
!597 = !DILocation(line: 1949, column: 8, scope: !197)
!598 = !DILocation(line: 1949, column: 33, scope: !595)
!599 = !DILocation(line: 1949, column: 23, scope: !595)
!600 = !DILocation(line: 1950, column: 8, scope: !601)
!601 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1950, column: 8)
!602 = !DILocation(line: 1950, column: 15, scope: !601)
!603 = !DILocation(line: 1950, column: 23, scope: !601)
!604 = !DILocation(line: 1950, column: 26, scope: !601)
!605 = !DILocation(line: 1950, column: 36, scope: !601)
!606 = !DILocation(line: 1950, column: 39, scope: !601)
!607 = !DILocation(line: 1950, column: 53, scope: !601)
!608 = !DILocation(line: 1950, column: 8, scope: !197)
!609 = !DILocation(line: 1951, column: 21, scope: !601)
!610 = !DILocation(line: 1951, column: 7, scope: !601)
!611 = !DILocation(line: 1953, column: 8, scope: !612)
!612 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1953, column: 8)
!613 = !DILocation(line: 1953, column: 15, scope: !612)
!614 = !DILocation(line: 1953, column: 26, scope: !612)
!615 = !DILocation(line: 1953, column: 29, scope: !612)
!616 = !DILocation(line: 1953, column: 37, scope: !612)
!617 = !DILocation(line: 1953, column: 8, scope: !197)
!618 = !DILocation(line: 1954, column: 17, scope: !619)
!619 = distinct !DILexicalBlock(scope: !612, file: !3, line: 1953, column: 48)
!620 = !DILocation(line: 1955, column: 17, scope: !619)
!621 = !DILocation(line: 1954, column: 7, scope: !619)
!622 = !DILocation(line: 1956, column: 7, scope: !619)
!623 = !DILocation(line: 1959, column: 8, scope: !624)
!624 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1959, column: 8)
!625 = !DILocation(line: 1959, column: 16, scope: !624)
!626 = !DILocation(line: 1959, column: 26, scope: !624)
!627 = !DILocation(line: 1959, column: 29, scope: !624)
!628 = !DILocation(line: 1959, column: 42, scope: !624)
!629 = !DILocation(line: 1959, column: 8, scope: !197)
!630 = !DILocation(line: 1960, column: 15, scope: !624)
!631 = !DILocation(line: 1960, column: 7, scope: !624)
!632 = !DILocation(line: 1962, column: 8, scope: !633)
!633 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1962, column: 8)
!634 = !DILocation(line: 1962, column: 15, scope: !633)
!635 = !DILocation(line: 1962, column: 8, scope: !197)
!636 = !DILocation(line: 1962, column: 38, scope: !633)
!637 = !DILocation(line: 1962, column: 24, scope: !633)
!638 = !DILocation(line: 1964, column: 8, scope: !639)
!639 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1964, column: 8)
!640 = !DILocation(line: 1964, column: 16, scope: !639)
!641 = !DILocation(line: 1964, column: 8, scope: !197)
!642 = !DILocation(line: 1965, column: 7, scope: !643)
!643 = distinct !DILexicalBlock(scope: !639, file: !3, line: 1964, column: 27)
!644 = !DILocation(line: 1966, column: 7, scope: !643)
!645 = !DILocation(line: 1968, column: 7, scope: !643)
!646 = !DILocation(line: 1970, column: 4, scope: !643)
!647 = !DILocation(line: 1972, column: 8, scope: !648)
!648 = distinct !DILexicalBlock(scope: !197, file: !3, line: 1972, column: 8)
!649 = !DILocation(line: 1972, column: 15, scope: !648)
!650 = !DILocation(line: 1972, column: 8, scope: !197)
!651 = !DILocation(line: 1973, column: 10, scope: !652)
!652 = distinct !DILexicalBlock(scope: !653, file: !3, line: 1973, column: 10)
!653 = distinct !DILexicalBlock(scope: !648, file: !3, line: 1972, column: 24)
!654 = !DILocation(line: 1973, column: 18, scope: !652)
!655 = !DILocation(line: 1973, column: 10, scope: !653)
!656 = !DILocation(line: 1974, column: 9, scope: !657)
!657 = distinct !DILexicalBlock(scope: !652, file: !3, line: 1973, column: 29)
!658 = !DILocation(line: 1975, column: 6, scope: !657)
!659 = !DILocation(line: 1976, column: 16, scope: !660)
!660 = distinct !DILexicalBlock(scope: !652, file: !3, line: 1975, column: 13)
!661 = !DILocation(line: 1977, column: 19, scope: !662)
!662 = distinct !DILexicalBlock(scope: !660, file: !3, line: 1977, column: 9)
!663 = !DILocation(line: 1977, column: 17, scope: !662)
!664 = !DILocation(line: 1977, column: 14, scope: !662)
!665 = !DILocation(line: 1977, column: 28, scope: !666)
!666 = distinct !DILexicalBlock(scope: !662, file: !3, line: 1977, column: 9)
!667 = !DILocation(line: 1977, column: 31, scope: !666)
!668 = !DILocation(line: 1977, column: 9, scope: !662)
!669 = !DILocation(line: 1978, column: 16, scope: !670)
!670 = distinct !DILexicalBlock(scope: !671, file: !3, line: 1978, column: 16)
!671 = distinct !DILexicalBlock(scope: !666, file: !3, line: 1977, column: 55)
!672 = !DILocation(line: 1978, column: 16, scope: !671)
!673 = !DILocation(line: 1978, column: 39, scope: !674)
!674 = distinct !DILexicalBlock(scope: !670, file: !3, line: 1978, column: 30)
!675 = !DILocation(line: 1978, column: 48, scope: !674)
!676 = !DILocation(line: 1979, column: 16, scope: !677)
!677 = distinct !DILexicalBlock(scope: !671, file: !3, line: 1979, column: 16)
!678 = !DILocation(line: 1979, column: 20, scope: !677)
!679 = !DILocation(line: 1979, column: 28, scope: !677)
!680 = !DILocation(line: 1979, column: 35, scope: !677)
!681 = !DILocation(line: 1979, column: 38, scope: !677)
!682 = !DILocation(line: 1979, column: 16, scope: !671)
!683 = !DILocation(line: 1979, column: 46, scope: !677)
!684 = !DILocation(line: 1980, column: 29, scope: !671)
!685 = !DILocation(line: 1981, column: 23, scope: !671)
!686 = !DILocation(line: 1981, column: 27, scope: !671)
!687 = !DILocation(line: 1981, column: 12, scope: !671)
!688 = !DILocation(line: 1982, column: 9, scope: !671)
!689 = !DILocation(line: 1977, column: 45, scope: !666)
!690 = !DILocation(line: 1977, column: 49, scope: !666)
!691 = !DILocation(line: 1977, column: 43, scope: !666)
!692 = !DILocation(line: 1977, column: 9, scope: !666)
!693 = distinct !{!693, !668, !694}
!694 = !DILocation(line: 1982, column: 9, scope: !662)
!695 = !DILocation(line: 1984, column: 4, scope: !653)
!696 = !DILocation(line: 1987, column: 8, scope: !697)
!697 = distinct !DILexicalBlock(scope: !648, file: !3, line: 1987, column: 8)
!698 = !DILocation(line: 1987, column: 15, scope: !697)
!699 = !DILocation(line: 1987, column: 8, scope: !648)
!700 = !DILocation(line: 1988, column: 21, scope: !701)
!701 = distinct !DILexicalBlock(scope: !697, file: !3, line: 1987, column: 26)
!702 = !DILocation(line: 1989, column: 11, scope: !703)
!703 = distinct !DILexicalBlock(scope: !701, file: !3, line: 1989, column: 11)
!704 = !DILocation(line: 1989, column: 19, scope: !703)
!705 = !DILocation(line: 1989, column: 11, scope: !701)
!706 = !DILocation(line: 1990, column: 10, scope: !707)
!707 = distinct !DILexicalBlock(scope: !703, file: !3, line: 1989, column: 30)
!708 = !DILocation(line: 1991, column: 7, scope: !707)
!709 = !DILocation(line: 1992, column: 17, scope: !710)
!710 = distinct !DILexicalBlock(scope: !703, file: !3, line: 1991, column: 14)
!711 = !DILocation(line: 1993, column: 20, scope: !712)
!712 = distinct !DILexicalBlock(scope: !710, file: !3, line: 1993, column: 10)
!713 = !DILocation(line: 1993, column: 18, scope: !712)
!714 = !DILocation(line: 1993, column: 15, scope: !712)
!715 = !DILocation(line: 1993, column: 29, scope: !716)
!716 = distinct !DILexicalBlock(scope: !712, file: !3, line: 1993, column: 10)
!717 = !DILocation(line: 1993, column: 32, scope: !716)
!718 = !DILocation(line: 1993, column: 10, scope: !712)
!719 = !DILocation(line: 1994, column: 17, scope: !720)
!720 = distinct !DILexicalBlock(scope: !721, file: !3, line: 1994, column: 17)
!721 = distinct !DILexicalBlock(scope: !716, file: !3, line: 1993, column: 56)
!722 = !DILocation(line: 1994, column: 17, scope: !721)
!723 = !DILocation(line: 1994, column: 40, scope: !724)
!724 = distinct !DILexicalBlock(scope: !720, file: !3, line: 1994, column: 31)
!725 = !DILocation(line: 1994, column: 49, scope: !724)
!726 = !DILocation(line: 1995, column: 17, scope: !727)
!727 = distinct !DILexicalBlock(scope: !721, file: !3, line: 1995, column: 17)
!728 = !DILocation(line: 1995, column: 21, scope: !727)
!729 = !DILocation(line: 1995, column: 29, scope: !727)
!730 = !DILocation(line: 1995, column: 36, scope: !727)
!731 = !DILocation(line: 1995, column: 39, scope: !727)
!732 = !DILocation(line: 1995, column: 17, scope: !721)
!733 = !DILocation(line: 1995, column: 47, scope: !727)
!734 = !DILocation(line: 1996, column: 30, scope: !721)
!735 = !DILocation(line: 1997, column: 26, scope: !721)
!736 = !DILocation(line: 1997, column: 30, scope: !721)
!737 = !DILocation(line: 1997, column: 13, scope: !721)
!738 = !DILocation(line: 1998, column: 10, scope: !721)
!739 = !DILocation(line: 1993, column: 46, scope: !716)
!740 = !DILocation(line: 1993, column: 50, scope: !716)
!741 = !DILocation(line: 1993, column: 44, scope: !716)
!742 = !DILocation(line: 1993, column: 10, scope: !716)
!743 = distinct !{!743, !718, !744}
!744 = !DILocation(line: 1998, column: 10, scope: !712)
!745 = !DILocation(line: 2000, column: 11, scope: !746)
!746 = distinct !DILexicalBlock(scope: !701, file: !3, line: 2000, column: 11)
!747 = !DILocation(line: 2000, column: 11, scope: !701)
!748 = !DILocation(line: 2001, column: 10, scope: !749)
!749 = distinct !DILexicalBlock(scope: !746, file: !3, line: 2000, column: 26)
!750 = !DILocation(line: 2002, column: 15, scope: !749)
!751 = !DILocation(line: 2002, column: 10, scope: !749)
!752 = !DILocation(line: 2004, column: 4, scope: !701)
!753 = !DILocation(line: 2007, column: 22, scope: !754)
!754 = distinct !DILexicalBlock(scope: !697, file: !3, line: 2006, column: 9)
!755 = !DILocation(line: 2008, column: 11, scope: !756)
!756 = distinct !DILexicalBlock(scope: !754, file: !3, line: 2008, column: 11)
!757 = !DILocation(line: 2008, column: 19, scope: !756)
!758 = !DILocation(line: 2008, column: 11, scope: !754)
!759 = !DILocation(line: 2009, column: 10, scope: !760)
!760 = distinct !DILexicalBlock(scope: !756, file: !3, line: 2008, column: 30)
!761 = !DILocation(line: 2010, column: 7, scope: !760)
!762 = !DILocation(line: 2011, column: 17, scope: !763)
!763 = distinct !DILexicalBlock(scope: !756, file: !3, line: 2010, column: 14)
!764 = !DILocation(line: 2012, column: 20, scope: !765)
!765 = distinct !DILexicalBlock(scope: !763, file: !3, line: 2012, column: 10)
!766 = !DILocation(line: 2012, column: 18, scope: !765)
!767 = !DILocation(line: 2012, column: 15, scope: !765)
!768 = !DILocation(line: 2012, column: 29, scope: !769)
!769 = distinct !DILexicalBlock(scope: !765, file: !3, line: 2012, column: 10)
!770 = !DILocation(line: 2012, column: 32, scope: !769)
!771 = !DILocation(line: 2012, column: 10, scope: !765)
!772 = !DILocation(line: 2013, column: 10, scope: !773)
!773 = distinct !DILexicalBlock(scope: !774, file: !3, line: 2013, column: 10)
!774 = distinct !DILexicalBlock(scope: !769, file: !3, line: 2012, column: 56)
!775 = !DILocation(line: 2013, column: 10, scope: !774)
!776 = !DILocation(line: 2013, column: 33, scope: !777)
!777 = distinct !DILexicalBlock(scope: !773, file: !3, line: 2013, column: 24)
!778 = !DILocation(line: 2013, column: 42, scope: !777)
!779 = !DILocation(line: 2014, column: 17, scope: !780)
!780 = distinct !DILexicalBlock(scope: !774, file: !3, line: 2014, column: 17)
!781 = !DILocation(line: 2014, column: 21, scope: !780)
!782 = !DILocation(line: 2014, column: 29, scope: !780)
!783 = !DILocation(line: 2014, column: 36, scope: !780)
!784 = !DILocation(line: 2014, column: 39, scope: !780)
!785 = !DILocation(line: 2014, column: 17, scope: !774)
!786 = !DILocation(line: 2014, column: 47, scope: !780)
!787 = !DILocation(line: 2015, column: 30, scope: !774)
!788 = !DILocation(line: 2016, column: 21, scope: !774)
!789 = !DILocation(line: 2016, column: 25, scope: !774)
!790 = !DILocation(line: 2016, column: 13, scope: !774)
!791 = !DILocation(line: 2017, column: 3, scope: !774)
!792 = !DILocation(line: 2012, column: 46, scope: !769)
!793 = !DILocation(line: 2012, column: 50, scope: !769)
!794 = !DILocation(line: 2012, column: 44, scope: !769)
!795 = !DILocation(line: 2012, column: 10, scope: !769)
!796 = distinct !{!796, !771, !797}
!797 = !DILocation(line: 2017, column: 3, scope: !765)
!798 = !DILocation(line: 2019, column: 11, scope: !799)
!799 = distinct !DILexicalBlock(scope: !754, file: !3, line: 2019, column: 11)
!800 = !DILocation(line: 2019, column: 26, scope: !799)
!801 = !DILocation(line: 2019, column: 29, scope: !799)
!802 = !DILocation(line: 2019, column: 11, scope: !754)
!803 = !DILocation(line: 2020, column: 20, scope: !804)
!804 = distinct !DILexicalBlock(scope: !799, file: !3, line: 2019, column: 36)
!805 = !DILocation(line: 2020, column: 10, scope: !804)
!806 = !DILocation(line: 2025, column: 10, scope: !804)
!807 = !DILocation(line: 2026, column: 15, scope: !804)
!808 = !DILocation(line: 2026, column: 10, scope: !804)
!809 = !DILocation(line: 2033, column: 9, scope: !197)
!810 = !DILocation(line: 2033, column: 7, scope: !197)
!811 = !DILocation(line: 2034, column: 4, scope: !197)
!812 = !DILocation(line: 2034, column: 11, scope: !197)
!813 = !DILocation(line: 2034, column: 14, scope: !197)
!814 = !DILocalVariable(name: "aa2", scope: !815, file: !3, line: 2035, type: !31)
!815 = distinct !DILexicalBlock(scope: !197, file: !3, line: 2034, column: 23)
!816 = !DILocation(line: 2035, column: 13, scope: !815)
!817 = !DILocation(line: 2035, column: 19, scope: !815)
!818 = !DILocation(line: 2035, column: 23, scope: !815)
!819 = !DILocation(line: 2036, column: 11, scope: !820)
!820 = distinct !DILexicalBlock(scope: !815, file: !3, line: 2036, column: 11)
!821 = !DILocation(line: 2036, column: 15, scope: !820)
!822 = !DILocation(line: 2036, column: 20, scope: !820)
!823 = !DILocation(line: 2036, column: 11, scope: !815)
!824 = !DILocation(line: 2036, column: 34, scope: !820)
!825 = !DILocation(line: 2036, column: 38, scope: !820)
!826 = !DILocation(line: 2036, column: 29, scope: !820)
!827 = !DILocation(line: 2037, column: 12, scope: !815)
!828 = !DILocation(line: 2037, column: 7, scope: !815)
!829 = !DILocation(line: 2038, column: 12, scope: !815)
!830 = !DILocation(line: 2038, column: 10, scope: !815)
!831 = distinct !{!831, !811, !832}
!832 = !DILocation(line: 2039, column: 4, scope: !197)
!833 = !DILocation(line: 2041, column: 11, scope: !197)
!834 = !DILocation(line: 2041, column: 4, scope: !197)
!835 = distinct !DISubprogram(name: "mySIGSEGVorSIGBUScatcher", scope: !3, file: !3, line: 825, type: !836, scopeLine: 826, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!836 = !DISubroutineType(types: !837)
!837 = !{null, !200}
!838 = !DILocalVariable(name: "n", arg: 1, scope: !835, file: !3, line: 825, type: !200)
!839 = !DILocation(line: 825, column: 43, scope: !835)
!840 = !DILocation(line: 827, column: 8, scope: !841)
!841 = distinct !DILexicalBlock(scope: !835, file: !3, line: 827, column: 8)
!842 = !DILocation(line: 827, column: 15, scope: !841)
!843 = !DILocation(line: 827, column: 8, scope: !835)
!844 = !DILocation(line: 829, column: 7, scope: !841)
!845 = !DILocation(line: 847, column: 7, scope: !841)
!846 = !DILocation(line: 828, column: 7, scope: !841)
!847 = !DILocation(line: 850, column: 7, scope: !841)
!848 = !DILocation(line: 870, column: 7, scope: !841)
!849 = !DILocation(line: 849, column: 7, scope: !841)
!850 = !DILocation(line: 872, column: 4, scope: !835)
!851 = !DILocation(line: 873, column: 8, scope: !852)
!852 = distinct !DILexicalBlock(scope: !835, file: !3, line: 873, column: 8)
!853 = !DILocation(line: 873, column: 15, scope: !852)
!854 = !DILocation(line: 873, column: 8, scope: !835)
!855 = !DILocation(line: 874, column: 7, scope: !852)
!856 = !DILocation(line: 875, column: 9, scope: !857)
!857 = distinct !DILexicalBlock(scope: !852, file: !3, line: 875, column: 7)
!858 = !DILocation(line: 875, column: 20, scope: !857)
!859 = distinct !DISubprogram(name: "copyFileName", scope: !3, file: !3, line: 928, type: !860, scopeLine: 929, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!860 = !DISubroutineType(types: !861)
!861 = !{null, !24, !24}
!862 = !DILocalVariable(name: "to", arg: 1, scope: !859, file: !3, line: 928, type: !24)
!863 = !DILocation(line: 928, column: 27, scope: !859)
!864 = !DILocalVariable(name: "from", arg: 2, scope: !859, file: !3, line: 928, type: !24)
!865 = !DILocation(line: 928, column: 37, scope: !859)
!866 = !DILocation(line: 930, column: 16, scope: !867)
!867 = distinct !DILexicalBlock(scope: !859, file: !3, line: 930, column: 9)
!868 = !DILocation(line: 930, column: 9, scope: !867)
!869 = !DILocation(line: 930, column: 22, scope: !867)
!870 = !DILocation(line: 930, column: 9, scope: !859)
!871 = !DILocation(line: 932, column: 10, scope: !872)
!872 = distinct !DILexicalBlock(scope: !867, file: !3, line: 930, column: 44)
!873 = !DILocation(line: 936, column: 10, scope: !872)
!874 = !DILocation(line: 931, column: 7, scope: !872)
!875 = !DILocation(line: 938, column: 7, scope: !872)
!876 = !DILocation(line: 939, column: 12, scope: !872)
!877 = !DILocation(line: 939, column: 7, scope: !872)
!878 = !DILocation(line: 942, column: 11, scope: !859)
!879 = !DILocation(line: 942, column: 14, scope: !859)
!880 = !DILocation(line: 942, column: 3, scope: !859)
!881 = !DILocation(line: 943, column: 3, scope: !859)
!882 = !DILocation(line: 943, column: 23, scope: !859)
!883 = !DILocation(line: 944, column: 1, scope: !859)
!884 = distinct !DISubprogram(name: "addFlagsFromEnvVar", scope: !3, file: !3, line: 1760, type: !885, scopeLine: 1761, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!885 = !DISubroutineType(types: !886)
!886 = !{null, !887, !24}
!887 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64)
!888 = !DILocalVariable(name: "argList", arg: 1, scope: !884, file: !3, line: 1760, type: !887)
!889 = !DILocation(line: 1760, column: 34, scope: !884)
!890 = !DILocalVariable(name: "varName", arg: 2, scope: !884, file: !3, line: 1760, type: !24)
!891 = !DILocation(line: 1760, column: 49, scope: !884)
!892 = !DILocalVariable(name: "i", scope: !884, file: !3, line: 1762, type: !28)
!893 = !DILocation(line: 1762, column: 10, scope: !884)
!894 = !DILocalVariable(name: "j", scope: !884, file: !3, line: 1762, type: !28)
!895 = !DILocation(line: 1762, column: 13, scope: !884)
!896 = !DILocalVariable(name: "k", scope: !884, file: !3, line: 1762, type: !28)
!897 = !DILocation(line: 1762, column: 16, scope: !884)
!898 = !DILocalVariable(name: "envbase", scope: !884, file: !3, line: 1763, type: !24)
!899 = !DILocation(line: 1763, column: 10, scope: !884)
!900 = !DILocalVariable(name: "p", scope: !884, file: !3, line: 1763, type: !24)
!901 = !DILocation(line: 1763, column: 20, scope: !884)
!902 = !DILocation(line: 1765, column: 21, scope: !884)
!903 = !DILocation(line: 1765, column: 14, scope: !884)
!904 = !DILocation(line: 1765, column: 12, scope: !884)
!905 = !DILocation(line: 1766, column: 8, scope: !906)
!906 = distinct !DILexicalBlock(scope: !884, file: !3, line: 1766, column: 8)
!907 = !DILocation(line: 1766, column: 16, scope: !906)
!908 = !DILocation(line: 1766, column: 8, scope: !884)
!909 = !DILocation(line: 1767, column: 11, scope: !910)
!910 = distinct !DILexicalBlock(scope: !906, file: !3, line: 1766, column: 25)
!911 = !DILocation(line: 1767, column: 9, scope: !910)
!912 = !DILocation(line: 1768, column: 9, scope: !910)
!913 = !DILocation(line: 1769, column: 7, scope: !910)
!914 = !DILocation(line: 1770, column: 14, scope: !915)
!915 = distinct !DILexicalBlock(scope: !916, file: !3, line: 1770, column: 14)
!916 = distinct !DILexicalBlock(scope: !910, file: !3, line: 1769, column: 20)
!917 = !DILocation(line: 1770, column: 16, scope: !915)
!918 = !DILocation(line: 1770, column: 19, scope: !915)
!919 = !DILocation(line: 1770, column: 14, scope: !916)
!920 = !DILocation(line: 1770, column: 25, scope: !915)
!921 = !DILocation(line: 1771, column: 15, scope: !916)
!922 = !DILocation(line: 1771, column: 12, scope: !916)
!923 = !DILocation(line: 1772, column: 12, scope: !916)
!924 = !DILocation(line: 1773, column: 10, scope: !916)
!925 = !DILocation(line: 1773, column: 17, scope: !916)
!926 = !DILocation(line: 1773, column: 42, scope: !916)
!927 = distinct !{!927, !924, !926}
!928 = !DILocation(line: 1774, column: 10, scope: !916)
!929 = !DILocation(line: 1774, column: 17, scope: !916)
!930 = !DILocation(line: 1774, column: 19, scope: !916)
!931 = !DILocation(line: 1774, column: 22, scope: !916)
!932 = !DILocation(line: 1774, column: 27, scope: !916)
!933 = !DILocation(line: 1774, column: 31, scope: !916)
!934 = !DILocation(line: 1774, column: 30, scope: !916)
!935 = !DILocation(line: 0, scope: !916)
!936 = !DILocation(line: 1774, column: 56, scope: !916)
!937 = distinct !{!937, !928, !936}
!938 = !DILocation(line: 1775, column: 14, scope: !939)
!939 = distinct !DILexicalBlock(scope: !916, file: !3, line: 1775, column: 14)
!940 = !DILocation(line: 1775, column: 16, scope: !939)
!941 = !DILocation(line: 1775, column: 14, scope: !916)
!942 = !DILocation(line: 1776, column: 17, scope: !943)
!943 = distinct !DILexicalBlock(scope: !939, file: !3, line: 1775, column: 21)
!944 = !DILocation(line: 1776, column: 15, scope: !943)
!945 = !DILocation(line: 1776, column: 24, scope: !946)
!946 = distinct !DILexicalBlock(scope: !943, file: !3, line: 1776, column: 24)
!947 = !DILocation(line: 1776, column: 26, scope: !946)
!948 = !DILocation(line: 1776, column: 24, scope: !943)
!949 = !DILocation(line: 1776, column: 48, scope: !946)
!950 = !DILocation(line: 1776, column: 46, scope: !946)
!951 = !DILocation(line: 1777, column: 20, scope: !952)
!952 = distinct !DILexicalBlock(scope: !943, file: !3, line: 1777, column: 13)
!953 = !DILocation(line: 1777, column: 18, scope: !952)
!954 = !DILocation(line: 1777, column: 25, scope: !955)
!955 = distinct !DILexicalBlock(scope: !952, file: !3, line: 1777, column: 13)
!956 = !DILocation(line: 1777, column: 29, scope: !955)
!957 = !DILocation(line: 1777, column: 27, scope: !955)
!958 = !DILocation(line: 1777, column: 13, scope: !952)
!959 = !DILocation(line: 1777, column: 50, scope: !955)
!960 = !DILocation(line: 1777, column: 52, scope: !955)
!961 = !DILocation(line: 1777, column: 45, scope: !955)
!962 = !DILocation(line: 1777, column: 37, scope: !955)
!963 = !DILocation(line: 1777, column: 48, scope: !955)
!964 = !DILocation(line: 1777, column: 33, scope: !955)
!965 = !DILocation(line: 1777, column: 13, scope: !955)
!966 = distinct !{!966, !958, !967}
!967 = !DILocation(line: 1777, column: 53, scope: !952)
!968 = !DILocation(line: 1778, column: 21, scope: !943)
!969 = !DILocation(line: 1778, column: 13, scope: !943)
!970 = !DILocation(line: 1778, column: 24, scope: !943)
!971 = !DILocation(line: 1779, column: 13, scope: !943)
!972 = !DILocation(line: 1780, column: 10, scope: !943)
!973 = distinct !{!973, !913, !974}
!974 = !DILocation(line: 1781, column: 7, scope: !910)
!975 = !DILocation(line: 1782, column: 4, scope: !910)
!976 = !DILocation(line: 1783, column: 1, scope: !884)
!977 = distinct !DISubprogram(name: "snocString", scope: !3, file: !3, line: 1742, type: !978, scopeLine: 1743, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!978 = !DISubroutineType(types: !979)
!979 = !{!31, !31, !24}
!980 = !DILocalVariable(name: "root", arg: 1, scope: !977, file: !3, line: 1742, type: !31)
!981 = !DILocation(line: 1742, column: 26, scope: !977)
!982 = !DILocalVariable(name: "name", arg: 2, scope: !977, file: !3, line: 1742, type: !24)
!983 = !DILocation(line: 1742, column: 38, scope: !977)
!984 = !DILocation(line: 1744, column: 8, scope: !985)
!985 = distinct !DILexicalBlock(scope: !977, file: !3, line: 1744, column: 8)
!986 = !DILocation(line: 1744, column: 13, scope: !985)
!987 = !DILocation(line: 1744, column: 8, scope: !977)
!988 = !DILocalVariable(name: "tmp", scope: !989, file: !3, line: 1745, type: !31)
!989 = distinct !DILexicalBlock(scope: !985, file: !3, line: 1744, column: 22)
!990 = !DILocation(line: 1745, column: 13, scope: !989)
!991 = !DILocation(line: 1745, column: 19, scope: !989)
!992 = !DILocation(line: 1746, column: 49, scope: !989)
!993 = !DILocation(line: 1746, column: 42, scope: !989)
!994 = !DILocation(line: 1746, column: 40, scope: !989)
!995 = !DILocation(line: 1746, column: 38, scope: !989)
!996 = !DILocation(line: 1746, column: 27, scope: !989)
!997 = !DILocation(line: 1746, column: 7, scope: !989)
!998 = !DILocation(line: 1746, column: 12, scope: !989)
!999 = !DILocation(line: 1746, column: 17, scope: !989)
!1000 = !DILocation(line: 1747, column: 16, scope: !989)
!1001 = !DILocation(line: 1747, column: 21, scope: !989)
!1002 = !DILocation(line: 1747, column: 27, scope: !989)
!1003 = !DILocation(line: 1747, column: 7, scope: !989)
!1004 = !DILocation(line: 1748, column: 14, scope: !989)
!1005 = !DILocation(line: 1748, column: 7, scope: !989)
!1006 = !DILocalVariable(name: "tmp", scope: !1007, file: !3, line: 1750, type: !31)
!1007 = distinct !DILexicalBlock(scope: !985, file: !3, line: 1749, column: 11)
!1008 = !DILocation(line: 1750, column: 13, scope: !1007)
!1009 = !DILocation(line: 1750, column: 19, scope: !1007)
!1010 = !DILocation(line: 1751, column: 7, scope: !1007)
!1011 = !DILocation(line: 1751, column: 14, scope: !1007)
!1012 = !DILocation(line: 1751, column: 19, scope: !1007)
!1013 = !DILocation(line: 1751, column: 24, scope: !1007)
!1014 = !DILocation(line: 1751, column: 39, scope: !1007)
!1015 = !DILocation(line: 1751, column: 44, scope: !1007)
!1016 = !DILocation(line: 1751, column: 37, scope: !1007)
!1017 = distinct !{!1017, !1010, !1015}
!1018 = !DILocation(line: 1752, column: 32, scope: !1007)
!1019 = !DILocation(line: 1752, column: 37, scope: !1007)
!1020 = !DILocation(line: 1752, column: 43, scope: !1007)
!1021 = !DILocation(line: 1752, column: 19, scope: !1007)
!1022 = !DILocation(line: 1752, column: 7, scope: !1007)
!1023 = !DILocation(line: 1752, column: 12, scope: !1007)
!1024 = !DILocation(line: 1752, column: 17, scope: !1007)
!1025 = !DILocation(line: 1753, column: 14, scope: !1007)
!1026 = !DILocation(line: 1753, column: 7, scope: !1007)
!1027 = !DILocation(line: 1755, column: 1, scope: !977)
!1028 = distinct !DISubprogram(name: "license", scope: !3, file: !3, line: 1614, type: !1029, scopeLine: 1615, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1029 = !DISubroutineType(types: !1030)
!1030 = !{null}
!1031 = !DILocation(line: 1616, column: 14, scope: !1028)
!1032 = !DILocation(line: 1632, column: 5, scope: !1028)
!1033 = !DILocation(line: 1616, column: 4, scope: !1028)
!1034 = !DILocation(line: 1634, column: 1, scope: !1028)
!1035 = distinct !DISubprogram(name: "usage", scope: !3, file: !3, line: 1639, type: !1036, scopeLine: 1640, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1036 = !DISubroutineType(types: !1037)
!1037 = !{null, !24}
!1038 = !DILocalVariable(name: "fullProgName", arg: 1, scope: !1035, file: !3, line: 1639, type: !24)
!1039 = !DILocation(line: 1639, column: 20, scope: !1035)
!1040 = !DILocation(line: 1642, column: 7, scope: !1035)
!1041 = !DILocation(line: 1675, column: 7, scope: !1035)
!1042 = !DILocation(line: 1676, column: 7, scope: !1035)
!1043 = !DILocation(line: 1641, column: 4, scope: !1035)
!1044 = !DILocation(line: 1678, column: 1, scope: !1035)
!1045 = distinct !DISubprogram(name: "redundant", scope: !3, file: !3, line: 1683, type: !1036, scopeLine: 1684, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1046 = !DILocalVariable(name: "flag", arg: 1, scope: !1045, file: !3, line: 1683, type: !24)
!1047 = !DILocation(line: 1683, column: 24, scope: !1045)
!1048 = !DILocation(line: 1686, column: 7, scope: !1045)
!1049 = !DILocation(line: 1688, column: 7, scope: !1045)
!1050 = !DILocation(line: 1688, column: 17, scope: !1045)
!1051 = !DILocation(line: 1685, column: 4, scope: !1045)
!1052 = !DILocation(line: 1689, column: 1, scope: !1045)
!1053 = distinct !DISubprogram(name: "mySignalCatcher", scope: !3, file: !3, line: 814, type: !836, scopeLine: 815, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1054 = !DILocalVariable(name: "n", arg: 1, scope: !1053, file: !3, line: 814, type: !200)
!1055 = !DILocation(line: 814, column: 34, scope: !1053)
!1056 = !DILocation(line: 816, column: 14, scope: !1053)
!1057 = !DILocation(line: 818, column: 14, scope: !1053)
!1058 = !DILocation(line: 816, column: 4, scope: !1053)
!1059 = !DILocation(line: 819, column: 4, scope: !1053)
!1060 = distinct !DISubprogram(name: "compress", scope: !3, file: !3, line: 1142, type: !1036, scopeLine: 1143, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1061 = !DILocalVariable(name: "name", arg: 1, scope: !1060, file: !3, line: 1142, type: !24)
!1062 = !DILocation(line: 1142, column: 23, scope: !1060)
!1063 = !DILocalVariable(name: "inStr", scope: !1060, file: !3, line: 1144, type: !97)
!1064 = !DILocation(line: 1144, column: 11, scope: !1060)
!1065 = !DILocalVariable(name: "outStr", scope: !1060, file: !3, line: 1145, type: !97)
!1066 = !DILocation(line: 1145, column: 11, scope: !1060)
!1067 = !DILocalVariable(name: "n", scope: !1060, file: !3, line: 1146, type: !28)
!1068 = !DILocation(line: 1146, column: 10, scope: !1060)
!1069 = !DILocalVariable(name: "i", scope: !1060, file: !3, line: 1146, type: !28)
!1070 = !DILocation(line: 1146, column: 13, scope: !1060)
!1071 = !DILocalVariable(name: "statBuf", scope: !1060, file: !3, line: 1147, type: !157)
!1072 = !DILocation(line: 1147, column: 19, scope: !1060)
!1073 = !DILocation(line: 1149, column: 28, scope: !1060)
!1074 = !DILocation(line: 1151, column: 8, scope: !1075)
!1075 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1151, column: 8)
!1076 = !DILocation(line: 1151, column: 13, scope: !1075)
!1077 = !DILocation(line: 1151, column: 21, scope: !1075)
!1078 = !DILocation(line: 1151, column: 24, scope: !1075)
!1079 = !DILocation(line: 1151, column: 32, scope: !1075)
!1080 = !DILocation(line: 1151, column: 8, scope: !1060)
!1081 = !DILocation(line: 1152, column: 7, scope: !1075)
!1082 = !DILocation(line: 1154, column: 12, scope: !1060)
!1083 = !DILocation(line: 1154, column: 4, scope: !1060)
!1084 = !DILocation(line: 1156, column: 10, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1154, column: 21)
!1086 = !DILocation(line: 1157, column: 10, scope: !1085)
!1087 = !DILocation(line: 1158, column: 10, scope: !1085)
!1088 = !DILocation(line: 1160, column: 33, scope: !1085)
!1089 = !DILocation(line: 1160, column: 10, scope: !1085)
!1090 = !DILocation(line: 1161, column: 34, scope: !1085)
!1091 = !DILocation(line: 1161, column: 10, scope: !1085)
!1092 = !DILocation(line: 1162, column: 10, scope: !1085)
!1093 = !DILocation(line: 1163, column: 10, scope: !1085)
!1094 = !DILocation(line: 1165, column: 33, scope: !1085)
!1095 = !DILocation(line: 1165, column: 10, scope: !1085)
!1096 = !DILocation(line: 1166, column: 10, scope: !1085)
!1097 = !DILocation(line: 1167, column: 10, scope: !1085)
!1098 = !DILocation(line: 1170, column: 9, scope: !1099)
!1099 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1170, column: 9)
!1100 = !DILocation(line: 1170, column: 17, scope: !1099)
!1101 = !DILocation(line: 1170, column: 27, scope: !1099)
!1102 = !DILocation(line: 1170, column: 30, scope: !1099)
!1103 = !DILocation(line: 1170, column: 9, scope: !1060)
!1104 = !DILocation(line: 1171, column: 11, scope: !1105)
!1105 = distinct !DILexicalBlock(scope: !1106, file: !3, line: 1171, column: 11)
!1106 = distinct !DILexicalBlock(scope: !1099, file: !3, line: 1170, column: 64)
!1107 = !DILocation(line: 1171, column: 11, scope: !1106)
!1108 = !DILocation(line: 1172, column: 17, scope: !1105)
!1109 = !DILocation(line: 1173, column: 17, scope: !1105)
!1110 = !DILocation(line: 1172, column: 7, scope: !1105)
!1111 = !DILocation(line: 1174, column: 7, scope: !1106)
!1112 = !DILocation(line: 1175, column: 7, scope: !1106)
!1113 = !DILocation(line: 1177, column: 9, scope: !1114)
!1114 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1177, column: 9)
!1115 = !DILocation(line: 1177, column: 17, scope: !1114)
!1116 = !DILocation(line: 1177, column: 27, scope: !1114)
!1117 = !DILocation(line: 1177, column: 31, scope: !1114)
!1118 = !DILocation(line: 1177, column: 9, scope: !1060)
!1119 = !DILocation(line: 1178, column: 17, scope: !1120)
!1120 = distinct !DILexicalBlock(scope: !1114, file: !3, line: 1177, column: 55)
!1121 = !DILocation(line: 1179, column: 17, scope: !1120)
!1122 = !DILocation(line: 1179, column: 44, scope: !1120)
!1123 = !DILocation(line: 1179, column: 35, scope: !1120)
!1124 = !DILocation(line: 1178, column: 7, scope: !1120)
!1125 = !DILocation(line: 1180, column: 7, scope: !1120)
!1126 = !DILocation(line: 1181, column: 7, scope: !1120)
!1127 = !DILocation(line: 1183, column: 11, scope: !1128)
!1128 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1183, column: 4)
!1129 = !DILocation(line: 1183, column: 9, scope: !1128)
!1130 = !DILocation(line: 1183, column: 16, scope: !1131)
!1131 = distinct !DILexicalBlock(scope: !1128, file: !3, line: 1183, column: 4)
!1132 = !DILocation(line: 1183, column: 18, scope: !1131)
!1133 = !DILocation(line: 1183, column: 4, scope: !1128)
!1134 = !DILocation(line: 1184, column: 37, scope: !1135)
!1135 = distinct !DILexicalBlock(scope: !1136, file: !3, line: 1184, column: 11)
!1136 = distinct !DILexicalBlock(scope: !1131, file: !3, line: 1183, column: 44)
!1137 = !DILocation(line: 1184, column: 29, scope: !1135)
!1138 = !DILocation(line: 1184, column: 11, scope: !1135)
!1139 = !DILocation(line: 1184, column: 11, scope: !1136)
!1140 = !DILocation(line: 1185, column: 14, scope: !1141)
!1141 = distinct !DILexicalBlock(scope: !1142, file: !3, line: 1185, column: 14)
!1142 = distinct !DILexicalBlock(scope: !1135, file: !3, line: 1184, column: 42)
!1143 = !DILocation(line: 1185, column: 14, scope: !1142)
!1144 = !DILocation(line: 1186, column: 20, scope: !1141)
!1145 = !DILocation(line: 1188, column: 20, scope: !1141)
!1146 = !DILocation(line: 1188, column: 46, scope: !1141)
!1147 = !DILocation(line: 1188, column: 38, scope: !1141)
!1148 = !DILocation(line: 1186, column: 10, scope: !1141)
!1149 = !DILocation(line: 1189, column: 10, scope: !1142)
!1150 = !DILocation(line: 1190, column: 10, scope: !1142)
!1151 = !DILocation(line: 1192, column: 4, scope: !1136)
!1152 = !DILocation(line: 1183, column: 40, scope: !1131)
!1153 = !DILocation(line: 1183, column: 4, scope: !1131)
!1154 = distinct !{!1154, !1133, !1155}
!1155 = !DILocation(line: 1192, column: 4, scope: !1128)
!1156 = !DILocation(line: 1193, column: 9, scope: !1157)
!1157 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1193, column: 9)
!1158 = !DILocation(line: 1193, column: 17, scope: !1157)
!1159 = !DILocation(line: 1193, column: 27, scope: !1157)
!1160 = !DILocation(line: 1193, column: 30, scope: !1157)
!1161 = !DILocation(line: 1193, column: 38, scope: !1157)
!1162 = !DILocation(line: 1193, column: 9, scope: !1060)
!1163 = !DILocation(line: 1194, column: 7, scope: !1164)
!1164 = distinct !DILexicalBlock(scope: !1157, file: !3, line: 1193, column: 50)
!1165 = !DILocation(line: 1195, column: 12, scope: !1166)
!1166 = distinct !DILexicalBlock(scope: !1164, file: !3, line: 1195, column: 12)
!1167 = !DILocation(line: 1195, column: 12, scope: !1164)
!1168 = !DILocation(line: 1196, column: 19, scope: !1169)
!1169 = distinct !DILexicalBlock(scope: !1166, file: !3, line: 1195, column: 42)
!1170 = !DILocation(line: 1198, column: 19, scope: !1169)
!1171 = !DILocation(line: 1196, column: 10, scope: !1169)
!1172 = !DILocation(line: 1199, column: 10, scope: !1169)
!1173 = !DILocation(line: 1200, column: 10, scope: !1169)
!1174 = !DILocation(line: 1202, column: 4, scope: !1164)
!1175 = !DILocation(line: 1203, column: 9, scope: !1176)
!1176 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1203, column: 9)
!1177 = !DILocation(line: 1203, column: 17, scope: !1176)
!1178 = !DILocation(line: 1203, column: 27, scope: !1176)
!1179 = !DILocation(line: 1203, column: 31, scope: !1176)
!1180 = !DILocation(line: 1203, column: 46, scope: !1176)
!1181 = !DILocation(line: 1203, column: 49, scope: !1176)
!1182 = !DILocation(line: 1203, column: 9, scope: !1060)
!1183 = !DILocation(line: 1204, column: 11, scope: !1184)
!1184 = distinct !DILexicalBlock(scope: !1185, file: !3, line: 1204, column: 11)
!1185 = distinct !DILexicalBlock(scope: !1176, file: !3, line: 1203, column: 78)
!1186 = !DILocation(line: 1204, column: 11, scope: !1185)
!1187 = !DILocation(line: 1205, column: 17, scope: !1184)
!1188 = !DILocation(line: 1206, column: 17, scope: !1184)
!1189 = !DILocation(line: 1205, column: 7, scope: !1184)
!1190 = !DILocation(line: 1207, column: 7, scope: !1185)
!1191 = !DILocation(line: 1208, column: 7, scope: !1185)
!1192 = !DILocation(line: 1210, column: 9, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1210, column: 9)
!1194 = !DILocation(line: 1210, column: 17, scope: !1193)
!1195 = !DILocation(line: 1210, column: 27, scope: !1193)
!1196 = !DILocation(line: 1210, column: 30, scope: !1193)
!1197 = !DILocation(line: 1210, column: 9, scope: !1060)
!1198 = !DILocation(line: 1211, column: 11, scope: !1199)
!1199 = distinct !DILexicalBlock(scope: !1200, file: !3, line: 1211, column: 11)
!1200 = distinct !DILexicalBlock(scope: !1193, file: !3, line: 1210, column: 55)
!1201 = !DILocation(line: 1211, column: 11, scope: !1200)
!1202 = !DILocation(line: 1212, column: 3, scope: !1203)
!1203 = distinct !DILexicalBlock(scope: !1199, file: !3, line: 1211, column: 27)
!1204 = !DILocation(line: 1213, column: 7, scope: !1203)
!1205 = !DILocation(line: 1214, column: 13, scope: !1206)
!1206 = distinct !DILexicalBlock(scope: !1199, file: !3, line: 1213, column: 14)
!1207 = !DILocation(line: 1215, column: 6, scope: !1206)
!1208 = !DILocation(line: 1214, column: 3, scope: !1206)
!1209 = !DILocation(line: 1216, column: 3, scope: !1206)
!1210 = !DILocation(line: 1217, column: 3, scope: !1206)
!1211 = !DILocation(line: 1219, column: 4, scope: !1200)
!1212 = !DILocation(line: 1220, column: 9, scope: !1213)
!1213 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1220, column: 9)
!1214 = !DILocation(line: 1220, column: 17, scope: !1213)
!1215 = !DILocation(line: 1220, column: 27, scope: !1213)
!1216 = !DILocation(line: 1220, column: 31, scope: !1213)
!1217 = !DILocation(line: 1220, column: 46, scope: !1213)
!1218 = !DILocation(line: 1221, column: 12, scope: !1213)
!1219 = !DILocation(line: 1221, column: 11, scope: !1213)
!1220 = !DILocation(line: 1221, column: 39, scope: !1213)
!1221 = !DILocation(line: 1220, column: 9, scope: !1060)
!1222 = !DILocation(line: 1222, column: 17, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !1213, file: !3, line: 1221, column: 44)
!1224 = !DILocation(line: 1223, column: 17, scope: !1223)
!1225 = !DILocation(line: 1223, column: 35, scope: !1223)
!1226 = !DILocation(line: 1223, column: 38, scope: !1223)
!1227 = !DILocation(line: 1223, column: 40, scope: !1223)
!1228 = !DILocation(line: 1222, column: 7, scope: !1223)
!1229 = !DILocation(line: 1224, column: 7, scope: !1223)
!1230 = !DILocation(line: 1225, column: 7, scope: !1223)
!1231 = !DILocation(line: 1228, column: 9, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1228, column: 9)
!1233 = !DILocation(line: 1228, column: 17, scope: !1232)
!1234 = !DILocation(line: 1228, column: 9, scope: !1060)
!1235 = !DILocation(line: 1231, column: 7, scope: !1236)
!1236 = distinct !DILexicalBlock(scope: !1232, file: !3, line: 1228, column: 29)
!1237 = !DILocation(line: 1232, column: 4, scope: !1236)
!1238 = !DILocation(line: 1234, column: 13, scope: !1060)
!1239 = !DILocation(line: 1234, column: 4, scope: !1060)
!1240 = !DILocation(line: 1237, column: 18, scope: !1241)
!1241 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1234, column: 23)
!1242 = !DILocation(line: 1237, column: 16, scope: !1241)
!1243 = !DILocation(line: 1238, column: 19, scope: !1241)
!1244 = !DILocation(line: 1238, column: 17, scope: !1241)
!1245 = !DILocation(line: 1239, column: 33, scope: !1246)
!1246 = distinct !DILexicalBlock(scope: !1241, file: !3, line: 1239, column: 15)
!1247 = !DILocation(line: 1239, column: 24, scope: !1246)
!1248 = !DILocation(line: 1239, column: 15, scope: !1246)
!1249 = !DILocation(line: 1239, column: 15, scope: !1241)
!1250 = !DILocation(line: 1240, column: 23, scope: !1251)
!1251 = distinct !DILexicalBlock(scope: !1246, file: !3, line: 1239, column: 46)
!1252 = !DILocation(line: 1242, column: 23, scope: !1251)
!1253 = !DILocation(line: 1240, column: 13, scope: !1251)
!1254 = !DILocation(line: 1243, column: 23, scope: !1251)
!1255 = !DILocation(line: 1244, column: 31, scope: !1251)
!1256 = !DILocation(line: 1244, column: 41, scope: !1251)
!1257 = !DILocation(line: 1243, column: 13, scope: !1251)
!1258 = !DILocation(line: 1245, column: 13, scope: !1251)
!1259 = !DILocation(line: 1246, column: 13, scope: !1251)
!1260 = !DILocation(line: 1248, column: 10, scope: !1241)
!1261 = !DILocation(line: 1251, column: 18, scope: !1241)
!1262 = !DILocation(line: 1251, column: 16, scope: !1241)
!1263 = !DILocation(line: 1252, column: 19, scope: !1241)
!1264 = !DILocation(line: 1252, column: 17, scope: !1241)
!1265 = !DILocation(line: 1253, column: 33, scope: !1266)
!1266 = distinct !DILexicalBlock(scope: !1241, file: !3, line: 1253, column: 15)
!1267 = !DILocation(line: 1253, column: 24, scope: !1266)
!1268 = !DILocation(line: 1253, column: 15, scope: !1266)
!1269 = !DILocation(line: 1253, column: 15, scope: !1241)
!1270 = !DILocation(line: 1254, column: 23, scope: !1271)
!1271 = distinct !DILexicalBlock(scope: !1266, file: !3, line: 1253, column: 46)
!1272 = !DILocation(line: 1256, column: 23, scope: !1271)
!1273 = !DILocation(line: 1254, column: 13, scope: !1271)
!1274 = !DILocation(line: 1257, column: 23, scope: !1271)
!1275 = !DILocation(line: 1258, column: 31, scope: !1271)
!1276 = !DILocation(line: 1258, column: 41, scope: !1271)
!1277 = !DILocation(line: 1257, column: 13, scope: !1271)
!1278 = !DILocation(line: 1259, column: 18, scope: !1279)
!1279 = distinct !DILexicalBlock(scope: !1271, file: !3, line: 1259, column: 18)
!1280 = !DILocation(line: 1259, column: 24, scope: !1279)
!1281 = !DILocation(line: 1259, column: 18, scope: !1271)
!1282 = !DILocation(line: 1259, column: 43, scope: !1279)
!1283 = !DILocation(line: 1259, column: 34, scope: !1279)
!1284 = !DILocation(line: 1260, column: 13, scope: !1271)
!1285 = !DILocation(line: 1261, column: 13, scope: !1271)
!1286 = !DILocation(line: 1263, column: 15, scope: !1287)
!1287 = distinct !DILexicalBlock(scope: !1241, file: !3, line: 1263, column: 15)
!1288 = !DILocation(line: 1263, column: 21, scope: !1287)
!1289 = !DILocation(line: 1263, column: 15, scope: !1241)
!1290 = !DILocation(line: 1264, column: 23, scope: !1291)
!1291 = distinct !DILexicalBlock(scope: !1287, file: !3, line: 1263, column: 31)
!1292 = !DILocation(line: 1265, column: 23, scope: !1291)
!1293 = !DILocation(line: 1265, column: 50, scope: !1291)
!1294 = !DILocation(line: 1265, column: 41, scope: !1291)
!1295 = !DILocation(line: 1264, column: 13, scope: !1291)
!1296 = !DILocation(line: 1266, column: 13, scope: !1291)
!1297 = !DILocation(line: 1267, column: 13, scope: !1291)
!1298 = !DILocation(line: 1269, column: 10, scope: !1241)
!1299 = !DILocation(line: 1272, column: 18, scope: !1241)
!1300 = !DILocation(line: 1272, column: 16, scope: !1241)
!1301 = !DILocation(line: 1273, column: 19, scope: !1241)
!1302 = !DILocation(line: 1273, column: 17, scope: !1241)
!1303 = !DILocation(line: 1274, column: 15, scope: !1304)
!1304 = distinct !DILexicalBlock(scope: !1241, file: !3, line: 1274, column: 15)
!1305 = !DILocation(line: 1274, column: 22, scope: !1304)
!1306 = !DILocation(line: 1274, column: 15, scope: !1241)
!1307 = !DILocation(line: 1275, column: 23, scope: !1308)
!1308 = distinct !DILexicalBlock(scope: !1304, file: !3, line: 1274, column: 31)
!1309 = !DILocation(line: 1276, column: 23, scope: !1308)
!1310 = !DILocation(line: 1276, column: 51, scope: !1308)
!1311 = !DILocation(line: 1276, column: 42, scope: !1308)
!1312 = !DILocation(line: 1275, column: 13, scope: !1308)
!1313 = !DILocation(line: 1277, column: 18, scope: !1314)
!1314 = distinct !DILexicalBlock(scope: !1308, file: !3, line: 1277, column: 18)
!1315 = !DILocation(line: 1277, column: 24, scope: !1314)
!1316 = !DILocation(line: 1277, column: 18, scope: !1308)
!1317 = !DILocation(line: 1277, column: 43, scope: !1314)
!1318 = !DILocation(line: 1277, column: 34, scope: !1314)
!1319 = !DILocation(line: 1278, column: 13, scope: !1308)
!1320 = !DILocation(line: 1279, column: 13, scope: !1308)
!1321 = !DILocation(line: 1281, column: 15, scope: !1322)
!1322 = distinct !DILexicalBlock(scope: !1241, file: !3, line: 1281, column: 15)
!1323 = !DILocation(line: 1281, column: 21, scope: !1322)
!1324 = !DILocation(line: 1281, column: 15, scope: !1241)
!1325 = !DILocation(line: 1282, column: 23, scope: !1326)
!1326 = distinct !DILexicalBlock(scope: !1322, file: !3, line: 1281, column: 31)
!1327 = !DILocation(line: 1283, column: 23, scope: !1326)
!1328 = !DILocation(line: 1283, column: 50, scope: !1326)
!1329 = !DILocation(line: 1283, column: 41, scope: !1326)
!1330 = !DILocation(line: 1282, column: 13, scope: !1326)
!1331 = !DILocation(line: 1284, column: 18, scope: !1332)
!1332 = distinct !DILexicalBlock(scope: !1326, file: !3, line: 1284, column: 18)
!1333 = !DILocation(line: 1284, column: 25, scope: !1332)
!1334 = !DILocation(line: 1284, column: 18, scope: !1326)
!1335 = !DILocation(line: 1284, column: 44, scope: !1332)
!1336 = !DILocation(line: 1284, column: 35, scope: !1332)
!1337 = !DILocation(line: 1285, column: 13, scope: !1326)
!1338 = !DILocation(line: 1286, column: 13, scope: !1326)
!1339 = !DILocation(line: 1288, column: 10, scope: !1241)
!1340 = !DILocation(line: 1291, column: 10, scope: !1241)
!1341 = !DILocation(line: 1295, column: 8, scope: !1342)
!1342 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1295, column: 8)
!1343 = !DILocation(line: 1295, column: 18, scope: !1342)
!1344 = !DILocation(line: 1295, column: 8, scope: !1060)
!1345 = !DILocation(line: 1296, column: 17, scope: !1346)
!1346 = distinct !DILexicalBlock(scope: !1342, file: !3, line: 1295, column: 24)
!1347 = !DILocation(line: 1296, column: 7, scope: !1346)
!1348 = !DILocation(line: 1297, column: 7, scope: !1346)
!1349 = !DILocation(line: 1298, column: 16, scope: !1346)
!1350 = !DILocation(line: 1298, column: 7, scope: !1346)
!1351 = !DILocation(line: 1299, column: 4, scope: !1346)
!1352 = !DILocation(line: 1302, column: 29, scope: !1060)
!1353 = !DILocation(line: 1302, column: 27, scope: !1060)
!1354 = !DILocation(line: 1303, column: 28, scope: !1060)
!1355 = !DILocation(line: 1304, column: 21, scope: !1060)
!1356 = !DILocation(line: 1304, column: 28, scope: !1060)
!1357 = !DILocation(line: 1304, column: 4, scope: !1060)
!1358 = !DILocation(line: 1305, column: 27, scope: !1060)
!1359 = !DILocation(line: 1308, column: 9, scope: !1360)
!1360 = distinct !DILexicalBlock(scope: !1060, file: !3, line: 1308, column: 9)
!1361 = !DILocation(line: 1308, column: 17, scope: !1360)
!1362 = !DILocation(line: 1308, column: 9, scope: !1060)
!1363 = !DILocation(line: 1309, column: 7, scope: !1364)
!1364 = distinct !DILexicalBlock(scope: !1360, file: !3, line: 1308, column: 29)
!1365 = !DILocation(line: 1310, column: 11, scope: !1366)
!1366 = distinct !DILexicalBlock(scope: !1364, file: !3, line: 1310, column: 11)
!1367 = !DILocation(line: 1310, column: 18, scope: !1366)
!1368 = !DILocation(line: 1310, column: 11, scope: !1364)
!1369 = !DILocation(line: 1311, column: 11, scope: !1370)
!1370 = distinct !DILexicalBlock(scope: !1366, file: !3, line: 1310, column: 26)
!1371 = !DILocation(line: 1313, column: 7, scope: !1370)
!1372 = !DILocation(line: 1314, column: 31, scope: !1364)
!1373 = !DILocation(line: 1315, column: 13, scope: !1374)
!1374 = distinct !DILexicalBlock(scope: !1364, file: !3, line: 1315, column: 12)
!1375 = !DILocation(line: 1315, column: 12, scope: !1364)
!1376 = !DILocalVariable(name: "retVal", scope: !1377, file: !3, line: 1316, type: !200)
!1377 = distinct !DILexicalBlock(scope: !1374, file: !3, line: 1315, column: 30)
!1378 = !DILocation(line: 1316, column: 20, scope: !1377)
!1379 = !DILocation(line: 1316, column: 29, scope: !1377)
!1380 = !DILocation(line: 1317, column: 10, scope: !1381)
!1381 = distinct !DILexicalBlock(scope: !1382, file: !3, line: 1317, column: 10)
!1382 = distinct !DILexicalBlock(scope: !1377, file: !3, line: 1317, column: 10)
!1383 = !DILocation(line: 1317, column: 10, scope: !1382)
!1384 = !DILocation(line: 1318, column: 7, scope: !1377)
!1385 = !DILocation(line: 1319, column: 4, scope: !1364)
!1386 = !DILocation(line: 1321, column: 28, scope: !1060)
!1387 = !DILocation(line: 1322, column: 1, scope: !1060)
!1388 = distinct !DISubprogram(name: "uncompress", scope: !3, file: !3, line: 1327, type: !1036, scopeLine: 1328, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1389 = !DILocalVariable(name: "name", arg: 1, scope: !1388, file: !3, line: 1327, type: !24)
!1390 = !DILocation(line: 1327, column: 25, scope: !1388)
!1391 = !DILocalVariable(name: "inStr", scope: !1388, file: !3, line: 1329, type: !97)
!1392 = !DILocation(line: 1329, column: 11, scope: !1388)
!1393 = !DILocalVariable(name: "outStr", scope: !1388, file: !3, line: 1330, type: !97)
!1394 = !DILocation(line: 1330, column: 11, scope: !1388)
!1395 = !DILocalVariable(name: "n", scope: !1388, file: !3, line: 1331, type: !28)
!1396 = !DILocation(line: 1331, column: 10, scope: !1388)
!1397 = !DILocalVariable(name: "i", scope: !1388, file: !3, line: 1331, type: !28)
!1398 = !DILocation(line: 1331, column: 13, scope: !1388)
!1399 = !DILocalVariable(name: "magicNumberOK", scope: !1388, file: !3, line: 1332, type: !22)
!1400 = !DILocation(line: 1332, column: 10, scope: !1388)
!1401 = !DILocalVariable(name: "cantGuess", scope: !1388, file: !3, line: 1333, type: !22)
!1402 = !DILocation(line: 1333, column: 10, scope: !1388)
!1403 = !DILocalVariable(name: "statBuf", scope: !1388, file: !3, line: 1334, type: !157)
!1404 = !DILocation(line: 1334, column: 19, scope: !1388)
!1405 = !DILocation(line: 1336, column: 28, scope: !1388)
!1406 = !DILocation(line: 1338, column: 8, scope: !1407)
!1407 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1338, column: 8)
!1408 = !DILocation(line: 1338, column: 13, scope: !1407)
!1409 = !DILocation(line: 1338, column: 21, scope: !1407)
!1410 = !DILocation(line: 1338, column: 24, scope: !1407)
!1411 = !DILocation(line: 1338, column: 32, scope: !1407)
!1412 = !DILocation(line: 1338, column: 8, scope: !1388)
!1413 = !DILocation(line: 1339, column: 7, scope: !1407)
!1414 = !DILocation(line: 1341, column: 14, scope: !1388)
!1415 = !DILocation(line: 1342, column: 12, scope: !1388)
!1416 = !DILocation(line: 1342, column: 4, scope: !1388)
!1417 = !DILocation(line: 1344, column: 10, scope: !1418)
!1418 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1342, column: 21)
!1419 = !DILocation(line: 1345, column: 10, scope: !1418)
!1420 = !DILocation(line: 1346, column: 10, scope: !1418)
!1421 = !DILocation(line: 1348, column: 33, scope: !1418)
!1422 = !DILocation(line: 1348, column: 10, scope: !1418)
!1423 = !DILocation(line: 1349, column: 34, scope: !1418)
!1424 = !DILocation(line: 1349, column: 10, scope: !1418)
!1425 = !DILocation(line: 1350, column: 17, scope: !1426)
!1426 = distinct !DILexicalBlock(scope: !1418, file: !3, line: 1350, column: 10)
!1427 = !DILocation(line: 1350, column: 15, scope: !1426)
!1428 = !DILocation(line: 1350, column: 22, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !1426, file: !3, line: 1350, column: 10)
!1430 = !DILocation(line: 1350, column: 24, scope: !1429)
!1431 = !DILocation(line: 1350, column: 10, scope: !1426)
!1432 = !DILocation(line: 1351, column: 43, scope: !1433)
!1433 = distinct !DILexicalBlock(scope: !1429, file: !3, line: 1351, column: 17)
!1434 = !DILocation(line: 1351, column: 35, scope: !1433)
!1435 = !DILocation(line: 1351, column: 56, scope: !1433)
!1436 = !DILocation(line: 1351, column: 46, scope: !1433)
!1437 = !DILocation(line: 1351, column: 17, scope: !1433)
!1438 = !DILocation(line: 1351, column: 17, scope: !1429)
!1439 = !DILocation(line: 1352, column: 16, scope: !1433)
!1440 = !DILocation(line: 1351, column: 58, scope: !1433)
!1441 = !DILocation(line: 1350, column: 46, scope: !1429)
!1442 = !DILocation(line: 1350, column: 10, scope: !1429)
!1443 = distinct !{!1443, !1431, !1444}
!1444 = !DILocation(line: 1352, column: 21, scope: !1426)
!1445 = !DILocation(line: 1353, column: 20, scope: !1418)
!1446 = !DILocation(line: 1354, column: 10, scope: !1418)
!1447 = !DILocation(line: 1355, column: 10, scope: !1418)
!1448 = !DILocation(line: 1357, column: 33, scope: !1418)
!1449 = !DILocation(line: 1357, column: 10, scope: !1418)
!1450 = !DILocation(line: 1358, column: 10, scope: !1418)
!1451 = !DILocation(line: 1359, column: 10, scope: !1418)
!1452 = !DILocation(line: 1360, column: 4, scope: !1418)
!1453 = !DILabel(scope: !1388, name: "zzz", file: !3, line: 1362)
!1454 = !DILocation(line: 1362, column: 4, scope: !1388)
!1455 = !DILocation(line: 1363, column: 9, scope: !1456)
!1456 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1363, column: 9)
!1457 = !DILocation(line: 1363, column: 17, scope: !1456)
!1458 = !DILocation(line: 1363, column: 27, scope: !1456)
!1459 = !DILocation(line: 1363, column: 30, scope: !1456)
!1460 = !DILocation(line: 1363, column: 9, scope: !1388)
!1461 = !DILocation(line: 1364, column: 11, scope: !1462)
!1462 = distinct !DILexicalBlock(scope: !1463, file: !3, line: 1364, column: 11)
!1463 = distinct !DILexicalBlock(scope: !1456, file: !3, line: 1363, column: 64)
!1464 = !DILocation(line: 1364, column: 11, scope: !1463)
!1465 = !DILocation(line: 1365, column: 17, scope: !1462)
!1466 = !DILocation(line: 1366, column: 17, scope: !1462)
!1467 = !DILocation(line: 1365, column: 7, scope: !1462)
!1468 = !DILocation(line: 1367, column: 7, scope: !1463)
!1469 = !DILocation(line: 1368, column: 7, scope: !1463)
!1470 = !DILocation(line: 1370, column: 9, scope: !1471)
!1471 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1370, column: 9)
!1472 = !DILocation(line: 1370, column: 17, scope: !1471)
!1473 = !DILocation(line: 1370, column: 27, scope: !1471)
!1474 = !DILocation(line: 1370, column: 31, scope: !1471)
!1475 = !DILocation(line: 1370, column: 9, scope: !1388)
!1476 = !DILocation(line: 1371, column: 17, scope: !1477)
!1477 = distinct !DILexicalBlock(scope: !1471, file: !3, line: 1370, column: 55)
!1478 = !DILocation(line: 1372, column: 17, scope: !1477)
!1479 = !DILocation(line: 1372, column: 44, scope: !1477)
!1480 = !DILocation(line: 1372, column: 35, scope: !1477)
!1481 = !DILocation(line: 1371, column: 7, scope: !1477)
!1482 = !DILocation(line: 1373, column: 7, scope: !1477)
!1483 = !DILocation(line: 1374, column: 7, scope: !1477)
!1484 = !DILocation(line: 1376, column: 9, scope: !1485)
!1485 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1376, column: 9)
!1486 = !DILocation(line: 1376, column: 17, scope: !1485)
!1487 = !DILocation(line: 1376, column: 27, scope: !1485)
!1488 = !DILocation(line: 1376, column: 30, scope: !1485)
!1489 = !DILocation(line: 1376, column: 38, scope: !1485)
!1490 = !DILocation(line: 1376, column: 9, scope: !1388)
!1491 = !DILocation(line: 1377, column: 7, scope: !1492)
!1492 = distinct !DILexicalBlock(scope: !1485, file: !3, line: 1376, column: 50)
!1493 = !DILocation(line: 1378, column: 12, scope: !1494)
!1494 = distinct !DILexicalBlock(scope: !1492, file: !3, line: 1378, column: 12)
!1495 = !DILocation(line: 1378, column: 12, scope: !1492)
!1496 = !DILocation(line: 1379, column: 19, scope: !1497)
!1497 = distinct !DILexicalBlock(scope: !1494, file: !3, line: 1378, column: 42)
!1498 = !DILocation(line: 1381, column: 19, scope: !1497)
!1499 = !DILocation(line: 1379, column: 10, scope: !1497)
!1500 = !DILocation(line: 1382, column: 10, scope: !1497)
!1501 = !DILocation(line: 1383, column: 10, scope: !1497)
!1502 = !DILocation(line: 1385, column: 4, scope: !1492)
!1503 = !DILocation(line: 1386, column: 9, scope: !1504)
!1504 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1386, column: 9)
!1505 = !DILocation(line: 1386, column: 17, scope: !1504)
!1506 = !DILocation(line: 1386, column: 27, scope: !1504)
!1507 = !DILocation(line: 1386, column: 31, scope: !1504)
!1508 = !DILocation(line: 1386, column: 46, scope: !1504)
!1509 = !DILocation(line: 1386, column: 49, scope: !1504)
!1510 = !DILocation(line: 1386, column: 9, scope: !1388)
!1511 = !DILocation(line: 1387, column: 11, scope: !1512)
!1512 = distinct !DILexicalBlock(scope: !1513, file: !3, line: 1387, column: 11)
!1513 = distinct !DILexicalBlock(scope: !1504, file: !3, line: 1386, column: 78)
!1514 = !DILocation(line: 1387, column: 11, scope: !1513)
!1515 = !DILocation(line: 1388, column: 17, scope: !1512)
!1516 = !DILocation(line: 1389, column: 17, scope: !1512)
!1517 = !DILocation(line: 1388, column: 7, scope: !1512)
!1518 = !DILocation(line: 1390, column: 7, scope: !1513)
!1519 = !DILocation(line: 1391, column: 7, scope: !1513)
!1520 = !DILocation(line: 1393, column: 44, scope: !1521)
!1521 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1393, column: 44)
!1522 = !DILocation(line: 1393, column: 44, scope: !1388)
!1523 = !DILocation(line: 1394, column: 11, scope: !1524)
!1524 = distinct !DILexicalBlock(scope: !1525, file: !3, line: 1394, column: 11)
!1525 = distinct !DILexicalBlock(scope: !1521, file: !3, line: 1393, column: 56)
!1526 = !DILocation(line: 1394, column: 11, scope: !1525)
!1527 = !DILocation(line: 1395, column: 17, scope: !1524)
!1528 = !DILocation(line: 1397, column: 17, scope: !1524)
!1529 = !DILocation(line: 1395, column: 7, scope: !1524)
!1530 = !DILocation(line: 1399, column: 4, scope: !1525)
!1531 = !DILocation(line: 1400, column: 9, scope: !1532)
!1532 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1400, column: 9)
!1533 = !DILocation(line: 1400, column: 17, scope: !1532)
!1534 = !DILocation(line: 1400, column: 27, scope: !1532)
!1535 = !DILocation(line: 1400, column: 30, scope: !1532)
!1536 = !DILocation(line: 1400, column: 9, scope: !1388)
!1537 = !DILocation(line: 1401, column: 11, scope: !1538)
!1538 = distinct !DILexicalBlock(scope: !1539, file: !3, line: 1401, column: 11)
!1539 = distinct !DILexicalBlock(scope: !1532, file: !3, line: 1400, column: 55)
!1540 = !DILocation(line: 1401, column: 11, scope: !1539)
!1541 = !DILocation(line: 1402, column: 2, scope: !1542)
!1542 = distinct !DILexicalBlock(scope: !1538, file: !3, line: 1401, column: 27)
!1543 = !DILocation(line: 1403, column: 7, scope: !1542)
!1544 = !DILocation(line: 1404, column: 19, scope: !1545)
!1545 = distinct !DILexicalBlock(scope: !1538, file: !3, line: 1403, column: 14)
!1546 = !DILocation(line: 1405, column: 19, scope: !1545)
!1547 = !DILocation(line: 1404, column: 9, scope: !1545)
!1548 = !DILocation(line: 1406, column: 9, scope: !1545)
!1549 = !DILocation(line: 1407, column: 9, scope: !1545)
!1550 = !DILocation(line: 1409, column: 4, scope: !1539)
!1551 = !DILocation(line: 1410, column: 9, scope: !1552)
!1552 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1410, column: 9)
!1553 = !DILocation(line: 1410, column: 17, scope: !1552)
!1554 = !DILocation(line: 1410, column: 27, scope: !1552)
!1555 = !DILocation(line: 1410, column: 31, scope: !1552)
!1556 = !DILocation(line: 1410, column: 46, scope: !1552)
!1557 = !DILocation(line: 1411, column: 12, scope: !1552)
!1558 = !DILocation(line: 1411, column: 11, scope: !1552)
!1559 = !DILocation(line: 1411, column: 40, scope: !1552)
!1560 = !DILocation(line: 1410, column: 9, scope: !1388)
!1561 = !DILocation(line: 1412, column: 17, scope: !1562)
!1562 = distinct !DILexicalBlock(scope: !1552, file: !3, line: 1411, column: 45)
!1563 = !DILocation(line: 1413, column: 17, scope: !1562)
!1564 = !DILocation(line: 1413, column: 35, scope: !1562)
!1565 = !DILocation(line: 1413, column: 38, scope: !1562)
!1566 = !DILocation(line: 1413, column: 40, scope: !1562)
!1567 = !DILocation(line: 1412, column: 7, scope: !1562)
!1568 = !DILocation(line: 1414, column: 7, scope: !1562)
!1569 = !DILocation(line: 1415, column: 7, scope: !1562)
!1570 = !DILocation(line: 1418, column: 9, scope: !1571)
!1571 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1418, column: 9)
!1572 = !DILocation(line: 1418, column: 17, scope: !1571)
!1573 = !DILocation(line: 1418, column: 9, scope: !1388)
!1574 = !DILocation(line: 1421, column: 7, scope: !1575)
!1575 = distinct !DILexicalBlock(scope: !1571, file: !3, line: 1418, column: 29)
!1576 = !DILocation(line: 1422, column: 4, scope: !1575)
!1577 = !DILocation(line: 1424, column: 13, scope: !1388)
!1578 = !DILocation(line: 1424, column: 4, scope: !1388)
!1579 = !DILocation(line: 1427, column: 18, scope: !1580)
!1580 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1424, column: 23)
!1581 = !DILocation(line: 1427, column: 16, scope: !1580)
!1582 = !DILocation(line: 1428, column: 19, scope: !1580)
!1583 = !DILocation(line: 1428, column: 17, scope: !1580)
!1584 = !DILocation(line: 1429, column: 33, scope: !1585)
!1585 = distinct !DILexicalBlock(scope: !1580, file: !3, line: 1429, column: 15)
!1586 = !DILocation(line: 1429, column: 24, scope: !1585)
!1587 = !DILocation(line: 1429, column: 15, scope: !1585)
!1588 = !DILocation(line: 1429, column: 15, scope: !1580)
!1589 = !DILocation(line: 1430, column: 23, scope: !1590)
!1590 = distinct !DILexicalBlock(scope: !1585, file: !3, line: 1429, column: 45)
!1591 = !DILocation(line: 1432, column: 23, scope: !1590)
!1592 = !DILocation(line: 1430, column: 13, scope: !1590)
!1593 = !DILocation(line: 1433, column: 23, scope: !1590)
!1594 = !DILocation(line: 1434, column: 31, scope: !1590)
!1595 = !DILocation(line: 1434, column: 41, scope: !1590)
!1596 = !DILocation(line: 1433, column: 13, scope: !1590)
!1597 = !DILocation(line: 1435, column: 13, scope: !1590)
!1598 = !DILocation(line: 1436, column: 13, scope: !1590)
!1599 = !DILocation(line: 1438, column: 10, scope: !1580)
!1600 = !DILocation(line: 1441, column: 18, scope: !1580)
!1601 = !DILocation(line: 1441, column: 16, scope: !1580)
!1602 = !DILocation(line: 1442, column: 19, scope: !1580)
!1603 = !DILocation(line: 1442, column: 17, scope: !1580)
!1604 = !DILocation(line: 1443, column: 15, scope: !1605)
!1605 = distinct !DILexicalBlock(scope: !1580, file: !3, line: 1443, column: 15)
!1606 = !DILocation(line: 1443, column: 21, scope: !1605)
!1607 = !DILocation(line: 1443, column: 15, scope: !1580)
!1608 = !DILocation(line: 1444, column: 23, scope: !1609)
!1609 = distinct !DILexicalBlock(scope: !1605, file: !3, line: 1443, column: 31)
!1610 = !DILocation(line: 1445, column: 23, scope: !1609)
!1611 = !DILocation(line: 1445, column: 50, scope: !1609)
!1612 = !DILocation(line: 1445, column: 41, scope: !1609)
!1613 = !DILocation(line: 1444, column: 13, scope: !1609)
!1614 = !DILocation(line: 1446, column: 18, scope: !1615)
!1615 = distinct !DILexicalBlock(scope: !1609, file: !3, line: 1446, column: 18)
!1616 = !DILocation(line: 1446, column: 24, scope: !1615)
!1617 = !DILocation(line: 1446, column: 18, scope: !1609)
!1618 = !DILocation(line: 1446, column: 43, scope: !1615)
!1619 = !DILocation(line: 1446, column: 34, scope: !1615)
!1620 = !DILocation(line: 1447, column: 13, scope: !1609)
!1621 = !DILocation(line: 1448, column: 13, scope: !1609)
!1622 = !DILocation(line: 1450, column: 10, scope: !1580)
!1623 = !DILocation(line: 1453, column: 18, scope: !1580)
!1624 = !DILocation(line: 1453, column: 16, scope: !1580)
!1625 = !DILocation(line: 1454, column: 19, scope: !1580)
!1626 = !DILocation(line: 1454, column: 17, scope: !1580)
!1627 = !DILocation(line: 1455, column: 15, scope: !1628)
!1628 = distinct !DILexicalBlock(scope: !1580, file: !3, line: 1455, column: 15)
!1629 = !DILocation(line: 1455, column: 22, scope: !1628)
!1630 = !DILocation(line: 1455, column: 15, scope: !1580)
!1631 = !DILocation(line: 1456, column: 23, scope: !1632)
!1632 = distinct !DILexicalBlock(scope: !1628, file: !3, line: 1455, column: 31)
!1633 = !DILocation(line: 1457, column: 23, scope: !1632)
!1634 = !DILocation(line: 1457, column: 51, scope: !1632)
!1635 = !DILocation(line: 1457, column: 42, scope: !1632)
!1636 = !DILocation(line: 1456, column: 13, scope: !1632)
!1637 = !DILocation(line: 1458, column: 18, scope: !1638)
!1638 = distinct !DILexicalBlock(scope: !1632, file: !3, line: 1458, column: 18)
!1639 = !DILocation(line: 1458, column: 24, scope: !1638)
!1640 = !DILocation(line: 1458, column: 18, scope: !1632)
!1641 = !DILocation(line: 1458, column: 43, scope: !1638)
!1642 = !DILocation(line: 1458, column: 34, scope: !1638)
!1643 = !DILocation(line: 1459, column: 13, scope: !1632)
!1644 = !DILocation(line: 1460, column: 13, scope: !1632)
!1645 = !DILocation(line: 1462, column: 15, scope: !1646)
!1646 = distinct !DILexicalBlock(scope: !1580, file: !3, line: 1462, column: 15)
!1647 = !DILocation(line: 1462, column: 21, scope: !1646)
!1648 = !DILocation(line: 1462, column: 15, scope: !1580)
!1649 = !DILocation(line: 1463, column: 23, scope: !1650)
!1650 = distinct !DILexicalBlock(scope: !1646, file: !3, line: 1462, column: 31)
!1651 = !DILocation(line: 1464, column: 23, scope: !1650)
!1652 = !DILocation(line: 1464, column: 50, scope: !1650)
!1653 = !DILocation(line: 1464, column: 41, scope: !1650)
!1654 = !DILocation(line: 1463, column: 13, scope: !1650)
!1655 = !DILocation(line: 1465, column: 18, scope: !1656)
!1656 = distinct !DILexicalBlock(scope: !1650, file: !3, line: 1465, column: 18)
!1657 = !DILocation(line: 1465, column: 25, scope: !1656)
!1658 = !DILocation(line: 1465, column: 18, scope: !1650)
!1659 = !DILocation(line: 1465, column: 44, scope: !1656)
!1660 = !DILocation(line: 1465, column: 35, scope: !1656)
!1661 = !DILocation(line: 1466, column: 13, scope: !1650)
!1662 = !DILocation(line: 1467, column: 13, scope: !1650)
!1663 = !DILocation(line: 1469, column: 10, scope: !1580)
!1664 = !DILocation(line: 1472, column: 10, scope: !1580)
!1665 = !DILocation(line: 1476, column: 8, scope: !1666)
!1666 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1476, column: 8)
!1667 = !DILocation(line: 1476, column: 18, scope: !1666)
!1668 = !DILocation(line: 1476, column: 8, scope: !1388)
!1669 = !DILocation(line: 1477, column: 17, scope: !1670)
!1670 = distinct !DILexicalBlock(scope: !1666, file: !3, line: 1476, column: 24)
!1671 = !DILocation(line: 1477, column: 7, scope: !1670)
!1672 = !DILocation(line: 1478, column: 7, scope: !1670)
!1673 = !DILocation(line: 1479, column: 16, scope: !1670)
!1674 = !DILocation(line: 1479, column: 7, scope: !1670)
!1675 = !DILocation(line: 1480, column: 4, scope: !1670)
!1676 = !DILocation(line: 1483, column: 29, scope: !1388)
!1677 = !DILocation(line: 1483, column: 27, scope: !1388)
!1678 = !DILocation(line: 1484, column: 28, scope: !1388)
!1679 = !DILocation(line: 1485, column: 39, scope: !1388)
!1680 = !DILocation(line: 1485, column: 46, scope: !1388)
!1681 = !DILocation(line: 1485, column: 20, scope: !1388)
!1682 = !DILocation(line: 1485, column: 18, scope: !1388)
!1683 = !DILocation(line: 1486, column: 27, scope: !1388)
!1684 = !DILocation(line: 1489, column: 9, scope: !1685)
!1685 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1489, column: 9)
!1686 = !DILocation(line: 1489, column: 9, scope: !1388)
!1687 = !DILocation(line: 1490, column: 12, scope: !1688)
!1688 = distinct !DILexicalBlock(scope: !1689, file: !3, line: 1490, column: 12)
!1689 = distinct !DILexicalBlock(scope: !1685, file: !3, line: 1489, column: 25)
!1690 = !DILocation(line: 1490, column: 20, scope: !1688)
!1691 = !DILocation(line: 1490, column: 12, scope: !1689)
!1692 = !DILocation(line: 1491, column: 10, scope: !1693)
!1693 = distinct !DILexicalBlock(scope: !1688, file: !3, line: 1490, column: 32)
!1694 = !DILocation(line: 1492, column: 34, scope: !1693)
!1695 = !DILocation(line: 1493, column: 16, scope: !1696)
!1696 = distinct !DILexicalBlock(scope: !1693, file: !3, line: 1493, column: 15)
!1697 = !DILocation(line: 1493, column: 15, scope: !1693)
!1698 = !DILocalVariable(name: "retVal", scope: !1699, file: !3, line: 1494, type: !200)
!1699 = distinct !DILexicalBlock(scope: !1696, file: !3, line: 1493, column: 33)
!1700 = !DILocation(line: 1494, column: 23, scope: !1699)
!1701 = !DILocation(line: 1494, column: 32, scope: !1699)
!1702 = !DILocation(line: 1495, column: 13, scope: !1703)
!1703 = distinct !DILexicalBlock(scope: !1704, file: !3, line: 1495, column: 13)
!1704 = distinct !DILexicalBlock(scope: !1699, file: !3, line: 1495, column: 13)
!1705 = !DILocation(line: 1495, column: 13, scope: !1704)
!1706 = !DILocation(line: 1496, column: 10, scope: !1699)
!1707 = !DILocation(line: 1497, column: 7, scope: !1693)
!1708 = !DILocation(line: 1498, column: 4, scope: !1689)
!1709 = !DILocation(line: 1499, column: 21, scope: !1710)
!1710 = distinct !DILexicalBlock(scope: !1685, file: !3, line: 1498, column: 11)
!1711 = !DILocation(line: 1500, column: 31, scope: !1710)
!1712 = !DILocation(line: 1501, column: 12, scope: !1713)
!1713 = distinct !DILexicalBlock(scope: !1710, file: !3, line: 1501, column: 12)
!1714 = !DILocation(line: 1501, column: 20, scope: !1713)
!1715 = !DILocation(line: 1501, column: 12, scope: !1710)
!1716 = !DILocalVariable(name: "retVal", scope: !1717, file: !3, line: 1502, type: !200)
!1717 = distinct !DILexicalBlock(scope: !1713, file: !3, line: 1501, column: 32)
!1718 = !DILocation(line: 1502, column: 20, scope: !1717)
!1719 = !DILocation(line: 1502, column: 29, scope: !1717)
!1720 = !DILocation(line: 1503, column: 10, scope: !1721)
!1721 = distinct !DILexicalBlock(scope: !1722, file: !3, line: 1503, column: 10)
!1722 = distinct !DILexicalBlock(scope: !1717, file: !3, line: 1503, column: 10)
!1723 = !DILocation(line: 1503, column: 10, scope: !1722)
!1724 = !DILocation(line: 1504, column: 7, scope: !1717)
!1725 = !DILocation(line: 1506, column: 28, scope: !1388)
!1726 = !DILocation(line: 1508, column: 9, scope: !1727)
!1727 = distinct !DILexicalBlock(scope: !1388, file: !3, line: 1508, column: 9)
!1728 = !DILocation(line: 1508, column: 9, scope: !1388)
!1729 = !DILocation(line: 1509, column: 11, scope: !1730)
!1730 = distinct !DILexicalBlock(scope: !1731, file: !3, line: 1509, column: 11)
!1731 = distinct !DILexicalBlock(scope: !1727, file: !3, line: 1508, column: 25)
!1732 = !DILocation(line: 1509, column: 21, scope: !1730)
!1733 = !DILocation(line: 1509, column: 11, scope: !1731)
!1734 = !DILocation(line: 1510, column: 20, scope: !1730)
!1735 = !DILocation(line: 1510, column: 10, scope: !1730)
!1736 = !DILocation(line: 1511, column: 4, scope: !1731)
!1737 = !DILocation(line: 1512, column: 7, scope: !1738)
!1738 = distinct !DILexicalBlock(scope: !1727, file: !3, line: 1511, column: 11)
!1739 = !DILocation(line: 1513, column: 11, scope: !1740)
!1740 = distinct !DILexicalBlock(scope: !1738, file: !3, line: 1513, column: 11)
!1741 = !DILocation(line: 1513, column: 21, scope: !1740)
!1742 = !DILocation(line: 1513, column: 11, scope: !1738)
!1743 = !DILocation(line: 1514, column: 20, scope: !1740)
!1744 = !DILocation(line: 1514, column: 10, scope: !1740)
!1745 = !DILocation(line: 1515, column: 20, scope: !1740)
!1746 = !DILocation(line: 1517, column: 20, scope: !1740)
!1747 = !DILocation(line: 1515, column: 10, scope: !1740)
!1748 = !DILocation(line: 1520, column: 1, scope: !1388)
!1749 = distinct !DISubprogram(name: "setExit", scope: !3, file: !3, line: 653, type: !1750, scopeLine: 654, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1750 = !DISubroutineType(types: !1751)
!1751 = !{null, !28}
!1752 = !DILocalVariable(name: "v", arg: 1, scope: !1749, file: !3, line: 653, type: !28)
!1753 = !DILocation(line: 653, column: 22, scope: !1749)
!1754 = !DILocation(line: 655, column: 8, scope: !1755)
!1755 = distinct !DILexicalBlock(scope: !1749, file: !3, line: 655, column: 8)
!1756 = !DILocation(line: 655, column: 12, scope: !1755)
!1757 = !DILocation(line: 655, column: 10, scope: !1755)
!1758 = !DILocation(line: 655, column: 8, scope: !1749)
!1759 = !DILocation(line: 655, column: 35, scope: !1755)
!1760 = !DILocation(line: 655, column: 33, scope: !1755)
!1761 = !DILocation(line: 655, column: 23, scope: !1755)
!1762 = !DILocation(line: 656, column: 1, scope: !1749)
!1763 = distinct !DISubprogram(name: "testf", scope: !3, file: !3, line: 1525, type: !1036, scopeLine: 1526, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1764 = !DILocalVariable(name: "name", arg: 1, scope: !1763, file: !3, line: 1525, type: !24)
!1765 = !DILocation(line: 1525, column: 20, scope: !1763)
!1766 = !DILocalVariable(name: "inStr", scope: !1763, file: !3, line: 1527, type: !97)
!1767 = !DILocation(line: 1527, column: 10, scope: !1763)
!1768 = !DILocalVariable(name: "allOK", scope: !1763, file: !3, line: 1528, type: !22)
!1769 = !DILocation(line: 1528, column: 9, scope: !1763)
!1770 = !DILocalVariable(name: "statBuf", scope: !1763, file: !3, line: 1529, type: !157)
!1771 = !DILocation(line: 1529, column: 19, scope: !1763)
!1772 = !DILocation(line: 1531, column: 28, scope: !1763)
!1773 = !DILocation(line: 1533, column: 8, scope: !1774)
!1774 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1533, column: 8)
!1775 = !DILocation(line: 1533, column: 13, scope: !1774)
!1776 = !DILocation(line: 1533, column: 21, scope: !1774)
!1777 = !DILocation(line: 1533, column: 24, scope: !1774)
!1778 = !DILocation(line: 1533, column: 32, scope: !1774)
!1779 = !DILocation(line: 1533, column: 8, scope: !1763)
!1780 = !DILocation(line: 1534, column: 7, scope: !1774)
!1781 = !DILocation(line: 1536, column: 4, scope: !1763)
!1782 = !DILocation(line: 1537, column: 12, scope: !1763)
!1783 = !DILocation(line: 1537, column: 4, scope: !1763)
!1784 = !DILocation(line: 1538, column: 20, scope: !1785)
!1785 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1537, column: 21)
!1786 = !DILocation(line: 1538, column: 63, scope: !1785)
!1787 = !DILocation(line: 1539, column: 43, scope: !1785)
!1788 = !DILocation(line: 1539, column: 20, scope: !1785)
!1789 = !DILocation(line: 1539, column: 51, scope: !1785)
!1790 = !DILocation(line: 1540, column: 43, scope: !1785)
!1791 = !DILocation(line: 1540, column: 20, scope: !1785)
!1792 = !DILocation(line: 1540, column: 51, scope: !1785)
!1793 = !DILocation(line: 1543, column: 9, scope: !1794)
!1794 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1543, column: 9)
!1795 = !DILocation(line: 1543, column: 17, scope: !1794)
!1796 = !DILocation(line: 1543, column: 27, scope: !1794)
!1797 = !DILocation(line: 1543, column: 30, scope: !1794)
!1798 = !DILocation(line: 1543, column: 9, scope: !1763)
!1799 = !DILocation(line: 1544, column: 11, scope: !1800)
!1800 = distinct !DILexicalBlock(scope: !1801, file: !3, line: 1544, column: 11)
!1801 = distinct !DILexicalBlock(scope: !1794, file: !3, line: 1543, column: 64)
!1802 = !DILocation(line: 1544, column: 11, scope: !1801)
!1803 = !DILocation(line: 1545, column: 17, scope: !1800)
!1804 = !DILocation(line: 1546, column: 17, scope: !1800)
!1805 = !DILocation(line: 1545, column: 7, scope: !1800)
!1806 = !DILocation(line: 1547, column: 7, scope: !1801)
!1807 = !DILocation(line: 1548, column: 7, scope: !1801)
!1808 = !DILocation(line: 1550, column: 9, scope: !1809)
!1809 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1550, column: 9)
!1810 = !DILocation(line: 1550, column: 17, scope: !1809)
!1811 = !DILocation(line: 1550, column: 27, scope: !1809)
!1812 = !DILocation(line: 1550, column: 31, scope: !1809)
!1813 = !DILocation(line: 1550, column: 9, scope: !1763)
!1814 = !DILocation(line: 1551, column: 17, scope: !1815)
!1815 = distinct !DILexicalBlock(scope: !1809, file: !3, line: 1550, column: 55)
!1816 = !DILocation(line: 1552, column: 17, scope: !1815)
!1817 = !DILocation(line: 1552, column: 44, scope: !1815)
!1818 = !DILocation(line: 1552, column: 35, scope: !1815)
!1819 = !DILocation(line: 1551, column: 7, scope: !1815)
!1820 = !DILocation(line: 1553, column: 7, scope: !1815)
!1821 = !DILocation(line: 1554, column: 7, scope: !1815)
!1822 = !DILocation(line: 1556, column: 9, scope: !1823)
!1823 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1556, column: 9)
!1824 = !DILocation(line: 1556, column: 17, scope: !1823)
!1825 = !DILocation(line: 1556, column: 9, scope: !1763)
!1826 = !DILocation(line: 1557, column: 7, scope: !1827)
!1827 = distinct !DILexicalBlock(scope: !1823, file: !3, line: 1556, column: 29)
!1828 = !DILocation(line: 1558, column: 12, scope: !1829)
!1829 = distinct !DILexicalBlock(scope: !1827, file: !3, line: 1558, column: 12)
!1830 = !DILocation(line: 1558, column: 12, scope: !1827)
!1831 = !DILocation(line: 1559, column: 19, scope: !1832)
!1832 = distinct !DILexicalBlock(scope: !1829, file: !3, line: 1558, column: 42)
!1833 = !DILocation(line: 1561, column: 19, scope: !1832)
!1834 = !DILocation(line: 1559, column: 10, scope: !1832)
!1835 = !DILocation(line: 1562, column: 10, scope: !1832)
!1836 = !DILocation(line: 1563, column: 10, scope: !1832)
!1837 = !DILocation(line: 1565, column: 4, scope: !1827)
!1838 = !DILocation(line: 1567, column: 13, scope: !1763)
!1839 = !DILocation(line: 1567, column: 4, scope: !1763)
!1840 = !DILocation(line: 1570, column: 33, scope: !1841)
!1841 = distinct !DILexicalBlock(scope: !1842, file: !3, line: 1570, column: 15)
!1842 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1567, column: 23)
!1843 = !DILocation(line: 1570, column: 24, scope: !1841)
!1844 = !DILocation(line: 1570, column: 15, scope: !1841)
!1845 = !DILocation(line: 1570, column: 15, scope: !1842)
!1846 = !DILocation(line: 1571, column: 23, scope: !1847)
!1847 = distinct !DILexicalBlock(scope: !1841, file: !3, line: 1570, column: 45)
!1848 = !DILocation(line: 1573, column: 23, scope: !1847)
!1849 = !DILocation(line: 1571, column: 13, scope: !1847)
!1850 = !DILocation(line: 1574, column: 23, scope: !1847)
!1851 = !DILocation(line: 1575, column: 31, scope: !1847)
!1852 = !DILocation(line: 1575, column: 41, scope: !1847)
!1853 = !DILocation(line: 1574, column: 13, scope: !1847)
!1854 = !DILocation(line: 1576, column: 13, scope: !1847)
!1855 = !DILocation(line: 1577, column: 13, scope: !1847)
!1856 = !DILocation(line: 1579, column: 18, scope: !1842)
!1857 = !DILocation(line: 1579, column: 16, scope: !1842)
!1858 = !DILocation(line: 1580, column: 10, scope: !1842)
!1859 = !DILocation(line: 1583, column: 18, scope: !1842)
!1860 = !DILocation(line: 1583, column: 16, scope: !1842)
!1861 = !DILocation(line: 1584, column: 15, scope: !1862)
!1862 = distinct !DILexicalBlock(scope: !1842, file: !3, line: 1584, column: 15)
!1863 = !DILocation(line: 1584, column: 21, scope: !1862)
!1864 = !DILocation(line: 1584, column: 15, scope: !1842)
!1865 = !DILocation(line: 1585, column: 23, scope: !1866)
!1866 = distinct !DILexicalBlock(scope: !1862, file: !3, line: 1584, column: 31)
!1867 = !DILocation(line: 1586, column: 23, scope: !1866)
!1868 = !DILocation(line: 1586, column: 50, scope: !1866)
!1869 = !DILocation(line: 1586, column: 41, scope: !1866)
!1870 = !DILocation(line: 1585, column: 13, scope: !1866)
!1871 = !DILocation(line: 1587, column: 13, scope: !1866)
!1872 = !DILocation(line: 1588, column: 13, scope: !1866)
!1873 = !DILocation(line: 1590, column: 10, scope: !1842)
!1874 = !DILocation(line: 1593, column: 10, scope: !1842)
!1875 = !DILocation(line: 1597, column: 8, scope: !1876)
!1876 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1597, column: 8)
!1877 = !DILocation(line: 1597, column: 18, scope: !1876)
!1878 = !DILocation(line: 1597, column: 8, scope: !1763)
!1879 = !DILocation(line: 1598, column: 17, scope: !1880)
!1880 = distinct !DILexicalBlock(scope: !1876, file: !3, line: 1597, column: 24)
!1881 = !DILocation(line: 1598, column: 7, scope: !1880)
!1882 = !DILocation(line: 1599, column: 7, scope: !1880)
!1883 = !DILocation(line: 1600, column: 16, scope: !1880)
!1884 = !DILocation(line: 1600, column: 7, scope: !1880)
!1885 = !DILocation(line: 1601, column: 4, scope: !1880)
!1886 = !DILocation(line: 1604, column: 27, scope: !1763)
!1887 = !DILocation(line: 1605, column: 25, scope: !1763)
!1888 = !DILocation(line: 1605, column: 12, scope: !1763)
!1889 = !DILocation(line: 1605, column: 10, scope: !1763)
!1890 = !DILocation(line: 1607, column: 8, scope: !1891)
!1891 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1607, column: 8)
!1892 = !DILocation(line: 1607, column: 14, scope: !1891)
!1893 = !DILocation(line: 1607, column: 17, scope: !1891)
!1894 = !DILocation(line: 1607, column: 27, scope: !1891)
!1895 = !DILocation(line: 1607, column: 8, scope: !1763)
!1896 = !DILocation(line: 1607, column: 43, scope: !1891)
!1897 = !DILocation(line: 1607, column: 33, scope: !1891)
!1898 = !DILocation(line: 1608, column: 9, scope: !1899)
!1899 = distinct !DILexicalBlock(scope: !1763, file: !3, line: 1608, column: 8)
!1900 = !DILocation(line: 1608, column: 8, scope: !1763)
!1901 = !DILocation(line: 1608, column: 31, scope: !1899)
!1902 = !DILocation(line: 1608, column: 16, scope: !1899)
!1903 = !DILocation(line: 1609, column: 1, scope: !1763)
!1904 = distinct !DISubprogram(name: "showFileNames", scope: !3, file: !3, line: 676, type: !1029, scopeLine: 677, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1905 = !DILocation(line: 678, column: 8, scope: !1906)
!1906 = distinct !DILexicalBlock(scope: !1904, file: !3, line: 678, column: 8)
!1907 = !DILocation(line: 678, column: 8, scope: !1904)
!1908 = !DILocation(line: 680, column: 7, scope: !1906)
!1909 = !DILocation(line: 679, column: 4, scope: !1906)
!1910 = !DILocation(line: 684, column: 1, scope: !1904)
!1911 = distinct !DISubprogram(name: "cleanUpAndFail", scope: !3, file: !3, line: 689, type: !1750, scopeLine: 690, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1912 = !DILocalVariable(name: "ec", arg: 1, scope: !1911, file: !3, line: 689, type: !28)
!1913 = !DILocation(line: 689, column: 29, scope: !1911)
!1914 = !DILocalVariable(name: "retVal", scope: !1911, file: !3, line: 691, type: !200)
!1915 = !DILocation(line: 691, column: 19, scope: !1911)
!1916 = !DILocalVariable(name: "statBuf", scope: !1911, file: !3, line: 692, type: !157)
!1917 = !DILocation(line: 692, column: 19, scope: !1911)
!1918 = !DILocation(line: 694, column: 9, scope: !1919)
!1919 = distinct !DILexicalBlock(scope: !1911, file: !3, line: 694, column: 9)
!1920 = !DILocation(line: 694, column: 17, scope: !1919)
!1921 = !DILocation(line: 695, column: 9, scope: !1919)
!1922 = !DILocation(line: 695, column: 12, scope: !1919)
!1923 = !DILocation(line: 695, column: 19, scope: !1919)
!1924 = !DILocation(line: 696, column: 9, scope: !1919)
!1925 = !DILocation(line: 696, column: 12, scope: !1919)
!1926 = !DILocation(line: 694, column: 9, scope: !1911)
!1927 = !DILocation(line: 703, column: 16, scope: !1928)
!1928 = distinct !DILexicalBlock(scope: !1919, file: !3, line: 696, column: 38)
!1929 = !DILocation(line: 703, column: 14, scope: !1928)
!1930 = !DILocation(line: 704, column: 11, scope: !1931)
!1931 = distinct !DILexicalBlock(scope: !1928, file: !3, line: 704, column: 11)
!1932 = !DILocation(line: 704, column: 18, scope: !1931)
!1933 = !DILocation(line: 704, column: 11, scope: !1928)
!1934 = !DILocation(line: 705, column: 14, scope: !1935)
!1935 = distinct !DILexicalBlock(scope: !1936, file: !3, line: 705, column: 14)
!1936 = distinct !DILexicalBlock(scope: !1931, file: !3, line: 704, column: 24)
!1937 = !DILocation(line: 705, column: 14, scope: !1936)
!1938 = !DILocation(line: 706, column: 23, scope: !1935)
!1939 = !DILocation(line: 708, column: 23, scope: !1935)
!1940 = !DILocation(line: 706, column: 13, scope: !1935)
!1941 = !DILocation(line: 709, column: 14, scope: !1942)
!1942 = distinct !DILexicalBlock(scope: !1936, file: !3, line: 709, column: 14)
!1943 = !DILocation(line: 709, column: 37, scope: !1942)
!1944 = !DILocation(line: 709, column: 14, scope: !1936)
!1945 = !DILocation(line: 710, column: 22, scope: !1942)
!1946 = !DILocation(line: 710, column: 13, scope: !1942)
!1947 = !DILocation(line: 711, column: 19, scope: !1936)
!1948 = !DILocation(line: 711, column: 17, scope: !1936)
!1949 = !DILocation(line: 712, column: 14, scope: !1950)
!1950 = distinct !DILexicalBlock(scope: !1936, file: !3, line: 712, column: 14)
!1951 = !DILocation(line: 712, column: 21, scope: !1950)
!1952 = !DILocation(line: 712, column: 14, scope: !1936)
!1953 = !DILocation(line: 713, column: 23, scope: !1950)
!1954 = !DILocation(line: 716, column: 23, scope: !1950)
!1955 = !DILocation(line: 713, column: 13, scope: !1950)
!1956 = !DILocation(line: 717, column: 7, scope: !1936)
!1957 = !DILocation(line: 718, column: 20, scope: !1958)
!1958 = distinct !DILexicalBlock(scope: !1931, file: !3, line: 717, column: 14)
!1959 = !DILocation(line: 720, column: 21, scope: !1958)
!1960 = !DILocation(line: 718, column: 10, scope: !1958)
!1961 = !DILocation(line: 721, column: 20, scope: !1958)
!1962 = !DILocation(line: 723, column: 20, scope: !1958)
!1963 = !DILocation(line: 721, column: 10, scope: !1958)
!1964 = !DILocation(line: 724, column: 20, scope: !1958)
!1965 = !DILocation(line: 726, column: 20, scope: !1958)
!1966 = !DILocation(line: 724, column: 10, scope: !1958)
!1967 = !DILocation(line: 727, column: 20, scope: !1958)
!1968 = !DILocation(line: 730, column: 20, scope: !1958)
!1969 = !DILocation(line: 727, column: 10, scope: !1958)
!1970 = !DILocation(line: 732, column: 4, scope: !1928)
!1971 = !DILocation(line: 734, column: 8, scope: !1972)
!1972 = distinct !DILexicalBlock(scope: !1911, file: !3, line: 734, column: 8)
!1973 = !DILocation(line: 734, column: 14, scope: !1972)
!1974 = !DILocation(line: 734, column: 17, scope: !1972)
!1975 = !DILocation(line: 734, column: 30, scope: !1972)
!1976 = !DILocation(line: 734, column: 34, scope: !1972)
!1977 = !DILocation(line: 734, column: 37, scope: !1972)
!1978 = !DILocation(line: 734, column: 57, scope: !1972)
!1979 = !DILocation(line: 734, column: 55, scope: !1972)
!1980 = !DILocation(line: 734, column: 8, scope: !1911)
!1981 = !DILocation(line: 735, column: 17, scope: !1982)
!1982 = distinct !DILexicalBlock(scope: !1972, file: !3, line: 734, column: 71)
!1983 = !DILocation(line: 738, column: 17, scope: !1982)
!1984 = !DILocation(line: 738, column: 27, scope: !1982)
!1985 = !DILocation(line: 739, column: 17, scope: !1982)
!1986 = !DILocation(line: 739, column: 31, scope: !1982)
!1987 = !DILocation(line: 739, column: 46, scope: !1982)
!1988 = !DILocation(line: 739, column: 44, scope: !1982)
!1989 = !DILocation(line: 735, column: 7, scope: !1982)
!1990 = !DILocation(line: 740, column: 4, scope: !1982)
!1991 = !DILocation(line: 741, column: 12, scope: !1911)
!1992 = !DILocation(line: 741, column: 4, scope: !1911)
!1993 = !DILocation(line: 742, column: 9, scope: !1911)
!1994 = !DILocation(line: 742, column: 4, scope: !1911)
!1995 = distinct !DISubprogram(name: "cadvise", scope: !3, file: !3, line: 661, type: !1029, scopeLine: 662, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!1996 = !DILocation(line: 663, column: 8, scope: !1997)
!1997 = distinct !DILexicalBlock(scope: !1995, file: !3, line: 663, column: 8)
!1998 = !DILocation(line: 663, column: 8, scope: !1995)
!1999 = !DILocation(line: 665, column: 7, scope: !1997)
!2000 = !DILocation(line: 664, column: 4, scope: !1997)
!2001 = !DILocation(line: 671, column: 1, scope: !1995)
!2002 = distinct !DISubprogram(name: "mkCell", scope: !3, file: !3, line: 1729, type: !2003, scopeLine: 1730, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2003 = !DISubroutineType(types: !2004)
!2004 = !{!31}
!2005 = !DILocalVariable(name: "c", scope: !2002, file: !3, line: 1731, type: !31)
!2006 = !DILocation(line: 1731, column: 10, scope: !2002)
!2007 = !DILocation(line: 1733, column: 16, scope: !2002)
!2008 = !DILocation(line: 1733, column: 8, scope: !2002)
!2009 = !DILocation(line: 1733, column: 6, scope: !2002)
!2010 = !DILocation(line: 1734, column: 4, scope: !2002)
!2011 = !DILocation(line: 1734, column: 7, scope: !2002)
!2012 = !DILocation(line: 1734, column: 12, scope: !2002)
!2013 = !DILocation(line: 1735, column: 4, scope: !2002)
!2014 = !DILocation(line: 1735, column: 7, scope: !2002)
!2015 = !DILocation(line: 1735, column: 12, scope: !2002)
!2016 = !DILocation(line: 1736, column: 11, scope: !2002)
!2017 = !DILocation(line: 1736, column: 4, scope: !2002)
!2018 = distinct !DISubprogram(name: "myMalloc", scope: !3, file: !3, line: 1717, type: !2019, scopeLine: 1718, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2019 = !DISubroutineType(types: !2020)
!2020 = !{!27, !28}
!2021 = !DILocalVariable(name: "n", arg: 1, scope: !2018, file: !3, line: 1717, type: !28)
!2022 = !DILocation(line: 1717, column: 24, scope: !2018)
!2023 = !DILocalVariable(name: "p", scope: !2018, file: !3, line: 1719, type: !27)
!2024 = !DILocation(line: 1719, column: 10, scope: !2018)
!2025 = !DILocation(line: 1721, column: 25, scope: !2018)
!2026 = !DILocation(line: 1721, column: 17, scope: !2018)
!2027 = !DILocation(line: 1721, column: 8, scope: !2018)
!2028 = !DILocation(line: 1721, column: 6, scope: !2018)
!2029 = !DILocation(line: 1722, column: 8, scope: !2030)
!2030 = distinct !DILexicalBlock(scope: !2018, file: !3, line: 1722, column: 8)
!2031 = !DILocation(line: 1722, column: 10, scope: !2030)
!2032 = !DILocation(line: 1722, column: 8, scope: !2018)
!2033 = !DILocation(line: 1722, column: 19, scope: !2030)
!2034 = !DILocation(line: 1723, column: 11, scope: !2018)
!2035 = !DILocation(line: 1723, column: 4, scope: !2018)
!2036 = distinct !DISubprogram(name: "outOfMemory", scope: !3, file: !3, line: 881, type: !1029, scopeLine: 882, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2037 = !DILocation(line: 883, column: 14, scope: !2036)
!2038 = !DILocation(line: 885, column: 14, scope: !2036)
!2039 = !DILocation(line: 883, column: 4, scope: !2036)
!2040 = !DILocation(line: 886, column: 4, scope: !2036)
!2041 = !DILocation(line: 887, column: 4, scope: !2036)
!2042 = distinct !DISubprogram(name: "panic", scope: !3, file: !3, line: 748, type: !2043, scopeLine: 749, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2043 = !DISubroutineType(types: !2044)
!2044 = !{null, !48}
!2045 = !DILocalVariable(name: "s", arg: 1, scope: !2042, file: !3, line: 748, type: !48)
!2046 = !DILocation(line: 748, column: 26, scope: !2042)
!2047 = !DILocation(line: 750, column: 14, scope: !2042)
!2048 = !DILocation(line: 755, column: 14, scope: !2042)
!2049 = !DILocation(line: 755, column: 24, scope: !2042)
!2050 = !DILocation(line: 750, column: 4, scope: !2042)
!2051 = !DILocation(line: 756, column: 4, scope: !2042)
!2052 = !DILocation(line: 757, column: 4, scope: !2042)
!2053 = distinct !DISubprogram(name: "containsDubiousChars", scope: !3, file: !3, line: 1092, type: !2054, scopeLine: 1093, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2054 = !DISubroutineType(types: !2055)
!2055 = !{!22, !24}
!2056 = !DILocalVariable(name: "name", arg: 1, scope: !2053, file: !3, line: 1092, type: !24)
!2057 = !DILocation(line: 1092, column: 35, scope: !2053)
!2058 = !DILocation(line: 1098, column: 4, scope: !2053)
!2059 = distinct !DISubprogram(name: "fileExists", scope: !3, file: !3, line: 949, type: !2054, scopeLine: 950, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2060 = !DILocalVariable(name: "name", arg: 1, scope: !2059, file: !3, line: 949, type: !24)
!2061 = !DILocation(line: 949, column: 25, scope: !2059)
!2062 = !DILocalVariable(name: "tmp", scope: !2059, file: !3, line: 951, type: !97)
!2063 = !DILocation(line: 951, column: 10, scope: !2059)
!2064 = !DILocation(line: 951, column: 26, scope: !2059)
!2065 = !DILocation(line: 951, column: 18, scope: !2059)
!2066 = !DILocalVariable(name: "exists", scope: !2059, file: !3, line: 952, type: !22)
!2067 = !DILocation(line: 952, column: 9, scope: !2059)
!2068 = !DILocation(line: 952, column: 19, scope: !2059)
!2069 = !DILocation(line: 952, column: 23, scope: !2059)
!2070 = !DILocation(line: 952, column: 18, scope: !2059)
!2071 = !DILocation(line: 953, column: 8, scope: !2072)
!2072 = distinct !DILexicalBlock(scope: !2059, file: !3, line: 953, column: 8)
!2073 = !DILocation(line: 953, column: 12, scope: !2072)
!2074 = !DILocation(line: 953, column: 8, scope: !2059)
!2075 = !DILocation(line: 953, column: 30, scope: !2072)
!2076 = !DILocation(line: 953, column: 21, scope: !2072)
!2077 = !DILocation(line: 954, column: 11, scope: !2059)
!2078 = !DILocation(line: 954, column: 4, scope: !2059)
!2079 = distinct !DISubprogram(name: "hasSuffix", scope: !3, file: !3, line: 1119, type: !2080, scopeLine: 1120, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2080 = !DISubroutineType(types: !2081)
!2081 = !{!22, !24, !48}
!2082 = !DILocalVariable(name: "s", arg: 1, scope: !2079, file: !3, line: 1119, type: !24)
!2083 = !DILocation(line: 1119, column: 24, scope: !2079)
!2084 = !DILocalVariable(name: "suffix", arg: 2, scope: !2079, file: !3, line: 1119, type: !48)
!2085 = !DILocation(line: 1119, column: 39, scope: !2079)
!2086 = !DILocalVariable(name: "ns", scope: !2079, file: !3, line: 1121, type: !28)
!2087 = !DILocation(line: 1121, column: 10, scope: !2079)
!2088 = !DILocation(line: 1121, column: 22, scope: !2079)
!2089 = !DILocation(line: 1121, column: 15, scope: !2079)
!2090 = !DILocalVariable(name: "nx", scope: !2079, file: !3, line: 1122, type: !28)
!2091 = !DILocation(line: 1122, column: 10, scope: !2079)
!2092 = !DILocation(line: 1122, column: 22, scope: !2079)
!2093 = !DILocation(line: 1122, column: 15, scope: !2079)
!2094 = !DILocation(line: 1123, column: 8, scope: !2095)
!2095 = distinct !DILexicalBlock(scope: !2079, file: !3, line: 1123, column: 8)
!2096 = !DILocation(line: 1123, column: 13, scope: !2095)
!2097 = !DILocation(line: 1123, column: 11, scope: !2095)
!2098 = !DILocation(line: 1123, column: 8, scope: !2079)
!2099 = !DILocation(line: 1123, column: 17, scope: !2095)
!2100 = !DILocation(line: 1124, column: 15, scope: !2101)
!2101 = distinct !DILexicalBlock(scope: !2079, file: !3, line: 1124, column: 8)
!2102 = !DILocation(line: 1124, column: 19, scope: !2101)
!2103 = !DILocation(line: 1124, column: 17, scope: !2101)
!2104 = !DILocation(line: 1124, column: 24, scope: !2101)
!2105 = !DILocation(line: 1124, column: 22, scope: !2101)
!2106 = !DILocation(line: 1124, column: 28, scope: !2101)
!2107 = !DILocation(line: 1124, column: 8, scope: !2101)
!2108 = !DILocation(line: 1124, column: 36, scope: !2101)
!2109 = !DILocation(line: 1124, column: 8, scope: !2079)
!2110 = !DILocation(line: 1124, column: 42, scope: !2101)
!2111 = !DILocation(line: 1125, column: 4, scope: !2079)
!2112 = !DILocation(line: 1126, column: 1, scope: !2079)
!2113 = distinct !DISubprogram(name: "notAStandardFile", scope: !3, file: !3, line: 990, type: !2054, scopeLine: 991, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2114 = !DILocalVariable(name: "name", arg: 1, scope: !2113, file: !3, line: 990, type: !24)
!2115 = !DILocation(line: 990, column: 31, scope: !2113)
!2116 = !DILocalVariable(name: "i", scope: !2113, file: !3, line: 992, type: !200)
!2117 = !DILocation(line: 992, column: 19, scope: !2113)
!2118 = !DILocalVariable(name: "statBuf", scope: !2113, file: !3, line: 993, type: !157)
!2119 = !DILocation(line: 993, column: 19, scope: !2113)
!2120 = !DILocation(line: 995, column: 19, scope: !2113)
!2121 = !DILocation(line: 995, column: 8, scope: !2113)
!2122 = !DILocation(line: 995, column: 6, scope: !2113)
!2123 = !DILocation(line: 996, column: 8, scope: !2124)
!2124 = distinct !DILexicalBlock(scope: !2113, file: !3, line: 996, column: 8)
!2125 = !DILocation(line: 996, column: 10, scope: !2124)
!2126 = !DILocation(line: 996, column: 8, scope: !2113)
!2127 = !DILocation(line: 996, column: 16, scope: !2124)
!2128 = !DILocation(line: 997, column: 8, scope: !2129)
!2129 = distinct !DILexicalBlock(scope: !2113, file: !3, line: 997, column: 8)
!2130 = !DILocation(line: 997, column: 8, scope: !2113)
!2131 = !DILocation(line: 997, column: 37, scope: !2129)
!2132 = !DILocation(line: 998, column: 4, scope: !2113)
!2133 = !DILocation(line: 999, column: 1, scope: !2113)
!2134 = distinct !DISubprogram(name: "countHardLinks", scope: !3, file: !3, line: 1007, type: !2135, scopeLine: 1008, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2135 = !DISubroutineType(types: !2136)
!2136 = !{!28, !24}
!2137 = !DILocalVariable(name: "name", arg: 1, scope: !2134, file: !3, line: 1007, type: !24)
!2138 = !DILocation(line: 1007, column: 30, scope: !2134)
!2139 = !DILocalVariable(name: "i", scope: !2134, file: !3, line: 1009, type: !200)
!2140 = !DILocation(line: 1009, column: 19, scope: !2134)
!2141 = !DILocalVariable(name: "statBuf", scope: !2134, file: !3, line: 1010, type: !157)
!2142 = !DILocation(line: 1010, column: 19, scope: !2134)
!2143 = !DILocation(line: 1012, column: 19, scope: !2134)
!2144 = !DILocation(line: 1012, column: 8, scope: !2134)
!2145 = !DILocation(line: 1012, column: 6, scope: !2134)
!2146 = !DILocation(line: 1013, column: 8, scope: !2147)
!2147 = distinct !DILexicalBlock(scope: !2134, file: !3, line: 1013, column: 8)
!2148 = !DILocation(line: 1013, column: 10, scope: !2147)
!2149 = !DILocation(line: 1013, column: 8, scope: !2134)
!2150 = !DILocation(line: 1013, column: 16, scope: !2147)
!2151 = !DILocation(line: 1014, column: 20, scope: !2134)
!2152 = !DILocation(line: 1014, column: 29, scope: !2134)
!2153 = !DILocation(line: 1014, column: 11, scope: !2134)
!2154 = !DILocation(line: 1014, column: 4, scope: !2134)
!2155 = !DILocation(line: 1015, column: 1, scope: !2134)
!2156 = distinct !DISubprogram(name: "saveInputFileMetaInfo", scope: !3, file: !3, line: 1047, type: !1036, scopeLine: 1048, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2157 = !DILocalVariable(name: "srcName", arg: 1, scope: !2156, file: !3, line: 1047, type: !24)
!2158 = !DILocation(line: 1047, column: 36, scope: !2156)
!2159 = !DILocalVariable(name: "retVal", scope: !2156, file: !3, line: 1050, type: !200)
!2160 = !DILocation(line: 1050, column: 14, scope: !2156)
!2161 = !DILocation(line: 1052, column: 22, scope: !2156)
!2162 = !DILocation(line: 1052, column: 13, scope: !2156)
!2163 = !DILocation(line: 1052, column: 11, scope: !2156)
!2164 = !DILocation(line: 1053, column: 4, scope: !2165)
!2165 = distinct !DILexicalBlock(scope: !2166, file: !3, line: 1053, column: 4)
!2166 = distinct !DILexicalBlock(scope: !2156, file: !3, line: 1053, column: 4)
!2167 = !DILocation(line: 1053, column: 4, scope: !2166)
!2168 = !DILocation(line: 1055, column: 1, scope: !2156)
!2169 = distinct !DISubprogram(name: "fopen_output_safely", scope: !3, file: !3, line: 969, type: !2170, scopeLine: 970, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2170 = !DISubroutineType(types: !2171)
!2171 = !{!97, !24, !2172}
!2172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2173, size: 64)
!2173 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !26)
!2174 = !DILocalVariable(name: "name", arg: 1, scope: !2169, file: !3, line: 969, type: !24)
!2175 = !DILocation(line: 969, column: 35, scope: !2169)
!2176 = !DILocalVariable(name: "mode", arg: 2, scope: !2169, file: !3, line: 969, type: !2172)
!2177 = !DILocation(line: 969, column: 53, scope: !2169)
!2178 = !DILocalVariable(name: "fp", scope: !2169, file: !3, line: 972, type: !97)
!2179 = !DILocation(line: 972, column: 14, scope: !2169)
!2180 = !DILocalVariable(name: "fh", scope: !2169, file: !3, line: 973, type: !200)
!2181 = !DILocation(line: 973, column: 14, scope: !2169)
!2182 = !DILocation(line: 974, column: 14, scope: !2169)
!2183 = !DILocation(line: 974, column: 9, scope: !2169)
!2184 = !DILocation(line: 974, column: 7, scope: !2169)
!2185 = !DILocation(line: 975, column: 8, scope: !2186)
!2186 = distinct !DILexicalBlock(scope: !2169, file: !3, line: 975, column: 8)
!2187 = !DILocation(line: 975, column: 11, scope: !2186)
!2188 = !DILocation(line: 975, column: 8, scope: !2169)
!2189 = !DILocation(line: 975, column: 18, scope: !2186)
!2190 = !DILocation(line: 976, column: 16, scope: !2169)
!2191 = !DILocation(line: 976, column: 20, scope: !2169)
!2192 = !DILocation(line: 976, column: 9, scope: !2169)
!2193 = !DILocation(line: 976, column: 7, scope: !2169)
!2194 = !DILocation(line: 977, column: 8, scope: !2195)
!2195 = distinct !DILexicalBlock(scope: !2169, file: !3, line: 977, column: 8)
!2196 = !DILocation(line: 977, column: 11, scope: !2195)
!2197 = !DILocation(line: 977, column: 8, scope: !2169)
!2198 = !DILocation(line: 977, column: 26, scope: !2195)
!2199 = !DILocation(line: 977, column: 20, scope: !2195)
!2200 = !DILocation(line: 978, column: 11, scope: !2169)
!2201 = !DILocation(line: 978, column: 4, scope: !2169)
!2202 = !DILocation(line: 982, column: 1, scope: !2169)
!2203 = distinct !DISubprogram(name: "pad", scope: !3, file: !3, line: 917, type: !1036, scopeLine: 918, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2204 = !DILocalVariable(name: "s", arg: 1, scope: !2203, file: !3, line: 917, type: !24)
!2205 = !DILocation(line: 917, column: 18, scope: !2203)
!2206 = !DILocalVariable(name: "i", scope: !2203, file: !3, line: 919, type: !28)
!2207 = !DILocation(line: 919, column: 10, scope: !2203)
!2208 = !DILocation(line: 920, column: 23, scope: !2209)
!2209 = distinct !DILexicalBlock(scope: !2203, file: !3, line: 920, column: 9)
!2210 = !DILocation(line: 920, column: 16, scope: !2209)
!2211 = !DILocation(line: 920, column: 9, scope: !2209)
!2212 = !DILocation(line: 920, column: 29, scope: !2209)
!2213 = !DILocation(line: 920, column: 26, scope: !2209)
!2214 = !DILocation(line: 920, column: 9, scope: !2203)
!2215 = !DILocation(line: 920, column: 47, scope: !2209)
!2216 = !DILocation(line: 921, column: 11, scope: !2217)
!2217 = distinct !DILexicalBlock(scope: !2203, file: !3, line: 921, column: 4)
!2218 = !DILocation(line: 921, column: 9, scope: !2217)
!2219 = !DILocation(line: 921, column: 16, scope: !2220)
!2220 = distinct !DILexicalBlock(scope: !2217, file: !3, line: 921, column: 4)
!2221 = !DILocation(line: 921, column: 21, scope: !2220)
!2222 = !DILocation(line: 921, column: 53, scope: !2220)
!2223 = !DILocation(line: 921, column: 46, scope: !2220)
!2224 = !DILocation(line: 921, column: 39, scope: !2220)
!2225 = !DILocation(line: 921, column: 37, scope: !2220)
!2226 = !DILocation(line: 921, column: 18, scope: !2220)
!2227 = !DILocation(line: 921, column: 4, scope: !2217)
!2228 = !DILocation(line: 922, column: 17, scope: !2220)
!2229 = !DILocation(line: 922, column: 7, scope: !2220)
!2230 = !DILocation(line: 921, column: 58, scope: !2220)
!2231 = !DILocation(line: 921, column: 4, scope: !2220)
!2232 = distinct !{!2232, !2227, !2233}
!2233 = !DILocation(line: 922, column: 29, scope: !2217)
!2234 = !DILocation(line: 923, column: 1, scope: !2203)
!2235 = distinct !DISubprogram(name: "compressStream", scope: !3, file: !3, line: 331, type: !2236, scopeLine: 332, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2236 = !DISubroutineType(types: !2237)
!2237 = !{null, !97, !97}
!2238 = !DILocalVariable(name: "stream", arg: 1, scope: !2235, file: !3, line: 331, type: !97)
!2239 = !DILocation(line: 331, column: 29, scope: !2235)
!2240 = !DILocalVariable(name: "zStream", arg: 2, scope: !2235, file: !3, line: 331, type: !97)
!2241 = !DILocation(line: 331, column: 43, scope: !2235)
!2242 = !DILocalVariable(name: "bzf", scope: !2235, file: !3, line: 333, type: !2243)
!2243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2244, size: 64)
!2244 = !DIDerivedType(tag: DW_TAG_typedef, name: "BZFILE", file: !2245, line: 137, baseType: null)
!2245 = !DIFile(filename: "./bzlib.h", directory: "/home/yongzhe/Documents/grpc/examples/cpp/bzip2")
!2246 = !DILocation(line: 333, column: 12, scope: !2235)
!2247 = !DILocalVariable(name: "ibuf", scope: !2235, file: !3, line: 334, type: !2248)
!2248 = !DICompositeType(tag: DW_TAG_array_type, baseType: !41, size: 40000, elements: !2249)
!2249 = !{!2250}
!2250 = !DISubrange(count: 5000)
!2251 = !DILocation(line: 334, column: 12, scope: !2235)
!2252 = !DILocalVariable(name: "nIbuf", scope: !2235, file: !3, line: 335, type: !28)
!2253 = !DILocation(line: 335, column: 12, scope: !2235)
!2254 = !DILocalVariable(name: "nbytes_in_lo32", scope: !2235, file: !3, line: 336, type: !2255)
!2255 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt32", file: !3, line: 166, baseType: !7)
!2256 = !DILocation(line: 336, column: 12, scope: !2235)
!2257 = !DILocalVariable(name: "nbytes_in_hi32", scope: !2235, file: !3, line: 336, type: !2255)
!2258 = !DILocation(line: 336, column: 28, scope: !2235)
!2259 = !DILocalVariable(name: "nbytes_out_lo32", scope: !2235, file: !3, line: 337, type: !2255)
!2260 = !DILocation(line: 337, column: 12, scope: !2235)
!2261 = !DILocalVariable(name: "nbytes_out_hi32", scope: !2235, file: !3, line: 337, type: !2255)
!2262 = !DILocation(line: 337, column: 29, scope: !2235)
!2263 = !DILocalVariable(name: "bzerr", scope: !2235, file: !3, line: 338, type: !28)
!2264 = !DILocation(line: 338, column: 12, scope: !2235)
!2265 = !DILocalVariable(name: "bzerr_dummy", scope: !2235, file: !3, line: 338, type: !28)
!2266 = !DILocation(line: 338, column: 19, scope: !2235)
!2267 = !DILocalVariable(name: "ret", scope: !2235, file: !3, line: 338, type: !28)
!2268 = !DILocation(line: 338, column: 32, scope: !2235)
!2269 = !DILocation(line: 343, column: 15, scope: !2270)
!2270 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 343, column: 8)
!2271 = !DILocation(line: 343, column: 8, scope: !2270)
!2272 = !DILocation(line: 343, column: 8, scope: !2235)
!2273 = !DILocation(line: 343, column: 24, scope: !2270)
!2274 = !DILocation(line: 344, column: 15, scope: !2275)
!2275 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 344, column: 8)
!2276 = !DILocation(line: 344, column: 8, scope: !2275)
!2277 = !DILocation(line: 344, column: 8, scope: !2235)
!2278 = !DILocation(line: 344, column: 25, scope: !2275)
!2279 = !DILocation(line: 346, column: 36, scope: !2235)
!2280 = !DILocation(line: 347, column: 28, scope: !2235)
!2281 = !DILocation(line: 347, column: 43, scope: !2235)
!2282 = !DILocation(line: 347, column: 54, scope: !2235)
!2283 = !DILocation(line: 346, column: 10, scope: !2235)
!2284 = !DILocation(line: 346, column: 8, scope: !2235)
!2285 = !DILocation(line: 348, column: 8, scope: !2286)
!2286 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 348, column: 8)
!2287 = !DILocation(line: 348, column: 14, scope: !2286)
!2288 = !DILocation(line: 348, column: 8, scope: !2235)
!2289 = !DILocation(line: 348, column: 24, scope: !2286)
!2290 = !DILocation(line: 350, column: 8, scope: !2291)
!2291 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 350, column: 8)
!2292 = !DILocation(line: 350, column: 18, scope: !2291)
!2293 = !DILocation(line: 350, column: 8, scope: !2235)
!2294 = !DILocation(line: 350, column: 34, scope: !2291)
!2295 = !DILocation(line: 350, column: 24, scope: !2291)
!2296 = !DILocation(line: 352, column: 4, scope: !2235)
!2297 = !DILocation(line: 354, column: 18, scope: !2298)
!2298 = distinct !DILexicalBlock(scope: !2299, file: !3, line: 354, column: 11)
!2299 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 352, column: 17)
!2300 = !DILocation(line: 354, column: 11, scope: !2298)
!2301 = !DILocation(line: 354, column: 11, scope: !2299)
!2302 = !DILocation(line: 354, column: 27, scope: !2298)
!2303 = !DILocation(line: 355, column: 23, scope: !2299)
!2304 = !DILocation(line: 355, column: 50, scope: !2299)
!2305 = !DILocation(line: 355, column: 15, scope: !2299)
!2306 = !DILocation(line: 355, column: 13, scope: !2299)
!2307 = !DILocation(line: 356, column: 18, scope: !2308)
!2308 = distinct !DILexicalBlock(scope: !2299, file: !3, line: 356, column: 11)
!2309 = !DILocation(line: 356, column: 11, scope: !2308)
!2310 = !DILocation(line: 356, column: 11, scope: !2299)
!2311 = !DILocation(line: 356, column: 27, scope: !2308)
!2312 = !DILocation(line: 357, column: 11, scope: !2313)
!2313 = distinct !DILexicalBlock(scope: !2299, file: !3, line: 357, column: 11)
!2314 = !DILocation(line: 357, column: 17, scope: !2313)
!2315 = !DILocation(line: 357, column: 11, scope: !2299)
!2316 = !DILocation(line: 357, column: 44, scope: !2313)
!2317 = !DILocation(line: 357, column: 56, scope: !2313)
!2318 = !DILocation(line: 357, column: 62, scope: !2313)
!2319 = !DILocation(line: 357, column: 22, scope: !2313)
!2320 = !DILocation(line: 358, column: 11, scope: !2321)
!2321 = distinct !DILexicalBlock(scope: !2299, file: !3, line: 358, column: 11)
!2322 = !DILocation(line: 358, column: 17, scope: !2321)
!2323 = !DILocation(line: 358, column: 11, scope: !2299)
!2324 = !DILocation(line: 358, column: 27, scope: !2321)
!2325 = distinct !{!2325, !2296, !2326}
!2326 = !DILocation(line: 360, column: 4, scope: !2235)
!2327 = !DILocation(line: 362, column: 33, scope: !2235)
!2328 = !DILocation(line: 362, column: 4, scope: !2235)
!2329 = !DILocation(line: 365, column: 8, scope: !2330)
!2330 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 365, column: 8)
!2331 = !DILocation(line: 365, column: 14, scope: !2330)
!2332 = !DILocation(line: 365, column: 8, scope: !2235)
!2333 = !DILocation(line: 365, column: 24, scope: !2330)
!2334 = !DILocation(line: 367, column: 15, scope: !2335)
!2335 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 367, column: 8)
!2336 = !DILocation(line: 367, column: 8, scope: !2335)
!2337 = !DILocation(line: 367, column: 8, scope: !2235)
!2338 = !DILocation(line: 367, column: 25, scope: !2335)
!2339 = !DILocation(line: 368, column: 19, scope: !2235)
!2340 = !DILocation(line: 368, column: 10, scope: !2235)
!2341 = !DILocation(line: 368, column: 8, scope: !2235)
!2342 = !DILocation(line: 369, column: 8, scope: !2343)
!2343 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 369, column: 8)
!2344 = !DILocation(line: 369, column: 12, scope: !2343)
!2345 = !DILocation(line: 369, column: 8, scope: !2235)
!2346 = !DILocation(line: 369, column: 20, scope: !2343)
!2347 = !DILocation(line: 370, column: 8, scope: !2348)
!2348 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 370, column: 8)
!2349 = !DILocation(line: 370, column: 19, scope: !2348)
!2350 = !DILocation(line: 370, column: 16, scope: !2348)
!2351 = !DILocation(line: 370, column: 8, scope: !2235)
!2352 = !DILocalVariable(name: "fd", scope: !2353, file: !3, line: 371, type: !28)
!2353 = distinct !DILexicalBlock(scope: !2348, file: !3, line: 370, column: 27)
!2354 = !DILocation(line: 371, column: 13, scope: !2353)
!2355 = !DILocation(line: 371, column: 27, scope: !2353)
!2356 = !DILocation(line: 371, column: 18, scope: !2353)
!2357 = !DILocation(line: 372, column: 11, scope: !2358)
!2358 = distinct !DILexicalBlock(scope: !2353, file: !3, line: 372, column: 11)
!2359 = !DILocation(line: 372, column: 14, scope: !2358)
!2360 = !DILocation(line: 372, column: 11, scope: !2353)
!2361 = !DILocation(line: 372, column: 19, scope: !2358)
!2362 = !DILocation(line: 373, column: 40, scope: !2353)
!2363 = !DILocation(line: 373, column: 7, scope: !2353)
!2364 = !DILocation(line: 374, column: 22, scope: !2353)
!2365 = !DILocation(line: 374, column: 13, scope: !2353)
!2366 = !DILocation(line: 374, column: 11, scope: !2353)
!2367 = !DILocation(line: 375, column: 30, scope: !2353)
!2368 = !DILocation(line: 376, column: 11, scope: !2369)
!2369 = distinct !DILexicalBlock(scope: !2353, file: !3, line: 376, column: 11)
!2370 = !DILocation(line: 376, column: 15, scope: !2369)
!2371 = !DILocation(line: 376, column: 11, scope: !2353)
!2372 = !DILocation(line: 376, column: 23, scope: !2369)
!2373 = !DILocation(line: 377, column: 4, scope: !2353)
!2374 = !DILocation(line: 378, column: 27, scope: !2235)
!2375 = !DILocation(line: 379, column: 15, scope: !2376)
!2376 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 379, column: 8)
!2377 = !DILocation(line: 379, column: 8, scope: !2376)
!2378 = !DILocation(line: 379, column: 8, scope: !2235)
!2379 = !DILocation(line: 379, column: 24, scope: !2376)
!2380 = !DILocation(line: 380, column: 19, scope: !2235)
!2381 = !DILocation(line: 380, column: 10, scope: !2235)
!2382 = !DILocation(line: 380, column: 8, scope: !2235)
!2383 = !DILocation(line: 381, column: 8, scope: !2384)
!2384 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 381, column: 8)
!2385 = !DILocation(line: 381, column: 12, scope: !2384)
!2386 = !DILocation(line: 381, column: 8, scope: !2235)
!2387 = !DILocation(line: 381, column: 20, scope: !2384)
!2388 = !DILocation(line: 383, column: 8, scope: !2389)
!2389 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 383, column: 8)
!2390 = !DILocation(line: 383, column: 18, scope: !2389)
!2391 = !DILocation(line: 383, column: 8, scope: !2235)
!2392 = !DILocation(line: 384, column: 11, scope: !2393)
!2393 = distinct !DILexicalBlock(scope: !2394, file: !3, line: 384, column: 11)
!2394 = distinct !DILexicalBlock(scope: !2389, file: !3, line: 383, column: 24)
!2395 = !DILocation(line: 384, column: 26, scope: !2393)
!2396 = !DILocation(line: 384, column: 31, scope: !2393)
!2397 = !DILocation(line: 384, column: 34, scope: !2393)
!2398 = !DILocation(line: 384, column: 49, scope: !2393)
!2399 = !DILocation(line: 384, column: 11, scope: !2394)
!2400 = !DILocation(line: 385, column: 13, scope: !2401)
!2401 = distinct !DILexicalBlock(scope: !2393, file: !3, line: 384, column: 55)
!2402 = !DILocation(line: 385, column: 3, scope: !2401)
!2403 = !DILocation(line: 386, column: 7, scope: !2401)
!2404 = !DILocalVariable(name: "buf_nin", scope: !2405, file: !3, line: 387, type: !2406)
!2405 = distinct !DILexicalBlock(scope: !2393, file: !3, line: 386, column: 14)
!2406 = !DICompositeType(tag: DW_TAG_array_type, baseType: !25, size: 256, elements: !2407)
!2407 = !{!2408}
!2408 = !DISubrange(count: 32)
!2409 = !DILocation(line: 387, column: 10, scope: !2405)
!2410 = !DILocalVariable(name: "buf_nout", scope: !2405, file: !3, line: 387, type: !2406)
!2411 = !DILocation(line: 387, column: 23, scope: !2405)
!2412 = !DILocalVariable(name: "nbytes_in", scope: !2405, file: !3, line: 388, type: !2413)
!2413 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt64", file: !3, line: 236, baseType: !2414)
!2414 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !3, line: 235, size: 64, elements: !2415)
!2415 = !{!2416}
!2416 = !DIDerivedType(tag: DW_TAG_member, name: "b", scope: !2414, file: !3, line: 235, baseType: !2417, size: 64)
!2417 = !DICompositeType(tag: DW_TAG_array_type, baseType: !41, size: 64, elements: !2418)
!2418 = !{!2419}
!2419 = !DISubrange(count: 8)
!2420 = !DILocation(line: 388, column: 10, scope: !2405)
!2421 = !DILocalVariable(name: "nbytes_out", scope: !2405, file: !3, line: 388, type: !2413)
!2422 = !DILocation(line: 388, column: 23, scope: !2405)
!2423 = !DILocalVariable(name: "nbytes_in_d", scope: !2405, file: !3, line: 389, type: !42)
!2424 = !DILocation(line: 389, column: 10, scope: !2405)
!2425 = !DILocalVariable(name: "nbytes_out_d", scope: !2405, file: !3, line: 389, type: !42)
!2426 = !DILocation(line: 389, column: 23, scope: !2405)
!2427 = !DILocation(line: 391, column: 11, scope: !2405)
!2428 = !DILocation(line: 391, column: 27, scope: !2405)
!2429 = !DILocation(line: 390, column: 3, scope: !2405)
!2430 = !DILocation(line: 393, column: 11, scope: !2405)
!2431 = !DILocation(line: 393, column: 28, scope: !2405)
!2432 = !DILocation(line: 392, column: 3, scope: !2405)
!2433 = !DILocation(line: 394, column: 18, scope: !2405)
!2434 = !DILocation(line: 394, column: 16, scope: !2405)
!2435 = !DILocation(line: 395, column: 18, scope: !2405)
!2436 = !DILocation(line: 395, column: 16, scope: !2405)
!2437 = !DILocation(line: 396, column: 20, scope: !2405)
!2438 = !DILocation(line: 396, column: 3, scope: !2405)
!2439 = !DILocation(line: 397, column: 20, scope: !2405)
!2440 = !DILocation(line: 397, column: 3, scope: !2405)
!2441 = !DILocation(line: 398, column: 13, scope: !2405)
!2442 = !DILocation(line: 400, column: 6, scope: !2405)
!2443 = !DILocation(line: 400, column: 20, scope: !2405)
!2444 = !DILocation(line: 400, column: 18, scope: !2405)
!2445 = !DILocation(line: 401, column: 13, scope: !2405)
!2446 = !DILocation(line: 401, column: 11, scope: !2405)
!2447 = !DILocation(line: 401, column: 29, scope: !2405)
!2448 = !DILocation(line: 401, column: 27, scope: !2405)
!2449 = !DILocation(line: 402, column: 21, scope: !2405)
!2450 = !DILocation(line: 402, column: 36, scope: !2405)
!2451 = !DILocation(line: 402, column: 34, scope: !2405)
!2452 = !DILocation(line: 402, column: 19, scope: !2405)
!2453 = !DILocation(line: 402, column: 12, scope: !2405)
!2454 = !DILocation(line: 403, column: 6, scope: !2405)
!2455 = !DILocation(line: 404, column: 6, scope: !2405)
!2456 = !DILocation(line: 398, column: 3, scope: !2405)
!2457 = !DILocation(line: 407, column: 4, scope: !2394)
!2458 = !DILocation(line: 409, column: 4, scope: !2235)
!2459 = !DILabel(scope: !2235, name: "errhandler", file: !3, line: 411)
!2460 = !DILocation(line: 411, column: 4, scope: !2235)
!2461 = !DILocation(line: 412, column: 39, scope: !2235)
!2462 = !DILocation(line: 412, column: 4, scope: !2235)
!2463 = !DILocation(line: 415, column: 12, scope: !2235)
!2464 = !DILocation(line: 415, column: 4, scope: !2235)
!2465 = !DILocation(line: 417, column: 10, scope: !2466)
!2466 = distinct !DILexicalBlock(scope: !2235, file: !3, line: 415, column: 19)
!2467 = !DILocation(line: 419, column: 10, scope: !2466)
!2468 = !DILabel(scope: !2466, name: "errhandler_io", file: !3, line: 421)
!2469 = !DILocation(line: 421, column: 10, scope: !2466)
!2470 = !DILocation(line: 422, column: 10, scope: !2466)
!2471 = !DILocation(line: 424, column: 10, scope: !2466)
!2472 = distinct !DISubprogram(name: "applySavedTimeInfoToOutputFile", scope: !3, file: !3, line: 1059, type: !1036, scopeLine: 1060, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2473 = !DILocalVariable(name: "dstName", arg: 1, scope: !2472, file: !3, line: 1059, type: !24)
!2474 = !DILocation(line: 1059, column: 45, scope: !2472)
!2475 = !DILocalVariable(name: "retVal", scope: !2472, file: !3, line: 1062, type: !200)
!2476 = !DILocation(line: 1062, column: 19, scope: !2472)
!2477 = !DILocalVariable(name: "uTimBuf", scope: !2472, file: !3, line: 1063, type: !2478)
!2478 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "utimbuf", file: !2479, line: 37, size: 128, elements: !2480)
!2479 = !DIFile(filename: "/usr/include/utime.h", directory: "")
!2480 = !{!2481, !2482}
!2481 = !DIDerivedType(tag: DW_TAG_member, name: "actime", scope: !2478, file: !2479, line: 39, baseType: !184, size: 64)
!2482 = !DIDerivedType(tag: DW_TAG_member, name: "modtime", scope: !2478, file: !2479, line: 40, baseType: !184, size: 64, offset: 64)
!2483 = !DILocation(line: 1063, column: 19, scope: !2472)
!2484 = !DILocation(line: 1065, column: 34, scope: !2472)
!2485 = !DILocation(line: 1065, column: 12, scope: !2472)
!2486 = !DILocation(line: 1065, column: 19, scope: !2472)
!2487 = !DILocation(line: 1066, column: 35, scope: !2472)
!2488 = !DILocation(line: 1066, column: 12, scope: !2472)
!2489 = !DILocation(line: 1066, column: 20, scope: !2472)
!2490 = !DILocation(line: 1068, column: 21, scope: !2472)
!2491 = !DILocation(line: 1068, column: 13, scope: !2472)
!2492 = !DILocation(line: 1068, column: 11, scope: !2472)
!2493 = !DILocation(line: 1069, column: 4, scope: !2494)
!2494 = distinct !DILexicalBlock(scope: !2495, file: !3, line: 1069, column: 4)
!2495 = distinct !DILexicalBlock(scope: !2472, file: !3, line: 1069, column: 4)
!2496 = !DILocation(line: 1069, column: 4, scope: !2495)
!2497 = !DILocation(line: 1071, column: 1, scope: !2472)
!2498 = distinct !DISubprogram(name: "logCompressSize", scope: !3, file: !3, line: 792, type: !2499, scopeLine: 792, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2499 = !DISubroutineType(types: !2500)
!2500 = !{null, !29}
!2501 = !DILocalVariable(name: "sz", arg: 1, scope: !2498, file: !3, line: 792, type: !29)
!2502 = !DILocation(line: 792, column: 26, scope: !2498)
!2503 = !DILocalVariable(name: "tmp_sz", scope: !2498, file: !3, line: 793, type: !29)
!2504 = !DILocation(line: 793, column: 48, scope: !2498)
!2505 = !DILocation(line: 793, column: 5, scope: !2498)
!2506 = !DILocation(line: 793, column: 57, scope: !2498)
!2507 = !DILocation(line: 794, column: 9, scope: !2508)
!2508 = distinct !DILexicalBlock(scope: !2498, file: !3, line: 794, column: 9)
!2509 = !DILocation(line: 794, column: 16, scope: !2508)
!2510 = !DILocation(line: 794, column: 9, scope: !2498)
!2511 = !DILocation(line: 795, column: 17, scope: !2508)
!2512 = !DILocation(line: 795, column: 47, scope: !2508)
!2513 = !DILocation(line: 795, column: 9, scope: !2508)
!2514 = !DILocation(line: 796, column: 1, scope: !2498)
!2515 = distinct !DISubprogram(name: "ioError", scope: !3, file: !3, line: 800, type: !1029, scopeLine: 801, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2516 = !DILocation(line: 802, column: 14, scope: !2515)
!2517 = !DILocation(line: 805, column: 14, scope: !2515)
!2518 = !DILocation(line: 802, column: 4, scope: !2515)
!2519 = !DILocation(line: 806, column: 13, scope: !2515)
!2520 = !DILocation(line: 806, column: 4, scope: !2515)
!2521 = !DILocation(line: 807, column: 4, scope: !2515)
!2522 = !DILocation(line: 808, column: 4, scope: !2515)
!2523 = distinct !DISubprogram(name: "myfeof", scope: !3, file: !3, line: 320, type: !2524, scopeLine: 321, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2524 = !DISubroutineType(types: !2525)
!2525 = !{!22, !97}
!2526 = !DILocalVariable(name: "f", arg: 1, scope: !2523, file: !3, line: 320, type: !97)
!2527 = !DILocation(line: 320, column: 21, scope: !2523)
!2528 = !DILocalVariable(name: "c", scope: !2523, file: !3, line: 322, type: !28)
!2529 = !DILocation(line: 322, column: 10, scope: !2523)
!2530 = !DILocation(line: 322, column: 22, scope: !2523)
!2531 = !DILocation(line: 322, column: 14, scope: !2523)
!2532 = !DILocation(line: 323, column: 8, scope: !2533)
!2533 = distinct !DILexicalBlock(scope: !2523, file: !3, line: 323, column: 8)
!2534 = !DILocation(line: 323, column: 10, scope: !2533)
!2535 = !DILocation(line: 323, column: 8, scope: !2523)
!2536 = !DILocation(line: 323, column: 18, scope: !2533)
!2537 = !DILocation(line: 324, column: 13, scope: !2523)
!2538 = !DILocation(line: 324, column: 16, scope: !2523)
!2539 = !DILocation(line: 324, column: 4, scope: !2523)
!2540 = !DILocation(line: 325, column: 4, scope: !2523)
!2541 = !DILocation(line: 326, column: 1, scope: !2523)
!2542 = distinct !DISubprogram(name: "applySavedFileAttrToOutputFile", scope: !3, file: !3, line: 1074, type: !836, scopeLine: 1075, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2543 = !DILocalVariable(name: "fd", arg: 1, scope: !2542, file: !3, line: 1074, type: !200)
!2544 = !DILocation(line: 1074, column: 49, scope: !2542)
!2545 = !DILocalVariable(name: "retVal", scope: !2542, file: !3, line: 1077, type: !200)
!2546 = !DILocation(line: 1077, column: 14, scope: !2542)
!2547 = !DILocation(line: 1079, column: 22, scope: !2542)
!2548 = !DILocation(line: 1079, column: 39, scope: !2542)
!2549 = !DILocation(line: 1079, column: 13, scope: !2542)
!2550 = !DILocation(line: 1079, column: 11, scope: !2542)
!2551 = !DILocation(line: 1080, column: 4, scope: !2552)
!2552 = distinct !DILexicalBlock(scope: !2553, file: !3, line: 1080, column: 4)
!2553 = distinct !DILexicalBlock(scope: !2542, file: !3, line: 1080, column: 4)
!2554 = !DILocation(line: 1080, column: 4, scope: !2553)
!2555 = !DILocation(line: 1082, column: 20, scope: !2542)
!2556 = !DILocation(line: 1082, column: 37, scope: !2542)
!2557 = !DILocation(line: 1082, column: 58, scope: !2542)
!2558 = !DILocation(line: 1082, column: 11, scope: !2542)
!2559 = !DILocation(line: 1087, column: 1, scope: !2542)
!2560 = distinct !DISubprogram(name: "uInt64_from_UInt32s", scope: !3, file: !3, line: 240, type: !2561, scopeLine: 241, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2561 = !DISubroutineType(types: !2562)
!2562 = !{null, !2563, !2255, !2255}
!2563 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2413, size: 64)
!2564 = !DILocalVariable(name: "n", arg: 1, scope: !2560, file: !3, line: 240, type: !2563)
!2565 = !DILocation(line: 240, column: 36, scope: !2560)
!2566 = !DILocalVariable(name: "lo32", arg: 2, scope: !2560, file: !3, line: 240, type: !2255)
!2567 = !DILocation(line: 240, column: 46, scope: !2560)
!2568 = !DILocalVariable(name: "hi32", arg: 3, scope: !2560, file: !3, line: 240, type: !2255)
!2569 = !DILocation(line: 240, column: 59, scope: !2560)
!2570 = !DILocation(line: 242, column: 23, scope: !2560)
!2571 = !DILocation(line: 242, column: 28, scope: !2560)
!2572 = !DILocation(line: 242, column: 35, scope: !2560)
!2573 = !DILocation(line: 242, column: 14, scope: !2560)
!2574 = !DILocation(line: 242, column: 4, scope: !2560)
!2575 = !DILocation(line: 242, column: 7, scope: !2560)
!2576 = !DILocation(line: 242, column: 12, scope: !2560)
!2577 = !DILocation(line: 243, column: 23, scope: !2560)
!2578 = !DILocation(line: 243, column: 28, scope: !2560)
!2579 = !DILocation(line: 243, column: 35, scope: !2560)
!2580 = !DILocation(line: 243, column: 14, scope: !2560)
!2581 = !DILocation(line: 243, column: 4, scope: !2560)
!2582 = !DILocation(line: 243, column: 7, scope: !2560)
!2583 = !DILocation(line: 243, column: 12, scope: !2560)
!2584 = !DILocation(line: 244, column: 23, scope: !2560)
!2585 = !DILocation(line: 244, column: 28, scope: !2560)
!2586 = !DILocation(line: 244, column: 35, scope: !2560)
!2587 = !DILocation(line: 244, column: 14, scope: !2560)
!2588 = !DILocation(line: 244, column: 4, scope: !2560)
!2589 = !DILocation(line: 244, column: 7, scope: !2560)
!2590 = !DILocation(line: 244, column: 12, scope: !2560)
!2591 = !DILocation(line: 245, column: 23, scope: !2560)
!2592 = !DILocation(line: 245, column: 35, scope: !2560)
!2593 = !DILocation(line: 245, column: 14, scope: !2560)
!2594 = !DILocation(line: 245, column: 4, scope: !2560)
!2595 = !DILocation(line: 245, column: 7, scope: !2560)
!2596 = !DILocation(line: 245, column: 12, scope: !2560)
!2597 = !DILocation(line: 246, column: 23, scope: !2560)
!2598 = !DILocation(line: 246, column: 28, scope: !2560)
!2599 = !DILocation(line: 246, column: 35, scope: !2560)
!2600 = !DILocation(line: 246, column: 14, scope: !2560)
!2601 = !DILocation(line: 246, column: 4, scope: !2560)
!2602 = !DILocation(line: 246, column: 7, scope: !2560)
!2603 = !DILocation(line: 246, column: 12, scope: !2560)
!2604 = !DILocation(line: 247, column: 23, scope: !2560)
!2605 = !DILocation(line: 247, column: 28, scope: !2560)
!2606 = !DILocation(line: 247, column: 35, scope: !2560)
!2607 = !DILocation(line: 247, column: 14, scope: !2560)
!2608 = !DILocation(line: 247, column: 4, scope: !2560)
!2609 = !DILocation(line: 247, column: 7, scope: !2560)
!2610 = !DILocation(line: 247, column: 12, scope: !2560)
!2611 = !DILocation(line: 248, column: 23, scope: !2560)
!2612 = !DILocation(line: 248, column: 28, scope: !2560)
!2613 = !DILocation(line: 248, column: 35, scope: !2560)
!2614 = !DILocation(line: 248, column: 14, scope: !2560)
!2615 = !DILocation(line: 248, column: 4, scope: !2560)
!2616 = !DILocation(line: 248, column: 7, scope: !2560)
!2617 = !DILocation(line: 248, column: 12, scope: !2560)
!2618 = !DILocation(line: 249, column: 23, scope: !2560)
!2619 = !DILocation(line: 249, column: 35, scope: !2560)
!2620 = !DILocation(line: 249, column: 14, scope: !2560)
!2621 = !DILocation(line: 249, column: 4, scope: !2560)
!2622 = !DILocation(line: 249, column: 7, scope: !2560)
!2623 = !DILocation(line: 249, column: 12, scope: !2560)
!2624 = !DILocation(line: 250, column: 1, scope: !2560)
!2625 = distinct !DISubprogram(name: "uInt64_to_double", scope: !3, file: !3, line: 254, type: !2626, scopeLine: 255, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2626 = !DISubroutineType(types: !2627)
!2627 = !{!42, !2563}
!2628 = !DILocalVariable(name: "n", arg: 1, scope: !2625, file: !3, line: 254, type: !2563)
!2629 = !DILocation(line: 254, column: 35, scope: !2625)
!2630 = !DILocalVariable(name: "i", scope: !2625, file: !3, line: 256, type: !28)
!2631 = !DILocation(line: 256, column: 11, scope: !2625)
!2632 = !DILocalVariable(name: "base", scope: !2625, file: !3, line: 257, type: !42)
!2633 = !DILocation(line: 257, column: 11, scope: !2625)
!2634 = !DILocalVariable(name: "sum", scope: !2625, file: !3, line: 258, type: !42)
!2635 = !DILocation(line: 258, column: 11, scope: !2625)
!2636 = !DILocation(line: 259, column: 11, scope: !2637)
!2637 = distinct !DILexicalBlock(scope: !2625, file: !3, line: 259, column: 4)
!2638 = !DILocation(line: 259, column: 9, scope: !2637)
!2639 = !DILocation(line: 259, column: 16, scope: !2640)
!2640 = distinct !DILexicalBlock(scope: !2637, file: !3, line: 259, column: 4)
!2641 = !DILocation(line: 259, column: 18, scope: !2640)
!2642 = !DILocation(line: 259, column: 4, scope: !2637)
!2643 = !DILocation(line: 260, column: 15, scope: !2644)
!2644 = distinct !DILexicalBlock(scope: !2640, file: !3, line: 259, column: 28)
!2645 = !DILocation(line: 260, column: 31, scope: !2644)
!2646 = !DILocation(line: 260, column: 34, scope: !2644)
!2647 = !DILocation(line: 260, column: 36, scope: !2644)
!2648 = !DILocation(line: 260, column: 22, scope: !2644)
!2649 = !DILocation(line: 260, column: 20, scope: !2644)
!2650 = !DILocation(line: 260, column: 12, scope: !2644)
!2651 = !DILocation(line: 261, column: 12, scope: !2644)
!2652 = !DILocation(line: 262, column: 4, scope: !2644)
!2653 = !DILocation(line: 259, column: 24, scope: !2640)
!2654 = !DILocation(line: 259, column: 4, scope: !2640)
!2655 = distinct !{!2655, !2642, !2656}
!2656 = !DILocation(line: 262, column: 4, scope: !2637)
!2657 = !DILocation(line: 263, column: 11, scope: !2625)
!2658 = !DILocation(line: 263, column: 4, scope: !2625)
!2659 = distinct !DISubprogram(name: "uInt64_toAscii", scope: !3, file: !3, line: 297, type: !2660, scopeLine: 298, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2660 = !DISubroutineType(types: !2661)
!2661 = !{null, !105, !2563}
!2662 = !DILocalVariable(name: "outbuf", arg: 1, scope: !2659, file: !3, line: 297, type: !105)
!2663 = !DILocation(line: 297, column: 29, scope: !2659)
!2664 = !DILocalVariable(name: "n", arg: 2, scope: !2659, file: !3, line: 297, type: !2563)
!2665 = !DILocation(line: 297, column: 45, scope: !2659)
!2666 = !DILocalVariable(name: "i", scope: !2659, file: !3, line: 299, type: !28)
!2667 = !DILocation(line: 299, column: 11, scope: !2659)
!2668 = !DILocalVariable(name: "q", scope: !2659, file: !3, line: 299, type: !28)
!2669 = !DILocation(line: 299, column: 14, scope: !2659)
!2670 = !DILocalVariable(name: "buf", scope: !2659, file: !3, line: 300, type: !2671)
!2671 = !DICompositeType(tag: DW_TAG_array_type, baseType: !41, size: 256, elements: !2407)
!2672 = !DILocation(line: 300, column: 11, scope: !2659)
!2673 = !DILocalVariable(name: "nBuf", scope: !2659, file: !3, line: 301, type: !28)
!2674 = !DILocation(line: 301, column: 11, scope: !2659)
!2675 = !DILocalVariable(name: "n_copy", scope: !2659, file: !3, line: 302, type: !2413)
!2676 = !DILocation(line: 302, column: 11, scope: !2659)
!2677 = !DILocation(line: 302, column: 21, scope: !2659)
!2678 = !DILocation(line: 302, column: 20, scope: !2659)
!2679 = !DILocation(line: 303, column: 4, scope: !2659)
!2680 = !DILocation(line: 304, column: 11, scope: !2681)
!2681 = distinct !DILexicalBlock(scope: !2659, file: !3, line: 303, column: 7)
!2682 = !DILocation(line: 304, column: 9, scope: !2681)
!2683 = !DILocation(line: 305, column: 19, scope: !2681)
!2684 = !DILocation(line: 305, column: 21, scope: !2681)
!2685 = !DILocation(line: 305, column: 11, scope: !2681)
!2686 = !DILocation(line: 305, column: 7, scope: !2681)
!2687 = !DILocation(line: 305, column: 17, scope: !2681)
!2688 = !DILocation(line: 306, column: 11, scope: !2681)
!2689 = !DILocation(line: 307, column: 4, scope: !2681)
!2690 = !DILocation(line: 307, column: 14, scope: !2659)
!2691 = !DILocation(line: 307, column: 13, scope: !2659)
!2692 = distinct !{!2692, !2679, !2693}
!2693 = !DILocation(line: 307, column: 36, scope: !2659)
!2694 = !DILocation(line: 308, column: 4, scope: !2659)
!2695 = !DILocation(line: 308, column: 11, scope: !2659)
!2696 = !DILocation(line: 308, column: 17, scope: !2659)
!2697 = !DILocation(line: 309, column: 11, scope: !2698)
!2698 = distinct !DILexicalBlock(scope: !2659, file: !3, line: 309, column: 4)
!2699 = !DILocation(line: 309, column: 9, scope: !2698)
!2700 = !DILocation(line: 309, column: 16, scope: !2701)
!2701 = distinct !DILexicalBlock(scope: !2698, file: !3, line: 309, column: 4)
!2702 = !DILocation(line: 309, column: 20, scope: !2701)
!2703 = !DILocation(line: 309, column: 18, scope: !2701)
!2704 = !DILocation(line: 309, column: 4, scope: !2698)
!2705 = !DILocation(line: 310, column: 23, scope: !2701)
!2706 = !DILocation(line: 310, column: 28, scope: !2701)
!2707 = !DILocation(line: 310, column: 27, scope: !2701)
!2708 = !DILocation(line: 310, column: 29, scope: !2701)
!2709 = !DILocation(line: 310, column: 19, scope: !2701)
!2710 = !DILocation(line: 310, column: 7, scope: !2701)
!2711 = !DILocation(line: 310, column: 14, scope: !2701)
!2712 = !DILocation(line: 310, column: 17, scope: !2701)
!2713 = !DILocation(line: 309, column: 27, scope: !2701)
!2714 = !DILocation(line: 309, column: 4, scope: !2701)
!2715 = distinct !{!2715, !2704, !2716}
!2716 = !DILocation(line: 310, column: 31, scope: !2698)
!2717 = !DILocation(line: 311, column: 1, scope: !2659)
!2718 = distinct !DISubprogram(name: "configError", scope: !3, file: !3, line: 893, type: !1029, scopeLine: 894, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2719 = !DILocation(line: 895, column: 14, scope: !2718)
!2720 = !DILocation(line: 895, column: 4, scope: !2718)
!2721 = !DILocation(line: 901, column: 4, scope: !2718)
!2722 = !DILocation(line: 902, column: 9, scope: !2718)
!2723 = !DILocation(line: 902, column: 4, scope: !2718)
!2724 = distinct !DISubprogram(name: "uInt64_qrm10", scope: !3, file: !3, line: 279, type: !2725, scopeLine: 280, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2725 = !DISubroutineType(types: !2726)
!2726 = !{!28, !2563}
!2727 = !DILocalVariable(name: "n", arg: 1, scope: !2724, file: !3, line: 279, type: !2563)
!2728 = !DILocation(line: 279, column: 30, scope: !2724)
!2729 = !DILocalVariable(name: "rem", scope: !2724, file: !3, line: 281, type: !2255)
!2730 = !DILocation(line: 281, column: 11, scope: !2724)
!2731 = !DILocalVariable(name: "tmp", scope: !2724, file: !3, line: 281, type: !2255)
!2732 = !DILocation(line: 281, column: 16, scope: !2724)
!2733 = !DILocalVariable(name: "i", scope: !2724, file: !3, line: 282, type: !28)
!2734 = !DILocation(line: 282, column: 11, scope: !2724)
!2735 = !DILocation(line: 283, column: 8, scope: !2724)
!2736 = !DILocation(line: 284, column: 11, scope: !2737)
!2737 = distinct !DILexicalBlock(scope: !2724, file: !3, line: 284, column: 4)
!2738 = !DILocation(line: 284, column: 9, scope: !2737)
!2739 = !DILocation(line: 284, column: 16, scope: !2740)
!2740 = distinct !DILexicalBlock(scope: !2737, file: !3, line: 284, column: 4)
!2741 = !DILocation(line: 284, column: 18, scope: !2740)
!2742 = !DILocation(line: 284, column: 4, scope: !2737)
!2743 = !DILocation(line: 285, column: 13, scope: !2744)
!2744 = distinct !DILexicalBlock(scope: !2740, file: !3, line: 284, column: 29)
!2745 = !DILocation(line: 285, column: 17, scope: !2744)
!2746 = !DILocation(line: 285, column: 25, scope: !2744)
!2747 = !DILocation(line: 285, column: 28, scope: !2744)
!2748 = !DILocation(line: 285, column: 30, scope: !2744)
!2749 = !DILocation(line: 285, column: 23, scope: !2744)
!2750 = !DILocation(line: 285, column: 11, scope: !2744)
!2751 = !DILocation(line: 286, column: 17, scope: !2744)
!2752 = !DILocation(line: 286, column: 21, scope: !2744)
!2753 = !DILocation(line: 286, column: 7, scope: !2744)
!2754 = !DILocation(line: 286, column: 10, scope: !2744)
!2755 = !DILocation(line: 286, column: 12, scope: !2744)
!2756 = !DILocation(line: 286, column: 15, scope: !2744)
!2757 = !DILocation(line: 287, column: 13, scope: !2744)
!2758 = !DILocation(line: 287, column: 17, scope: !2744)
!2759 = !DILocation(line: 287, column: 11, scope: !2744)
!2760 = !DILocation(line: 288, column: 4, scope: !2744)
!2761 = !DILocation(line: 284, column: 25, scope: !2740)
!2762 = !DILocation(line: 284, column: 4, scope: !2740)
!2763 = distinct !{!2763, !2742, !2764}
!2764 = !DILocation(line: 288, column: 4, scope: !2737)
!2765 = !DILocation(line: 289, column: 11, scope: !2724)
!2766 = !DILocation(line: 289, column: 4, scope: !2724)
!2767 = distinct !DISubprogram(name: "uInt64_isZero", scope: !3, file: !3, line: 268, type: !2768, scopeLine: 269, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2768 = !DISubroutineType(types: !2769)
!2769 = !{!22, !2563}
!2770 = !DILocalVariable(name: "n", arg: 1, scope: !2767, file: !3, line: 268, type: !2563)
!2771 = !DILocation(line: 268, column: 30, scope: !2767)
!2772 = !DILocalVariable(name: "i", scope: !2767, file: !3, line: 270, type: !28)
!2773 = !DILocation(line: 270, column: 10, scope: !2767)
!2774 = !DILocation(line: 271, column: 11, scope: !2775)
!2775 = distinct !DILexicalBlock(scope: !2767, file: !3, line: 271, column: 4)
!2776 = !DILocation(line: 271, column: 9, scope: !2775)
!2777 = !DILocation(line: 271, column: 16, scope: !2778)
!2778 = distinct !DILexicalBlock(scope: !2775, file: !3, line: 271, column: 4)
!2779 = !DILocation(line: 271, column: 18, scope: !2778)
!2780 = !DILocation(line: 271, column: 4, scope: !2775)
!2781 = !DILocation(line: 272, column: 11, scope: !2782)
!2782 = distinct !DILexicalBlock(scope: !2778, file: !3, line: 272, column: 11)
!2783 = !DILocation(line: 272, column: 14, scope: !2782)
!2784 = !DILocation(line: 272, column: 16, scope: !2782)
!2785 = !DILocation(line: 272, column: 19, scope: !2782)
!2786 = !DILocation(line: 272, column: 11, scope: !2778)
!2787 = !DILocation(line: 272, column: 25, scope: !2782)
!2788 = !DILocation(line: 272, column: 22, scope: !2782)
!2789 = !DILocation(line: 271, column: 24, scope: !2778)
!2790 = !DILocation(line: 271, column: 4, scope: !2778)
!2791 = distinct !{!2791, !2780, !2792}
!2792 = !DILocation(line: 272, column: 32, scope: !2775)
!2793 = !DILocation(line: 273, column: 4, scope: !2767)
!2794 = !DILocation(line: 274, column: 1, scope: !2767)
!2795 = distinct !DISubprogram(name: "mapSuffix", scope: !3, file: !3, line: 1129, type: !2796, scopeLine: 1132, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2796 = !DISubroutineType(types: !2797)
!2797 = !{!22, !24, !48, !48}
!2798 = !DILocalVariable(name: "name", arg: 1, scope: !2795, file: !3, line: 1129, type: !24)
!2799 = !DILocation(line: 1129, column: 24, scope: !2795)
!2800 = !DILocalVariable(name: "oldSuffix", arg: 2, scope: !2795, file: !3, line: 1130, type: !48)
!2801 = !DILocation(line: 1130, column: 30, scope: !2795)
!2802 = !DILocalVariable(name: "newSuffix", arg: 3, scope: !2795, file: !3, line: 1131, type: !48)
!2803 = !DILocation(line: 1131, column: 30, scope: !2795)
!2804 = !DILocation(line: 1133, column: 19, scope: !2805)
!2805 = distinct !DILexicalBlock(scope: !2795, file: !3, line: 1133, column: 8)
!2806 = !DILocation(line: 1133, column: 24, scope: !2805)
!2807 = !DILocation(line: 1133, column: 9, scope: !2805)
!2808 = !DILocation(line: 1133, column: 8, scope: !2795)
!2809 = !DILocation(line: 1133, column: 36, scope: !2805)
!2810 = !DILocation(line: 1134, column: 4, scope: !2795)
!2811 = !DILocation(line: 1134, column: 16, scope: !2795)
!2812 = !DILocation(line: 1134, column: 9, scope: !2795)
!2813 = !DILocation(line: 1134, column: 29, scope: !2795)
!2814 = !DILocation(line: 1134, column: 22, scope: !2795)
!2815 = !DILocation(line: 1134, column: 21, scope: !2795)
!2816 = !DILocation(line: 1134, column: 41, scope: !2795)
!2817 = !DILocation(line: 1135, column: 13, scope: !2795)
!2818 = !DILocation(line: 1135, column: 19, scope: !2795)
!2819 = !DILocation(line: 1135, column: 4, scope: !2795)
!2820 = !DILocation(line: 1136, column: 4, scope: !2795)
!2821 = !DILocation(line: 1137, column: 1, scope: !2795)
!2822 = distinct !DISubprogram(name: "uncompressStream", scope: !3, file: !3, line: 435, type: !2823, scopeLine: 436, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!2823 = !DISubroutineType(types: !2824)
!2824 = !{!22, !97, !97}
!2825 = !DILocalVariable(name: "zStream", arg: 1, scope: !2822, file: !3, line: 435, type: !97)
!2826 = !DILocation(line: 435, column: 31, scope: !2822)
!2827 = !DILocalVariable(name: "stream", arg: 2, scope: !2822, file: !3, line: 435, type: !97)
!2828 = !DILocation(line: 435, column: 46, scope: !2822)
!2829 = !DILocalVariable(name: "bzf", scope: !2822, file: !3, line: 437, type: !2243)
!2830 = !DILocation(line: 437, column: 12, scope: !2822)
!2831 = !DILocalVariable(name: "bzerr", scope: !2822, file: !3, line: 438, type: !28)
!2832 = !DILocation(line: 438, column: 12, scope: !2822)
!2833 = !DILocalVariable(name: "bzerr_dummy", scope: !2822, file: !3, line: 438, type: !28)
!2834 = !DILocation(line: 438, column: 19, scope: !2822)
!2835 = !DILocalVariable(name: "ret", scope: !2822, file: !3, line: 438, type: !28)
!2836 = !DILocation(line: 438, column: 32, scope: !2822)
!2837 = !DILocalVariable(name: "nread", scope: !2822, file: !3, line: 438, type: !28)
!2838 = !DILocation(line: 438, column: 37, scope: !2822)
!2839 = !DILocalVariable(name: "streamNo", scope: !2822, file: !3, line: 438, type: !28)
!2840 = !DILocation(line: 438, column: 44, scope: !2822)
!2841 = !DILocalVariable(name: "i", scope: !2822, file: !3, line: 438, type: !28)
!2842 = !DILocation(line: 438, column: 54, scope: !2822)
!2843 = !DILocalVariable(name: "obuf", scope: !2822, file: !3, line: 439, type: !2248)
!2844 = !DILocation(line: 439, column: 12, scope: !2822)
!2845 = !DILocalVariable(name: "unused", scope: !2822, file: !3, line: 440, type: !2248)
!2846 = !DILocation(line: 440, column: 12, scope: !2822)
!2847 = !DILocalVariable(name: "nUnused", scope: !2822, file: !3, line: 441, type: !28)
!2848 = !DILocation(line: 441, column: 12, scope: !2822)
!2849 = !DILocalVariable(name: "unusedTmpV", scope: !2822, file: !3, line: 442, type: !27)
!2850 = !DILocation(line: 442, column: 12, scope: !2822)
!2851 = !DILocalVariable(name: "unusedTmp", scope: !2822, file: !3, line: 443, type: !43)
!2852 = !DILocation(line: 443, column: 12, scope: !2822)
!2853 = !DILocation(line: 445, column: 12, scope: !2822)
!2854 = !DILocation(line: 446, column: 13, scope: !2822)
!2855 = !DILocation(line: 451, column: 15, scope: !2856)
!2856 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 451, column: 8)
!2857 = !DILocation(line: 451, column: 8, scope: !2856)
!2858 = !DILocation(line: 451, column: 8, scope: !2822)
!2859 = !DILocation(line: 451, column: 24, scope: !2856)
!2860 = !DILocation(line: 452, column: 15, scope: !2861)
!2861 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 452, column: 8)
!2862 = !DILocation(line: 452, column: 8, scope: !2861)
!2863 = !DILocation(line: 452, column: 8, scope: !2822)
!2864 = !DILocation(line: 452, column: 25, scope: !2861)
!2865 = !DILocation(line: 454, column: 4, scope: !2822)
!2866 = !DILocation(line: 457, column: 24, scope: !2867)
!2867 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 454, column: 17)
!2868 = !DILocation(line: 457, column: 33, scope: !2867)
!2869 = !DILocation(line: 458, column: 21, scope: !2867)
!2870 = !DILocation(line: 458, column: 16, scope: !2867)
!2871 = !DILocation(line: 458, column: 32, scope: !2867)
!2872 = !DILocation(line: 458, column: 40, scope: !2867)
!2873 = !DILocation(line: 456, column: 13, scope: !2867)
!2874 = !DILocation(line: 456, column: 11, scope: !2867)
!2875 = !DILocation(line: 460, column: 11, scope: !2876)
!2876 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 460, column: 11)
!2877 = !DILocation(line: 460, column: 15, scope: !2876)
!2878 = !DILocation(line: 460, column: 23, scope: !2876)
!2879 = !DILocation(line: 460, column: 26, scope: !2876)
!2880 = !DILocation(line: 460, column: 32, scope: !2876)
!2881 = !DILocation(line: 460, column: 11, scope: !2867)
!2882 = !DILocation(line: 460, column: 42, scope: !2876)
!2883 = !DILocation(line: 461, column: 15, scope: !2867)
!2884 = !DILocation(line: 463, column: 7, scope: !2867)
!2885 = !DILocation(line: 463, column: 14, scope: !2867)
!2886 = !DILocation(line: 463, column: 20, scope: !2867)
!2887 = !DILocation(line: 464, column: 39, scope: !2888)
!2888 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 463, column: 30)
!2889 = !DILocation(line: 464, column: 44, scope: !2888)
!2890 = !DILocation(line: 464, column: 18, scope: !2888)
!2891 = !DILocation(line: 464, column: 16, scope: !2888)
!2892 = !DILocation(line: 465, column: 14, scope: !2893)
!2893 = distinct !DILexicalBlock(scope: !2888, file: !3, line: 465, column: 14)
!2894 = !DILocation(line: 465, column: 20, scope: !2893)
!2895 = !DILocation(line: 465, column: 14, scope: !2888)
!2896 = !DILocation(line: 465, column: 44, scope: !2893)
!2897 = !DILocation(line: 466, column: 15, scope: !2898)
!2898 = distinct !DILexicalBlock(scope: !2888, file: !3, line: 466, column: 14)
!2899 = !DILocation(line: 466, column: 21, scope: !2898)
!2900 = !DILocation(line: 466, column: 30, scope: !2898)
!2901 = !DILocation(line: 466, column: 33, scope: !2898)
!2902 = !DILocation(line: 466, column: 39, scope: !2898)
!2903 = !DILocation(line: 466, column: 57, scope: !2898)
!2904 = !DILocation(line: 466, column: 60, scope: !2898)
!2905 = !DILocation(line: 466, column: 66, scope: !2898)
!2906 = !DILocation(line: 466, column: 14, scope: !2888)
!2907 = !DILocation(line: 467, column: 22, scope: !2898)
!2908 = !DILocation(line: 467, column: 43, scope: !2898)
!2909 = !DILocation(line: 467, column: 50, scope: !2898)
!2910 = !DILocation(line: 467, column: 13, scope: !2898)
!2911 = !DILocation(line: 468, column: 21, scope: !2912)
!2912 = distinct !DILexicalBlock(scope: !2888, file: !3, line: 468, column: 14)
!2913 = !DILocation(line: 468, column: 14, scope: !2912)
!2914 = !DILocation(line: 468, column: 14, scope: !2888)
!2915 = !DILocation(line: 468, column: 30, scope: !2912)
!2916 = distinct !{!2916, !2884, !2917}
!2917 = !DILocation(line: 469, column: 7, scope: !2867)
!2918 = !DILocation(line: 470, column: 11, scope: !2919)
!2919 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 470, column: 11)
!2920 = !DILocation(line: 470, column: 17, scope: !2919)
!2921 = !DILocation(line: 470, column: 11, scope: !2867)
!2922 = !DILocation(line: 470, column: 35, scope: !2919)
!2923 = !DILocation(line: 472, column: 37, scope: !2867)
!2924 = !DILocation(line: 472, column: 7, scope: !2867)
!2925 = !DILocation(line: 473, column: 11, scope: !2926)
!2926 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 473, column: 11)
!2927 = !DILocation(line: 473, column: 17, scope: !2926)
!2928 = !DILocation(line: 473, column: 11, scope: !2867)
!2929 = !DILocation(line: 473, column: 27, scope: !2926)
!2930 = !DILocation(line: 475, column: 27, scope: !2867)
!2931 = !DILocation(line: 475, column: 17, scope: !2867)
!2932 = !DILocation(line: 476, column: 14, scope: !2933)
!2933 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 476, column: 7)
!2934 = !DILocation(line: 476, column: 12, scope: !2933)
!2935 = !DILocation(line: 476, column: 19, scope: !2936)
!2936 = distinct !DILexicalBlock(scope: !2933, file: !3, line: 476, column: 7)
!2937 = !DILocation(line: 476, column: 23, scope: !2936)
!2938 = !DILocation(line: 476, column: 21, scope: !2936)
!2939 = !DILocation(line: 476, column: 7, scope: !2933)
!2940 = !DILocation(line: 476, column: 49, scope: !2936)
!2941 = !DILocation(line: 476, column: 59, scope: !2936)
!2942 = !DILocation(line: 476, column: 44, scope: !2936)
!2943 = !DILocation(line: 476, column: 37, scope: !2936)
!2944 = !DILocation(line: 476, column: 47, scope: !2936)
!2945 = !DILocation(line: 476, column: 33, scope: !2936)
!2946 = !DILocation(line: 476, column: 7, scope: !2936)
!2947 = distinct !{!2947, !2939, !2948}
!2948 = !DILocation(line: 476, column: 60, scope: !2933)
!2949 = !DILocation(line: 478, column: 33, scope: !2867)
!2950 = !DILocation(line: 478, column: 7, scope: !2867)
!2951 = !DILocation(line: 479, column: 11, scope: !2952)
!2952 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 479, column: 11)
!2953 = !DILocation(line: 479, column: 17, scope: !2952)
!2954 = !DILocation(line: 479, column: 11, scope: !2867)
!2955 = !DILocation(line: 479, column: 27, scope: !2952)
!2956 = !DILocation(line: 481, column: 11, scope: !2957)
!2957 = distinct !DILexicalBlock(scope: !2867, file: !3, line: 481, column: 11)
!2958 = !DILocation(line: 481, column: 19, scope: !2957)
!2959 = !DILocation(line: 481, column: 24, scope: !2957)
!2960 = !DILocation(line: 481, column: 34, scope: !2957)
!2961 = !DILocation(line: 481, column: 27, scope: !2957)
!2962 = !DILocation(line: 481, column: 11, scope: !2867)
!2963 = !DILocation(line: 481, column: 44, scope: !2957)
!2964 = distinct !{!2964, !2865, !2965}
!2965 = !DILocation(line: 482, column: 4, scope: !2822)
!2966 = !DILabel(scope: !2822, name: "closeok", file: !3, line: 484)
!2967 = !DILocation(line: 484, column: 4, scope: !2822)
!2968 = !DILocation(line: 485, column: 15, scope: !2969)
!2969 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 485, column: 8)
!2970 = !DILocation(line: 485, column: 8, scope: !2969)
!2971 = !DILocation(line: 485, column: 8, scope: !2822)
!2972 = !DILocation(line: 485, column: 25, scope: !2969)
!2973 = !DILocation(line: 486, column: 8, scope: !2974)
!2974 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 486, column: 8)
!2975 = !DILocation(line: 486, column: 18, scope: !2974)
!2976 = !DILocation(line: 486, column: 15, scope: !2974)
!2977 = !DILocation(line: 486, column: 8, scope: !2822)
!2978 = !DILocalVariable(name: "fd", scope: !2979, file: !3, line: 487, type: !28)
!2979 = distinct !DILexicalBlock(scope: !2974, file: !3, line: 486, column: 26)
!2980 = !DILocation(line: 487, column: 13, scope: !2979)
!2981 = !DILocation(line: 487, column: 27, scope: !2979)
!2982 = !DILocation(line: 487, column: 18, scope: !2979)
!2983 = !DILocation(line: 488, column: 11, scope: !2984)
!2984 = distinct !DILexicalBlock(scope: !2979, file: !3, line: 488, column: 11)
!2985 = !DILocation(line: 488, column: 14, scope: !2984)
!2986 = !DILocation(line: 488, column: 11, scope: !2979)
!2987 = !DILocation(line: 488, column: 19, scope: !2984)
!2988 = !DILocation(line: 489, column: 40, scope: !2979)
!2989 = !DILocation(line: 489, column: 7, scope: !2979)
!2990 = !DILocation(line: 490, column: 4, scope: !2979)
!2991 = !DILocation(line: 491, column: 19, scope: !2822)
!2992 = !DILocation(line: 491, column: 10, scope: !2822)
!2993 = !DILocation(line: 491, column: 8, scope: !2822)
!2994 = !DILocation(line: 492, column: 8, scope: !2995)
!2995 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 492, column: 8)
!2996 = !DILocation(line: 492, column: 12, scope: !2995)
!2997 = !DILocation(line: 492, column: 8, scope: !2822)
!2998 = !DILocation(line: 492, column: 20, scope: !2995)
!2999 = !DILocation(line: 494, column: 15, scope: !3000)
!3000 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 494, column: 8)
!3001 = !DILocation(line: 494, column: 8, scope: !3000)
!3002 = !DILocation(line: 494, column: 8, scope: !2822)
!3003 = !DILocation(line: 494, column: 24, scope: !3000)
!3004 = !DILocation(line: 495, column: 19, scope: !2822)
!3005 = !DILocation(line: 495, column: 10, scope: !2822)
!3006 = !DILocation(line: 495, column: 8, scope: !2822)
!3007 = !DILocation(line: 496, column: 8, scope: !3008)
!3008 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 496, column: 8)
!3009 = !DILocation(line: 496, column: 12, scope: !3008)
!3010 = !DILocation(line: 496, column: 8, scope: !2822)
!3011 = !DILocation(line: 496, column: 18, scope: !3008)
!3012 = !DILocation(line: 497, column: 8, scope: !3013)
!3013 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 497, column: 8)
!3014 = !DILocation(line: 497, column: 18, scope: !3013)
!3015 = !DILocation(line: 497, column: 15, scope: !3013)
!3016 = !DILocation(line: 497, column: 8, scope: !2822)
!3017 = !DILocation(line: 498, column: 22, scope: !3018)
!3018 = distinct !DILexicalBlock(scope: !3013, file: !3, line: 497, column: 26)
!3019 = !DILocation(line: 498, column: 13, scope: !3018)
!3020 = !DILocation(line: 498, column: 11, scope: !3018)
!3021 = !DILocation(line: 499, column: 30, scope: !3018)
!3022 = !DILocation(line: 500, column: 11, scope: !3023)
!3023 = distinct !DILexicalBlock(scope: !3018, file: !3, line: 500, column: 11)
!3024 = !DILocation(line: 500, column: 15, scope: !3023)
!3025 = !DILocation(line: 500, column: 11, scope: !3018)
!3026 = !DILocation(line: 500, column: 23, scope: !3023)
!3027 = !DILocation(line: 501, column: 4, scope: !3018)
!3028 = !DILocation(line: 502, column: 27, scope: !2822)
!3029 = !DILocation(line: 503, column: 8, scope: !3030)
!3030 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 503, column: 8)
!3031 = !DILocation(line: 503, column: 18, scope: !3030)
!3032 = !DILocation(line: 503, column: 8, scope: !2822)
!3033 = !DILocation(line: 503, column: 34, scope: !3030)
!3034 = !DILocation(line: 503, column: 24, scope: !3030)
!3035 = !DILocation(line: 504, column: 4, scope: !2822)
!3036 = !DILabel(scope: !2822, name: "trycat", file: !3, line: 506)
!3037 = !DILocation(line: 506, column: 4, scope: !2822)
!3038 = !DILocation(line: 507, column: 8, scope: !3039)
!3039 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 507, column: 8)
!3040 = !DILocation(line: 507, column: 8, scope: !2822)
!3041 = !DILocation(line: 508, column: 14, scope: !3042)
!3042 = distinct !DILexicalBlock(scope: !3039, file: !3, line: 507, column: 24)
!3043 = !DILocation(line: 508, column: 7, scope: !3042)
!3044 = !DILocation(line: 509, column: 7, scope: !3042)
!3045 = !DILocation(line: 510, column: 20, scope: !3046)
!3046 = distinct !DILexicalBlock(scope: !3047, file: !3, line: 510, column: 13)
!3047 = distinct !DILexicalBlock(scope: !3042, file: !3, line: 509, column: 20)
!3048 = !DILocation(line: 510, column: 13, scope: !3046)
!3049 = !DILocation(line: 510, column: 13, scope: !3047)
!3050 = !DILocation(line: 510, column: 30, scope: !3046)
!3051 = !DILocation(line: 511, column: 25, scope: !3047)
!3052 = !DILocation(line: 511, column: 52, scope: !3047)
!3053 = !DILocation(line: 511, column: 17, scope: !3047)
!3054 = !DILocation(line: 511, column: 15, scope: !3047)
!3055 = !DILocation(line: 512, column: 20, scope: !3056)
!3056 = distinct !DILexicalBlock(scope: !3047, file: !3, line: 512, column: 13)
!3057 = !DILocation(line: 512, column: 13, scope: !3056)
!3058 = !DILocation(line: 512, column: 13, scope: !3047)
!3059 = !DILocation(line: 512, column: 30, scope: !3056)
!3060 = !DILocation(line: 513, column: 13, scope: !3061)
!3061 = distinct !DILexicalBlock(scope: !3047, file: !3, line: 513, column: 13)
!3062 = !DILocation(line: 513, column: 19, scope: !3061)
!3063 = !DILocation(line: 513, column: 13, scope: !3047)
!3064 = !DILocation(line: 513, column: 33, scope: !3061)
!3065 = !DILocation(line: 513, column: 54, scope: !3061)
!3066 = !DILocation(line: 513, column: 61, scope: !3061)
!3067 = !DILocation(line: 513, column: 24, scope: !3061)
!3068 = !DILocation(line: 514, column: 20, scope: !3069)
!3069 = distinct !DILexicalBlock(scope: !3047, file: !3, line: 514, column: 13)
!3070 = !DILocation(line: 514, column: 13, scope: !3069)
!3071 = !DILocation(line: 514, column: 13, scope: !3047)
!3072 = !DILocation(line: 514, column: 29, scope: !3069)
!3073 = distinct !{!3073, !3044, !3074}
!3074 = !DILocation(line: 515, column: 7, scope: !3042)
!3075 = !DILocation(line: 516, column: 7, scope: !3042)
!3076 = !DILabel(scope: !2822, name: "errhandler", file: !3, line: 519)
!3077 = !DILocation(line: 519, column: 4, scope: !2822)
!3078 = !DILocation(line: 520, column: 36, scope: !2822)
!3079 = !DILocation(line: 520, column: 4, scope: !2822)
!3080 = !DILocation(line: 521, column: 12, scope: !2822)
!3081 = !DILocation(line: 521, column: 4, scope: !2822)
!3082 = !DILocation(line: 523, column: 10, scope: !3083)
!3083 = distinct !DILexicalBlock(scope: !2822, file: !3, line: 521, column: 19)
!3084 = !DILabel(scope: !3083, name: "errhandler_io", file: !3, line: 525)
!3085 = !DILocation(line: 525, column: 10, scope: !3083)
!3086 = !DILocation(line: 526, column: 10, scope: !3083)
!3087 = !DILocation(line: 528, column: 10, scope: !3083)
!3088 = !DILocation(line: 530, column: 10, scope: !3083)
!3089 = !DILocation(line: 532, column: 10, scope: !3083)
!3090 = !DILocation(line: 534, column: 14, scope: !3091)
!3091 = distinct !DILexicalBlock(scope: !3083, file: !3, line: 534, column: 14)
!3092 = !DILocation(line: 534, column: 25, scope: !3091)
!3093 = !DILocation(line: 534, column: 22, scope: !3091)
!3094 = !DILocation(line: 534, column: 14, scope: !3083)
!3095 = !DILocation(line: 534, column: 39, scope: !3091)
!3096 = !DILocation(line: 534, column: 32, scope: !3091)
!3097 = !DILocation(line: 535, column: 14, scope: !3098)
!3098 = distinct !DILexicalBlock(scope: !3083, file: !3, line: 535, column: 14)
!3099 = !DILocation(line: 535, column: 24, scope: !3098)
!3100 = !DILocation(line: 535, column: 21, scope: !3098)
!3101 = !DILocation(line: 535, column: 14, scope: !3083)
!3102 = !DILocation(line: 535, column: 39, scope: !3098)
!3103 = !DILocation(line: 535, column: 32, scope: !3098)
!3104 = !DILocation(line: 536, column: 14, scope: !3105)
!3105 = distinct !DILexicalBlock(scope: !3083, file: !3, line: 536, column: 14)
!3106 = !DILocation(line: 536, column: 23, scope: !3105)
!3107 = !DILocation(line: 536, column: 14, scope: !3083)
!3108 = !DILocation(line: 537, column: 13, scope: !3109)
!3109 = distinct !DILexicalBlock(scope: !3105, file: !3, line: 536, column: 29)
!3110 = !DILocation(line: 539, column: 17, scope: !3111)
!3111 = distinct !DILexicalBlock(scope: !3112, file: !3, line: 539, column: 17)
!3112 = distinct !DILexicalBlock(scope: !3105, file: !3, line: 538, column: 17)
!3113 = !DILocation(line: 539, column: 17, scope: !3112)
!3114 = !DILocation(line: 540, column: 23, scope: !3111)
!3115 = !DILocation(line: 542, column: 23, scope: !3111)
!3116 = !DILocation(line: 540, column: 13, scope: !3111)
!3117 = !DILocation(line: 543, column: 13, scope: !3112)
!3118 = !DILocation(line: 546, column: 10, scope: !3083)
!3119 = !DILocation(line: 551, column: 1, scope: !2822)
!3120 = distinct !DISubprogram(name: "crcError", scope: !3, file: !3, line: 763, type: !1029, scopeLine: 764, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!3121 = !DILocation(line: 765, column: 14, scope: !3120)
!3122 = !DILocation(line: 767, column: 14, scope: !3120)
!3123 = !DILocation(line: 765, column: 4, scope: !3120)
!3124 = !DILocation(line: 768, column: 4, scope: !3120)
!3125 = !DILocation(line: 769, column: 4, scope: !3120)
!3126 = !DILocation(line: 770, column: 4, scope: !3120)
!3127 = distinct !DISubprogram(name: "compressedStreamEOF", scope: !3, file: !3, line: 776, type: !1029, scopeLine: 777, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!3128 = !DILocation(line: 778, column: 7, scope: !3129)
!3129 = distinct !DILexicalBlock(scope: !3127, file: !3, line: 778, column: 7)
!3130 = !DILocation(line: 778, column: 7, scope: !3127)
!3131 = !DILocation(line: 779, column: 15, scope: !3132)
!3132 = distinct !DILexicalBlock(scope: !3129, file: !3, line: 778, column: 14)
!3133 = !DILocation(line: 782, column: 8, scope: !3132)
!3134 = !DILocation(line: 779, column: 5, scope: !3132)
!3135 = !DILocation(line: 783, column: 14, scope: !3132)
!3136 = !DILocation(line: 783, column: 5, scope: !3132)
!3137 = !DILocation(line: 784, column: 5, scope: !3132)
!3138 = !DILocation(line: 785, column: 5, scope: !3132)
!3139 = !DILocation(line: 786, column: 3, scope: !3132)
!3140 = !DILocation(line: 787, column: 3, scope: !3127)
!3141 = distinct !DISubprogram(name: "testStream", scope: !3, file: !3, line: 556, type: !2524, scopeLine: 557, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !202)
!3142 = !DILocalVariable(name: "zStream", arg: 1, scope: !3141, file: !3, line: 556, type: !97)
!3143 = !DILocation(line: 556, column: 25, scope: !3141)
!3144 = !DILocalVariable(name: "bzf", scope: !3141, file: !3, line: 558, type: !2243)
!3145 = !DILocation(line: 558, column: 12, scope: !3141)
!3146 = !DILocalVariable(name: "bzerr", scope: !3141, file: !3, line: 559, type: !28)
!3147 = !DILocation(line: 559, column: 12, scope: !3141)
!3148 = !DILocalVariable(name: "bzerr_dummy", scope: !3141, file: !3, line: 559, type: !28)
!3149 = !DILocation(line: 559, column: 19, scope: !3141)
!3150 = !DILocalVariable(name: "ret", scope: !3141, file: !3, line: 559, type: !28)
!3151 = !DILocation(line: 559, column: 32, scope: !3141)
!3152 = !DILocalVariable(name: "nread", scope: !3141, file: !3, line: 559, type: !28)
!3153 = !DILocation(line: 559, column: 37, scope: !3141)
!3154 = !DILocalVariable(name: "streamNo", scope: !3141, file: !3, line: 559, type: !28)
!3155 = !DILocation(line: 559, column: 44, scope: !3141)
!3156 = !DILocalVariable(name: "i", scope: !3141, file: !3, line: 559, type: !28)
!3157 = !DILocation(line: 559, column: 54, scope: !3141)
!3158 = !DILocalVariable(name: "obuf", scope: !3141, file: !3, line: 560, type: !2248)
!3159 = !DILocation(line: 560, column: 12, scope: !3141)
!3160 = !DILocalVariable(name: "unused", scope: !3141, file: !3, line: 561, type: !2248)
!3161 = !DILocation(line: 561, column: 12, scope: !3141)
!3162 = !DILocalVariable(name: "nUnused", scope: !3141, file: !3, line: 562, type: !28)
!3163 = !DILocation(line: 562, column: 12, scope: !3141)
!3164 = !DILocalVariable(name: "unusedTmpV", scope: !3141, file: !3, line: 563, type: !27)
!3165 = !DILocation(line: 563, column: 12, scope: !3141)
!3166 = !DILocalVariable(name: "unusedTmp", scope: !3141, file: !3, line: 564, type: !43)
!3167 = !DILocation(line: 564, column: 12, scope: !3141)
!3168 = !DILocation(line: 566, column: 12, scope: !3141)
!3169 = !DILocation(line: 567, column: 13, scope: !3141)
!3170 = !DILocation(line: 570, column: 15, scope: !3171)
!3171 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 570, column: 8)
!3172 = !DILocation(line: 570, column: 8, scope: !3171)
!3173 = !DILocation(line: 570, column: 8, scope: !3141)
!3174 = !DILocation(line: 570, column: 25, scope: !3171)
!3175 = !DILocation(line: 572, column: 4, scope: !3141)
!3176 = !DILocation(line: 575, column: 24, scope: !3177)
!3177 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 572, column: 17)
!3178 = !DILocation(line: 575, column: 33, scope: !3177)
!3179 = !DILocation(line: 576, column: 21, scope: !3177)
!3180 = !DILocation(line: 576, column: 16, scope: !3177)
!3181 = !DILocation(line: 576, column: 32, scope: !3177)
!3182 = !DILocation(line: 576, column: 40, scope: !3177)
!3183 = !DILocation(line: 574, column: 13, scope: !3177)
!3184 = !DILocation(line: 574, column: 11, scope: !3177)
!3185 = !DILocation(line: 578, column: 11, scope: !3186)
!3186 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 578, column: 11)
!3187 = !DILocation(line: 578, column: 15, scope: !3186)
!3188 = !DILocation(line: 578, column: 23, scope: !3186)
!3189 = !DILocation(line: 578, column: 26, scope: !3186)
!3190 = !DILocation(line: 578, column: 32, scope: !3186)
!3191 = !DILocation(line: 578, column: 11, scope: !3177)
!3192 = !DILocation(line: 578, column: 42, scope: !3186)
!3193 = !DILocation(line: 579, column: 15, scope: !3177)
!3194 = !DILocation(line: 581, column: 7, scope: !3177)
!3195 = !DILocation(line: 581, column: 14, scope: !3177)
!3196 = !DILocation(line: 581, column: 20, scope: !3177)
!3197 = !DILocation(line: 582, column: 39, scope: !3198)
!3198 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 581, column: 30)
!3199 = !DILocation(line: 582, column: 44, scope: !3198)
!3200 = !DILocation(line: 582, column: 18, scope: !3198)
!3201 = !DILocation(line: 582, column: 16, scope: !3198)
!3202 = !DILocation(line: 583, column: 14, scope: !3203)
!3203 = distinct !DILexicalBlock(scope: !3198, file: !3, line: 583, column: 14)
!3204 = !DILocation(line: 583, column: 20, scope: !3203)
!3205 = !DILocation(line: 583, column: 14, scope: !3198)
!3206 = !DILocation(line: 583, column: 44, scope: !3203)
!3207 = distinct !{!3207, !3194, !3208}
!3208 = !DILocation(line: 584, column: 7, scope: !3177)
!3209 = !DILocation(line: 585, column: 11, scope: !3210)
!3210 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 585, column: 11)
!3211 = !DILocation(line: 585, column: 17, scope: !3210)
!3212 = !DILocation(line: 585, column: 11, scope: !3177)
!3213 = !DILocation(line: 585, column: 35, scope: !3210)
!3214 = !DILocation(line: 587, column: 37, scope: !3177)
!3215 = !DILocation(line: 587, column: 7, scope: !3177)
!3216 = !DILocation(line: 588, column: 11, scope: !3217)
!3217 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 588, column: 11)
!3218 = !DILocation(line: 588, column: 17, scope: !3217)
!3219 = !DILocation(line: 588, column: 11, scope: !3177)
!3220 = !DILocation(line: 588, column: 27, scope: !3217)
!3221 = !DILocation(line: 590, column: 27, scope: !3177)
!3222 = !DILocation(line: 590, column: 17, scope: !3177)
!3223 = !DILocation(line: 591, column: 14, scope: !3224)
!3224 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 591, column: 7)
!3225 = !DILocation(line: 591, column: 12, scope: !3224)
!3226 = !DILocation(line: 591, column: 19, scope: !3227)
!3227 = distinct !DILexicalBlock(scope: !3224, file: !3, line: 591, column: 7)
!3228 = !DILocation(line: 591, column: 23, scope: !3227)
!3229 = !DILocation(line: 591, column: 21, scope: !3227)
!3230 = !DILocation(line: 591, column: 7, scope: !3224)
!3231 = !DILocation(line: 591, column: 49, scope: !3227)
!3232 = !DILocation(line: 591, column: 59, scope: !3227)
!3233 = !DILocation(line: 591, column: 44, scope: !3227)
!3234 = !DILocation(line: 591, column: 37, scope: !3227)
!3235 = !DILocation(line: 591, column: 47, scope: !3227)
!3236 = !DILocation(line: 591, column: 33, scope: !3227)
!3237 = !DILocation(line: 591, column: 7, scope: !3227)
!3238 = distinct !{!3238, !3230, !3239}
!3239 = !DILocation(line: 591, column: 60, scope: !3224)
!3240 = !DILocation(line: 593, column: 33, scope: !3177)
!3241 = !DILocation(line: 593, column: 7, scope: !3177)
!3242 = !DILocation(line: 594, column: 11, scope: !3243)
!3243 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 594, column: 11)
!3244 = !DILocation(line: 594, column: 17, scope: !3243)
!3245 = !DILocation(line: 594, column: 11, scope: !3177)
!3246 = !DILocation(line: 594, column: 27, scope: !3243)
!3247 = !DILocation(line: 595, column: 11, scope: !3248)
!3248 = distinct !DILexicalBlock(scope: !3177, file: !3, line: 595, column: 11)
!3249 = !DILocation(line: 595, column: 19, scope: !3248)
!3250 = !DILocation(line: 595, column: 24, scope: !3248)
!3251 = !DILocation(line: 595, column: 34, scope: !3248)
!3252 = !DILocation(line: 595, column: 27, scope: !3248)
!3253 = !DILocation(line: 595, column: 11, scope: !3177)
!3254 = !DILocation(line: 595, column: 44, scope: !3248)
!3255 = distinct !{!3255, !3175, !3256}
!3256 = !DILocation(line: 597, column: 4, scope: !3141)
!3257 = !DILocation(line: 599, column: 15, scope: !3258)
!3258 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 599, column: 8)
!3259 = !DILocation(line: 599, column: 8, scope: !3258)
!3260 = !DILocation(line: 599, column: 8, scope: !3141)
!3261 = !DILocation(line: 599, column: 25, scope: !3258)
!3262 = !DILocation(line: 600, column: 19, scope: !3141)
!3263 = !DILocation(line: 600, column: 10, scope: !3141)
!3264 = !DILocation(line: 600, column: 8, scope: !3141)
!3265 = !DILocation(line: 601, column: 8, scope: !3266)
!3266 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 601, column: 8)
!3267 = !DILocation(line: 601, column: 12, scope: !3266)
!3268 = !DILocation(line: 601, column: 8, scope: !3141)
!3269 = !DILocation(line: 601, column: 20, scope: !3266)
!3270 = !DILocation(line: 603, column: 8, scope: !3271)
!3271 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 603, column: 8)
!3272 = !DILocation(line: 603, column: 18, scope: !3271)
!3273 = !DILocation(line: 603, column: 8, scope: !3141)
!3274 = !DILocation(line: 603, column: 34, scope: !3271)
!3275 = !DILocation(line: 603, column: 24, scope: !3271)
!3276 = !DILocation(line: 604, column: 4, scope: !3141)
!3277 = !DILabel(scope: !3141, name: "errhandler", file: !3, line: 606)
!3278 = !DILocation(line: 606, column: 4, scope: !3141)
!3279 = !DILocation(line: 607, column: 36, scope: !3141)
!3280 = !DILocation(line: 607, column: 4, scope: !3141)
!3281 = !DILocation(line: 608, column: 8, scope: !3282)
!3282 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 608, column: 8)
!3283 = !DILocation(line: 608, column: 18, scope: !3282)
!3284 = !DILocation(line: 608, column: 8, scope: !3141)
!3285 = !DILocation(line: 609, column: 17, scope: !3282)
!3286 = !DILocation(line: 609, column: 37, scope: !3282)
!3287 = !DILocation(line: 609, column: 7, scope: !3282)
!3288 = !DILocation(line: 610, column: 12, scope: !3141)
!3289 = !DILocation(line: 610, column: 4, scope: !3141)
!3290 = !DILocation(line: 612, column: 10, scope: !3291)
!3291 = distinct !DILexicalBlock(scope: !3141, file: !3, line: 610, column: 19)
!3292 = !DILabel(scope: !3291, name: "errhandler_io", file: !3, line: 614)
!3293 = !DILocation(line: 614, column: 10, scope: !3291)
!3294 = !DILocation(line: 615, column: 10, scope: !3291)
!3295 = !DILocation(line: 617, column: 20, scope: !3291)
!3296 = !DILocation(line: 617, column: 10, scope: !3291)
!3297 = !DILocation(line: 619, column: 10, scope: !3291)
!3298 = !DILocation(line: 621, column: 10, scope: !3291)
!3299 = !DILocation(line: 623, column: 20, scope: !3291)
!3300 = !DILocation(line: 623, column: 10, scope: !3291)
!3301 = !DILocation(line: 625, column: 10, scope: !3291)
!3302 = !DILocation(line: 627, column: 14, scope: !3303)
!3303 = distinct !DILexicalBlock(scope: !3291, file: !3, line: 627, column: 14)
!3304 = !DILocation(line: 627, column: 25, scope: !3303)
!3305 = !DILocation(line: 627, column: 22, scope: !3303)
!3306 = !DILocation(line: 627, column: 14, scope: !3291)
!3307 = !DILocation(line: 627, column: 39, scope: !3303)
!3308 = !DILocation(line: 627, column: 32, scope: !3303)
!3309 = !DILocation(line: 628, column: 14, scope: !3310)
!3310 = distinct !DILexicalBlock(scope: !3291, file: !3, line: 628, column: 14)
!3311 = !DILocation(line: 628, column: 23, scope: !3310)
!3312 = !DILocation(line: 628, column: 14, scope: !3291)
!3313 = !DILocation(line: 629, column: 21, scope: !3314)
!3314 = distinct !DILexicalBlock(scope: !3310, file: !3, line: 628, column: 29)
!3315 = !DILocation(line: 629, column: 11, scope: !3314)
!3316 = !DILocation(line: 631, column: 13, scope: !3314)
!3317 = !DILocation(line: 633, column: 17, scope: !3318)
!3318 = distinct !DILexicalBlock(scope: !3319, file: !3, line: 633, column: 17)
!3319 = distinct !DILexicalBlock(scope: !3310, file: !3, line: 632, column: 17)
!3320 = !DILocation(line: 633, column: 17, scope: !3319)
!3321 = !DILocation(line: 634, column: 23, scope: !3318)
!3322 = !DILocation(line: 634, column: 13, scope: !3318)
!3323 = !DILocation(line: 636, column: 13, scope: !3319)
!3324 = !DILocation(line: 639, column: 10, scope: !3291)
!3325 = !DILocation(line: 644, column: 1, scope: !3141)
