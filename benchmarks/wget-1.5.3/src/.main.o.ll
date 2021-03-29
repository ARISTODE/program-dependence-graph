; ModuleID = '.main.o.bc'
source_filename = "main.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.option = type { i8*, i32, i32*, i32 }
%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.options = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8*, i32, i8*, i32, i32, i8**, i8**, i8**, i8**, i8**, i8**, i32, i32, i8*, %struct.__sFILE*, i32, i8*, i8*, i32, i32, i32, i8*, i8*, i8*, i32, i32, i8*, i8*, i8**, i8*, i8*, i8*, i64, i64, i32, i64, i64, i32, i32, i32, i32, i32, i32, i8*, i32, i32, i32, i64, i32, i32, i32 }

@.str = private unnamed_addr constant [10 x i8] c"sensitive\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [7 x i8] c"main.c\00", section "llvm.metadata"
@main.long_options = internal global [66 x %struct.option] [%struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i32 0, i32 0), i32 0, i32* null, i32 98 }, %struct.option { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.3, i32 0, i32 0), i32 0, i32* null, i32 99 }, %struct.option { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.4, i32 0, i32 0), i32 0, i32* null, i32 107 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i32 0, i32 0), i32 0, i32* null, i32 100 }, %struct.option { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.6, i32 0, i32 0), i32 0, i32* null, i32 21 }, %struct.option { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.7, i32 0, i32 0), i32 0, i32* null, i32 69 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.8, i32 0, i32 0), i32 0, i32* null, i32 14 }, %struct.option { i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.9, i32 0, i32 0), i32 0, i32* null, i32 120 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.10, i32 0, i32 0), i32 0, i32* null, i32 120 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.11, i32 0, i32 0), i32 0, i32* null, i32 70 }, %struct.option { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.12, i32 0, i32 0), i32 0, i32* null, i32 104 }, %struct.option { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.13, i32 0, i32 0), i32 0, i32* null, i32 10 }, %struct.option { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.14, i32 0, i32 0), i32 0, i32* null, i32 109 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.15, i32 0, i32 0), i32 0, i32* null, i32 13 }, %struct.option { i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.16, i32 0, i32 0), i32 0, i32* null, i32 19 }, %struct.option { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.17, i32 0, i32 0), i32 0, i32* null, i32 20 }, %struct.option { i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.18, i32 0, i32 0), i32 0, i32* null, i32 22 }, %struct.option { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.19, i32 0, i32 0), i32 0, i32* null, i32 5 }, %struct.option { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.20, i32 0, i32 0), i32 0, i32* null, i32 18 }, %struct.option { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.21, i32 0, i32 0), i32 0, i32* null, i32 11 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.22, i32 0, i32 0), i32 0, i32* null, i32 113 }, %struct.option { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.23, i32 0, i32 0), i32 0, i32* null, i32 114 }, %struct.option { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.24, i32 0, i32 0), i32 0, i32* null, i32 76 }, %struct.option { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.25, i32 0, i32 0), i32 0, i32* null, i32 9 }, %struct.option { i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.26, i32 0, i32 0), i32 0, i32* null, i32 115 }, %struct.option { i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.27, i32 0, i32 0), i32 0, i32* null, i32 83 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.28, i32 0, i32 0), i32 0, i32* null, i32 72 }, %struct.option { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.29, i32 0, i32 0), i32 0, i32* null, i32 4 }, %struct.option { i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.30, i32 0, i32 0), i32 0, i32* null, i32 78 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.31, i32 0, i32 0), i32 0, i32* null, i32 118 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.32, i32 0, i32 0), i32 0, i32* null, i32 86 }, %struct.option { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i32 0, i32 0), i32 1, i32* null, i32 65 }, %struct.option { i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.34, i32 0, i32 0), i32 1, i32* null, i32 97 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.35, i32 0, i32 0), i32 1, i32* null, i32 23 }, %struct.option { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.36, i32 0, i32 0), i32 1, i32* null, i32 66 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.37, i32 0, i32 0), i32 1, i32* null, i32 67 }, %struct.option { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.38, i32 0, i32 0), i32 1, i32* null, i32 17 }, %struct.option { i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.39, i32 0, i32 0), i32 0, i32* null, i32 8 }, %struct.option { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.40, i32 0, i32 0), i32 1, i32* null, i32 80 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.41, i32 0, i32 0), i32 1, i32* null, i32 68 }, %struct.option { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.42, i32 0, i32 0), i32 1, i32* null, i32 6 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.43, i32 0, i32 0), i32 1, i32* null, i32 101 }, %struct.option { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.44, i32 0, i32 0), i32 1, i32* null, i32 88 }, %struct.option { i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.45, i32 0, i32 0), i32 1, i32* null, i32 12 }, %struct.option { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0), i32 1, i32* null, i32 103 }, %struct.option { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.47, i32 0, i32 0), i32 1, i32* null, i32 3 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.48, i32 0, i32 0), i32 1, i32* null, i32 7 }, %struct.option { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.49, i32 0, i32 0), i32 1, i32* null, i32 2 }, %struct.option { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.50, i32 0, i32 0), i32 1, i32* null, i32 1 }, %struct.option { i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.51, i32 0, i32 0), i32 1, i32* null, i32 73 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.52, i32 0, i32 0), i32 1, i32* null, i32 105 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.53, i32 0, i32 0), i32 1, i32* null, i32 108 }, %struct.option { i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.54, i32 0, i32 0), i32 1, i32* null, i32 110 }, %struct.option { i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.55, i32 0, i32 0), i32 1, i32* null, i32 79 }, %struct.option { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.56, i32 0, i32 0), i32 1, i32* null, i32 111 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.57, i32 0, i32 0), i32 1, i32* null, i32 89 }, %struct.option { i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.58, i32 0, i32 0), i32 1, i32* null, i32 16 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.59, i32 0, i32 0), i32 1, i32* null, i32 15 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.60, i32 0, i32 0), i32 1, i32* null, i32 81 }, %struct.option { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.61, i32 0, i32 0), i32 1, i32* null, i32 82 }, %struct.option { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.62, i32 0, i32 0), i32 1, i32* null, i32 84 }, %struct.option { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.63, i32 0, i32 0), i32 1, i32* null, i32 116 }, %struct.option { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.64, i32 0, i32 0), i32 1, i32* null, i32 85 }, %struct.option { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.65, i32 0, i32 0), i32 1, i32* null, i32 89 }, %struct.option { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.66, i32 0, i32 0), i32 1, i32* null, i32 119 }, %struct.option zeroinitializer], align 16, !dbg !0
@.str.2 = private unnamed_addr constant [11 x i8] c"background\00", align 1
@.str.3 = private unnamed_addr constant [9 x i8] c"continue\00", align 1
@.str.4 = private unnamed_addr constant [14 x i8] c"convert-links\00", align 1
@.str.5 = private unnamed_addr constant [6 x i8] c"debug\00", align 1
@.str.6 = private unnamed_addr constant [20 x i8] c"dont-remove-listing\00", align 1
@.str.7 = private unnamed_addr constant [14 x i8] c"email-address\00", align 1
@.str.8 = private unnamed_addr constant [11 x i8] c"follow-ftp\00", align 1
@.str.9 = private unnamed_addr constant [18 x i8] c"force-directories\00", align 1
@.str.10 = private unnamed_addr constant [11 x i8] c"force-hier\00", align 1
@.str.11 = private unnamed_addr constant [11 x i8] c"force-html\00", align 1
@.str.12 = private unnamed_addr constant [5 x i8] c"help\00", align 1
@.str.13 = private unnamed_addr constant [14 x i8] c"ignore-length\00", align 1
@.str.14 = private unnamed_addr constant [7 x i8] c"mirror\00", align 1
@.str.15 = private unnamed_addr constant [11 x i8] c"no-clobber\00", align 1
@.str.16 = private unnamed_addr constant [15 x i8] c"no-directories\00", align 1
@.str.17 = private unnamed_addr constant [20 x i8] c"no-host-directories\00", align 1
@.str.18 = private unnamed_addr constant [15 x i8] c"no-host-lookup\00", align 1
@.str.19 = private unnamed_addr constant [10 x i8] c"no-parent\00", align 1
@.str.20 = private unnamed_addr constant [12 x i8] c"non-verbose\00", align 1
@.str.21 = private unnamed_addr constant [12 x i8] c"passive-ftp\00", align 1
@.str.22 = private unnamed_addr constant [6 x i8] c"quiet\00", align 1
@.str.23 = private unnamed_addr constant [10 x i8] c"recursive\00", align 1
@.str.24 = private unnamed_addr constant [9 x i8] c"relative\00", align 1
@.str.25 = private unnamed_addr constant [14 x i8] c"retr-symlinks\00", align 1
@.str.26 = private unnamed_addr constant [13 x i8] c"save-headers\00", align 1
@.str.27 = private unnamed_addr constant [16 x i8] c"server-response\00", align 1
@.str.28 = private unnamed_addr constant [11 x i8] c"span-hosts\00", align 1
@.str.29 = private unnamed_addr constant [7 x i8] c"spider\00", align 1
@.str.30 = private unnamed_addr constant [13 x i8] c"timestamping\00", align 1
@.str.31 = private unnamed_addr constant [8 x i8] c"verbose\00", align 1
@.str.32 = private unnamed_addr constant [8 x i8] c"version\00", align 1
@.str.33 = private unnamed_addr constant [7 x i8] c"accept\00", align 1
@.str.34 = private unnamed_addr constant [14 x i8] c"append-output\00", align 1
@.str.35 = private unnamed_addr constant [8 x i8] c"backups\00", align 1
@.str.36 = private unnamed_addr constant [5 x i8] c"base\00", align 1
@.str.37 = private unnamed_addr constant [6 x i8] c"cache\00", align 1
@.str.38 = private unnamed_addr constant [9 x i8] c"cut-dirs\00", align 1
@.str.39 = private unnamed_addr constant [13 x i8] c"delete-after\00", align 1
@.str.40 = private unnamed_addr constant [17 x i8] c"directory-prefix\00", align 1
@.str.41 = private unnamed_addr constant [8 x i8] c"domains\00", align 1
@.str.42 = private unnamed_addr constant [10 x i8] c"dot-style\00", align 1
@.str.43 = private unnamed_addr constant [8 x i8] c"execute\00", align 1
@.str.44 = private unnamed_addr constant [20 x i8] c"exclude-directories\00", align 1
@.str.45 = private unnamed_addr constant [16 x i8] c"exclude-domains\00", align 1
@.str.46 = private unnamed_addr constant [5 x i8] c"glob\00", align 1
@.str.47 = private unnamed_addr constant [7 x i8] c"header\00", align 1
@.str.48 = private unnamed_addr constant [8 x i8] c"htmlify\00", align 1
@.str.49 = private unnamed_addr constant [12 x i8] c"http-passwd\00", align 1
@.str.50 = private unnamed_addr constant [10 x i8] c"http-user\00", align 1
@.str.51 = private unnamed_addr constant [20 x i8] c"include-directories\00", align 1
@.str.52 = private unnamed_addr constant [11 x i8] c"input-file\00", align 1
@.str.53 = private unnamed_addr constant [6 x i8] c"level\00", align 1
@.str.54 = private unnamed_addr constant [3 x i8] c"no\00", align 1
@.str.55 = private unnamed_addr constant [16 x i8] c"output-document\00", align 1
@.str.56 = private unnamed_addr constant [12 x i8] c"output-file\00", align 1
@.str.57 = private unnamed_addr constant [6 x i8] c"proxy\00", align 1
@.str.58 = private unnamed_addr constant [13 x i8] c"proxy-passwd\00", align 1
@.str.59 = private unnamed_addr constant [11 x i8] c"proxy-user\00", align 1
@.str.60 = private unnamed_addr constant [6 x i8] c"quota\00", align 1
@.str.61 = private unnamed_addr constant [7 x i8] c"reject\00", align 1
@.str.62 = private unnamed_addr constant [8 x i8] c"timeout\00", align 1
@.str.63 = private unnamed_addr constant [6 x i8] c"tries\00", align 1
@.str.64 = private unnamed_addr constant [11 x i8] c"user-agent\00", align 1
@.str.65 = private unnamed_addr constant [10 x i8] c"use-proxy\00", align 1
@.str.66 = private unnamed_addr constant [5 x i8] c"wait\00", align 1
@exec_name = common global i8* null, align 8, !dbg !232
@.str.67 = private unnamed_addr constant [62 x i8] c"hVqvdksxmNWrHSLcFbEY:g:T:U:O:l:n:i:o:a:t:D:A:R:P:B:e:Q:X:I:w:\00", align 1
@.str.68 = private unnamed_addr constant [3 x i8] c"on\00", align 1
@.str.69 = private unnamed_addr constant [9 x i8] c"noparent\00", align 1
@.str.70 = private unnamed_addr constant [12 x i8] c"deleteafter\00", align 1
@.str.71 = private unnamed_addr constant [13 x i8] c"retrsymlinks\00", align 1
@.str.72 = private unnamed_addr constant [13 x i8] c"ignorelength\00", align 1
@.str.73 = private unnamed_addr constant [11 x i8] c"passiveftp\00", align 1
@.str.74 = private unnamed_addr constant [10 x i8] c"noclobber\00", align 1
@.str.75 = private unnamed_addr constant [10 x i8] c"followftp\00", align 1
@.str.76 = private unnamed_addr constant [8 x i8] c"cutdirs\00", align 1
@optarg = external global i8*, align 8
@.str.77 = private unnamed_addr constant [4 x i8] c"off\00", align 1
@.str.78 = private unnamed_addr constant [10 x i8] c"dirstruct\00", align 1
@.str.79 = private unnamed_addr constant [11 x i8] c"addhostdir\00", align 1
@.str.80 = private unnamed_addr constant [14 x i8] c"removelisting\00", align 1
@.str.81 = private unnamed_addr constant [16 x i8] c"simplehostcheck\00", align 1
@.str.82 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.83 = private unnamed_addr constant [10 x i8] c"forcehtml\00", align 1
@.str.84 = private unnamed_addr constant [10 x i8] c"spanhosts\00", align 1
@.str.85 = private unnamed_addr constant [13 x i8] c"convertlinks\00", align 1
@.str.86 = private unnamed_addr constant [13 x i8] c"relativeonly\00", align 1
@.str.87 = private unnamed_addr constant [15 x i8] c"serverresponse\00", align 1
@.str.88 = private unnamed_addr constant [12 x i8] c"saveheaders\00", align 1
@.str.89 = private unnamed_addr constant [14 x i8] c"GNU Wget %s\0A\0A\00", align 1
@version_string = external global i8*, align 8
@.str.90 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.91 = private unnamed_addr constant [303 x i8] c"Copyright (C) 1995, 1996, 1997, 1998 Free Software Foundation, Inc.\0AThis program is distributed in the hope that it will be useful,\0Abut WITHOUT ANY WARRANTY; without even the implied warranty of\0AMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\0AGNU General Public License for more details.\0A\00", align 1
@.str.92 = private unnamed_addr constant [46 x i8] c"\0AWritten by Hrvoje Niksic <hniksic@srce.hr>.\0A\00", align 1
@.str.93 = private unnamed_addr constant [9 x i8] c"httpuser\00", align 1
@.str.94 = private unnamed_addr constant [11 x i8] c"httppasswd\00", align 1
@.str.95 = private unnamed_addr constant [9 x i8] c"dotstyle\00", align 1
@.str.96 = private unnamed_addr constant [15 x i8] c"excludedomains\00", align 1
@.str.97 = private unnamed_addr constant [10 x i8] c"proxyuser\00", align 1
@.str.98 = private unnamed_addr constant [12 x i8] c"proxypasswd\00", align 1
@.str.99 = private unnamed_addr constant [8 x i8] c"logfile\00", align 1
@__stderrp = external global %struct.__sFILE*, align 8
@.str.100 = private unnamed_addr constant [25 x i8] c"%s: %s: invalid command\0A\00", align 1
@.str.101 = private unnamed_addr constant [19 x i8] c"includedirectories\00", align 1
@.str.102 = private unnamed_addr constant [6 x i8] c"input\00", align 1
@.str.103 = private unnamed_addr constant [9 x i8] c"reclevel\00", align 1
@.str.104 = private unnamed_addr constant [30 x i8] c"%s: illegal option -- `-n%c'\0A\00", align 1
@.str.105 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.106 = private unnamed_addr constant [35 x i8] c"Try `%s --help' for more options.\0A\00", align 1
@.str.107 = private unnamed_addr constant [15 x i8] c"outputdocument\00", align 1
@.str.108 = private unnamed_addr constant [10 x i8] c"dirprefix\00", align 1
@.str.109 = private unnamed_addr constant [10 x i8] c"useragent\00", align 1
@.str.110 = private unnamed_addr constant [19 x i8] c"excludedirectories\00", align 1
@.str.111 = private unnamed_addr constant [9 x i8] c"useproxy\00", align 1
@opt = common global %struct.options zeroinitializer, align 8, !dbg !97
@.str.112 = private unnamed_addr constant [46 x i8] c"Can't be verbose and quiet at the same time.\0A\00", align 1
@.str.113 = private unnamed_addr constant [61 x i8] c"Can't timestamp and not clobber old files at the same time.\0A\00", align 1
@optind = external global i32, align 4
@.str.114 = private unnamed_addr constant [17 x i8] c"%s: missing URL\0A\00", align 1
@.str.115 = private unnamed_addr constant [41 x i8] c"DEBUG output created by Wget %s on %s.\0A\0A\00", align 1
@.str.116 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@__stdoutp = external global %struct.__sFILE*, align 8
@.str.117 = private unnamed_addr constant [3 x i8] c"wb\00", align 1
@.str.118 = private unnamed_addr constant [22 x i8] c"No URLs found in %s.\0A\00", align 1
@.str.119 = private unnamed_addr constant [51 x i8] c"\0AFINISHED --%s--\0ADownloaded: %s bytes in %d files\0A\00", align 1
@.str.120 = private unnamed_addr constant [37 x i8] c"Download quota (%s bytes) EXCEEDED!\0A\00", align 1
@.str.121 = private unnamed_addr constant [5 x i8] c"wget\00", align 1
@.str.122 = private unnamed_addr constant [24 x i8] c"/usr/local/share/locale\00", align 1
@.str.123 = private unnamed_addr constant [51 x i8] c"GNU Wget %s, a non-interactive network retriever.\0A\00", align 1
@.str.124 = private unnamed_addr constant [21 x i8] c"%s%s%s%s%s%s%s%s%s%s\00", align 1
@.str.125 = private unnamed_addr constant [76 x i8] c"\0AMandatory arguments to long options are mandatory for short options too.\0A\0A\00", align 1
@.str.126 = private unnamed_addr constant [235 x i8] c"Startup:\0A  -V,  --version           display the version of Wget and exit.\0A  -h,  --help              print this help.\0A  -b,  --background        go to background after startup.\0A  -e,  --execute=COMMAND   execute a `.wgetrc' command.\0A\0A\00", align 1
@.str.127 = private unnamed_addr constant [477 x i8] c"Logging and input file:\0A  -o,  --output-file=FILE     log messages to FILE.\0A  -a,  --append-output=FILE   append messages to FILE.\0A  -d,  --debug                print debug output.\0A  -q,  --quiet                quiet (no output).\0A  -v,  --verbose              be verbose (this is the default).\0A  -nv, --non-verbose          turn off verboseness, without being quiet.\0A  -i,  --input-file=FILE      read URL-s from file.\0A  -F,  --force-html           treat input file as HTML.\0A\0A\00", align 1
@.str.128 = private unnamed_addr constant [769 x i8] c"Download:\0A  -t,  --tries=NUMBER           set number of retries to NUMBER (0 unlimits).\0A  -O   --output-document=FILE   write documents to FILE.\0A  -nc, --no-clobber             don't clobber existing files.\0A  -c,  --continue               restart getting an existing file.\0A       --dot-style=STYLE        set retrieval display style.\0A  -N,  --timestamping           don't retrieve files if older than local.\0A  -S,  --server-response        print server response.\0A       --spider                 don't download anything.\0A  -T,  --timeout=SECONDS        set the read timeout to SECONDS.\0A  -w,  --wait=SECONDS           wait SECONDS between retrievals.\0A  -Y,  --proxy=on/off           turn proxy on or off.\0A  -Q,  --quota=NUMBER           set retrieval quota to NUMBER.\0A\0A\00", align 1
@.str.129 = private unnamed_addr constant [346 x i8] c"Directories:\0A  -nd  --no-directories            don't create directories.\0A  -x,  --force-directories         force creation of directories.\0A  -nH, --no-host-directories       don't create host directories.\0A  -P,  --directory-prefix=PREFIX   save files to PREFIX/...\0A       --cut-dirs=NUMBER           ignore NUMBER remote directory components.\0A\0A\00", align 1
@.str.130 = private unnamed_addr constant [578 x i8] c"HTTP options:\0A       --http-user=USER      set http user to USER.\0A       --http-passwd=PASS    set http password to PASS.\0A  -C,  --cache=on/off        (dis)allow server-cached data (normally allowed).\0A       --ignore-length       ignore `Content-Length' header field.\0A       --header=STRING       insert STRING among the headers.\0A       --proxy-user=USER     set USER as proxy username.\0A       --proxy-passwd=PASS   set PASS as proxy password.\0A  -s,  --save-headers        save the HTTP headers to file.\0A  -U,  --user-agent=AGENT    identify as AGENT instead of Wget/VERSION.\0A\0A\00", align 1
@.str.131 = private unnamed_addr constant [187 x i8] c"FTP options:\0A       --retr-symlinks   retrieve FTP symbolic links.\0A  -g,  --glob=on/off     turn file name globbing on or off.\0A       --passive-ftp     use the \22passive\22 transfer mode.\0A\0A\00", align 1
@.str.132 = private unnamed_addr constant [423 x i8] c"Recursive retrieval:\0A  -r,  --recursive             recursive web-suck -- use with care!.\0A  -l,  --level=NUMBER          maximum recursion depth (0 to unlimit).\0A       --delete-after          delete downloaded files.\0A  -k,  --convert-links         convert non-relative links to relative.\0A  -m,  --mirror                turn on options suitable for mirroring.\0A  -nr, --dont-remove-listing   don't remove `.listing' files.\0A\0A\00", align 1
@.str.133 = private unnamed_addr constant [772 x i8] c"Recursive accept/reject:\0A  -A,  --accept=LIST                list of accepted extensions.\0A  -R,  --reject=LIST                list of rejected extensions.\0A  -D,  --domains=LIST               list of accepted domains.\0A       --exclude-domains=LIST       comma-separated list of rejected domains.\0A  -L,  --relative                   follow relative links only.\0A       --follow-ftp                 follow FTP links from HTML documents.\0A  -H,  --span-hosts                 go to foreign hosts when recursive.\0A  -I,  --include-directories=LIST   list of allowed directories.\0A  -X,  --exclude-directories=LIST   list of excluded directories.\0A  -nh, --no-host-lookup             don't DNS-lookup hosts.\0A  -np, --no-parent                  don't ascend to the parent directory.\0A\0A\00", align 1
@.str.134 = private unnamed_addr constant [57 x i8] c"Mail bug reports and suggestions to <bug-wget@gnu.org>.\0A\00", align 1
@.str.135 = private unnamed_addr constant [32 x i8] c"Usage: %s [OPTION]... [URL]...\0A\00", align 1
@.str.136 = private unnamed_addr constant [43 x i8] c"%s received, redirecting output to `%%s'.\0A\00", align 1
@.str.137 = private unnamed_addr constant [7 x i8] c"SIGHUP\00", align 1
@.str.138 = private unnamed_addr constant [8 x i8] c"SIGUSR1\00", align 1
@.str.139 = private unnamed_addr constant [6 x i8] c"WTF?!\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !2 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %url = alloca i8**, align 8
  %t = alloca i8**, align 8
  %i = alloca i32, align 4
  %c = alloca i32, align 4
  %nurl = alloca i32, align 4
  %status = alloca i32, align 4
  %append_to_log = alloca i32, align 4
  %com = alloca i8*, align 8
  %val = alloca i8*, align 8
  %p = alloca i8*, align 8
  %irix4_cc_needs_this = alloca i8*, align 8
  %filename = alloca i8*, align 8
  %new_file = alloca i8*, align 8
  %dt = alloca i32, align 4
  %count = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !250, metadata !DIExpression()), !dbg !251
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !252, metadata !DIExpression()), !dbg !253
  call void @llvm.dbg.declare(metadata i8*** %url, metadata !254, metadata !DIExpression()), !dbg !255
  %url1 = bitcast i8*** %url to i8*, !dbg !256
  call void @llvm.var.annotation(i8* %url1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i32 197), !dbg !256
  call void @llvm.dbg.declare(metadata i8*** %t, metadata !257, metadata !DIExpression()), !dbg !258
  %t2 = bitcast i8*** %t to i8*, !dbg !256
  call void @llvm.var.annotation(i8* %t2, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i32 197), !dbg !256
  call void @llvm.dbg.declare(metadata i32* %i, metadata !259, metadata !DIExpression()), !dbg !260
  call void @llvm.dbg.declare(metadata i32* %c, metadata !261, metadata !DIExpression()), !dbg !262
  call void @llvm.dbg.declare(metadata i32* %nurl, metadata !263, metadata !DIExpression()), !dbg !264
  call void @llvm.dbg.declare(metadata i32* %status, metadata !265, metadata !DIExpression()), !dbg !266
  call void @llvm.dbg.declare(metadata i32* %append_to_log, metadata !267, metadata !DIExpression()), !dbg !268
  call void @i18n_initialize(), !dbg !269
  store i32 0, i32* %append_to_log, align 4, !dbg !270
  %0 = load i8**, i8*** %argv.addr, align 8, !dbg !271
  %arrayidx = getelementptr inbounds i8*, i8** %0, i64 0, !dbg !271
  %1 = load i8*, i8** %arrayidx, align 8, !dbg !271
  %call = call i8* @strrchr(i8* %1, i32 47), !dbg !272
  store i8* %call, i8** @exec_name, align 8, !dbg !273
  %2 = load i8*, i8** @exec_name, align 8, !dbg !274
  %tobool = icmp ne i8* %2, null, !dbg !274
  br i1 %tobool, label %if.else, label %if.then, !dbg !276

if.then:                                          ; preds = %entry
  %3 = load i8**, i8*** %argv.addr, align 8, !dbg !277
  %arrayidx3 = getelementptr inbounds i8*, i8** %3, i64 0, !dbg !277
  %4 = load i8*, i8** %arrayidx3, align 8, !dbg !277
  store i8* %4, i8** @exec_name, align 8, !dbg !278
  br label %if.end, !dbg !279

if.else:                                          ; preds = %entry
  %5 = load i8*, i8** @exec_name, align 8, !dbg !280
  %incdec.ptr = getelementptr inbounds i8, i8* %5, i32 1, !dbg !280
  store i8* %incdec.ptr, i8** @exec_name, align 8, !dbg !280
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  call void @initialize(), !dbg !281
  br label %while.cond, !dbg !282

while.cond:                                       ; preds = %sw.epilog169, %if.end
  %6 = load i32, i32* %argc.addr, align 4, !dbg !283
  %7 = load i8**, i8*** %argv.addr, align 8, !dbg !284
  %call4 = call i32 @getopt_long(i32 %6, i8** %7, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.67, i64 0, i64 0), %struct.option* getelementptr inbounds ([66 x %struct.option], [66 x %struct.option]* @main.long_options, i64 0, i64 0), i32* null), !dbg !285
  store i32 %call4, i32* %c, align 4, !dbg !286
  %cmp = icmp ne i32 %call4, -1, !dbg !287
  br i1 %cmp, label %while.body, label %while.end, !dbg !282

while.body:                                       ; preds = %while.cond
  %8 = load i32, i32* %c, align 4, !dbg !288
  switch i32 %8, label %sw.epilog169 [
    i32 4, label %sw.bb
    i32 5, label %sw.bb6
    i32 8, label %sw.bb8
    i32 9, label %sw.bb10
    i32 10, label %sw.bb12
    i32 11, label %sw.bb14
    i32 13, label %sw.bb16
    i32 14, label %sw.bb18
    i32 17, label %sw.bb20
    i32 18, label %sw.bb22
    i32 19, label %sw.bb24
    i32 20, label %sw.bb26
    i32 21, label %sw.bb28
    i32 22, label %sw.bb30
    i32 98, label %sw.bb32
    i32 99, label %sw.bb34
    i32 100, label %sw.bb36
    i32 69, label %sw.bb38
    i32 70, label %sw.bb41
    i32 72, label %sw.bb43
    i32 104, label %sw.bb45
    i32 107, label %sw.bb46
    i32 76, label %sw.bb48
    i32 109, label %sw.bb50
    i32 78, label %sw.bb52
    i32 83, label %sw.bb54
    i32 115, label %sw.bb56
    i32 113, label %sw.bb58
    i32 114, label %sw.bb60
    i32 86, label %sw.bb62
    i32 118, label %sw.bb68
    i32 120, label %sw.bb70
    i32 1, label %sw.bb72
    i32 2, label %sw.bb74
    i32 3, label %sw.bb76
    i32 6, label %sw.bb78
    i32 7, label %sw.bb80
    i32 12, label %sw.bb82
    i32 15, label %sw.bb84
    i32 16, label %sw.bb86
    i32 23, label %sw.bb88
    i32 65, label %sw.bb90
    i32 97, label %sw.bb92
    i32 66, label %sw.bb94
    i32 67, label %sw.bb96
    i32 68, label %sw.bb98
    i32 101, label %sw.bb100
    i32 103, label %sw.bb112
    i32 73, label %sw.bb114
    i32 105, label %sw.bb116
    i32 108, label %sw.bb118
    i32 110, label %sw.bb120
    i32 79, label %sw.bb143
    i32 111, label %sw.bb145
    i32 80, label %sw.bb147
    i32 81, label %sw.bb149
    i32 82, label %sw.bb151
    i32 84, label %sw.bb153
    i32 116, label %sw.bb155
    i32 85, label %sw.bb157
    i32 119, label %sw.bb159
    i32 88, label %sw.bb161
    i32 89, label %sw.bb163
    i32 63, label %sw.bb165
  ], !dbg !290

sw.bb:                                            ; preds = %while.body
  %call5 = call i32 @setval(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.29, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !291
  br label %sw.epilog169, !dbg !293

sw.bb6:                                           ; preds = %while.body
  %call7 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.69, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !294
  br label %sw.epilog169, !dbg !295

sw.bb8:                                           ; preds = %while.body
  %call9 = call i32 @setval(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.70, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !296
  br label %sw.epilog169, !dbg !297

sw.bb10:                                          ; preds = %while.body
  %call11 = call i32 @setval(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.71, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !298
  br label %sw.epilog169, !dbg !299

sw.bb12:                                          ; preds = %while.body
  %call13 = call i32 @setval(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.72, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !300
  br label %sw.epilog169, !dbg !301

sw.bb14:                                          ; preds = %while.body
  %call15 = call i32 @setval(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.73, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !302
  br label %sw.epilog169, !dbg !303

sw.bb16:                                          ; preds = %while.body
  %call17 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.74, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !304
  br label %sw.epilog169, !dbg !305

sw.bb18:                                          ; preds = %while.body
  %call19 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.75, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !306
  br label %sw.epilog169, !dbg !307

sw.bb20:                                          ; preds = %while.body
  %9 = load i8*, i8** @optarg, align 8, !dbg !308
  %call21 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.76, i64 0, i64 0), i8* %9), !dbg !309
  br label %sw.epilog169, !dbg !310

sw.bb22:                                          ; preds = %while.body
  %call23 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.31, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !311
  br label %sw.epilog169, !dbg !312

sw.bb24:                                          ; preds = %while.body
  %call25 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.78, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !313
  br label %sw.epilog169, !dbg !314

sw.bb26:                                          ; preds = %while.body
  %call27 = call i32 @setval(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.79, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !315
  br label %sw.epilog169, !dbg !316

sw.bb28:                                          ; preds = %while.body
  %call29 = call i32 @setval(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.80, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !317
  br label %sw.epilog169, !dbg !318

sw.bb30:                                          ; preds = %while.body
  %call31 = call i32 @setval(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.81, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !319
  br label %sw.epilog169, !dbg !320

sw.bb32:                                          ; preds = %while.body
  %call33 = call i32 @setval(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.2, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !321
  br label %sw.epilog169, !dbg !322

sw.bb34:                                          ; preds = %while.body
  %call35 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.3, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !323
  br label %sw.epilog169, !dbg !324

sw.bb36:                                          ; preds = %while.body
  %call37 = call i32 @setval(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !325
  br label %sw.epilog169, !dbg !326

sw.bb38:                                          ; preds = %while.body
  %call39 = call i8* @ftp_getaddress(), !dbg !327
  %call40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.82, i64 0, i64 0), i8* %call39), !dbg !328
  call void @exit(i32 0) #7, !dbg !329
  unreachable, !dbg !329

sw.bb41:                                          ; preds = %while.body
  %call42 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.83, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !330
  br label %sw.epilog169, !dbg !331

sw.bb43:                                          ; preds = %while.body
  %call44 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.84, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !332
  br label %sw.epilog169, !dbg !333

sw.bb45:                                          ; preds = %while.body
  call void @print_help(), !dbg !334
  call void @exit(i32 0) #7, !dbg !335
  unreachable, !dbg !335

sw.bb46:                                          ; preds = %while.body
  %call47 = call i32 @setval(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.85, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !336
  br label %sw.epilog169, !dbg !337

sw.bb48:                                          ; preds = %while.body
  %call49 = call i32 @setval(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.86, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !338
  br label %sw.epilog169, !dbg !339

sw.bb50:                                          ; preds = %while.body
  %call51 = call i32 @setval(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.14, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !340
  br label %sw.epilog169, !dbg !341

sw.bb52:                                          ; preds = %while.body
  %call53 = call i32 @setval(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.30, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !342
  br label %sw.epilog169, !dbg !343

sw.bb54:                                          ; preds = %while.body
  %call55 = call i32 @setval(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.87, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !344
  br label %sw.epilog169, !dbg !345

sw.bb56:                                          ; preds = %while.body
  %call57 = call i32 @setval(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.88, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !346
  br label %sw.epilog169, !dbg !347

sw.bb58:                                          ; preds = %while.body
  %call59 = call i32 @setval(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.22, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !348
  br label %sw.epilog169, !dbg !349

sw.bb60:                                          ; preds = %while.body
  %call61 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.23, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !350
  br label %sw.epilog169, !dbg !351

sw.bb62:                                          ; preds = %while.body
  %10 = load i8*, i8** @version_string, align 8, !dbg !352
  %call63 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.89, i64 0, i64 0), i8* %10), !dbg !353
  %call64 = call i8* @libintl_gettext(i8* getelementptr inbounds ([303 x i8], [303 x i8]* @.str.91, i64 0, i64 0)), !dbg !354
  %call65 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.90, i64 0, i64 0), i8* %call64), !dbg !355
  %call66 = call i8* @libintl_gettext(i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.92, i64 0, i64 0)), !dbg !356
  %call67 = call i32 (i8*, ...) @printf(i8* %call66), !dbg !357
  call void @exit(i32 0) #7, !dbg !358
  unreachable, !dbg !358

sw.bb68:                                          ; preds = %while.body
  %call69 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.31, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !359
  br label %sw.epilog169, !dbg !360

sw.bb70:                                          ; preds = %while.body
  %call71 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.78, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !361
  br label %sw.epilog169, !dbg !362

sw.bb72:                                          ; preds = %while.body
  %11 = load i8*, i8** @optarg, align 8, !dbg !363
  %call73 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.93, i64 0, i64 0), i8* %11), !dbg !364
  br label %sw.epilog169, !dbg !365

sw.bb74:                                          ; preds = %while.body
  %12 = load i8*, i8** @optarg, align 8, !dbg !366
  %call75 = call i32 @setval(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.94, i64 0, i64 0), i8* %12), !dbg !367
  br label %sw.epilog169, !dbg !368

sw.bb76:                                          ; preds = %while.body
  %13 = load i8*, i8** @optarg, align 8, !dbg !369
  %call77 = call i32 @setval(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.47, i64 0, i64 0), i8* %13), !dbg !370
  br label %sw.epilog169, !dbg !371

sw.bb78:                                          ; preds = %while.body
  %14 = load i8*, i8** @optarg, align 8, !dbg !372
  %call79 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.95, i64 0, i64 0), i8* %14), !dbg !373
  br label %sw.epilog169, !dbg !374

sw.bb80:                                          ; preds = %while.body
  %15 = load i8*, i8** @optarg, align 8, !dbg !375
  %call81 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.48, i64 0, i64 0), i8* %15), !dbg !376
  br label %sw.epilog169, !dbg !377

sw.bb82:                                          ; preds = %while.body
  %16 = load i8*, i8** @optarg, align 8, !dbg !378
  %call83 = call i32 @setval(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.96, i64 0, i64 0), i8* %16), !dbg !379
  br label %sw.epilog169, !dbg !380

sw.bb84:                                          ; preds = %while.body
  %17 = load i8*, i8** @optarg, align 8, !dbg !381
  %call85 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.97, i64 0, i64 0), i8* %17), !dbg !382
  br label %sw.epilog169, !dbg !383

sw.bb86:                                          ; preds = %while.body
  %18 = load i8*, i8** @optarg, align 8, !dbg !384
  %call87 = call i32 @setval(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.98, i64 0, i64 0), i8* %18), !dbg !385
  br label %sw.epilog169, !dbg !386

sw.bb88:                                          ; preds = %while.body
  %19 = load i8*, i8** @optarg, align 8, !dbg !387
  %call89 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.35, i64 0, i64 0), i8* %19), !dbg !388
  br label %sw.epilog169, !dbg !389

sw.bb90:                                          ; preds = %while.body
  %20 = load i8*, i8** @optarg, align 8, !dbg !390
  %call91 = call i32 @setval(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i64 0, i64 0), i8* %20), !dbg !391
  br label %sw.epilog169, !dbg !392

sw.bb92:                                          ; preds = %while.body
  %21 = load i8*, i8** @optarg, align 8, !dbg !393
  %call93 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.99, i64 0, i64 0), i8* %21), !dbg !394
  store i32 1, i32* %append_to_log, align 4, !dbg !395
  br label %sw.epilog169, !dbg !396

sw.bb94:                                          ; preds = %while.body
  %22 = load i8*, i8** @optarg, align 8, !dbg !397
  %call95 = call i32 @setval(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.36, i64 0, i64 0), i8* %22), !dbg !398
  br label %sw.epilog169, !dbg !399

sw.bb96:                                          ; preds = %while.body
  %23 = load i8*, i8** @optarg, align 8, !dbg !400
  %call97 = call i32 @setval(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.37, i64 0, i64 0), i8* %23), !dbg !401
  br label %sw.epilog169, !dbg !402

sw.bb98:                                          ; preds = %while.body
  %24 = load i8*, i8** @optarg, align 8, !dbg !403
  %call99 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.41, i64 0, i64 0), i8* %24), !dbg !404
  br label %sw.epilog169, !dbg !405

sw.bb100:                                         ; preds = %while.body
  call void @llvm.dbg.declare(metadata i8** %com, metadata !406, metadata !DIExpression()), !dbg !408
  call void @llvm.dbg.declare(metadata i8** %val, metadata !409, metadata !DIExpression()), !dbg !410
  %25 = load i8*, i8** @optarg, align 8, !dbg !411
  %call101 = call i32 @parse_line(i8* %25, i8** %com, i8** %val), !dbg !413
  %tobool102 = icmp ne i32 %call101, 0, !dbg !413
  br i1 %tobool102, label %if.then103, label %if.else108, !dbg !414

if.then103:                                       ; preds = %sw.bb100
  %26 = load i8*, i8** %com, align 8, !dbg !415
  %27 = load i8*, i8** %val, align 8, !dbg !418
  %call104 = call i32 @setval(i8* %26, i8* %27), !dbg !419
  %tobool105 = icmp ne i32 %call104, 0, !dbg !419
  br i1 %tobool105, label %if.end107, label %if.then106, !dbg !420

if.then106:                                       ; preds = %if.then103
  call void @exit(i32 1) #7, !dbg !421
  unreachable, !dbg !421

if.end107:                                        ; preds = %if.then103
  br label %if.end111, !dbg !422

if.else108:                                       ; preds = %sw.bb100
  %28 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !423
  %call109 = call i8* @libintl_gettext(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.100, i64 0, i64 0)), !dbg !425
  %29 = load i8*, i8** @exec_name, align 8, !dbg !426
  %30 = load i8*, i8** @optarg, align 8, !dbg !427
  %call110 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %28, i8* %call109, i8* %29, i8* %30), !dbg !428
  call void @exit(i32 1) #7, !dbg !429
  unreachable, !dbg !429

if.end111:                                        ; preds = %if.end107
  %31 = load i8*, i8** %com, align 8, !dbg !430
  call void @free(i8* %31), !dbg !431
  %32 = load i8*, i8** %val, align 8, !dbg !432
  call void @free(i8* %32), !dbg !433
  br label %sw.epilog169, !dbg !434

sw.bb112:                                         ; preds = %while.body
  %33 = load i8*, i8** @optarg, align 8, !dbg !435
  %call113 = call i32 @setval(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i64 0, i64 0), i8* %33), !dbg !436
  br label %sw.epilog169, !dbg !437

sw.bb114:                                         ; preds = %while.body
  %34 = load i8*, i8** @optarg, align 8, !dbg !438
  %call115 = call i32 @setval(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.101, i64 0, i64 0), i8* %34), !dbg !439
  br label %sw.epilog169, !dbg !440

sw.bb116:                                         ; preds = %while.body
  %35 = load i8*, i8** @optarg, align 8, !dbg !441
  %call117 = call i32 @setval(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.102, i64 0, i64 0), i8* %35), !dbg !442
  br label %sw.epilog169, !dbg !443

sw.bb118:                                         ; preds = %while.body
  %36 = load i8*, i8** @optarg, align 8, !dbg !444
  %call119 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.103, i64 0, i64 0), i8* %36), !dbg !445
  br label %sw.epilog169, !dbg !446

sw.bb120:                                         ; preds = %while.body
  call void @llvm.dbg.declare(metadata i8** %p, metadata !447, metadata !DIExpression()), !dbg !449
  %37 = load i8*, i8** @optarg, align 8, !dbg !450
  store i8* %37, i8** %p, align 8, !dbg !452
  br label %for.cond, !dbg !453

for.cond:                                         ; preds = %for.inc, %sw.bb120
  %38 = load i8*, i8** %p, align 8, !dbg !454
  %39 = load i8, i8* %38, align 1, !dbg !456
  %tobool121 = icmp ne i8 %39, 0, !dbg !457
  br i1 %tobool121, label %for.body, label %for.end, !dbg !457

for.body:                                         ; preds = %for.cond
  %40 = load i8*, i8** %p, align 8, !dbg !458
  %41 = load i8, i8* %40, align 1, !dbg !459
  %conv = sext i8 %41 to i32, !dbg !459
  switch i32 %conv, label %sw.default [
    i32 118, label %sw.bb122
    i32 104, label %sw.bb124
    i32 72, label %sw.bb126
    i32 100, label %sw.bb128
    i32 99, label %sw.bb130
    i32 114, label %sw.bb132
    i32 112, label %sw.bb134
  ], !dbg !460

sw.bb122:                                         ; preds = %for.body
  %call123 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.31, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !461
  br label %sw.epilog, !dbg !463

sw.bb124:                                         ; preds = %for.body
  %call125 = call i32 @setval(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.81, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !464
  br label %sw.epilog, !dbg !465

sw.bb126:                                         ; preds = %for.body
  %call127 = call i32 @setval(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.79, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !466
  br label %sw.epilog, !dbg !467

sw.bb128:                                         ; preds = %for.body
  %call129 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.78, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !468
  br label %sw.epilog, !dbg !469

sw.bb130:                                         ; preds = %for.body
  %call131 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.74, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !470
  br label %sw.epilog, !dbg !471

sw.bb132:                                         ; preds = %for.body
  %call133 = call i32 @setval(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.80, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.77, i64 0, i64 0)), !dbg !472
  br label %sw.epilog, !dbg !473

sw.bb134:                                         ; preds = %for.body
  %call135 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.69, i64 0, i64 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i64 0, i64 0)), !dbg !474
  br label %sw.epilog, !dbg !475

sw.default:                                       ; preds = %for.body
  %call136 = call i8* @libintl_gettext(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.104, i64 0, i64 0)), !dbg !476
  %42 = load i8*, i8** @exec_name, align 8, !dbg !477
  %43 = load i8*, i8** %p, align 8, !dbg !478
  %44 = load i8, i8* %43, align 1, !dbg !479
  %conv137 = sext i8 %44 to i32, !dbg !479
  %call138 = call i32 (i8*, ...) @printf(i8* %call136, i8* %42, i32 %conv137), !dbg !480
  call void @print_usage(), !dbg !481
  %call139 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0)), !dbg !482
  %call140 = call i8* @libintl_gettext(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.106, i64 0, i64 0)), !dbg !483
  %45 = load i8*, i8** @exec_name, align 8, !dbg !484
  %call141 = call i32 (i8*, ...) @printf(i8* %call140, i8* %45), !dbg !485
  call void @exit(i32 1) #7, !dbg !486
  unreachable, !dbg !486

sw.epilog:                                        ; preds = %sw.bb134, %sw.bb132, %sw.bb130, %sw.bb128, %sw.bb126, %sw.bb124, %sw.bb122
  br label %for.inc, !dbg !487

for.inc:                                          ; preds = %sw.epilog
  %46 = load i8*, i8** %p, align 8, !dbg !488
  %incdec.ptr142 = getelementptr inbounds i8, i8* %46, i32 1, !dbg !488
  store i8* %incdec.ptr142, i8** %p, align 8, !dbg !488
  br label %for.cond, !dbg !489, !llvm.loop !490

for.end:                                          ; preds = %for.cond
  br label %sw.epilog169, !dbg !492

sw.bb143:                                         ; preds = %while.body
  %47 = load i8*, i8** @optarg, align 8, !dbg !493
  %call144 = call i32 @setval(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.107, i64 0, i64 0), i8* %47), !dbg !494
  br label %sw.epilog169, !dbg !495

sw.bb145:                                         ; preds = %while.body
  %48 = load i8*, i8** @optarg, align 8, !dbg !496
  %call146 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.99, i64 0, i64 0), i8* %48), !dbg !497
  br label %sw.epilog169, !dbg !498

sw.bb147:                                         ; preds = %while.body
  %49 = load i8*, i8** @optarg, align 8, !dbg !499
  %call148 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.108, i64 0, i64 0), i8* %49), !dbg !500
  br label %sw.epilog169, !dbg !501

sw.bb149:                                         ; preds = %while.body
  %50 = load i8*, i8** @optarg, align 8, !dbg !502
  %call150 = call i32 @setval(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.60, i64 0, i64 0), i8* %50), !dbg !503
  br label %sw.epilog169, !dbg !504

sw.bb151:                                         ; preds = %while.body
  %51 = load i8*, i8** @optarg, align 8, !dbg !505
  %call152 = call i32 @setval(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.61, i64 0, i64 0), i8* %51), !dbg !506
  br label %sw.epilog169, !dbg !507

sw.bb153:                                         ; preds = %while.body
  %52 = load i8*, i8** @optarg, align 8, !dbg !508
  %call154 = call i32 @setval(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.62, i64 0, i64 0), i8* %52), !dbg !509
  br label %sw.epilog169, !dbg !510

sw.bb155:                                         ; preds = %while.body
  %53 = load i8*, i8** @optarg, align 8, !dbg !511
  %call156 = call i32 @setval(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.63, i64 0, i64 0), i8* %53), !dbg !512
  br label %sw.epilog169, !dbg !513

sw.bb157:                                         ; preds = %while.body
  %54 = load i8*, i8** @optarg, align 8, !dbg !514
  %call158 = call i32 @setval(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.109, i64 0, i64 0), i8* %54), !dbg !515
  br label %sw.epilog169, !dbg !516

sw.bb159:                                         ; preds = %while.body
  %55 = load i8*, i8** @optarg, align 8, !dbg !517
  %call160 = call i32 @setval(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.66, i64 0, i64 0), i8* %55), !dbg !518
  br label %sw.epilog169, !dbg !519

sw.bb161:                                         ; preds = %while.body
  %56 = load i8*, i8** @optarg, align 8, !dbg !520
  %call162 = call i32 @setval(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.110, i64 0, i64 0), i8* %56), !dbg !521
  br label %sw.epilog169, !dbg !522

sw.bb163:                                         ; preds = %while.body
  %57 = load i8*, i8** @optarg, align 8, !dbg !523
  %call164 = call i32 @setval(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.111, i64 0, i64 0), i8* %57), !dbg !524
  br label %sw.epilog169, !dbg !525

sw.bb165:                                         ; preds = %while.body
  call void @print_usage(), !dbg !526
  %call166 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0)), !dbg !527
  %call167 = call i8* @libintl_gettext(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.106, i64 0, i64 0)), !dbg !528
  %58 = load i8*, i8** @exec_name, align 8, !dbg !529
  %call168 = call i32 (i8*, ...) @printf(i8* %call167, i8* %58), !dbg !530
  call void @exit(i32 0) #7, !dbg !531
  unreachable, !dbg !531

sw.epilog169:                                     ; preds = %while.body, %sw.bb163, %sw.bb161, %sw.bb159, %sw.bb157, %sw.bb155, %sw.bb153, %sw.bb151, %sw.bb149, %sw.bb147, %sw.bb145, %sw.bb143, %for.end, %sw.bb118, %sw.bb116, %sw.bb114, %sw.bb112, %if.end111, %sw.bb98, %sw.bb96, %sw.bb94, %sw.bb92, %sw.bb90, %sw.bb88, %sw.bb86, %sw.bb84, %sw.bb82, %sw.bb80, %sw.bb78, %sw.bb76, %sw.bb74, %sw.bb72, %sw.bb70, %sw.bb68, %sw.bb60, %sw.bb58, %sw.bb56, %sw.bb54, %sw.bb52, %sw.bb50, %sw.bb48, %sw.bb46, %sw.bb43, %sw.bb41, %sw.bb36, %sw.bb34, %sw.bb32, %sw.bb30, %sw.bb28, %sw.bb26, %sw.bb24, %sw.bb22, %sw.bb20, %sw.bb18, %sw.bb16, %sw.bb14, %sw.bb12, %sw.bb10, %sw.bb8, %sw.bb6, %sw.bb
  br label %while.cond, !dbg !282, !llvm.loop !532

while.end:                                        ; preds = %while.cond
  %59 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 0), align 8, !dbg !534
  %cmp170 = icmp eq i32 %59, -1, !dbg !536
  br i1 %cmp170, label %if.then172, label %if.end174, !dbg !537

if.then172:                                       ; preds = %while.end
  %60 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 1), align 4, !dbg !538
  %tobool173 = icmp ne i32 %60, 0, !dbg !539
  %lnot = xor i1 %tobool173, true, !dbg !539
  %lnot.ext = zext i1 %lnot to i32, !dbg !539
  store i32 %lnot.ext, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 0), align 8, !dbg !540
  br label %if.end174, !dbg !541

if.end174:                                        ; preds = %if.then172, %while.end
  %61 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 0), align 8, !dbg !542
  %tobool175 = icmp ne i32 %61, 0, !dbg !544
  br i1 %tobool175, label %land.lhs.true, label %if.end180, !dbg !545

land.lhs.true:                                    ; preds = %if.end174
  %62 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 1), align 4, !dbg !546
  %tobool176 = icmp ne i32 %62, 0, !dbg !547
  br i1 %tobool176, label %if.then177, label %if.end180, !dbg !548

if.then177:                                       ; preds = %land.lhs.true
  %call178 = call i8* @libintl_gettext(i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.112, i64 0, i64 0)), !dbg !549
  %call179 = call i32 (i8*, ...) @printf(i8* %call178), !dbg !551
  call void @print_usage(), !dbg !552
  call void @exit(i32 1) #7, !dbg !553
  unreachable, !dbg !553

if.end180:                                        ; preds = %land.lhs.true, %if.end174
  %63 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 59), align 8, !dbg !554
  %tobool181 = icmp ne i32 %63, 0, !dbg !556
  br i1 %tobool181, label %land.lhs.true182, label %if.end187, !dbg !557

land.lhs.true182:                                 ; preds = %if.end180
  %64 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 16), align 8, !dbg !558
  %tobool183 = icmp ne i32 %64, 0, !dbg !559
  br i1 %tobool183, label %if.then184, label %if.end187, !dbg !560

if.then184:                                       ; preds = %land.lhs.true182
  %call185 = call i8* @libintl_gettext(i8* getelementptr inbounds ([61 x i8], [61 x i8]* @.str.113, i64 0, i64 0)), !dbg !561
  %call186 = call i32 (i8*, ...) @printf(i8* %call185), !dbg !563
  call void @print_usage(), !dbg !564
  call void @exit(i32 1) #7, !dbg !565
  unreachable, !dbg !565

if.end187:                                        ; preds = %land.lhs.true182, %if.end180
  %65 = load i32, i32* %argc.addr, align 4, !dbg !566
  %66 = load i32, i32* @optind, align 4, !dbg !567
  %sub = sub nsw i32 %65, %66, !dbg !568
  store i32 %sub, i32* %nurl, align 4, !dbg !569
  %67 = load i32, i32* %nurl, align 4, !dbg !570
  %tobool188 = icmp ne i32 %67, 0, !dbg !570
  br i1 %tobool188, label %if.end197, label %land.lhs.true189, !dbg !572

land.lhs.true189:                                 ; preds = %if.end187
  %68 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 20), align 8, !dbg !573
  %tobool190 = icmp ne i8* %68, null, !dbg !574
  br i1 %tobool190, label %if.end197, label %if.then191, !dbg !575

if.then191:                                       ; preds = %land.lhs.true189
  %call192 = call i8* @libintl_gettext(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.114, i64 0, i64 0)), !dbg !576
  %69 = load i8*, i8** @exec_name, align 8, !dbg !578
  %call193 = call i32 (i8*, ...) @printf(i8* %call192, i8* %69), !dbg !579
  call void @print_usage(), !dbg !580
  %call194 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.105, i64 0, i64 0)), !dbg !581
  %call195 = call i8* @libintl_gettext(i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.106, i64 0, i64 0)), !dbg !582
  %70 = load i8*, i8** @exec_name, align 8, !dbg !583
  %call196 = call i32 (i8*, ...) @printf(i8* %call195, i8* %70), !dbg !584
  call void @exit(i32 1) #7, !dbg !585
  unreachable, !dbg !585

if.end197:                                        ; preds = %land.lhs.true189, %if.end187
  %71 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 3), align 4, !dbg !586
  %tobool198 = icmp ne i32 %71, 0, !dbg !588
  br i1 %tobool198, label %if.then199, label %if.end200, !dbg !589

if.then199:                                       ; preds = %if.end197
  call void @fork_to_background(), !dbg !590
  br label %if.end200, !dbg !590

if.end200:                                        ; preds = %if.then199, %if.end197
  %72 = load i32, i32* %nurl, align 4, !dbg !591
  %add = add nsw i32 %72, 1, !dbg !591
  %conv201 = sext i32 %add to i64, !dbg !591
  %mul = mul i64 %conv201, 8, !dbg !591
  %73 = alloca i8, i64 %mul, align 16, !dbg !591
  %74 = bitcast i8* %73 to i8**, !dbg !591
  store i8** %74, i8*** %url, align 8, !dbg !592
  store i32 0, i32* %i, align 4, !dbg !593
  br label %for.cond202, !dbg !595

for.cond202:                                      ; preds = %for.inc214, %if.end200
  %75 = load i32, i32* %i, align 4, !dbg !596
  %76 = load i32, i32* %nurl, align 4, !dbg !598
  %cmp203 = icmp slt i32 %75, %76, !dbg !599
  br i1 %cmp203, label %for.body205, label %for.end216, !dbg !600

for.body205:                                      ; preds = %for.cond202
  call void @llvm.dbg.declare(metadata i8** %irix4_cc_needs_this, metadata !601, metadata !DIExpression()), !dbg !603
  br label %do.body, !dbg !604

do.body:                                          ; preds = %for.body205
  %77 = load i8**, i8*** %argv.addr, align 8, !dbg !605
  %78 = load i32, i32* @optind, align 4, !dbg !605
  %idxprom = sext i32 %78 to i64, !dbg !605
  %arrayidx206 = getelementptr inbounds i8*, i8** %77, i64 %idxprom, !dbg !605
  %79 = load i8*, i8** %arrayidx206, align 8, !dbg !605
  %call207 = call i64 @strlen(i8* %79), !dbg !605
  %add208 = add i64 %call207, 1, !dbg !605
  %80 = alloca i8, i64 %add208, align 16, !dbg !605
  store i8* %80, i8** %irix4_cc_needs_this, align 8, !dbg !605
  %81 = load i8*, i8** %irix4_cc_needs_this, align 8, !dbg !605
  %82 = load i8**, i8*** %argv.addr, align 8, !dbg !605
  %83 = load i32, i32* @optind, align 4, !dbg !605
  %idxprom209 = sext i32 %83 to i64, !dbg !605
  %arrayidx210 = getelementptr inbounds i8*, i8** %82, i64 %idxprom209, !dbg !605
  %84 = load i8*, i8** %arrayidx210, align 8, !dbg !605
  %85 = load i8*, i8** %irix4_cc_needs_this, align 8, !dbg !605
  %86 = call i64 @llvm.objectsize.i64.p0i8(i8* %85, i1 false, i1 true, i1 false), !dbg !605
  %call211 = call i8* @__strcpy_chk(i8* %81, i8* %84, i64 %86) #8, !dbg !605
  br label %do.end, !dbg !605

do.end:                                           ; preds = %do.body
  %87 = load i8*, i8** %irix4_cc_needs_this, align 8, !dbg !607
  %88 = load i8**, i8*** %url, align 8, !dbg !608
  %89 = load i32, i32* %i, align 4, !dbg !609
  %idxprom212 = sext i32 %89 to i64, !dbg !608
  %arrayidx213 = getelementptr inbounds i8*, i8** %88, i64 %idxprom212, !dbg !608
  store i8* %87, i8** %arrayidx213, align 8, !dbg !610
  br label %for.inc214, !dbg !611

for.inc214:                                       ; preds = %do.end
  %90 = load i32, i32* %i, align 4, !dbg !612
  %inc = add nsw i32 %90, 1, !dbg !612
  store i32 %inc, i32* %i, align 4, !dbg !612
  %91 = load i32, i32* @optind, align 4, !dbg !613
  %inc215 = add nsw i32 %91, 1, !dbg !613
  store i32 %inc215, i32* @optind, align 4, !dbg !613
  br label %for.cond202, !dbg !614, !llvm.loop !615

for.end216:                                       ; preds = %for.cond202
  %92 = load i8**, i8*** %url, align 8, !dbg !617
  %93 = load i32, i32* %i, align 4, !dbg !618
  %idxprom217 = sext i32 %93 to i64, !dbg !617
  %arrayidx218 = getelementptr inbounds i8*, i8** %92, i64 %idxprom217, !dbg !617
  store i8* null, i8** %arrayidx218, align 8, !dbg !619
  %94 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 18), align 8, !dbg !620
  %95 = load i32, i32* %append_to_log, align 4, !dbg !621
  call void @log_init(i8* %94, i32 %95), !dbg !622
  br label %do.body219, !dbg !623

do.body219:                                       ; preds = %for.end216
  %96 = load i8*, i8** @version_string, align 8, !dbg !624
  call void (i8*, ...) @debug_logprintf(i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.115, i64 0, i64 0), i8* %96, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.116, i64 0, i64 0)), !dbg !624
  br label %do.end220, !dbg !624

do.end220:                                        ; preds = %do.body219
  %97 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 31), align 8, !dbg !626
  %tobool221 = icmp ne i8* %97, null, !dbg !628
  br i1 %tobool221, label %if.then222, label %if.end236, !dbg !629

if.then222:                                       ; preds = %do.end220
  %98 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 31), align 8, !dbg !630
  %99 = load i8, i8* %98, align 1, !dbg !630
  %conv223 = sext i8 %99 to i32, !dbg !630
  %cmp224 = icmp eq i32 %conv223, 45, !dbg !630
  br i1 %cmp224, label %land.lhs.true226, label %if.else229, !dbg !630

land.lhs.true226:                                 ; preds = %if.then222
  %100 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 31), align 8, !dbg !630
  %add.ptr = getelementptr inbounds i8, i8* %100, i64 1, !dbg !630
  %101 = load i8, i8* %add.ptr, align 1, !dbg !630
  %tobool227 = icmp ne i8 %101, 0, !dbg !630
  br i1 %tobool227, label %if.else229, label %if.then228, !dbg !633

if.then228:                                       ; preds = %land.lhs.true226
  %102 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8, !dbg !634
  store %struct.__sFILE* %102, %struct.__sFILE** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 32), align 8, !dbg !635
  br label %if.end235, !dbg !636

if.else229:                                       ; preds = %land.lhs.true226, %if.then222
  %103 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 31), align 8, !dbg !637
  %call230 = call %struct.__sFILE* @"\01_fopen"(i8* %103, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.117, i64 0, i64 0)), !dbg !639
  store %struct.__sFILE* %call230, %struct.__sFILE** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 32), align 8, !dbg !640
  %104 = load %struct.__sFILE*, %struct.__sFILE** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 32), align 8, !dbg !641
  %cmp231 = icmp eq %struct.__sFILE* %104, null, !dbg !643
  br i1 %cmp231, label %if.then233, label %if.end234, !dbg !644

if.then233:                                       ; preds = %if.else229
  %105 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 31), align 8, !dbg !645
  call void @perror(i8* %105) #9, !dbg !647
  call void @exit(i32 1) #7, !dbg !648
  unreachable, !dbg !648

if.end234:                                        ; preds = %if.else229
  br label %if.end235

if.end235:                                        ; preds = %if.end234, %if.then228
  br label %if.end236, !dbg !649

if.end236:                                        ; preds = %if.end235, %do.end220
  %call237 = call void (i32)* @signal(i32 1, void (i32)* inttoptr (i64 1 to void (i32)*)), !dbg !650
  %cmp238 = icmp ne void (i32)* %call237, inttoptr (i64 1 to void (i32)*), !dbg !652
  br i1 %cmp238, label %if.then240, label %if.end242, !dbg !653

if.then240:                                       ; preds = %if.end236
  %call241 = call void (i32)* @signal(i32 1, void (i32)* @redirect_output_signal), !dbg !654
  br label %if.end242, !dbg !654

if.end242:                                        ; preds = %if.then240, %if.end236
  %call243 = call void (i32)* @signal(i32 30, void (i32)* @redirect_output_signal), !dbg !655
  %call244 = call void (i32)* @signal(i32 13, void (i32)* inttoptr (i64 1 to void (i32)*)), !dbg !656
  store i32 39, i32* %status, align 4, !dbg !657
  call void @recursive_reset(), !dbg !658
  %106 = load i8**, i8*** %url, align 8, !dbg !659
  store i8** %106, i8*** %t, align 8, !dbg !661
  br label %for.cond245, !dbg !662

for.cond245:                                      ; preds = %for.inc269, %if.end242
  %107 = load i8**, i8*** %t, align 8, !dbg !663
  %108 = load i8*, i8** %107, align 8, !dbg !665
  %tobool246 = icmp ne i8* %108, null, !dbg !666
  br i1 %tobool246, label %for.body247, label %for.end271, !dbg !666

for.body247:                                      ; preds = %for.cond245
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !667, metadata !DIExpression()), !dbg !669
  call void @llvm.dbg.declare(metadata i8** %new_file, metadata !670, metadata !DIExpression()), !dbg !671
  call void @llvm.dbg.declare(metadata i32* %dt, metadata !672, metadata !DIExpression()), !dbg !673
  %109 = load i8**, i8*** %t, align 8, !dbg !674
  %110 = load i8*, i8** %109, align 8, !dbg !675
  %call248 = call i32 @retrieve_url(i8* %110, i8** %filename, i8** %new_file, i8* null, i32* %dt), !dbg !676
  store i32 %call248, i32* %status, align 4, !dbg !677
  %111 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 6), align 8, !dbg !678
  %tobool249 = icmp ne i32 %111, 0, !dbg !680
  br i1 %tobool249, label %land.lhs.true250, label %if.end258, !dbg !681

land.lhs.true250:                                 ; preds = %for.body247
  %112 = load i32, i32* %status, align 4, !dbg !682
  %cmp251 = icmp eq i32 %112, 39, !dbg !683
  br i1 %cmp251, label %land.lhs.true253, label %if.end258, !dbg !684

land.lhs.true253:                                 ; preds = %land.lhs.true250
  %113 = load i32, i32* %dt, align 4, !dbg !685
  %and = and i32 %113, 1, !dbg !686
  %tobool254 = icmp ne i32 %and, 0, !dbg !686
  br i1 %tobool254, label %if.then255, label %if.end258, !dbg !687

if.then255:                                       ; preds = %land.lhs.true253
  %114 = load i8*, i8** %filename, align 8, !dbg !688
  %115 = load i8*, i8** %new_file, align 8, !dbg !689
  %tobool256 = icmp ne i8* %115, null, !dbg !689
  br i1 %tobool256, label %cond.true, label %cond.false, !dbg !689

cond.true:                                        ; preds = %if.then255
  %116 = load i8*, i8** %new_file, align 8, !dbg !690
  br label %cond.end, !dbg !689

cond.false:                                       ; preds = %if.then255
  %117 = load i8**, i8*** %t, align 8, !dbg !691
  %118 = load i8*, i8** %117, align 8, !dbg !692
  br label %cond.end, !dbg !689

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i8* [ %116, %cond.true ], [ %118, %cond.false ], !dbg !689
  %call257 = call i32 @recursive_retrieve(i8* %114, i8* %cond), !dbg !693
  store i32 %call257, i32* %status, align 4, !dbg !694
  br label %if.end258, !dbg !695

if.end258:                                        ; preds = %cond.end, %land.lhs.true253, %land.lhs.true250, %for.body247
  br label %do.body259, !dbg !696

do.body259:                                       ; preds = %if.end258
  %119 = load i8*, i8** %new_file, align 8, !dbg !697
  %tobool260 = icmp ne i8* %119, null, !dbg !697
  br i1 %tobool260, label %if.then261, label %if.end262, !dbg !700

if.then261:                                       ; preds = %do.body259
  %120 = load i8*, i8** %new_file, align 8, !dbg !697
  call void @free(i8* %120), !dbg !697
  br label %if.end262, !dbg !697

if.end262:                                        ; preds = %if.then261, %do.body259
  br label %do.end263, !dbg !700

do.end263:                                        ; preds = %if.end262
  br label %do.body264, !dbg !701

do.body264:                                       ; preds = %do.end263
  %121 = load i8*, i8** %filename, align 8, !dbg !702
  %tobool265 = icmp ne i8* %121, null, !dbg !702
  br i1 %tobool265, label %if.then266, label %if.end267, !dbg !705

if.then266:                                       ; preds = %do.body264
  %122 = load i8*, i8** %filename, align 8, !dbg !702
  call void @free(i8* %122), !dbg !702
  br label %if.end267, !dbg !702

if.end267:                                        ; preds = %if.then266, %do.body264
  br label %do.end268, !dbg !705

do.end268:                                        ; preds = %if.end267
  br label %for.inc269, !dbg !706

for.inc269:                                       ; preds = %do.end268
  %123 = load i8**, i8*** %t, align 8, !dbg !707
  %incdec.ptr270 = getelementptr inbounds i8*, i8** %123, i32 1, !dbg !707
  store i8** %incdec.ptr270, i8*** %t, align 8, !dbg !707
  br label %for.cond245, !dbg !708, !llvm.loop !709

for.end271:                                       ; preds = %for.cond245
  %124 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 20), align 8, !dbg !711
  %tobool272 = icmp ne i8* %124, null, !dbg !713
  br i1 %tobool272, label %if.then273, label %if.end279, !dbg !714

if.then273:                                       ; preds = %for.end271
  call void @llvm.dbg.declare(metadata i32* %count, metadata !715, metadata !DIExpression()), !dbg !717
  %125 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 20), align 8, !dbg !718
  %126 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 21), align 8, !dbg !719
  %call274 = call i32 @retrieve_from_file(i8* %125, i32 %126, i32* %count), !dbg !720
  store i32 %call274, i32* %status, align 4, !dbg !721
  %127 = load i32, i32* %count, align 4, !dbg !722
  %tobool275 = icmp ne i32 %127, 0, !dbg !722
  br i1 %tobool275, label %if.end278, label %if.then276, !dbg !724

if.then276:                                       ; preds = %if.then273
  %call277 = call i8* @libintl_gettext(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.118, i64 0, i64 0)), !dbg !725
  %128 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 20), align 8, !dbg !726
  call void (i32, i8*, ...) @logprintf(i32 1, i8* %call277, i8* %128), !dbg !727
  br label %if.end278, !dbg !727

if.end278:                                        ; preds = %if.then276, %if.then273
  br label %if.end279, !dbg !728

if.end279:                                        ; preds = %if.end278, %for.end271
  %129 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 6), align 8, !dbg !729
  %tobool280 = icmp ne i32 %129, 0, !dbg !731
  br i1 %tobool280, label %if.then288, label %lor.lhs.false, !dbg !732

lor.lhs.false:                                    ; preds = %if.end279
  %130 = load i32, i32* %nurl, align 4, !dbg !733
  %cmp281 = icmp sgt i32 %130, 1, !dbg !734
  br i1 %cmp281, label %if.then288, label %lor.lhs.false283, !dbg !735

lor.lhs.false283:                                 ; preds = %lor.lhs.false
  %131 = load i8*, i8** getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 20), align 8, !dbg !736
  %tobool284 = icmp ne i8* %131, null, !dbg !737
  br i1 %tobool284, label %land.lhs.true285, label %if.end300, !dbg !738

land.lhs.true285:                                 ; preds = %lor.lhs.false283
  %132 = load i64, i64* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 54), align 8, !dbg !739
  %cmp286 = icmp ne i64 %132, 0, !dbg !740
  br i1 %cmp286, label %if.then288, label %if.end300, !dbg !741

if.then288:                                       ; preds = %land.lhs.true285, %lor.lhs.false, %if.end279
  %call289 = call i8* @libintl_gettext(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.119, i64 0, i64 0)), !dbg !742
  %call290 = call i8* @time_str(i64* null), !dbg !744
  %133 = load i64, i64* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 54), align 8, !dbg !745
  %call291 = call i8* @legible(i64 %133), !dbg !746
  %134 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 55), align 8, !dbg !747
  call void (i32, i8*, ...) @logprintf(i32 1, i8* %call289, i8* %call290, i8* %call291, i32 %134), !dbg !748
  %135 = load i64, i64* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 53), align 8, !dbg !749
  %tobool292 = icmp ne i64 %135, 0, !dbg !751
  br i1 %tobool292, label %land.lhs.true293, label %if.end299, !dbg !752

land.lhs.true293:                                 ; preds = %if.then288
  %136 = load i64, i64* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 54), align 8, !dbg !753
  %137 = load i64, i64* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 53), align 8, !dbg !754
  %cmp294 = icmp sgt i64 %136, %137, !dbg !755
  br i1 %cmp294, label %if.then296, label %if.end299, !dbg !756

if.then296:                                       ; preds = %land.lhs.true293
  %call297 = call i8* @libintl_gettext(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.120, i64 0, i64 0)), !dbg !757
  %138 = load i64, i64* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 53), align 8, !dbg !758
  %call298 = call i8* @legible(i64 %138), !dbg !759
  call void (i32, i8*, ...) @logprintf(i32 1, i8* %call297, i8* %call298), !dbg !760
  br label %if.end299, !dbg !760

if.end299:                                        ; preds = %if.then296, %land.lhs.true293, %if.then288
  br label %if.end300, !dbg !761

if.end300:                                        ; preds = %if.end299, %land.lhs.true285, %lor.lhs.false283
  %139 = load i32, i32* getelementptr inbounds (%struct.options, %struct.options* @opt, i32 0, i32 62), align 8, !dbg !762
  %tobool301 = icmp ne i32 %139, 0, !dbg !764
  br i1 %tobool301, label %if.then302, label %if.end303, !dbg !765

if.then302:                                       ; preds = %if.end300
  call void @convert_all_links(), !dbg !766
  br label %if.end303, !dbg !768

if.end303:                                        ; preds = %if.then302, %if.end300
  call void @log_close(), !dbg !769
  call void @cleanup(), !dbg !770
  %140 = load i32, i32* %status, align 4, !dbg !771
  %cmp304 = icmp eq i32 %140, 39, !dbg !773
  br i1 %cmp304, label %if.then306, label %if.else307, !dbg !774

if.then306:                                       ; preds = %if.end303
  store i32 0, i32* %retval, align 4, !dbg !775
  br label %return, !dbg !775

if.else307:                                       ; preds = %if.end303
  store i32 1, i32* %retval, align 4, !dbg !776
  br label %return, !dbg !776

return:                                           ; preds = %if.else307, %if.then306
  %141 = load i32, i32* %retval, align 4, !dbg !777
  ret i32 %141, !dbg !777
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @i18n_initialize() #0 !dbg !778 {
entry:
  %call = call i8* @libintl_setlocale(i32 6, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.116, i64 0, i64 0)), !dbg !781
  %call1 = call i8* @libintl_bindtextdomain(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.121, i64 0, i64 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.122, i64 0, i64 0)), !dbg !782
  %call2 = call i8* @libintl_textdomain(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.121, i64 0, i64 0)), !dbg !783
  ret void, !dbg !784
}

declare i8* @strrchr(i8*, i32) #3

declare void @initialize() #3

declare i32 @getopt_long(i32, i8**, i8*, %struct.option*, i32*) #3

declare i32 @setval(i8*, i8*) #3

declare i32 @printf(i8*, ...) #3

declare i8* @ftp_getaddress() #3

; Function Attrs: noreturn
declare void @exit(i32) #4

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @print_help() #0 !dbg !785 {
entry:
  %call = call i8* @libintl_gettext(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.123, i64 0, i64 0)), !dbg !786
  %0 = load i8*, i8** @version_string, align 8, !dbg !787
  %call1 = call i32 (i8*, ...) @printf(i8* %call, i8* %0), !dbg !788
  call void @print_usage(), !dbg !789
  %call2 = call i8* @libintl_gettext(i8* getelementptr inbounds ([76 x i8], [76 x i8]* @.str.125, i64 0, i64 0)), !dbg !790
  %call3 = call i8* @libintl_gettext(i8* getelementptr inbounds ([235 x i8], [235 x i8]* @.str.126, i64 0, i64 0)), !dbg !791
  %call4 = call i8* @libintl_gettext(i8* getelementptr inbounds ([477 x i8], [477 x i8]* @.str.127, i64 0, i64 0)), !dbg !792
  %call5 = call i8* @libintl_gettext(i8* getelementptr inbounds ([769 x i8], [769 x i8]* @.str.128, i64 0, i64 0)), !dbg !793
  %call6 = call i8* @libintl_gettext(i8* getelementptr inbounds ([346 x i8], [346 x i8]* @.str.129, i64 0, i64 0)), !dbg !794
  %call7 = call i8* @libintl_gettext(i8* getelementptr inbounds ([578 x i8], [578 x i8]* @.str.130, i64 0, i64 0)), !dbg !795
  %call8 = call i8* @libintl_gettext(i8* getelementptr inbounds ([187 x i8], [187 x i8]* @.str.131, i64 0, i64 0)), !dbg !796
  %call9 = call i8* @libintl_gettext(i8* getelementptr inbounds ([423 x i8], [423 x i8]* @.str.132, i64 0, i64 0)), !dbg !797
  %call10 = call i8* @libintl_gettext(i8* getelementptr inbounds ([772 x i8], [772 x i8]* @.str.133, i64 0, i64 0)), !dbg !798
  %call11 = call i8* @libintl_gettext(i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.134, i64 0, i64 0)), !dbg !799
  %call12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.124, i64 0, i64 0), i8* %call2, i8* %call3, i8* %call4, i8* %call5, i8* %call6, i8* %call7, i8* %call8, i8* %call9, i8* %call10, i8* %call11), !dbg !800
  ret void, !dbg !801
}

declare i8* @libintl_gettext(i8*) #3

declare i32 @parse_line(i8*, i8**, i8**) #3

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #3

declare void @free(i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @print_usage() #0 !dbg !802 {
entry:
  %call = call i8* @libintl_gettext(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.135, i64 0, i64 0)), !dbg !803
  %0 = load i8*, i8** @exec_name, align 8, !dbg !804
  %call1 = call i32 (i8*, ...) @printf(i8* %call, i8* %0), !dbg !805
  ret void, !dbg !806
}

declare void @fork_to_background() #3

declare i64 @strlen(i8*) #3

; Function Attrs: nounwind
declare i8* @__strcpy_chk(i8*, i8*, i64) #5

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1 immarg, i1 immarg, i1 immarg) #1

declare void @log_init(i8*, i32) #3

declare void @debug_logprintf(i8*, ...) #3

declare %struct.__sFILE* @"\01_fopen"(i8*, i8*) #3

; Function Attrs: cold
declare void @perror(i8*) #6

declare void (i32)* @signal(i32, void (i32)*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @redirect_output_signal(i32 %sig) #0 !dbg !807 {
entry:
  %sig.addr = alloca i32, align 4
  %tmp = alloca [100 x i8], align 16
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !808, metadata !DIExpression()), !dbg !809
  call void @llvm.dbg.declare(metadata [100 x i8]* %tmp, metadata !810, metadata !DIExpression()), !dbg !814
  %0 = load i32, i32* %sig.addr, align 4, !dbg !815
  %call = call void (i32)* @signal(i32 %0, void (i32)* @redirect_output_signal), !dbg !816
  %arraydecay = getelementptr inbounds [100 x i8], [100 x i8]* %tmp, i64 0, i64 0, !dbg !817
  %call1 = call i8* @libintl_gettext(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.136, i64 0, i64 0)), !dbg !817
  %1 = load i32, i32* %sig.addr, align 4, !dbg !817
  %cmp = icmp eq i32 %1, 1, !dbg !817
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !817

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !817

cond.false:                                       ; preds = %entry
  %2 = load i32, i32* %sig.addr, align 4, !dbg !817
  %cmp2 = icmp eq i32 %2, 30, !dbg !817
  %3 = zext i1 %cmp2 to i64, !dbg !817
  %cond = select i1 %cmp2, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.138, i64 0, i64 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.139, i64 0, i64 0), !dbg !817
  br label %cond.end, !dbg !817

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond3 = phi i8* [ getelementptr inbounds ([7 x i8], [7 x i8]* @.str.137, i64 0, i64 0), %cond.true ], [ %cond, %cond.false ], !dbg !817
  %call4 = call i32 (i8*, i32, i64, i8*, ...) @__sprintf_chk(i8* %arraydecay, i32 0, i64 100, i8* %call1, i8* %cond3), !dbg !817
  %arraydecay5 = getelementptr inbounds [100 x i8], [100 x i8]* %tmp, i64 0, i64 0, !dbg !818
  call void @redirect_output(i8* %arraydecay5), !dbg !819
  ret void, !dbg !820
}

declare void @recursive_reset() #3

declare i32 @retrieve_url(i8*, i8**, i8**, i8*, i32*) #3

declare i32 @recursive_retrieve(i8*, i8*) #3

declare i32 @retrieve_from_file(i8*, i32, i32*) #3

declare void @logprintf(i32, i8*, ...) #3

declare i8* @time_str(i64*) #3

declare i8* @legible(i64) #3

declare void @convert_all_links() #3

declare void @log_close() #3

declare void @cleanup() #3

declare i8* @libintl_setlocale(i32, i8*) #3

declare i8* @libintl_bindtextdomain(i8*, i8*) #3

declare i8* @libintl_textdomain(i8*) #3

declare i32 @__sprintf_chk(i8*, i32, i64, i8*, ...) #3

declare void @redirect_output(i8*) #3

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { nounwind willreturn }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { cold "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn }
attributes #8 = { nounwind }
attributes #9 = { cold }

!llvm.dbg.cu = !{!11}
!llvm.module.flags = !{!245, !246, !247, !248}
!llvm.ident = !{!249}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "long_options", scope: !2, file: !3, line: 200, type: !235, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 195, type: !4, scopeLine: 196, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !11, retainedNodes: !234)
!3 = !DIFile(filename: "main.c", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/wget-1.5.3/src")
!4 = !DISubroutineType(types: !5)
!5 = !{!6, !6, !7}
!6 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!8 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !9)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!11 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !12, retainedTypes: !89, globals: !96, nameTableKind: None)
!12 = !{!13, !76, !83}
!13 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !14, line: 184, baseType: !15, size: 32, elements: !16)
!14 = !DIFile(filename: "./wget.h", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/wget-1.5.3/src")
!15 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!16 = !{!17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75}
!17 = !DIEnumerator(name: "NOCONERROR", value: 0, isUnsigned: true)
!18 = !DIEnumerator(name: "HOSTERR", value: 1, isUnsigned: true)
!19 = !DIEnumerator(name: "CONSOCKERR", value: 2, isUnsigned: true)
!20 = !DIEnumerator(name: "CONERROR", value: 3, isUnsigned: true)
!21 = !DIEnumerator(name: "CONREFUSED", value: 4, isUnsigned: true)
!22 = !DIEnumerator(name: "NEWLOCATION", value: 5, isUnsigned: true)
!23 = !DIEnumerator(name: "NOTENOUGHMEM", value: 6, isUnsigned: true)
!24 = !DIEnumerator(name: "CONPORTERR", value: 7, isUnsigned: true)
!25 = !DIEnumerator(name: "BINDERR", value: 8, isUnsigned: true)
!26 = !DIEnumerator(name: "BINDOK", value: 9, isUnsigned: true)
!27 = !DIEnumerator(name: "LISTENERR", value: 10, isUnsigned: true)
!28 = !DIEnumerator(name: "ACCEPTERR", value: 11, isUnsigned: true)
!29 = !DIEnumerator(name: "ACCEPTOK", value: 12, isUnsigned: true)
!30 = !DIEnumerator(name: "CONCLOSED", value: 13, isUnsigned: true)
!31 = !DIEnumerator(name: "FTPOK", value: 14, isUnsigned: true)
!32 = !DIEnumerator(name: "FTPLOGINC", value: 15, isUnsigned: true)
!33 = !DIEnumerator(name: "FTPLOGREFUSED", value: 16, isUnsigned: true)
!34 = !DIEnumerator(name: "FTPPORTERR", value: 17, isUnsigned: true)
!35 = !DIEnumerator(name: "FTPNSFOD", value: 18, isUnsigned: true)
!36 = !DIEnumerator(name: "FTPRETROK", value: 19, isUnsigned: true)
!37 = !DIEnumerator(name: "FTPUNKNOWNTYPE", value: 20, isUnsigned: true)
!38 = !DIEnumerator(name: "FTPRERR", value: 21, isUnsigned: true)
!39 = !DIEnumerator(name: "FTPREXC", value: 22, isUnsigned: true)
!40 = !DIEnumerator(name: "FTPSRVERR", value: 23, isUnsigned: true)
!41 = !DIEnumerator(name: "FTPRETRINT", value: 24, isUnsigned: true)
!42 = !DIEnumerator(name: "FTPRESTFAIL", value: 25, isUnsigned: true)
!43 = !DIEnumerator(name: "URLOK", value: 26, isUnsigned: true)
!44 = !DIEnumerator(name: "URLHTTP", value: 27, isUnsigned: true)
!45 = !DIEnumerator(name: "URLFTP", value: 28, isUnsigned: true)
!46 = !DIEnumerator(name: "URLFILE", value: 29, isUnsigned: true)
!47 = !DIEnumerator(name: "URLUNKNOWN", value: 30, isUnsigned: true)
!48 = !DIEnumerator(name: "URLBADPORT", value: 31, isUnsigned: true)
!49 = !DIEnumerator(name: "URLBADHOST", value: 32, isUnsigned: true)
!50 = !DIEnumerator(name: "FOPENERR", value: 33, isUnsigned: true)
!51 = !DIEnumerator(name: "FWRITEERR", value: 34, isUnsigned: true)
!52 = !DIEnumerator(name: "HOK", value: 35, isUnsigned: true)
!53 = !DIEnumerator(name: "HLEXC", value: 36, isUnsigned: true)
!54 = !DIEnumerator(name: "HEOF", value: 37, isUnsigned: true)
!55 = !DIEnumerator(name: "HERR", value: 38, isUnsigned: true)
!56 = !DIEnumerator(name: "RETROK", value: 39, isUnsigned: true)
!57 = !DIEnumerator(name: "RECLEVELEXC", value: 40, isUnsigned: true)
!58 = !DIEnumerator(name: "FTPACCDENIED", value: 41, isUnsigned: true)
!59 = !DIEnumerator(name: "WRONGCODE", value: 42, isUnsigned: true)
!60 = !DIEnumerator(name: "FTPINVPASV", value: 43, isUnsigned: true)
!61 = !DIEnumerator(name: "FTPNOPASV", value: 44, isUnsigned: true)
!62 = !DIEnumerator(name: "RETRFINISHED", value: 45, isUnsigned: true)
!63 = !DIEnumerator(name: "READERR", value: 46, isUnsigned: true)
!64 = !DIEnumerator(name: "TRYLIMEXC", value: 47, isUnsigned: true)
!65 = !DIEnumerator(name: "URLBADPATTERN", value: 48, isUnsigned: true)
!66 = !DIEnumerator(name: "FILEBADFILE", value: 49, isUnsigned: true)
!67 = !DIEnumerator(name: "RANGEERR", value: 50, isUnsigned: true)
!68 = !DIEnumerator(name: "RETRBADPATTERN", value: 51, isUnsigned: true)
!69 = !DIEnumerator(name: "RETNOTSUP", value: 52, isUnsigned: true)
!70 = !DIEnumerator(name: "ROBOTSOK", value: 53, isUnsigned: true)
!71 = !DIEnumerator(name: "NOROBOTS", value: 54, isUnsigned: true)
!72 = !DIEnumerator(name: "PROXERR", value: 55, isUnsigned: true)
!73 = !DIEnumerator(name: "AUTHFAILED", value: 56, isUnsigned: true)
!74 = !DIEnumerator(name: "QUOTEXC", value: 57, isUnsigned: true)
!75 = !DIEnumerator(name: "WRITEFAILED", value: 58, isUnsigned: true)
!76 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !14, line: 173, baseType: !15, size: 32, elements: !77)
!77 = !{!78, !79, !80, !81, !82}
!78 = !DIEnumerator(name: "TEXTHTML", value: 1, isUnsigned: true)
!79 = !DIEnumerator(name: "RETROKF", value: 2, isUnsigned: true)
!80 = !DIEnumerator(name: "HEAD_ONLY", value: 4, isUnsigned: true)
!81 = !DIEnumerator(name: "SEND_NOCACHE", value: 8, isUnsigned: true)
!82 = !DIEnumerator(name: "ACCEPTRANGES", value: 16, isUnsigned: true)
!83 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "log_options", file: !14, line: 88, baseType: !15, size: 32, elements: !84)
!84 = !{!85, !86, !87, !88}
!85 = !DIEnumerator(name: "LOG_VERBOSE", value: 0, isUnsigned: true)
!86 = !DIEnumerator(name: "LOG_NOTQUIET", value: 1, isUnsigned: true)
!87 = !DIEnumerator(name: "LOG_NONVERBOSE", value: 2, isUnsigned: true)
!88 = !DIEnumerator(name: "LOG_ALWAYS", value: 3, isUnsigned: true)
!89 = !{!90, !91, !9, !92, !93}
!90 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64)
!94 = !DISubroutineType(types: !95)
!95 = !{null, !6}
!96 = !{!0, !97, !232}
!97 = !DIGlobalVariableExpression(var: !98, expr: !DIExpression())
!98 = distinct !DIGlobalVariable(name: "opt", scope: !11, file: !3, line: 63, type: !99, isLocal: false, isDefinition: true)
!99 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "options", file: !100, line: 23, size: 3328, elements: !101)
!100 = !DIFile(filename: "./options.h", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/wget-1.5.3/src")
!101 = !{!102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !214, !215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231}
!102 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !99, file: !100, line: 25, baseType: !6, size: 32)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "quiet", scope: !99, file: !100, line: 26, baseType: !6, size: 32, offset: 32)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "ntry", scope: !99, file: !100, line: 27, baseType: !6, size: 32, offset: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "background", scope: !99, file: !100, line: 28, baseType: !6, size: 32, offset: 96)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "kill_longer", scope: !99, file: !100, line: 29, baseType: !6, size: 32, offset: 128)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "ignore_length", scope: !99, file: !100, line: 32, baseType: !6, size: 32, offset: 160)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "recursive", scope: !99, file: !100, line: 33, baseType: !6, size: 32, offset: 192)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "spanhost", scope: !99, file: !100, line: 34, baseType: !6, size: 32, offset: 224)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "relative_only", scope: !99, file: !100, line: 36, baseType: !6, size: 32, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "no_parent", scope: !99, file: !100, line: 37, baseType: !6, size: 32, offset: 288)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "simple_check", scope: !99, file: !100, line: 39, baseType: !6, size: 32, offset: 320)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "reclevel", scope: !99, file: !100, line: 42, baseType: !6, size: 32, offset: 352)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "dirstruct", scope: !99, file: !100, line: 43, baseType: !6, size: 32, offset: 384)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "no_dirstruct", scope: !99, file: !100, line: 45, baseType: !6, size: 32, offset: 416)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "cut_dirs", scope: !99, file: !100, line: 46, baseType: !6, size: 32, offset: 448)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "add_hostdir", scope: !99, file: !100, line: 47, baseType: !6, size: 32, offset: 480)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "noclobber", scope: !99, file: !100, line: 48, baseType: !6, size: 32, offset: 512)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "dir_prefix", scope: !99, file: !100, line: 50, baseType: !9, size: 64, offset: 576)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "lfilename", scope: !99, file: !100, line: 51, baseType: !9, size: 64, offset: 640)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "no_flush", scope: !99, file: !100, line: 52, baseType: !6, size: 32, offset: 704)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "input_filename", scope: !99, file: !100, line: 53, baseType: !9, size: 64, offset: 768)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "force_html", scope: !99, file: !100, line: 54, baseType: !6, size: 32, offset: 832)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "spider", scope: !99, file: !100, line: 56, baseType: !6, size: 32, offset: 864)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "accepts", scope: !99, file: !100, line: 58, baseType: !91, size: 64, offset: 896)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "rejects", scope: !99, file: !100, line: 59, baseType: !91, size: 64, offset: 960)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "excludes", scope: !99, file: !100, line: 60, baseType: !91, size: 64, offset: 1024)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "includes", scope: !99, file: !100, line: 61, baseType: !91, size: 64, offset: 1088)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "domains", scope: !99, file: !100, line: 64, baseType: !91, size: 64, offset: 1152)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "exclude_domains", scope: !99, file: !100, line: 65, baseType: !91, size: 64, offset: 1216)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "follow_ftp", scope: !99, file: !100, line: 67, baseType: !6, size: 32, offset: 1280)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "retr_symlinks", scope: !99, file: !100, line: 69, baseType: !6, size: 32, offset: 1312)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "output_document", scope: !99, file: !100, line: 71, baseType: !9, size: 64, offset: 1344)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "dfp", scope: !99, file: !100, line: 73, baseType: !135, size: 64, offset: 1408)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !136, size: 64)
!136 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !137, line: 157, baseType: !138)
!137 = !DIFile(filename: "/usr/include/_stdio.h", directory: "")
!138 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "__sFILE", file: !137, line: 126, size: 1216, elements: !139)
!139 = !{!140, !143, !144, !145, !147, !148, !153, !154, !155, !159, !163, !173, !179, !180, !183, !184, !188, !192, !193, !194}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "_p", scope: !138, file: !137, line: 127, baseType: !141, size: 64)
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64)
!142 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "_r", scope: !138, file: !137, line: 128, baseType: !6, size: 32, offset: 64)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "_w", scope: !138, file: !137, line: 129, baseType: !6, size: 32, offset: 96)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !138, file: !137, line: 130, baseType: !146, size: 16, offset: 128)
!146 = !DIBasicType(name: "short", size: 16, encoding: DW_ATE_signed)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "_file", scope: !138, file: !137, line: 131, baseType: !146, size: 16, offset: 144)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "_bf", scope: !138, file: !137, line: 132, baseType: !149, size: 128, offset: 192)
!149 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "__sbuf", file: !137, line: 92, size: 128, elements: !150)
!150 = !{!151, !152}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "_base", scope: !149, file: !137, line: 93, baseType: !141, size: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "_size", scope: !149, file: !137, line: 94, baseType: !6, size: 32, offset: 64)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "_lbfsize", scope: !138, file: !137, line: 133, baseType: !6, size: 32, offset: 320)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "_cookie", scope: !138, file: !137, line: 136, baseType: !92, size: 64, offset: 384)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "_close", scope: !138, file: !137, line: 137, baseType: !156, size: 64, offset: 448)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64)
!157 = !DISubroutineType(types: !158)
!158 = !{!6, !92}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "_read", scope: !138, file: !137, line: 138, baseType: !160, size: 64, offset: 512)
!160 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64)
!161 = !DISubroutineType(types: !162)
!162 = !{!6, !92, !9, !6}
!163 = !DIDerivedType(tag: DW_TAG_member, name: "_seek", scope: !138, file: !137, line: 139, baseType: !164, size: 64, offset: 576)
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64)
!165 = !DISubroutineType(types: !166)
!166 = !{!167, !92, !167, !6}
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "fpos_t", file: !137, line: 81, baseType: !168)
!168 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_off_t", file: !169, line: 71, baseType: !170)
!169 = !DIFile(filename: "/usr/include/sys/_types.h", directory: "")
!170 = !DIDerivedType(tag: DW_TAG_typedef, name: "__int64_t", file: !171, line: 46, baseType: !172)
!171 = !DIFile(filename: "/usr/include/i386/_types.h", directory: "")
!172 = !DIBasicType(name: "long long int", size: 64, encoding: DW_ATE_signed)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "_write", scope: !138, file: !137, line: 140, baseType: !174, size: 64, offset: 640)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64)
!175 = !DISubroutineType(types: !176)
!176 = !{!6, !92, !177, !6}
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !178, size: 64)
!178 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !10)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "_ub", scope: !138, file: !137, line: 143, baseType: !149, size: 128, offset: 704)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "_extra", scope: !138, file: !137, line: 144, baseType: !181, size: 64, offset: 832)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64)
!182 = !DICompositeType(tag: DW_TAG_structure_type, name: "__sFILEX", file: !137, line: 98, flags: DIFlagFwdDecl)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "_ur", scope: !138, file: !137, line: 145, baseType: !6, size: 32, offset: 896)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "_ubuf", scope: !138, file: !137, line: 148, baseType: !185, size: 24, offset: 928)
!185 = !DICompositeType(tag: DW_TAG_array_type, baseType: !142, size: 24, elements: !186)
!186 = !{!187}
!187 = !DISubrange(count: 3)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "_nbuf", scope: !138, file: !137, line: 149, baseType: !189, size: 8, offset: 952)
!189 = !DICompositeType(tag: DW_TAG_array_type, baseType: !142, size: 8, elements: !190)
!190 = !{!191}
!191 = !DISubrange(count: 1)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "_lb", scope: !138, file: !137, line: 152, baseType: !149, size: 128, offset: 960)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "_blksize", scope: !138, file: !137, line: 155, baseType: !6, size: 32, offset: 1088)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !138, file: !137, line: 156, baseType: !167, size: 64, offset: 1152)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "always_rest", scope: !99, file: !100, line: 76, baseType: !6, size: 32, offset: 1472)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_acc", scope: !99, file: !100, line: 77, baseType: !9, size: 64, offset: 1536)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_pass", scope: !99, file: !100, line: 78, baseType: !9, size: 64, offset: 1600)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !99, file: !100, line: 79, baseType: !6, size: 32, offset: 1664)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_glob", scope: !99, file: !100, line: 80, baseType: !6, size: 32, offset: 1696)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_pasv", scope: !99, file: !100, line: 81, baseType: !6, size: 32, offset: 1728)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "http_user", scope: !99, file: !100, line: 83, baseType: !9, size: 64, offset: 1792)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "http_passwd", scope: !99, file: !100, line: 84, baseType: !9, size: 64, offset: 1856)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "user_header", scope: !99, file: !100, line: 85, baseType: !9, size: 64, offset: 1920)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "use_proxy", scope: !99, file: !100, line: 87, baseType: !6, size: 32, offset: 1984)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_cache", scope: !99, file: !100, line: 88, baseType: !6, size: 32, offset: 2016)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !99, file: !100, line: 89, baseType: !9, size: 64, offset: 2048)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_proxy", scope: !99, file: !100, line: 89, baseType: !9, size: 64, offset: 2112)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "no_proxy", scope: !99, file: !100, line: 90, baseType: !91, size: 64, offset: 2176)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "base_href", scope: !99, file: !100, line: 91, baseType: !9, size: 64, offset: 2240)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user", scope: !99, file: !100, line: 92, baseType: !9, size: 64, offset: 2304)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_passwd", scope: !99, file: !100, line: 93, baseType: !9, size: 64, offset: 2368)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !99, file: !100, line: 95, baseType: !213, size: 64, offset: 2432)
!213 = !DIBasicType(name: "long int", size: 64, encoding: DW_ATE_signed)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "wait", scope: !99, file: !100, line: 98, baseType: !213, size: 64, offset: 2496)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "use_robots", scope: !99, file: !100, line: 99, baseType: !6, size: 32, offset: 2560)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "quota", scope: !99, file: !100, line: 101, baseType: !213, size: 64, offset: 2624)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !99, file: !100, line: 103, baseType: !213, size: 64, offset: 2688)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "numurls", scope: !99, file: !100, line: 104, baseType: !6, size: 32, offset: 2752)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "server_response", scope: !99, file: !100, line: 107, baseType: !6, size: 32, offset: 2784)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "save_headers", scope: !99, file: !100, line: 108, baseType: !6, size: 32, offset: 2816)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "debug", scope: !99, file: !100, line: 112, baseType: !6, size: 32, offset: 2848)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "timestamping", scope: !99, file: !100, line: 115, baseType: !6, size: 32, offset: 2880)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "backups", scope: !99, file: !100, line: 116, baseType: !6, size: 32, offset: 2912)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "useragent", scope: !99, file: !100, line: 118, baseType: !9, size: 64, offset: 2944)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "convert_links", scope: !99, file: !100, line: 121, baseType: !6, size: 32, offset: 3008)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "remove_listing", scope: !99, file: !100, line: 123, baseType: !6, size: 32, offset: 3040)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "htmlify", scope: !99, file: !100, line: 125, baseType: !6, size: 32, offset: 3072)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "dot_bytes", scope: !99, file: !100, line: 128, baseType: !213, size: 64, offset: 3136)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "dots_in_line", scope: !99, file: !100, line: 130, baseType: !6, size: 32, offset: 3200)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "dot_spacing", scope: !99, file: !100, line: 131, baseType: !6, size: 32, offset: 3232)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "delete_after", scope: !99, file: !100, line: 133, baseType: !6, size: 32, offset: 3264)
!232 = !DIGlobalVariableExpression(var: !233, expr: !DIExpression())
!233 = distinct !DIGlobalVariable(name: "exec_name", scope: !11, file: !3, line: 72, type: !177, isLocal: false, isDefinition: true)
!234 = !{}
!235 = !DICompositeType(tag: DW_TAG_array_type, baseType: !236, size: 16896, elements: !243)
!236 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "option", file: !237, line: 77, size: 256, elements: !238)
!237 = !DIFile(filename: "./getopt.h", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/wget-1.5.3/src")
!238 = !{!239, !240, !241, !242}
!239 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !236, file: !237, line: 80, baseType: !177, size: 64)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "has_arg", scope: !236, file: !237, line: 86, baseType: !6, size: 32, offset: 64)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "flag", scope: !236, file: !237, line: 87, baseType: !90, size: 64, offset: 128)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "val", scope: !236, file: !237, line: 88, baseType: !6, size: 32, offset: 192)
!243 = !{!244}
!244 = !DISubrange(count: 66)
!245 = !{i32 7, !"Dwarf Version", i32 4}
!246 = !{i32 2, !"Debug Info Version", i32 3}
!247 = !{i32 1, !"wchar_size", i32 4}
!248 = !{i32 7, !"PIC Level", i32 2}
!249 = !{!"clang version 10.0.0 "}
!250 = !DILocalVariable(name: "argc", arg: 1, scope: !2, file: !3, line: 195, type: !6)
!251 = !DILocation(line: 195, column: 11, scope: !2)
!252 = !DILocalVariable(name: "argv", arg: 2, scope: !2, file: !3, line: 195, type: !7)
!253 = !DILocation(line: 195, column: 30, scope: !2)
!254 = !DILocalVariable(name: "url", scope: !2, file: !3, line: 197, type: !91)
!255 = !DILocation(line: 197, column: 49, scope: !2)
!256 = !DILocation(line: 197, column: 3, scope: !2)
!257 = !DILocalVariable(name: "t", scope: !2, file: !3, line: 197, type: !91)
!258 = !DILocation(line: 197, column: 56, scope: !2)
!259 = !DILocalVariable(name: "i", scope: !2, file: !3, line: 198, type: !6)
!260 = !DILocation(line: 198, column: 7, scope: !2)
!261 = !DILocalVariable(name: "c", scope: !2, file: !3, line: 198, type: !6)
!262 = !DILocation(line: 198, column: 10, scope: !2)
!263 = !DILocalVariable(name: "nurl", scope: !2, file: !3, line: 198, type: !6)
!264 = !DILocation(line: 198, column: 13, scope: !2)
!265 = !DILocalVariable(name: "status", scope: !2, file: !3, line: 198, type: !6)
!266 = !DILocation(line: 198, column: 19, scope: !2)
!267 = !DILocalVariable(name: "append_to_log", scope: !2, file: !3, line: 198, type: !6)
!268 = !DILocation(line: 198, column: 27, scope: !2)
!269 = !DILocation(line: 271, column: 3, scope: !2)
!270 = !DILocation(line: 273, column: 17, scope: !2)
!271 = !DILocation(line: 276, column: 24, scope: !2)
!272 = !DILocation(line: 276, column: 15, scope: !2)
!273 = !DILocation(line: 276, column: 13, scope: !2)
!274 = !DILocation(line: 277, column: 8, scope: !275)
!275 = distinct !DILexicalBlock(scope: !2, file: !3, line: 277, column: 7)
!276 = !DILocation(line: 277, column: 7, scope: !2)
!277 = !DILocation(line: 278, column: 17, scope: !275)
!278 = !DILocation(line: 278, column: 15, scope: !275)
!279 = !DILocation(line: 278, column: 5, scope: !275)
!280 = !DILocation(line: 280, column: 5, scope: !275)
!281 = !DILocation(line: 286, column: 3, scope: !2)
!282 = !DILocation(line: 288, column: 3, scope: !2)
!283 = !DILocation(line: 288, column: 28, scope: !2)
!284 = !DILocation(line: 288, column: 34, scope: !2)
!285 = !DILocation(line: 288, column: 15, scope: !2)
!286 = !DILocation(line: 288, column: 13, scope: !2)
!287 = !DILocation(line: 290, column: 32, scope: !2)
!288 = !DILocation(line: 292, column: 15, scope: !289)
!289 = distinct !DILexicalBlock(scope: !2, file: !3, line: 291, column: 5)
!290 = !DILocation(line: 292, column: 7, scope: !289)
!291 = !DILocation(line: 296, column: 4, scope: !292)
!292 = distinct !DILexicalBlock(scope: !289, file: !3, line: 293, column: 2)
!293 = !DILocation(line: 297, column: 4, scope: !292)
!294 = !DILocation(line: 299, column: 4, scope: !292)
!295 = !DILocation(line: 300, column: 4, scope: !292)
!296 = !DILocation(line: 302, column: 4, scope: !292)
!297 = !DILocation(line: 303, column: 4, scope: !292)
!298 = !DILocation(line: 305, column: 4, scope: !292)
!299 = !DILocation(line: 306, column: 4, scope: !292)
!300 = !DILocation(line: 308, column: 4, scope: !292)
!301 = !DILocation(line: 309, column: 4, scope: !292)
!302 = !DILocation(line: 311, column: 4, scope: !292)
!303 = !DILocation(line: 312, column: 4, scope: !292)
!304 = !DILocation(line: 314, column: 4, scope: !292)
!305 = !DILocation(line: 315, column: 4, scope: !292)
!306 = !DILocation(line: 317, column: 4, scope: !292)
!307 = !DILocation(line: 318, column: 4, scope: !292)
!308 = !DILocation(line: 320, column: 23, scope: !292)
!309 = !DILocation(line: 320, column: 4, scope: !292)
!310 = !DILocation(line: 321, column: 4, scope: !292)
!311 = !DILocation(line: 323, column: 4, scope: !292)
!312 = !DILocation(line: 324, column: 4, scope: !292)
!313 = !DILocation(line: 326, column: 4, scope: !292)
!314 = !DILocation(line: 327, column: 4, scope: !292)
!315 = !DILocation(line: 329, column: 4, scope: !292)
!316 = !DILocation(line: 330, column: 4, scope: !292)
!317 = !DILocation(line: 332, column: 4, scope: !292)
!318 = !DILocation(line: 333, column: 4, scope: !292)
!319 = !DILocation(line: 335, column: 4, scope: !292)
!320 = !DILocation(line: 336, column: 4, scope: !292)
!321 = !DILocation(line: 338, column: 4, scope: !292)
!322 = !DILocation(line: 339, column: 4, scope: !292)
!323 = !DILocation(line: 341, column: 4, scope: !292)
!324 = !DILocation(line: 342, column: 4, scope: !292)
!325 = !DILocation(line: 345, column: 4, scope: !292)
!326 = !DILocation(line: 350, column: 4, scope: !292)
!327 = !DILocation(line: 353, column: 20, scope: !292)
!328 = !DILocation(line: 353, column: 4, scope: !292)
!329 = !DILocation(line: 354, column: 4, scope: !292)
!330 = !DILocation(line: 357, column: 4, scope: !292)
!331 = !DILocation(line: 358, column: 4, scope: !292)
!332 = !DILocation(line: 360, column: 4, scope: !292)
!333 = !DILocation(line: 361, column: 4, scope: !292)
!334 = !DILocation(line: 363, column: 4, scope: !292)
!335 = !DILocation(line: 367, column: 4, scope: !292)
!336 = !DILocation(line: 370, column: 4, scope: !292)
!337 = !DILocation(line: 371, column: 4, scope: !292)
!338 = !DILocation(line: 373, column: 4, scope: !292)
!339 = !DILocation(line: 374, column: 4, scope: !292)
!340 = !DILocation(line: 376, column: 4, scope: !292)
!341 = !DILocation(line: 377, column: 4, scope: !292)
!342 = !DILocation(line: 379, column: 4, scope: !292)
!343 = !DILocation(line: 380, column: 4, scope: !292)
!344 = !DILocation(line: 382, column: 4, scope: !292)
!345 = !DILocation(line: 383, column: 4, scope: !292)
!346 = !DILocation(line: 385, column: 4, scope: !292)
!347 = !DILocation(line: 386, column: 4, scope: !292)
!348 = !DILocation(line: 388, column: 4, scope: !292)
!349 = !DILocation(line: 389, column: 4, scope: !292)
!350 = !DILocation(line: 391, column: 4, scope: !292)
!351 = !DILocation(line: 392, column: 4, scope: !292)
!352 = !DILocation(line: 394, column: 31, scope: !292)
!353 = !DILocation(line: 394, column: 4, scope: !292)
!354 = !DILocation(line: 395, column: 18, scope: !292)
!355 = !DILocation(line: 395, column: 4, scope: !292)
!356 = !DILocation(line: 401, column: 12, scope: !292)
!357 = !DILocation(line: 401, column: 4, scope: !292)
!358 = !DILocation(line: 402, column: 4, scope: !292)
!359 = !DILocation(line: 405, column: 4, scope: !292)
!360 = !DILocation(line: 406, column: 4, scope: !292)
!361 = !DILocation(line: 408, column: 4, scope: !292)
!362 = !DILocation(line: 409, column: 4, scope: !292)
!363 = !DILocation(line: 413, column: 24, scope: !292)
!364 = !DILocation(line: 413, column: 4, scope: !292)
!365 = !DILocation(line: 414, column: 4, scope: !292)
!366 = !DILocation(line: 416, column: 26, scope: !292)
!367 = !DILocation(line: 416, column: 4, scope: !292)
!368 = !DILocation(line: 417, column: 4, scope: !292)
!369 = !DILocation(line: 419, column: 22, scope: !292)
!370 = !DILocation(line: 419, column: 4, scope: !292)
!371 = !DILocation(line: 420, column: 4, scope: !292)
!372 = !DILocation(line: 422, column: 24, scope: !292)
!373 = !DILocation(line: 422, column: 4, scope: !292)
!374 = !DILocation(line: 423, column: 4, scope: !292)
!375 = !DILocation(line: 425, column: 23, scope: !292)
!376 = !DILocation(line: 425, column: 4, scope: !292)
!377 = !DILocation(line: 426, column: 4, scope: !292)
!378 = !DILocation(line: 428, column: 30, scope: !292)
!379 = !DILocation(line: 428, column: 4, scope: !292)
!380 = !DILocation(line: 429, column: 4, scope: !292)
!381 = !DILocation(line: 431, column: 25, scope: !292)
!382 = !DILocation(line: 431, column: 4, scope: !292)
!383 = !DILocation(line: 432, column: 4, scope: !292)
!384 = !DILocation(line: 434, column: 27, scope: !292)
!385 = !DILocation(line: 434, column: 4, scope: !292)
!386 = !DILocation(line: 435, column: 4, scope: !292)
!387 = !DILocation(line: 437, column: 23, scope: !292)
!388 = !DILocation(line: 437, column: 4, scope: !292)
!389 = !DILocation(line: 438, column: 4, scope: !292)
!390 = !DILocation(line: 440, column: 22, scope: !292)
!391 = !DILocation(line: 440, column: 4, scope: !292)
!392 = !DILocation(line: 441, column: 4, scope: !292)
!393 = !DILocation(line: 443, column: 23, scope: !292)
!394 = !DILocation(line: 443, column: 4, scope: !292)
!395 = !DILocation(line: 444, column: 18, scope: !292)
!396 = !DILocation(line: 445, column: 4, scope: !292)
!397 = !DILocation(line: 447, column: 20, scope: !292)
!398 = !DILocation(line: 447, column: 4, scope: !292)
!399 = !DILocation(line: 448, column: 4, scope: !292)
!400 = !DILocation(line: 450, column: 21, scope: !292)
!401 = !DILocation(line: 450, column: 4, scope: !292)
!402 = !DILocation(line: 451, column: 4, scope: !292)
!403 = !DILocation(line: 453, column: 23, scope: !292)
!404 = !DILocation(line: 453, column: 4, scope: !292)
!405 = !DILocation(line: 454, column: 4, scope: !292)
!406 = !DILocalVariable(name: "com", scope: !407, file: !3, line: 457, type: !9)
!407 = distinct !DILexicalBlock(scope: !292, file: !3, line: 456, column: 4)
!408 = !DILocation(line: 457, column: 12, scope: !407)
!409 = !DILocalVariable(name: "val", scope: !407, file: !3, line: 457, type: !9)
!410 = !DILocation(line: 457, column: 18, scope: !407)
!411 = !DILocation(line: 458, column: 22, scope: !412)
!412 = distinct !DILexicalBlock(scope: !407, file: !3, line: 458, column: 10)
!413 = !DILocation(line: 458, column: 10, scope: !412)
!414 = !DILocation(line: 458, column: 10, scope: !407)
!415 = !DILocation(line: 460, column: 16, scope: !416)
!416 = distinct !DILexicalBlock(scope: !417, file: !3, line: 460, column: 7)
!417 = distinct !DILexicalBlock(scope: !412, file: !3, line: 459, column: 8)
!418 = !DILocation(line: 460, column: 21, scope: !416)
!419 = !DILocation(line: 460, column: 8, scope: !416)
!420 = !DILocation(line: 460, column: 7, scope: !417)
!421 = !DILocation(line: 461, column: 5, scope: !416)
!422 = !DILocation(line: 462, column: 8, scope: !417)
!423 = !DILocation(line: 465, column: 12, scope: !424)
!424 = distinct !DILexicalBlock(scope: !412, file: !3, line: 464, column: 8)
!425 = !DILocation(line: 465, column: 20, scope: !424)
!426 = !DILocation(line: 465, column: 52, scope: !424)
!427 = !DILocation(line: 466, column: 5, scope: !424)
!428 = !DILocation(line: 465, column: 3, scope: !424)
!429 = !DILocation(line: 467, column: 3, scope: !424)
!430 = !DILocation(line: 469, column: 12, scope: !407)
!431 = !DILocation(line: 469, column: 6, scope: !407)
!432 = !DILocation(line: 470, column: 12, scope: !407)
!433 = !DILocation(line: 470, column: 6, scope: !407)
!434 = !DILocation(line: 472, column: 4, scope: !292)
!435 = !DILocation(line: 474, column: 20, scope: !292)
!436 = !DILocation(line: 474, column: 4, scope: !292)
!437 = !DILocation(line: 475, column: 4, scope: !292)
!438 = !DILocation(line: 477, column: 34, scope: !292)
!439 = !DILocation(line: 477, column: 4, scope: !292)
!440 = !DILocation(line: 478, column: 4, scope: !292)
!441 = !DILocation(line: 480, column: 21, scope: !292)
!442 = !DILocation(line: 480, column: 4, scope: !292)
!443 = !DILocation(line: 481, column: 4, scope: !292)
!444 = !DILocation(line: 483, column: 24, scope: !292)
!445 = !DILocation(line: 483, column: 4, scope: !292)
!446 = !DILocation(line: 484, column: 4, scope: !292)
!447 = !DILocalVariable(name: "p", scope: !448, file: !3, line: 488, type: !9)
!448 = distinct !DILexicalBlock(scope: !292, file: !3, line: 486, column: 4)
!449 = !DILocation(line: 488, column: 12, scope: !448)
!450 = !DILocation(line: 490, column: 15, scope: !451)
!451 = distinct !DILexicalBlock(scope: !448, file: !3, line: 490, column: 6)
!452 = !DILocation(line: 490, column: 13, scope: !451)
!453 = !DILocation(line: 490, column: 11, scope: !451)
!454 = !DILocation(line: 490, column: 24, scope: !455)
!455 = distinct !DILexicalBlock(scope: !451, file: !3, line: 490, column: 6)
!456 = !DILocation(line: 490, column: 23, scope: !455)
!457 = !DILocation(line: 490, column: 6, scope: !451)
!458 = !DILocation(line: 491, column: 17, scope: !455)
!459 = !DILocation(line: 491, column: 16, scope: !455)
!460 = !DILocation(line: 491, column: 8, scope: !455)
!461 = !DILocation(line: 494, column: 5, scope: !462)
!462 = distinct !DILexicalBlock(scope: !455, file: !3, line: 492, column: 3)
!463 = !DILocation(line: 495, column: 5, scope: !462)
!464 = !DILocation(line: 497, column: 5, scope: !462)
!465 = !DILocation(line: 498, column: 5, scope: !462)
!466 = !DILocation(line: 500, column: 5, scope: !462)
!467 = !DILocation(line: 501, column: 5, scope: !462)
!468 = !DILocation(line: 503, column: 5, scope: !462)
!469 = !DILocation(line: 504, column: 5, scope: !462)
!470 = !DILocation(line: 506, column: 5, scope: !462)
!471 = !DILocation(line: 507, column: 5, scope: !462)
!472 = !DILocation(line: 509, column: 5, scope: !462)
!473 = !DILocation(line: 510, column: 5, scope: !462)
!474 = !DILocation(line: 512, column: 5, scope: !462)
!475 = !DILocation(line: 513, column: 5, scope: !462)
!476 = !DILocation(line: 515, column: 13, scope: !462)
!477 = !DILocation(line: 515, column: 50, scope: !462)
!478 = !DILocation(line: 515, column: 62, scope: !462)
!479 = !DILocation(line: 515, column: 61, scope: !462)
!480 = !DILocation(line: 515, column: 5, scope: !462)
!481 = !DILocation(line: 516, column: 5, scope: !462)
!482 = !DILocation(line: 517, column: 5, scope: !462)
!483 = !DILocation(line: 518, column: 13, scope: !462)
!484 = !DILocation(line: 518, column: 56, scope: !462)
!485 = !DILocation(line: 518, column: 5, scope: !462)
!486 = !DILocation(line: 519, column: 5, scope: !462)
!487 = !DILocation(line: 520, column: 3, scope: !462)
!488 = !DILocation(line: 490, column: 28, scope: !455)
!489 = !DILocation(line: 490, column: 6, scope: !455)
!490 = distinct !{!490, !457, !491}
!491 = !DILocation(line: 520, column: 3, scope: !451)
!492 = !DILocation(line: 521, column: 6, scope: !448)
!493 = !DILocation(line: 524, column: 30, scope: !292)
!494 = !DILocation(line: 524, column: 4, scope: !292)
!495 = !DILocation(line: 525, column: 4, scope: !292)
!496 = !DILocation(line: 527, column: 23, scope: !292)
!497 = !DILocation(line: 527, column: 4, scope: !292)
!498 = !DILocation(line: 528, column: 4, scope: !292)
!499 = !DILocation(line: 530, column: 25, scope: !292)
!500 = !DILocation(line: 530, column: 4, scope: !292)
!501 = !DILocation(line: 531, column: 4, scope: !292)
!502 = !DILocation(line: 533, column: 21, scope: !292)
!503 = !DILocation(line: 533, column: 4, scope: !292)
!504 = !DILocation(line: 534, column: 4, scope: !292)
!505 = !DILocation(line: 536, column: 22, scope: !292)
!506 = !DILocation(line: 536, column: 4, scope: !292)
!507 = !DILocation(line: 537, column: 4, scope: !292)
!508 = !DILocation(line: 539, column: 23, scope: !292)
!509 = !DILocation(line: 539, column: 4, scope: !292)
!510 = !DILocation(line: 540, column: 4, scope: !292)
!511 = !DILocation(line: 542, column: 21, scope: !292)
!512 = !DILocation(line: 542, column: 4, scope: !292)
!513 = !DILocation(line: 543, column: 4, scope: !292)
!514 = !DILocation(line: 545, column: 25, scope: !292)
!515 = !DILocation(line: 545, column: 4, scope: !292)
!516 = !DILocation(line: 546, column: 4, scope: !292)
!517 = !DILocation(line: 548, column: 20, scope: !292)
!518 = !DILocation(line: 548, column: 4, scope: !292)
!519 = !DILocation(line: 549, column: 4, scope: !292)
!520 = !DILocation(line: 551, column: 34, scope: !292)
!521 = !DILocation(line: 551, column: 4, scope: !292)
!522 = !DILocation(line: 552, column: 4, scope: !292)
!523 = !DILocation(line: 554, column: 24, scope: !292)
!524 = !DILocation(line: 554, column: 4, scope: !292)
!525 = !DILocation(line: 555, column: 4, scope: !292)
!526 = !DILocation(line: 558, column: 4, scope: !292)
!527 = !DILocation(line: 559, column: 4, scope: !292)
!528 = !DILocation(line: 560, column: 12, scope: !292)
!529 = !DILocation(line: 560, column: 54, scope: !292)
!530 = !DILocation(line: 560, column: 4, scope: !292)
!531 = !DILocation(line: 561, column: 4, scope: !292)
!532 = distinct !{!532, !282, !533}
!533 = !DILocation(line: 564, column: 5, scope: !2)
!534 = !DILocation(line: 565, column: 11, scope: !535)
!535 = distinct !DILexicalBlock(scope: !2, file: !3, line: 565, column: 7)
!536 = !DILocation(line: 565, column: 19, scope: !535)
!537 = !DILocation(line: 565, column: 7, scope: !2)
!538 = !DILocation(line: 566, column: 24, scope: !535)
!539 = !DILocation(line: 566, column: 19, scope: !535)
!540 = !DILocation(line: 566, column: 17, scope: !535)
!541 = !DILocation(line: 566, column: 5, scope: !535)
!542 = !DILocation(line: 569, column: 11, scope: !543)
!543 = distinct !DILexicalBlock(scope: !2, file: !3, line: 569, column: 7)
!544 = !DILocation(line: 569, column: 7, scope: !543)
!545 = !DILocation(line: 569, column: 19, scope: !543)
!546 = !DILocation(line: 569, column: 26, scope: !543)
!547 = !DILocation(line: 569, column: 22, scope: !543)
!548 = !DILocation(line: 569, column: 7, scope: !2)
!549 = !DILocation(line: 571, column: 15, scope: !550)
!550 = distinct !DILexicalBlock(scope: !543, file: !3, line: 570, column: 5)
!551 = !DILocation(line: 571, column: 7, scope: !550)
!552 = !DILocation(line: 572, column: 7, scope: !550)
!553 = !DILocation(line: 573, column: 7, scope: !550)
!554 = !DILocation(line: 575, column: 11, scope: !555)
!555 = distinct !DILexicalBlock(scope: !2, file: !3, line: 575, column: 7)
!556 = !DILocation(line: 575, column: 7, scope: !555)
!557 = !DILocation(line: 575, column: 24, scope: !555)
!558 = !DILocation(line: 575, column: 31, scope: !555)
!559 = !DILocation(line: 575, column: 27, scope: !555)
!560 = !DILocation(line: 575, column: 7, scope: !2)
!561 = !DILocation(line: 577, column: 15, scope: !562)
!562 = distinct !DILexicalBlock(scope: !555, file: !3, line: 576, column: 5)
!563 = !DILocation(line: 577, column: 7, scope: !562)
!564 = !DILocation(line: 579, column: 7, scope: !562)
!565 = !DILocation(line: 580, column: 7, scope: !562)
!566 = !DILocation(line: 582, column: 10, scope: !2)
!567 = !DILocation(line: 582, column: 17, scope: !2)
!568 = !DILocation(line: 582, column: 15, scope: !2)
!569 = !DILocation(line: 582, column: 8, scope: !2)
!570 = !DILocation(line: 583, column: 8, scope: !571)
!571 = distinct !DILexicalBlock(scope: !2, file: !3, line: 583, column: 7)
!572 = !DILocation(line: 583, column: 13, scope: !571)
!573 = !DILocation(line: 583, column: 21, scope: !571)
!574 = !DILocation(line: 583, column: 17, scope: !571)
!575 = !DILocation(line: 583, column: 7, scope: !2)
!576 = !DILocation(line: 586, column: 15, scope: !577)
!577 = distinct !DILexicalBlock(scope: !571, file: !3, line: 584, column: 5)
!578 = !DILocation(line: 586, column: 39, scope: !577)
!579 = !DILocation(line: 586, column: 7, scope: !577)
!580 = !DILocation(line: 587, column: 7, scope: !577)
!581 = !DILocation(line: 588, column: 7, scope: !577)
!582 = !DILocation(line: 591, column: 15, scope: !577)
!583 = !DILocation(line: 591, column: 57, scope: !577)
!584 = !DILocation(line: 591, column: 7, scope: !577)
!585 = !DILocation(line: 592, column: 7, scope: !577)
!586 = !DILocation(line: 595, column: 11, scope: !587)
!587 = distinct !DILexicalBlock(scope: !2, file: !3, line: 595, column: 7)
!588 = !DILocation(line: 595, column: 7, scope: !587)
!589 = !DILocation(line: 595, column: 7, scope: !2)
!590 = !DILocation(line: 596, column: 5, scope: !587)
!591 = !DILocation(line: 599, column: 9, scope: !2)
!592 = !DILocation(line: 599, column: 7, scope: !2)
!593 = !DILocation(line: 601, column: 10, scope: !594)
!594 = distinct !DILexicalBlock(scope: !2, file: !3, line: 601, column: 3)
!595 = !DILocation(line: 601, column: 8, scope: !594)
!596 = !DILocation(line: 601, column: 15, scope: !597)
!597 = distinct !DILexicalBlock(scope: !594, file: !3, line: 601, column: 3)
!598 = !DILocation(line: 601, column: 19, scope: !597)
!599 = !DILocation(line: 601, column: 17, scope: !597)
!600 = !DILocation(line: 601, column: 3, scope: !594)
!601 = !DILocalVariable(name: "irix4_cc_needs_this", scope: !602, file: !3, line: 603, type: !9)
!602 = distinct !DILexicalBlock(scope: !597, file: !3, line: 602, column: 5)
!603 = !DILocation(line: 603, column: 13, scope: !602)
!604 = !DILocation(line: 604, column: 7, scope: !602)
!605 = !DILocation(line: 604, column: 7, scope: !606)
!606 = distinct !DILexicalBlock(scope: !602, file: !3, line: 604, column: 7)
!607 = !DILocation(line: 605, column: 16, scope: !602)
!608 = !DILocation(line: 605, column: 7, scope: !602)
!609 = !DILocation(line: 605, column: 11, scope: !602)
!610 = !DILocation(line: 605, column: 14, scope: !602)
!611 = !DILocation(line: 606, column: 5, scope: !602)
!612 = !DILocation(line: 601, column: 26, scope: !597)
!613 = !DILocation(line: 601, column: 36, scope: !597)
!614 = !DILocation(line: 601, column: 3, scope: !597)
!615 = distinct !{!615, !600, !616}
!616 = !DILocation(line: 606, column: 5, scope: !594)
!617 = !DILocation(line: 607, column: 3, scope: !2)
!618 = !DILocation(line: 607, column: 7, scope: !2)
!619 = !DILocation(line: 607, column: 10, scope: !2)
!620 = !DILocation(line: 616, column: 17, scope: !2)
!621 = !DILocation(line: 616, column: 28, scope: !2)
!622 = !DILocation(line: 616, column: 3, scope: !2)
!623 = !DILocation(line: 618, column: 3, scope: !2)
!624 = !DILocation(line: 618, column: 3, scope: !625)
!625 = distinct !DILexicalBlock(scope: !2, file: !3, line: 618, column: 3)
!626 = !DILocation(line: 621, column: 11, scope: !627)
!627 = distinct !DILexicalBlock(scope: !2, file: !3, line: 621, column: 7)
!628 = !DILocation(line: 621, column: 7, scope: !627)
!629 = !DILocation(line: 621, column: 7, scope: !2)
!630 = !DILocation(line: 623, column: 11, scope: !631)
!631 = distinct !DILexicalBlock(scope: !632, file: !3, line: 623, column: 11)
!632 = distinct !DILexicalBlock(scope: !627, file: !3, line: 622, column: 5)
!633 = !DILocation(line: 623, column: 11, scope: !632)
!634 = !DILocation(line: 624, column: 12, scope: !631)
!635 = !DILocation(line: 624, column: 10, scope: !631)
!636 = !DILocation(line: 624, column: 2, scope: !631)
!637 = !DILocation(line: 627, column: 25, scope: !638)
!638 = distinct !DILexicalBlock(scope: !631, file: !3, line: 626, column: 2)
!639 = !DILocation(line: 627, column: 14, scope: !638)
!640 = !DILocation(line: 627, column: 12, scope: !638)
!641 = !DILocation(line: 628, column: 12, scope: !642)
!642 = distinct !DILexicalBlock(scope: !638, file: !3, line: 628, column: 8)
!643 = !DILocation(line: 628, column: 16, scope: !642)
!644 = !DILocation(line: 628, column: 8, scope: !638)
!645 = !DILocation(line: 630, column: 20, scope: !646)
!646 = distinct !DILexicalBlock(scope: !642, file: !3, line: 629, column: 6)
!647 = !DILocation(line: 630, column: 8, scope: !646)
!648 = !DILocation(line: 631, column: 8, scope: !646)
!649 = !DILocation(line: 634, column: 5, scope: !632)
!650 = !DILocation(line: 643, column: 7, scope: !651)
!651 = distinct !DILexicalBlock(scope: !2, file: !3, line: 643, column: 7)
!652 = !DILocation(line: 643, column: 31, scope: !651)
!653 = !DILocation(line: 643, column: 7, scope: !2)
!654 = !DILocation(line: 644, column: 5, scope: !651)
!655 = !DILocation(line: 646, column: 3, scope: !2)
!656 = !DILocation(line: 650, column: 3, scope: !2)
!657 = !DILocation(line: 653, column: 10, scope: !2)
!658 = !DILocation(line: 654, column: 3, scope: !2)
!659 = !DILocation(line: 656, column: 12, scope: !660)
!660 = distinct !DILexicalBlock(scope: !2, file: !3, line: 656, column: 3)
!661 = !DILocation(line: 656, column: 10, scope: !660)
!662 = !DILocation(line: 656, column: 8, scope: !660)
!663 = !DILocation(line: 656, column: 18, scope: !664)
!664 = distinct !DILexicalBlock(scope: !660, file: !3, line: 656, column: 3)
!665 = !DILocation(line: 656, column: 17, scope: !664)
!666 = !DILocation(line: 656, column: 3, scope: !660)
!667 = !DILocalVariable(name: "filename", scope: !668, file: !3, line: 658, type: !9)
!668 = distinct !DILexicalBlock(scope: !664, file: !3, line: 657, column: 5)
!669 = !DILocation(line: 658, column: 13, scope: !668)
!670 = !DILocalVariable(name: "new_file", scope: !668, file: !3, line: 658, type: !9)
!671 = !DILocation(line: 658, column: 24, scope: !668)
!672 = !DILocalVariable(name: "dt", scope: !668, file: !3, line: 659, type: !6)
!673 = !DILocation(line: 659, column: 11, scope: !668)
!674 = !DILocation(line: 661, column: 31, scope: !668)
!675 = !DILocation(line: 661, column: 30, scope: !668)
!676 = !DILocation(line: 661, column: 16, scope: !668)
!677 = !DILocation(line: 661, column: 14, scope: !668)
!678 = !DILocation(line: 662, column: 15, scope: !679)
!679 = distinct !DILexicalBlock(scope: !668, file: !3, line: 662, column: 11)
!680 = !DILocation(line: 662, column: 11, scope: !679)
!681 = !DILocation(line: 662, column: 25, scope: !679)
!682 = !DILocation(line: 662, column: 28, scope: !679)
!683 = !DILocation(line: 662, column: 35, scope: !679)
!684 = !DILocation(line: 662, column: 45, scope: !679)
!685 = !DILocation(line: 662, column: 49, scope: !679)
!686 = !DILocation(line: 662, column: 52, scope: !679)
!687 = !DILocation(line: 662, column: 11, scope: !668)
!688 = !DILocation(line: 663, column: 31, scope: !679)
!689 = !DILocation(line: 663, column: 41, scope: !679)
!690 = !DILocation(line: 663, column: 52, scope: !679)
!691 = !DILocation(line: 663, column: 64, scope: !679)
!692 = !DILocation(line: 663, column: 63, scope: !679)
!693 = !DILocation(line: 663, column: 11, scope: !679)
!694 = !DILocation(line: 663, column: 9, scope: !679)
!695 = !DILocation(line: 663, column: 2, scope: !679)
!696 = !DILocation(line: 664, column: 7, scope: !668)
!697 = !DILocation(line: 664, column: 7, scope: !698)
!698 = distinct !DILexicalBlock(scope: !699, file: !3, line: 664, column: 7)
!699 = distinct !DILexicalBlock(scope: !668, file: !3, line: 664, column: 7)
!700 = !DILocation(line: 664, column: 7, scope: !699)
!701 = !DILocation(line: 665, column: 7, scope: !668)
!702 = !DILocation(line: 665, column: 7, scope: !703)
!703 = distinct !DILexicalBlock(scope: !704, file: !3, line: 665, column: 7)
!704 = distinct !DILexicalBlock(scope: !668, file: !3, line: 665, column: 7)
!705 = !DILocation(line: 665, column: 7, scope: !704)
!706 = !DILocation(line: 666, column: 5, scope: !668)
!707 = !DILocation(line: 656, column: 22, scope: !664)
!708 = !DILocation(line: 656, column: 3, scope: !664)
!709 = distinct !{!709, !666, !710}
!710 = !DILocation(line: 666, column: 5, scope: !660)
!711 = !DILocation(line: 669, column: 11, scope: !712)
!712 = distinct !DILexicalBlock(scope: !2, file: !3, line: 669, column: 7)
!713 = !DILocation(line: 669, column: 7, scope: !712)
!714 = !DILocation(line: 669, column: 7, scope: !2)
!715 = !DILocalVariable(name: "count", scope: !716, file: !3, line: 671, type: !6)
!716 = distinct !DILexicalBlock(scope: !712, file: !3, line: 670, column: 5)
!717 = !DILocation(line: 671, column: 11, scope: !716)
!718 = !DILocation(line: 672, column: 40, scope: !716)
!719 = !DILocation(line: 672, column: 60, scope: !716)
!720 = !DILocation(line: 672, column: 16, scope: !716)
!721 = !DILocation(line: 672, column: 14, scope: !716)
!722 = !DILocation(line: 673, column: 12, scope: !723)
!723 = distinct !DILexicalBlock(scope: !716, file: !3, line: 673, column: 11)
!724 = !DILocation(line: 673, column: 11, scope: !716)
!725 = !DILocation(line: 674, column: 27, scope: !723)
!726 = !DILocation(line: 675, column: 10, scope: !723)
!727 = !DILocation(line: 674, column: 2, scope: !723)
!728 = !DILocation(line: 676, column: 5, scope: !716)
!729 = !DILocation(line: 678, column: 11, scope: !730)
!730 = distinct !DILexicalBlock(scope: !2, file: !3, line: 678, column: 7)
!731 = !DILocation(line: 678, column: 7, scope: !730)
!732 = !DILocation(line: 679, column: 7, scope: !730)
!733 = !DILocation(line: 679, column: 10, scope: !730)
!734 = !DILocation(line: 679, column: 15, scope: !730)
!735 = !DILocation(line: 680, column: 7, scope: !730)
!736 = !DILocation(line: 680, column: 15, scope: !730)
!737 = !DILocation(line: 680, column: 11, scope: !730)
!738 = !DILocation(line: 680, column: 30, scope: !730)
!739 = !DILocation(line: 680, column: 37, scope: !730)
!740 = !DILocation(line: 680, column: 48, scope: !730)
!741 = !DILocation(line: 678, column: 7, scope: !2)
!742 = !DILocation(line: 683, column: 4, scope: !743)
!743 = distinct !DILexicalBlock(scope: !730, file: !3, line: 681, column: 5)
!744 = !DILocation(line: 684, column: 4, scope: !743)
!745 = !DILocation(line: 684, column: 34, scope: !743)
!746 = !DILocation(line: 684, column: 21, scope: !743)
!747 = !DILocation(line: 684, column: 51, scope: !743)
!748 = !DILocation(line: 682, column: 7, scope: !743)
!749 = !DILocation(line: 686, column: 15, scope: !750)
!750 = distinct !DILexicalBlock(scope: !743, file: !3, line: 686, column: 11)
!751 = !DILocation(line: 686, column: 11, scope: !750)
!752 = !DILocation(line: 686, column: 21, scope: !750)
!753 = !DILocation(line: 686, column: 28, scope: !750)
!754 = !DILocation(line: 686, column: 45, scope: !750)
!755 = !DILocation(line: 686, column: 39, scope: !750)
!756 = !DILocation(line: 686, column: 11, scope: !743)
!757 = !DILocation(line: 688, column: 6, scope: !750)
!758 = !DILocation(line: 689, column: 19, scope: !750)
!759 = !DILocation(line: 689, column: 6, scope: !750)
!760 = !DILocation(line: 687, column: 2, scope: !750)
!761 = !DILocation(line: 690, column: 5, scope: !743)
!762 = !DILocation(line: 691, column: 11, scope: !763)
!763 = distinct !DILexicalBlock(scope: !2, file: !3, line: 691, column: 7)
!764 = !DILocation(line: 691, column: 7, scope: !763)
!765 = !DILocation(line: 691, column: 7, scope: !2)
!766 = !DILocation(line: 693, column: 7, scope: !767)
!767 = distinct !DILexicalBlock(scope: !763, file: !3, line: 692, column: 5)
!768 = !DILocation(line: 694, column: 5, scope: !767)
!769 = !DILocation(line: 695, column: 3, scope: !2)
!770 = !DILocation(line: 696, column: 3, scope: !2)
!771 = !DILocation(line: 697, column: 7, scope: !772)
!772 = distinct !DILexicalBlock(scope: !2, file: !3, line: 697, column: 7)
!773 = !DILocation(line: 697, column: 14, scope: !772)
!774 = !DILocation(line: 697, column: 7, scope: !2)
!775 = !DILocation(line: 698, column: 5, scope: !772)
!776 = !DILocation(line: 700, column: 5, scope: !772)
!777 = !DILocation(line: 701, column: 1, scope: !2)
!778 = distinct !DISubprogram(name: "i18n_initialize", scope: !3, file: !3, line: 78, type: !779, scopeLine: 79, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !11, retainedNodes: !234)
!779 = !DISubroutineType(types: !780)
!780 = !{null}
!781 = !DILocation(line: 90, column: 3, scope: !778)
!782 = !DILocation(line: 92, column: 3, scope: !778)
!783 = !DILocation(line: 93, column: 3, scope: !778)
!784 = !DILocation(line: 95, column: 1, scope: !778)
!785 = distinct !DISubprogram(name: "print_help", scope: !3, file: !3, line: 107, type: !779, scopeLine: 108, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !11, retainedNodes: !234)
!786 = !DILocation(line: 109, column: 11, scope: !785)
!787 = !DILocation(line: 110, column: 4, scope: !785)
!788 = !DILocation(line: 109, column: 3, scope: !785)
!789 = !DILocation(line: 111, column: 3, scope: !785)
!790 = !DILocation(line: 114, column: 35, scope: !785)
!791 = !DILocation(line: 117, column: 7, scope: !785)
!792 = !DILocation(line: 123, column: 7, scope: !785)
!793 = !DILocation(line: 133, column: 7, scope: !785)
!794 = !DILocation(line: 147, column: 8, scope: !785)
!795 = !DILocation(line: 154, column: 7, scope: !785)
!796 = !DILocation(line: 165, column: 7, scope: !785)
!797 = !DILocation(line: 170, column: 7, scope: !785)
!798 = !DILocation(line: 178, column: 7, scope: !785)
!799 = !DILocation(line: 191, column: 7, scope: !785)
!800 = !DILocation(line: 114, column: 3, scope: !785)
!801 = !DILocation(line: 192, column: 1, scope: !785)
!802 = distinct !DISubprogram(name: "print_usage", scope: !3, file: !3, line: 99, type: !779, scopeLine: 100, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !11, retainedNodes: !234)
!803 = !DILocation(line: 101, column: 11, scope: !802)
!804 = !DILocation(line: 101, column: 50, scope: !802)
!805 = !DILocation(line: 101, column: 3, scope: !802)
!806 = !DILocation(line: 102, column: 1, scope: !802)
!807 = distinct !DISubprogram(name: "redirect_output_signal", scope: !3, file: !3, line: 709, type: !94, scopeLine: 710, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !11, retainedNodes: !234)
!808 = !DILocalVariable(name: "sig", arg: 1, scope: !807, file: !3, line: 709, type: !6)
!809 = !DILocation(line: 709, column: 29, scope: !807)
!810 = !DILocalVariable(name: "tmp", scope: !807, file: !3, line: 711, type: !811)
!811 = !DICompositeType(tag: DW_TAG_array_type, baseType: !10, size: 800, elements: !812)
!812 = !{!813}
!813 = !DISubrange(count: 100)
!814 = !DILocation(line: 711, column: 8, scope: !807)
!815 = !DILocation(line: 712, column: 11, scope: !807)
!816 = !DILocation(line: 712, column: 3, scope: !807)
!817 = !DILocation(line: 715, column: 3, scope: !807)
!818 = !DILocation(line: 719, column: 20, scope: !807)
!819 = !DILocation(line: 719, column: 3, scope: !807)
!820 = !DILocation(line: 720, column: 1, scope: !807)
