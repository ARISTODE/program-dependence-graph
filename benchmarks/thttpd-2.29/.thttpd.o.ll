; ModuleID = '.thttpd.o.bc'
source_filename = "thttpd.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.throttletab = type { i8*, i64, i64, i64, i64, i32 }
%struct.httpd_server = type { i8*, i8*, i16, i8*, i32, i32, i8*, i8*, i32, i8*, i32, i32, i32, %struct.__sFILE*, i32, i32, i32, i8*, i8*, i32 }
%union.ClientData = type { i8* }
%struct.connecttab = type { i32, i32, %struct.httpd_conn*, [10 x i32], i32, i64, i64, i64, i64, %struct.TimerStruct*, %struct.TimerStruct*, i64, i64, i64, i64 }
%struct.httpd_conn = type { i32, %struct.httpd_server*, %union.httpd_sockaddr, i8*, i64, i64, i64, i32, i32, i32, i64, i64, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i8*, i8*, i32, i32, i32, i32, i64, i64, i32, i32, %struct.stat, i32, i8* }
%union.httpd_sockaddr = type { %struct.sockaddr_storage }
%struct.sockaddr_storage = type { i8, i8, [6 x i8], i64, [112 x i8] }
%struct.stat = type { i32, i16, i16, i64, i32, i32, i32, %struct.timespec, %struct.timespec, %struct.timespec, %struct.timespec, i64, i64, i32, i32, i32, i32, [2 x i64] }
%struct.timespec = type { i64, i64 }
%struct.TimerStruct = type { void (i8*, %struct.timeval*)*, %union.ClientData, i64, i32, %struct.timeval, %struct.TimerStruct*, %struct.TimerStruct*, i32 }
%struct.timeval = type { i64, i32 }
%struct.passwd = type { i8*, i8*, i32, i32, i64, i8*, i8*, i8*, i8*, i64 }
%struct.addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.addrinfo* }
%struct.sockaddr = type { i8, i8, [14 x i8] }
%struct.iovec = type { i8*, i64 }

@terminate = global i32 0, align 4, !dbg !0
@.str = private unnamed_addr constant [10 x i8] c"sensitive\00", section "llvm.metadata"
@.str.1 = private unnamed_addr constant [9 x i8] c"thttpd.c\00", section "llvm.metadata"
@argv0 = internal global i8* null, align 8, !dbg !413
@.str.2 = private unnamed_addr constant [29 x i8] c"can't find any valid address\00", align 1
@__stderrp = external global %struct.__sFILE*, align 8
@.str.3 = private unnamed_addr constant [34 x i8] c"%s: can't find any valid address\0A\00", align 1
@numthrottles = internal global i32 0, align 4, !dbg !461
@maxthrottles = internal global i32 0, align 4, !dbg !463
@throttles = internal global %struct.throttletab* null, align 8, !dbg !459
@throttlefile = internal global i8* null, align 8, !dbg !445
@user = internal global i8* null, align 8, !dbg !451
@.str.4 = private unnamed_addr constant [23 x i8] c"unknown user - '%.80s'\00", align 1
@.str.5 = private unnamed_addr constant [25 x i8] c"%s: unknown user - '%s'\0A\00", align 1
@logfile = internal global i8* null, align 8, !dbg !443
@.str.6 = private unnamed_addr constant [10 x i8] c"/dev/null\00", align 1
@no_log = internal global i32 0, align 4, !dbg !425
@.str.7 = private unnamed_addr constant [2 x i8] c"-\00", align 1
@__stdoutp = external global %struct.__sFILE*, align 8
@.str.8 = private unnamed_addr constant [2 x i8] c"a\00", align 1
@.str.9 = private unnamed_addr constant [11 x i8] c"%.80s - %m\00", align 1
@.str.10 = private unnamed_addr constant [67 x i8] c"logfile is not an absolute path, you may not be able to re-open it\00", align 1
@.str.11 = private unnamed_addr constant [72 x i8] c"%s: logfile is not an absolute path, you may not be able to re-open it\0A\00", align 1
@.str.12 = private unnamed_addr constant [20 x i8] c"fchown logfile - %m\00", align 1
@.str.13 = private unnamed_addr constant [15 x i8] c"fchown logfile\00", align 1
@dir = internal global i8* null, align 8, !dbg !419
@.str.14 = private unnamed_addr constant [11 x i8] c"chdir - %m\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"chdir\00", align 1
@.str.16 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@debug = internal global i32 0, align 4, !dbg !415
@__stdinp = external global %struct.__sFILE*, align 8
@.str.17 = private unnamed_addr constant [12 x i8] c"daemon - %m\00", align 1
@pidfile = internal global i8* null, align 8, !dbg !449
@.str.18 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.19 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@max_connects = internal global i32 0, align 4, !dbg !469
@.str.20 = private unnamed_addr constant [31 x i8] c"fdwatch initialization failure\00", align 1
@do_chroot = internal global i32 0, align 4, !dbg !423
@.str.21 = private unnamed_addr constant [12 x i8] c"chroot - %m\00", align 1
@.str.22 = private unnamed_addr constant [7 x i8] c"chroot\00", align 1
@.str.23 = private unnamed_addr constant [74 x i8] c"logfile is not within the chroot tree, you will not be able to re-open it\00", align 1
@.str.24 = private unnamed_addr constant [79 x i8] c"%s: logfile is not within the chroot tree, you will not be able to re-open it\0A\00", align 1
@.str.25 = private unnamed_addr constant [18 x i8] c"chroot chdir - %m\00", align 1
@.str.26 = private unnamed_addr constant [13 x i8] c"chroot chdir\00", align 1
@data_dir = internal global i8* null, align 8, !dbg !421
@.str.27 = private unnamed_addr constant [20 x i8] c"data_dir chdir - %m\00", align 1
@.str.28 = private unnamed_addr constant [15 x i8] c"data_dir chdir\00", align 1
@got_hup = internal global i32 0, align 4, !dbg !485
@got_usr1 = internal global i32 0, align 4, !dbg !488
@watchdog_flag = internal global i32 0, align 4, !dbg !490
@hostname = internal global i8* null, align 8, !dbg !447
@port = internal global i16 0, align 2, !dbg !417
@cgi_pattern = internal global i8* null, align 8, !dbg !433
@cgi_limit = internal global i32 0, align 4, !dbg !435
@charset = internal global i8* null, align 8, !dbg !453
@p3p = internal global i8* null, align 8, !dbg !455
@max_age = internal global i32 0, align 4, !dbg !457
@no_symlink_check = internal global i32 0, align 4, !dbg !427
@do_vhost = internal global i32 0, align 4, !dbg !429
@do_global_passwd = internal global i32 0, align 4, !dbg !431
@url_pattern = internal global i8* null, align 8, !dbg !437
@local_pattern = internal global i8* null, align 8, !dbg !441
@no_empty_referrers = internal global i32 0, align 4, !dbg !439
@hs = internal global %struct.httpd_server* null, align 8, !dbg !492
@JunkClientData = external global %union.ClientData, align 8
@.str.29 = private unnamed_addr constant [30 x i8] c"tmr_create(occasional) failed\00", align 1
@.str.30 = private unnamed_addr constant [24 x i8] c"tmr_create(idle) failed\00", align 1
@.str.31 = private unnamed_addr constant [36 x i8] c"tmr_create(update_throttles) failed\00", align 1
@.str.32 = private unnamed_addr constant [30 x i8] c"tmr_create(show_stats) failed\00", align 1
@stats_time = common global i64 0, align 8, !dbg !477
@start_time = common global i64 0, align 8, !dbg !475
@stats_connections = common global i64 0, align 8, !dbg !479
@stats_bytes = common global i64 0, align 8, !dbg !481
@stats_simultaneous = common global i32 0, align 4, !dbg !483
@.str.33 = private unnamed_addr constant [15 x i8] c"setgroups - %m\00", align 1
@.str.34 = private unnamed_addr constant [12 x i8] c"setgid - %m\00", align 1
@.str.35 = private unnamed_addr constant [16 x i8] c"initgroups - %m\00", align 1
@.str.36 = private unnamed_addr constant [12 x i8] c"setuid - %m\00", align 1
@.str.37 = private unnamed_addr constant [58 x i8] c"started as root without requesting chroot(), warning only\00", align 1
@connects = internal global %struct.connecttab* null, align 8, !dbg !465
@.str.38 = private unnamed_addr constant [38 x i8] c"out of memory allocating a connecttab\00", align 1
@first_free_connect = internal global i32 0, align 4, !dbg !471
@num_connects = internal global i32 0, align 4, !dbg !467
@httpd_conn_count = internal global i32 0, align 4, !dbg !473
@.str.39 = private unnamed_addr constant [13 x i8] c"fdwatch - %m\00", align 1
@.str.40 = private unnamed_addr constant [8 x i8] c"exiting\00", align 1
@.str.41 = private unnamed_addr constant [25 x i8] c"exiting due to signal %d\00", align 1
@.str.42 = private unnamed_addr constant [16 x i8] c"child wait - %m\00", align 1
@.str.43 = private unnamed_addr constant [39 x i8] c"up %ld seconds, stats for %ld seconds:\00", align 1
@.str.44 = private unnamed_addr constant [104 x i8] c"  thttpd - %ld connections (%g/sec), %d max simultaneous, %lld bytes (%g/sec), %d httpd_conns allocated\00", align 1
@.str.45 = private unnamed_addr constant [5 x i8] c"/tmp\00", align 1
@.str.46 = private unnamed_addr constant [19 x i8] c"re-opening logfile\00", align 1
@.str.47 = private unnamed_addr constant [22 x i8] c"re-opening %.80s - %m\00", align 1
@.str.48 = private unnamed_addr constant [7 x i8] c"nobody\00", align 1
@.str.49 = private unnamed_addr constant [6 x i8] c"UTF-8\00", align 1
@.str.50 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.51 = private unnamed_addr constant [3 x i8] c"-V\00", align 1
@.str.52 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.53 = private unnamed_addr constant [22 x i8] c"thttpd/2.29 23May2018\00", align 1
@.str.54 = private unnamed_addr constant [3 x i8] c"-C\00", align 1
@.str.55 = private unnamed_addr constant [3 x i8] c"-p\00", align 1
@.str.56 = private unnamed_addr constant [3 x i8] c"-d\00", align 1
@.str.57 = private unnamed_addr constant [3 x i8] c"-r\00", align 1
@.str.58 = private unnamed_addr constant [5 x i8] c"-nor\00", align 1
@.str.59 = private unnamed_addr constant [4 x i8] c"-dd\00", align 1
@.str.60 = private unnamed_addr constant [3 x i8] c"-s\00", align 1
@.str.61 = private unnamed_addr constant [5 x i8] c"-nos\00", align 1
@.str.62 = private unnamed_addr constant [3 x i8] c"-u\00", align 1
@.str.63 = private unnamed_addr constant [3 x i8] c"-c\00", align 1
@.str.64 = private unnamed_addr constant [3 x i8] c"-t\00", align 1
@.str.65 = private unnamed_addr constant [3 x i8] c"-h\00", align 1
@.str.66 = private unnamed_addr constant [3 x i8] c"-l\00", align 1
@.str.67 = private unnamed_addr constant [3 x i8] c"-v\00", align 1
@.str.68 = private unnamed_addr constant [5 x i8] c"-nov\00", align 1
@.str.69 = private unnamed_addr constant [3 x i8] c"-g\00", align 1
@.str.70 = private unnamed_addr constant [5 x i8] c"-nog\00", align 1
@.str.71 = private unnamed_addr constant [3 x i8] c"-i\00", align 1
@.str.72 = private unnamed_addr constant [3 x i8] c"-T\00", align 1
@.str.73 = private unnamed_addr constant [3 x i8] c"-P\00", align 1
@.str.74 = private unnamed_addr constant [3 x i8] c"-M\00", align 1
@.str.75 = private unnamed_addr constant [3 x i8] c"-D\00", align 1
@.str.76 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.77 = private unnamed_addr constant [5 x i8] c" \09\0A\0D\00", align 1
@.str.78 = private unnamed_addr constant [6 x i8] c"debug\00", align 1
@.str.79 = private unnamed_addr constant [5 x i8] c"port\00", align 1
@.str.80 = private unnamed_addr constant [4 x i8] c"dir\00", align 1
@.str.81 = private unnamed_addr constant [9 x i8] c"nochroot\00", align 1
@.str.82 = private unnamed_addr constant [9 x i8] c"data_dir\00", align 1
@.str.83 = private unnamed_addr constant [15 x i8] c"nosymlinkcheck\00", align 1
@.str.84 = private unnamed_addr constant [13 x i8] c"symlinkcheck\00", align 1
@.str.85 = private unnamed_addr constant [5 x i8] c"user\00", align 1
@.str.86 = private unnamed_addr constant [7 x i8] c"cgipat\00", align 1
@.str.87 = private unnamed_addr constant [9 x i8] c"cgilimit\00", align 1
@.str.88 = private unnamed_addr constant [7 x i8] c"urlpat\00", align 1
@.str.89 = private unnamed_addr constant [16 x i8] c"noemptyreferers\00", align 1
@.str.90 = private unnamed_addr constant [17 x i8] c"noemptyreferrers\00", align 1
@.str.91 = private unnamed_addr constant [9 x i8] c"localpat\00", align 1
@.str.92 = private unnamed_addr constant [10 x i8] c"throttles\00", align 1
@.str.93 = private unnamed_addr constant [5 x i8] c"host\00", align 1
@.str.94 = private unnamed_addr constant [8 x i8] c"logfile\00", align 1
@.str.95 = private unnamed_addr constant [6 x i8] c"vhost\00", align 1
@.str.96 = private unnamed_addr constant [8 x i8] c"novhost\00", align 1
@.str.97 = private unnamed_addr constant [13 x i8] c"globalpasswd\00", align 1
@.str.98 = private unnamed_addr constant [15 x i8] c"noglobalpasswd\00", align 1
@.str.99 = private unnamed_addr constant [8 x i8] c"pidfile\00", align 1
@.str.100 = private unnamed_addr constant [8 x i8] c"charset\00", align 1
@.str.101 = private unnamed_addr constant [4 x i8] c"p3p\00", align 1
@.str.102 = private unnamed_addr constant [8 x i8] c"max_age\00", align 1
@.str.103 = private unnamed_addr constant [32 x i8] c"%s: unknown config option '%s'\0A\00", align 1
@.str.104 = private unnamed_addr constant [37 x i8] c"%s: no value required for %s option\0A\00", align 1
@.str.105 = private unnamed_addr constant [34 x i8] c"%s: value required for %s option\0A\00", align 1
@.str.106 = private unnamed_addr constant [31 x i8] c"out of memory copying a string\00", align 1
@.str.107 = private unnamed_addr constant [36 x i8] c"%s: out of memory copying a string\0A\00", align 1
@.str.108 = private unnamed_addr constant [219 x i8] c"usage:  %s [-C configfile] [-p port] [-d dir] [-r|-nor] [-dd data_dir] [-s|-nos] [-v|-nov] [-g|-nog] [-u user] [-c cgipat] [-t throttles] [-h host] [-l logfile] [-i pidfile] [-T charset] [-P P3P] [-M maxage] [-V] [-D]\0A\00", align 1
@.str.109 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.110 = private unnamed_addr constant [26 x i8] c"getaddrinfo %.80s - %.80s\00", align 1
@.str.111 = private unnamed_addr constant [25 x i8] c"%s: getaddrinfo %s - %s\0A\00", align 1
@.str.112 = private unnamed_addr constant [39 x i8] c"%.80s - sockaddr too small (%lu < %lu)\00", align 1
@.str.113 = private unnamed_addr constant [20 x i8] c" %4900[^ \09] %ld-%ld\00", align 1
@.str.114 = private unnamed_addr constant [16 x i8] c" %4900[^ \09] %ld\00", align 1
@.str.115 = private unnamed_addr constant [33 x i8] c"unparsable line in %.80s - %.80s\00", align 1
@.str.116 = private unnamed_addr constant [38 x i8] c"%s: unparsable line in %.80s - %.80s\0A\00", align 1
@.str.117 = private unnamed_addr constant [3 x i8] c"|/\00", align 1
@.str.118 = private unnamed_addr constant [39 x i8] c"out of memory allocating a throttletab\00", align 1
@.str.119 = private unnamed_addr constant [44 x i8] c"%s: out of memory allocating a throttletab\0A\00", align 1
@.str.120 = private unnamed_addr constant [22 x i8] c"too many connections!\00", align 1
@.str.121 = private unnamed_addr constant [36 x i8] c"the connects free list is messed up\00", align 1
@.str.122 = private unnamed_addr constant [39 x i8] c"out of memory allocating an httpd_conn\00", align 1
@httpd_err400title = external global i8*, align 8
@httpd_err400form = external global i8*, align 8
@httpd_err503title = external global i8*, align 8
@httpd_err503form = external global i8*, align 8
@.str.123 = private unnamed_addr constant [56 x i8] c"throttle sending count was negative - shouldn't happen!\00", align 1
@.str.124 = private unnamed_addr constant [33 x i8] c"replacing non-null wakeup_timer!\00", align 1
@.str.125 = private unnamed_addr constant [37 x i8] c"tmr_create(wakeup_connection) failed\00", align 1
@.str.126 = private unnamed_addr constant [25 x i8] c"write - %m sending %.80s\00", align 1
@.str.127 = private unnamed_addr constant [70 x i8] c"throttle #%d '%.80s' rate %ld greatly exceeding limit %ld; %d sending\00", align 1
@.str.128 = private unnamed_addr constant [62 x i8] c"throttle #%d '%.80s' rate %ld exceeding limit %ld; %d sending\00", align 1
@.str.129 = private unnamed_addr constant [65 x i8] c"throttle #%d '%.80s' rate %ld lower than minimum %ld; %d sending\00", align 1
@.str.130 = private unnamed_addr constant [33 x i8] c"replacing non-null linger_timer!\00", align 1
@.str.131 = private unnamed_addr constant [43 x i8] c"tmr_create(linger_clear_connection) failed\00", align 1
@.str.132 = private unnamed_addr constant [35 x i8] c"%.80s connection timed out reading\00", align 1
@httpd_err408title = external global i8*, align 8
@httpd_err408form = external global i8*, align 8
@.str.133 = private unnamed_addr constant [35 x i8] c"%.80s connection timed out sending\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !499 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %cp = alloca i8*, align 8
  %pwd = alloca %struct.passwd*, align 8
  %uid = alloca i32, align 4
  %gid = alloca i32, align 4
  %cwd = alloca [1025 x i8], align 16
  %logfp = alloca %struct.__sFILE*, align 8
  %num_ready = alloca i32, align 4
  %cnum = alloca i32, align 4
  %c = alloca %struct.connecttab*, align 8
  %hc = alloca %struct.httpd_conn*, align 8
  %sa4 = alloca %union.httpd_sockaddr, align 8
  %sa6 = alloca %union.httpd_sockaddr, align 8
  %gotv4 = alloca i32, align 4
  %gotv6 = alloca i32, align 4
  %tv = alloca %struct.timeval, align 8
  %pidfp = alloca %struct.__sFILE*, align 8
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !503, metadata !DIExpression()), !dbg !504
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !505, metadata !DIExpression()), !dbg !506
  call void @llvm.dbg.declare(metadata i8** %cp, metadata !507, metadata !DIExpression()), !dbg !508
  call void @llvm.dbg.declare(metadata %struct.passwd** %pwd, metadata !509, metadata !DIExpression()), !dbg !510
  %pwd1 = bitcast %struct.passwd** %pwd to i8*, !dbg !511
  call void @llvm.var.annotation(i8* %pwd1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.1, i32 0, i32 0), i32 358), !dbg !511
  call void @llvm.dbg.declare(metadata i32* %uid, metadata !512, metadata !DIExpression()), !dbg !513
  store i32 32767, i32* %uid, align 4, !dbg !513
  call void @llvm.dbg.declare(metadata i32* %gid, metadata !514, metadata !DIExpression()), !dbg !515
  store i32 32767, i32* %gid, align 4, !dbg !515
  call void @llvm.dbg.declare(metadata [1025 x i8]* %cwd, metadata !516, metadata !DIExpression()), !dbg !520
  call void @llvm.dbg.declare(metadata %struct.__sFILE** %logfp, metadata !521, metadata !DIExpression()), !dbg !522
  call void @llvm.dbg.declare(metadata i32* %num_ready, metadata !523, metadata !DIExpression()), !dbg !524
  call void @llvm.dbg.declare(metadata i32* %cnum, metadata !525, metadata !DIExpression()), !dbg !526
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c, metadata !527, metadata !DIExpression()), !dbg !528
  call void @llvm.dbg.declare(metadata %struct.httpd_conn** %hc, metadata !529, metadata !DIExpression()), !dbg !530
  call void @llvm.dbg.declare(metadata %union.httpd_sockaddr* %sa4, metadata !531, metadata !DIExpression()), !dbg !532
  call void @llvm.dbg.declare(metadata %union.httpd_sockaddr* %sa6, metadata !533, metadata !DIExpression()), !dbg !534
  call void @llvm.dbg.declare(metadata i32* %gotv4, metadata !535, metadata !DIExpression()), !dbg !536
  call void @llvm.dbg.declare(metadata i32* %gotv6, metadata !537, metadata !DIExpression()), !dbg !538
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !539, metadata !DIExpression()), !dbg !540
  %0 = load i8**, i8*** %argv.addr, align 8, !dbg !541
  %arrayidx = getelementptr inbounds i8*, i8** %0, i64 0, !dbg !541
  %1 = load i8*, i8** %arrayidx, align 8, !dbg !541
  store i8* %1, i8** @argv0, align 8, !dbg !542
  %2 = load i8*, i8** @argv0, align 8, !dbg !543
  %call = call i8* @strrchr(i8* %2, i32 47), !dbg !544
  store i8* %call, i8** %cp, align 8, !dbg !545
  %3 = load i8*, i8** %cp, align 8, !dbg !546
  %cmp = icmp ne i8* %3, null, !dbg !548
  br i1 %cmp, label %if.then, label %if.else, !dbg !549

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %cp, align 8, !dbg !550
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 1, !dbg !550
  store i8* %incdec.ptr, i8** %cp, align 8, !dbg !550
  br label %if.end, !dbg !550

if.else:                                          ; preds = %entry
  %5 = load i8*, i8** @argv0, align 8, !dbg !551
  store i8* %5, i8** %cp, align 8, !dbg !552
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %6 = load i8*, i8** %cp, align 8, !dbg !553
  call void @openlog(i8* %6, i32 9, i32 24), !dbg !554
  %7 = load i32, i32* %argc.addr, align 4, !dbg !555
  %8 = load i8**, i8*** %argv.addr, align 8, !dbg !556
  call void @parse_args(i32 %7, i8** %8), !dbg !557
  call void @tzset(), !dbg !558
  call void @lookup_hostname(%union.httpd_sockaddr* %sa4, i64 128, i32* %gotv4, %union.httpd_sockaddr* %sa6, i64 128, i32* %gotv6), !dbg !559
  %9 = load i32, i32* %gotv4, align 4, !dbg !560
  %tobool = icmp ne i32 %9, 0, !dbg !560
  br i1 %tobool, label %if.end5, label %lor.lhs.false, !dbg !562

lor.lhs.false:                                    ; preds = %if.end
  %10 = load i32, i32* %gotv6, align 4, !dbg !563
  %tobool2 = icmp ne i32 %10, 0, !dbg !563
  br i1 %tobool2, label %if.end5, label %if.then3, !dbg !564

if.then3:                                         ; preds = %lor.lhs.false
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.2, i64 0, i64 0)), !dbg !565
  %11 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !567
  %12 = load i8*, i8** @argv0, align 8, !dbg !568
  %call4 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %11, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.3, i64 0, i64 0), i8* %12), !dbg !569
  call void @exit(i32 1) #11, !dbg !570
  unreachable, !dbg !570

if.end5:                                          ; preds = %lor.lhs.false, %if.end
  store i32 0, i32* @numthrottles, align 4, !dbg !571
  store i32 0, i32* @maxthrottles, align 4, !dbg !572
  store %struct.throttletab* null, %struct.throttletab** @throttles, align 8, !dbg !573
  %13 = load i8*, i8** @throttlefile, align 8, !dbg !574
  %cmp6 = icmp ne i8* %13, null, !dbg !576
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !577

if.then7:                                         ; preds = %if.end5
  %14 = load i8*, i8** @throttlefile, align 8, !dbg !578
  call void @read_throttlefile(i8* %14), !dbg !579
  br label %if.end8, !dbg !579

if.end8:                                          ; preds = %if.then7, %if.end5
  %call9 = call i32 @getuid(), !dbg !580
  %cmp10 = icmp eq i32 %call9, 0, !dbg !582
  br i1 %cmp10, label %if.then11, label %if.end17, !dbg !583

if.then11:                                        ; preds = %if.end8
  %15 = load i8*, i8** @user, align 8, !dbg !584
  %call12 = call %struct.passwd* @getpwnam(i8* %15), !dbg !586
  store %struct.passwd* %call12, %struct.passwd** %pwd, align 8, !dbg !587
  %16 = load %struct.passwd*, %struct.passwd** %pwd, align 8, !dbg !588
  %cmp13 = icmp eq %struct.passwd* %16, null, !dbg !590
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !591

if.then14:                                        ; preds = %if.then11
  %17 = load i8*, i8** @user, align 8, !dbg !592
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i64 0, i64 0), i8* %17), !dbg !594
  %18 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !595
  %19 = load i8*, i8** @argv0, align 8, !dbg !596
  %20 = load i8*, i8** @user, align 8, !dbg !597
  %call15 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %18, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.5, i64 0, i64 0), i8* %19, i8* %20), !dbg !598
  call void @exit(i32 1) #11, !dbg !599
  unreachable, !dbg !599

if.end16:                                         ; preds = %if.then11
  %21 = load %struct.passwd*, %struct.passwd** %pwd, align 8, !dbg !600
  %pw_uid = getelementptr inbounds %struct.passwd, %struct.passwd* %21, i32 0, i32 2, !dbg !601
  %22 = load i32, i32* %pw_uid, align 8, !dbg !601
  store i32 %22, i32* %uid, align 4, !dbg !602
  %23 = load %struct.passwd*, %struct.passwd** %pwd, align 8, !dbg !603
  %pw_gid = getelementptr inbounds %struct.passwd, %struct.passwd* %23, i32 0, i32 3, !dbg !604
  %24 = load i32, i32* %pw_gid, align 4, !dbg !604
  store i32 %24, i32* %gid, align 4, !dbg !605
  br label %if.end17, !dbg !606

if.end17:                                         ; preds = %if.end16, %if.end8
  %25 = load i8*, i8** @logfile, align 8, !dbg !607
  %cmp18 = icmp ne i8* %25, null, !dbg !609
  br i1 %cmp18, label %if.then19, label %if.else53, !dbg !610

if.then19:                                        ; preds = %if.end17
  %26 = load i8*, i8** @logfile, align 8, !dbg !611
  %call20 = call i32 @strcmp(i8* %26, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.6, i64 0, i64 0)), !dbg !614
  %cmp21 = icmp eq i32 %call20, 0, !dbg !615
  br i1 %cmp21, label %if.then22, label %if.else23, !dbg !616

if.then22:                                        ; preds = %if.then19
  store i32 1, i32* @no_log, align 4, !dbg !617
  store %struct.__sFILE* null, %struct.__sFILE** %logfp, align 8, !dbg !619
  br label %if.end52, !dbg !620

if.else23:                                        ; preds = %if.then19
  %27 = load i8*, i8** @logfile, align 8, !dbg !621
  %call24 = call i32 @strcmp(i8* %27, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.7, i64 0, i64 0)), !dbg !623
  %cmp25 = icmp eq i32 %call24, 0, !dbg !624
  br i1 %cmp25, label %if.then26, label %if.else27, !dbg !625

if.then26:                                        ; preds = %if.else23
  %28 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8, !dbg !626
  store %struct.__sFILE* %28, %struct.__sFILE** %logfp, align 8, !dbg !627
  br label %if.end51, !dbg !628

if.else27:                                        ; preds = %if.else23
  %29 = load i8*, i8** @logfile, align 8, !dbg !629
  %call28 = call %struct.__sFILE* @"\01_fopen"(i8* %29, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.8, i64 0, i64 0)), !dbg !631
  store %struct.__sFILE* %call28, %struct.__sFILE** %logfp, align 8, !dbg !632
  %30 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !633
  %cmp29 = icmp eq %struct.__sFILE* %30, null, !dbg !635
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !636

if.then30:                                        ; preds = %if.else27
  %31 = load i8*, i8** @logfile, align 8, !dbg !637
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i64 0, i64 0), i8* %31), !dbg !639
  %32 = load i8*, i8** @logfile, align 8, !dbg !640
  call void @perror(i8* %32) #12, !dbg !641
  call void @exit(i32 1) #11, !dbg !642
  unreachable, !dbg !642

if.end31:                                         ; preds = %if.else27
  %33 = load i8*, i8** @logfile, align 8, !dbg !643
  %arrayidx32 = getelementptr inbounds i8, i8* %33, i64 0, !dbg !643
  %34 = load i8, i8* %arrayidx32, align 1, !dbg !643
  %conv = sext i8 %34 to i32, !dbg !643
  %cmp33 = icmp ne i32 %conv, 47, !dbg !645
  br i1 %cmp33, label %if.then35, label %if.end37, !dbg !646

if.then35:                                        ; preds = %if.end31
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 4, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.10, i64 0, i64 0)), !dbg !647
  %35 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !649
  %36 = load i8*, i8** @argv0, align 8, !dbg !650
  %call36 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %35, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @.str.11, i64 0, i64 0), i8* %36), !dbg !651
  br label %if.end37, !dbg !652

if.end37:                                         ; preds = %if.then35, %if.end31
  %37 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !653
  %call38 = call i32 @fileno(%struct.__sFILE* %37), !dbg !654
  %call39 = call i32 (i32, i32, ...) @"\01_fcntl"(i32 %call38, i32 2, i32 1), !dbg !655
  %call40 = call i32 @getuid(), !dbg !656
  %cmp41 = icmp eq i32 %call40, 0, !dbg !658
  br i1 %cmp41, label %if.then43, label %if.end50, !dbg !659

if.then43:                                        ; preds = %if.end37
  %38 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !660
  %call44 = call i32 @fileno(%struct.__sFILE* %38), !dbg !663
  %39 = load i32, i32* %uid, align 4, !dbg !664
  %40 = load i32, i32* %gid, align 4, !dbg !665
  %call45 = call i32 @fchown(i32 %call44, i32 %39, i32 %40), !dbg !666
  %cmp46 = icmp slt i32 %call45, 0, !dbg !667
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !668

if.then48:                                        ; preds = %if.then43
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 4, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.12, i64 0, i64 0)), !dbg !669
  call void @perror(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.13, i64 0, i64 0)) #12, !dbg !671
  br label %if.end49, !dbg !672

if.end49:                                         ; preds = %if.then48, %if.then43
  br label %if.end50, !dbg !673

if.end50:                                         ; preds = %if.end49, %if.end37
  br label %if.end51

if.end51:                                         ; preds = %if.end50, %if.then26
  br label %if.end52

if.end52:                                         ; preds = %if.end51, %if.then22
  br label %if.end54, !dbg !674

if.else53:                                        ; preds = %if.end17
  store %struct.__sFILE* null, %struct.__sFILE** %logfp, align 8, !dbg !675
  br label %if.end54

if.end54:                                         ; preds = %if.else53, %if.end52
  %41 = load i8*, i8** @dir, align 8, !dbg !676
  %cmp55 = icmp ne i8* %41, null, !dbg !678
  br i1 %cmp55, label %if.then57, label %if.end63, !dbg !679

if.then57:                                        ; preds = %if.end54
  %42 = load i8*, i8** @dir, align 8, !dbg !680
  %call58 = call i32 @chdir(i8* %42), !dbg !683
  %cmp59 = icmp slt i32 %call58, 0, !dbg !684
  br i1 %cmp59, label %if.then61, label %if.end62, !dbg !685

if.then61:                                        ; preds = %if.then57
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.14, i64 0, i64 0)), !dbg !686
  call void @perror(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i64 0, i64 0)) #12, !dbg !688
  call void @exit(i32 1) #11, !dbg !689
  unreachable, !dbg !689

if.end62:                                         ; preds = %if.then57
  br label %if.end63, !dbg !690

if.end63:                                         ; preds = %if.end62, %if.end54
  %arraydecay = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !691
  %call64 = call i8* @getcwd(i8* %arraydecay, i64 1024), !dbg !692
  %arraydecay65 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !693
  %call66 = call i64 @strlen(i8* %arraydecay65), !dbg !695
  %sub = sub i64 %call66, 1, !dbg !696
  %arrayidx67 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 %sub, !dbg !697
  %43 = load i8, i8* %arrayidx67, align 1, !dbg !697
  %conv68 = sext i8 %43 to i32, !dbg !697
  %cmp69 = icmp ne i32 %conv68, 47, !dbg !698
  br i1 %cmp69, label %if.then71, label %if.end74, !dbg !699

if.then71:                                        ; preds = %if.end63
  %arraydecay72 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !700
  %call73 = call i8* @__strcat_chk(i8* %arraydecay72, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.16, i64 0, i64 0), i64 1025) #13, !dbg !700
  br label %if.end74, !dbg !701

if.end74:                                         ; preds = %if.then71, %if.end63
  %44 = load i32, i32* @debug, align 4, !dbg !702
  %tobool75 = icmp ne i32 %44, 0, !dbg !702
  br i1 %tobool75, label %if.else89, label %if.then76, !dbg !704

if.then76:                                        ; preds = %if.end74
  %45 = load %struct.__sFILE*, %struct.__sFILE** @__stdinp, align 8, !dbg !705
  %call77 = call i32 @fclose(%struct.__sFILE* %45), !dbg !707
  %46 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !708
  %47 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8, !dbg !710
  %cmp78 = icmp ne %struct.__sFILE* %46, %47, !dbg !711
  br i1 %cmp78, label %if.then80, label %if.end82, !dbg !712

if.then80:                                        ; preds = %if.then76
  %48 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8, !dbg !713
  %call81 = call i32 @fclose(%struct.__sFILE* %48), !dbg !714
  br label %if.end82, !dbg !715

if.end82:                                         ; preds = %if.then80, %if.then76
  %49 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !716
  %call83 = call i32 @fclose(%struct.__sFILE* %49), !dbg !717
  %call84 = call i32 @"\01_daemon$1050"(i32 1, i32 1), !dbg !718
  %cmp85 = icmp slt i32 %call84, 0, !dbg !720
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !721

if.then87:                                        ; preds = %if.end82
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.17, i64 0, i64 0)), !dbg !722
  call void @exit(i32 1) #11, !dbg !724
  unreachable, !dbg !724

if.end88:                                         ; preds = %if.end82
  br label %if.end91, !dbg !725

if.else89:                                        ; preds = %if.end74
  %call90 = call i32 @setsid(), !dbg !726
  br label %if.end91

if.end91:                                         ; preds = %if.else89, %if.end88
  %50 = load i8*, i8** @pidfile, align 8, !dbg !728
  %cmp92 = icmp ne i8* %50, null, !dbg !730
  br i1 %cmp92, label %if.then94, label %if.end103, !dbg !731

if.then94:                                        ; preds = %if.end91
  call void @llvm.dbg.declare(metadata %struct.__sFILE** %pidfp, metadata !732, metadata !DIExpression()), !dbg !734
  %51 = load i8*, i8** @pidfile, align 8, !dbg !735
  %call95 = call %struct.__sFILE* @"\01_fopen"(i8* %51, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i64 0, i64 0)), !dbg !736
  store %struct.__sFILE* %call95, %struct.__sFILE** %pidfp, align 8, !dbg !734
  %52 = load %struct.__sFILE*, %struct.__sFILE** %pidfp, align 8, !dbg !737
  %cmp96 = icmp eq %struct.__sFILE* %52, null, !dbg !739
  br i1 %cmp96, label %if.then98, label %if.end99, !dbg !740

if.then98:                                        ; preds = %if.then94
  %53 = load i8*, i8** @pidfile, align 8, !dbg !741
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i64 0, i64 0), i8* %53), !dbg !743
  call void @exit(i32 1) #11, !dbg !744
  unreachable, !dbg !744

if.end99:                                         ; preds = %if.then94
  %54 = load %struct.__sFILE*, %struct.__sFILE** %pidfp, align 8, !dbg !745
  %call100 = call i32 @getpid(), !dbg !746
  %call101 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %54, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.19, i64 0, i64 0), i32 %call100), !dbg !747
  %55 = load %struct.__sFILE*, %struct.__sFILE** %pidfp, align 8, !dbg !748
  %call102 = call i32 @fclose(%struct.__sFILE* %55), !dbg !749
  br label %if.end103, !dbg !750

if.end103:                                        ; preds = %if.end99, %if.end91
  %call104 = call i32 @fdwatch_get_nfiles(), !dbg !751
  store i32 %call104, i32* @max_connects, align 4, !dbg !752
  %56 = load i32, i32* @max_connects, align 4, !dbg !753
  %cmp105 = icmp slt i32 %56, 0, !dbg !755
  br i1 %cmp105, label %if.then107, label %if.end108, !dbg !756

if.then107:                                       ; preds = %if.end103
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.20, i64 0, i64 0)), !dbg !757
  call void @exit(i32 1) #11, !dbg !759
  unreachable, !dbg !759

if.end108:                                        ; preds = %if.end103
  %57 = load i32, i32* @max_connects, align 4, !dbg !760
  %sub109 = sub nsw i32 %57, 10, !dbg !760
  store i32 %sub109, i32* @max_connects, align 4, !dbg !760
  %58 = load i32, i32* @do_chroot, align 4, !dbg !761
  %tobool110 = icmp ne i32 %58, 0, !dbg !761
  br i1 %tobool110, label %if.then111, label %if.end153, !dbg !763

if.then111:                                       ; preds = %if.end108
  %arraydecay112 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !764
  %call113 = call i32 @chroot(i8* %arraydecay112), !dbg !767
  %cmp114 = icmp slt i32 %call113, 0, !dbg !768
  br i1 %cmp114, label %if.then116, label %if.end117, !dbg !769

if.then116:                                       ; preds = %if.then111
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.21, i64 0, i64 0)), !dbg !770
  call void @perror(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.22, i64 0, i64 0)) #12, !dbg !772
  call void @exit(i32 1) #11, !dbg !773
  unreachable, !dbg !773

if.end117:                                        ; preds = %if.then111
  %59 = load i8*, i8** @logfile, align 8, !dbg !774
  %cmp118 = icmp ne i8* %59, null, !dbg !776
  br i1 %cmp118, label %land.lhs.true, label %if.end144, !dbg !777

land.lhs.true:                                    ; preds = %if.end117
  %60 = load i8*, i8** @logfile, align 8, !dbg !778
  %call120 = call i32 @strcmp(i8* %60, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.7, i64 0, i64 0)), !dbg !779
  %cmp121 = icmp ne i32 %call120, 0, !dbg !780
  br i1 %cmp121, label %if.then123, label %if.end144, !dbg !781

if.then123:                                       ; preds = %land.lhs.true
  %61 = load i8*, i8** @logfile, align 8, !dbg !782
  %arraydecay124 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !785
  %arraydecay125 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !786
  %call126 = call i64 @strlen(i8* %arraydecay125), !dbg !787
  %call127 = call i32 @strncmp(i8* %61, i8* %arraydecay124, i64 %call126), !dbg !788
  %cmp128 = icmp eq i32 %call127, 0, !dbg !789
  br i1 %cmp128, label %if.then130, label %if.else141, !dbg !790

if.then130:                                       ; preds = %if.then123
  %62 = load i8*, i8** @logfile, align 8, !dbg !791
  %63 = load i8*, i8** @logfile, align 8, !dbg !791
  %arraydecay131 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !791
  %call132 = call i64 @strlen(i8* %arraydecay131), !dbg !791
  %sub133 = sub i64 %call132, 1, !dbg !791
  %arrayidx134 = getelementptr inbounds i8, i8* %63, i64 %sub133, !dbg !791
  %64 = load i8*, i8** @logfile, align 8, !dbg !791
  %arraydecay135 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !791
  %call136 = call i64 @strlen(i8* %arraydecay135), !dbg !791
  %sub137 = sub i64 %call136, 1, !dbg !791
  %arrayidx138 = getelementptr inbounds i8, i8* %64, i64 %sub137, !dbg !791
  %call139 = call i64 @strlen(i8* %arrayidx138), !dbg !791
  %add = add i64 %call139, 1, !dbg !791
  %65 = load i8*, i8** @logfile, align 8, !dbg !791
  %66 = call i64 @llvm.objectsize.i64.p0i8(i8* %65, i1 false, i1 true, i1 false), !dbg !791
  %call140 = call i8* @__memmove_chk(i8* %62, i8* %arrayidx134, i64 %add, i64 %66) #13, !dbg !791
  br label %if.end143, !dbg !793

if.else141:                                       ; preds = %if.then123
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 4, i8* getelementptr inbounds ([74 x i8], [74 x i8]* @.str.23, i64 0, i64 0)), !dbg !794
  %67 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !796
  %68 = load i8*, i8** @argv0, align 8, !dbg !797
  %call142 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %67, i8* getelementptr inbounds ([79 x i8], [79 x i8]* @.str.24, i64 0, i64 0), i8* %68), !dbg !798
  br label %if.end143

if.end143:                                        ; preds = %if.else141, %if.then130
  br label %if.end144, !dbg !799

if.end144:                                        ; preds = %if.end143, %land.lhs.true, %if.end117
  %arraydecay145 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !800
  %call146 = call i8* @__strcpy_chk(i8* %arraydecay145, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.16, i64 0, i64 0), i64 1025) #13, !dbg !800
  %arraydecay147 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !801
  %call148 = call i32 @chdir(i8* %arraydecay147), !dbg !803
  %cmp149 = icmp slt i32 %call148, 0, !dbg !804
  br i1 %cmp149, label %if.then151, label %if.end152, !dbg !805

if.then151:                                       ; preds = %if.end144
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.25, i64 0, i64 0)), !dbg !806
  call void @perror(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.26, i64 0, i64 0)) #12, !dbg !808
  call void @exit(i32 1) #11, !dbg !809
  unreachable, !dbg !809

if.end152:                                        ; preds = %if.end144
  br label %if.end153, !dbg !810

if.end153:                                        ; preds = %if.end152, %if.end108
  %69 = load i8*, i8** @data_dir, align 8, !dbg !811
  %cmp154 = icmp ne i8* %69, null, !dbg !813
  br i1 %cmp154, label %if.then156, label %if.end162, !dbg !814

if.then156:                                       ; preds = %if.end153
  %70 = load i8*, i8** @data_dir, align 8, !dbg !815
  %call157 = call i32 @chdir(i8* %70), !dbg !818
  %cmp158 = icmp slt i32 %call157, 0, !dbg !819
  br i1 %cmp158, label %if.then160, label %if.end161, !dbg !820

if.then160:                                       ; preds = %if.then156
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.27, i64 0, i64 0)), !dbg !821
  call void @perror(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.28, i64 0, i64 0)) #12, !dbg !823
  call void @exit(i32 1) #11, !dbg !824
  unreachable, !dbg !824

if.end161:                                        ; preds = %if.then156
  br label %if.end162, !dbg !825

if.end162:                                        ; preds = %if.end161, %if.end153
  %call163 = call void (i32)* @sigset(i32 15, void (i32)* @handle_term), !dbg !826
  %call164 = call void (i32)* @sigset(i32 2, void (i32)* @handle_term), !dbg !827
  %call165 = call void (i32)* @sigset(i32 20, void (i32)* @handle_chld), !dbg !828
  %call166 = call void (i32)* @sigset(i32 13, void (i32)* inttoptr (i64 1 to void (i32)*)), !dbg !829
  %call167 = call void (i32)* @sigset(i32 1, void (i32)* @handle_hup), !dbg !830
  %call168 = call void (i32)* @sigset(i32 30, void (i32)* @handle_usr1), !dbg !831
  %call169 = call void (i32)* @sigset(i32 31, void (i32)* @handle_usr2), !dbg !832
  %call170 = call void (i32)* @sigset(i32 14, void (i32)* @handle_alrm), !dbg !833
  store volatile i32 0, i32* @got_hup, align 4, !dbg !834
  store volatile i32 0, i32* @got_usr1, align 4, !dbg !835
  store volatile i32 0, i32* @watchdog_flag, align 4, !dbg !836
  %call171 = call i32 @alarm(i32 360), !dbg !837
  call void @tmr_init(), !dbg !838
  %71 = load i8*, i8** @hostname, align 8, !dbg !839
  %72 = load i32, i32* %gotv4, align 4, !dbg !840
  %tobool172 = icmp ne i32 %72, 0, !dbg !840
  br i1 %tobool172, label %cond.true, label %cond.false, !dbg !840

cond.true:                                        ; preds = %if.end162
  br label %cond.end, !dbg !840

cond.false:                                       ; preds = %if.end162
  br label %cond.end, !dbg !840

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %union.httpd_sockaddr* [ %sa4, %cond.true ], [ null, %cond.false ], !dbg !840
  %73 = load i32, i32* %gotv6, align 4, !dbg !841
  %tobool173 = icmp ne i32 %73, 0, !dbg !841
  br i1 %tobool173, label %cond.true174, label %cond.false175, !dbg !841

cond.true174:                                     ; preds = %cond.end
  br label %cond.end176, !dbg !841

cond.false175:                                    ; preds = %cond.end
  br label %cond.end176, !dbg !841

cond.end176:                                      ; preds = %cond.false175, %cond.true174
  %cond177 = phi %union.httpd_sockaddr* [ %sa6, %cond.true174 ], [ null, %cond.false175 ], !dbg !841
  %74 = load i16, i16* @port, align 2, !dbg !842
  %75 = load i8*, i8** @cgi_pattern, align 8, !dbg !843
  %76 = load i32, i32* @cgi_limit, align 4, !dbg !844
  %77 = load i8*, i8** @charset, align 8, !dbg !845
  %78 = load i8*, i8** @p3p, align 8, !dbg !846
  %79 = load i32, i32* @max_age, align 4, !dbg !847
  %arraydecay178 = getelementptr inbounds [1025 x i8], [1025 x i8]* %cwd, i64 0, i64 0, !dbg !848
  %80 = load i32, i32* @no_log, align 4, !dbg !849
  %81 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !850
  %82 = load i32, i32* @no_symlink_check, align 4, !dbg !851
  %83 = load i32, i32* @do_vhost, align 4, !dbg !852
  %84 = load i32, i32* @do_global_passwd, align 4, !dbg !853
  %85 = load i8*, i8** @url_pattern, align 8, !dbg !854
  %86 = load i8*, i8** @local_pattern, align 8, !dbg !855
  %87 = load i32, i32* @no_empty_referrers, align 4, !dbg !856
  %call179 = call %struct.httpd_server* @httpd_initialize(i8* %71, %union.httpd_sockaddr* %cond, %union.httpd_sockaddr* %cond177, i16 zeroext %74, i8* %75, i32 %76, i8* %77, i8* %78, i32 %79, i8* %arraydecay178, i32 %80, %struct.__sFILE* %81, i32 %82, i32 %83, i32 %84, i8* %85, i8* %86, i32 %87), !dbg !857
  store %struct.httpd_server* %call179, %struct.httpd_server** @hs, align 8, !dbg !858
  %88 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !859
  %cmp180 = icmp eq %struct.httpd_server* %88, null, !dbg !861
  br i1 %cmp180, label %if.then182, label %if.end183, !dbg !862

if.then182:                                       ; preds = %cond.end176
  call void @exit(i32 1) #11, !dbg !863
  unreachable, !dbg !863

if.end183:                                        ; preds = %cond.end176
  %89 = load i8*, i8** getelementptr inbounds (%union.ClientData, %union.ClientData* @JunkClientData, i32 0, i32 0), align 8, !dbg !864
  %call184 = call %struct.TimerStruct* @tmr_create(%struct.timeval* null, void (i8*, %struct.timeval*)* @occasional, i8* %89, i64 120000, i32 1), !dbg !864
  %cmp185 = icmp eq %struct.TimerStruct* %call184, null, !dbg !866
  br i1 %cmp185, label %if.then187, label %if.end188, !dbg !867

if.then187:                                       ; preds = %if.end183
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.29, i64 0, i64 0)), !dbg !868
  call void @exit(i32 1) #11, !dbg !870
  unreachable, !dbg !870

if.end188:                                        ; preds = %if.end183
  %90 = load i8*, i8** getelementptr inbounds (%union.ClientData, %union.ClientData* @JunkClientData, i32 0, i32 0), align 8, !dbg !871
  %call189 = call %struct.TimerStruct* @tmr_create(%struct.timeval* null, void (i8*, %struct.timeval*)* @idle, i8* %90, i64 5000, i32 1), !dbg !871
  %cmp190 = icmp eq %struct.TimerStruct* %call189, null, !dbg !873
  br i1 %cmp190, label %if.then192, label %if.end193, !dbg !874

if.then192:                                       ; preds = %if.end188
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.30, i64 0, i64 0)), !dbg !875
  call void @exit(i32 1) #11, !dbg !877
  unreachable, !dbg !877

if.end193:                                        ; preds = %if.end188
  %91 = load i32, i32* @numthrottles, align 4, !dbg !878
  %cmp194 = icmp sgt i32 %91, 0, !dbg !880
  br i1 %cmp194, label %if.then196, label %if.end202, !dbg !881

if.then196:                                       ; preds = %if.end193
  %92 = load i8*, i8** getelementptr inbounds (%union.ClientData, %union.ClientData* @JunkClientData, i32 0, i32 0), align 8, !dbg !882
  %call197 = call %struct.TimerStruct* @tmr_create(%struct.timeval* null, void (i8*, %struct.timeval*)* @update_throttles, i8* %92, i64 2000, i32 1), !dbg !882
  %cmp198 = icmp eq %struct.TimerStruct* %call197, null, !dbg !885
  br i1 %cmp198, label %if.then200, label %if.end201, !dbg !886

if.then200:                                       ; preds = %if.then196
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.31, i64 0, i64 0)), !dbg !887
  call void @exit(i32 1) #11, !dbg !889
  unreachable, !dbg !889

if.end201:                                        ; preds = %if.then196
  br label %if.end202, !dbg !890

if.end202:                                        ; preds = %if.end201, %if.end193
  %93 = load i8*, i8** getelementptr inbounds (%union.ClientData, %union.ClientData* @JunkClientData, i32 0, i32 0), align 8, !dbg !891
  %call203 = call %struct.TimerStruct* @tmr_create(%struct.timeval* null, void (i8*, %struct.timeval*)* @show_stats, i8* %93, i64 3600000, i32 1), !dbg !891
  %cmp204 = icmp eq %struct.TimerStruct* %call203, null, !dbg !893
  br i1 %cmp204, label %if.then206, label %if.end207, !dbg !894

if.then206:                                       ; preds = %if.end202
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.32, i64 0, i64 0)), !dbg !895
  call void @exit(i32 1) #11, !dbg !897
  unreachable, !dbg !897

if.end207:                                        ; preds = %if.end202
  %call208 = call i64 @time(i64* null), !dbg !898
  store i64 %call208, i64* @stats_time, align 8, !dbg !899
  store i64 %call208, i64* @start_time, align 8, !dbg !900
  store i64 0, i64* @stats_connections, align 8, !dbg !901
  store i64 0, i64* @stats_bytes, align 8, !dbg !902
  store i32 0, i32* @stats_simultaneous, align 4, !dbg !903
  %call209 = call i32 @getuid(), !dbg !904
  %cmp210 = icmp eq i32 %call209, 0, !dbg !906
  br i1 %cmp210, label %if.then212, label %if.end237, !dbg !907

if.then212:                                       ; preds = %if.end207
  %call213 = call i32 @setgroups(i32 0, i32* null), !dbg !908
  %cmp214 = icmp slt i32 %call213, 0, !dbg !911
  br i1 %cmp214, label %if.then216, label %if.end217, !dbg !912

if.then216:                                       ; preds = %if.then212
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.33, i64 0, i64 0)), !dbg !913
  call void @exit(i32 1) #11, !dbg !915
  unreachable, !dbg !915

if.end217:                                        ; preds = %if.then212
  %94 = load i32, i32* %gid, align 4, !dbg !916
  %call218 = call i32 @setgid(i32 %94), !dbg !918
  %cmp219 = icmp slt i32 %call218, 0, !dbg !919
  br i1 %cmp219, label %if.then221, label %if.end222, !dbg !920

if.then221:                                       ; preds = %if.end217
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.34, i64 0, i64 0)), !dbg !921
  call void @exit(i32 1) #11, !dbg !923
  unreachable, !dbg !923

if.end222:                                        ; preds = %if.end217
  %95 = load i8*, i8** @user, align 8, !dbg !924
  %96 = load i32, i32* %gid, align 4, !dbg !926
  %call223 = call i32 @initgroups(i8* %95, i32 %96), !dbg !927
  %cmp224 = icmp slt i32 %call223, 0, !dbg !928
  br i1 %cmp224, label %if.then226, label %if.end227, !dbg !929

if.then226:                                       ; preds = %if.end222
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 4, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.35, i64 0, i64 0)), !dbg !930
  br label %if.end227, !dbg !930

if.end227:                                        ; preds = %if.then226, %if.end222
  %97 = load i8*, i8** @user, align 8, !dbg !931
  %call228 = call i32 @setlogin(i8* %97), !dbg !932
  %98 = load i32, i32* %uid, align 4, !dbg !933
  %call229 = call i32 @setuid(i32 %98), !dbg !935
  %cmp230 = icmp slt i32 %call229, 0, !dbg !936
  br i1 %cmp230, label %if.then232, label %if.end233, !dbg !937

if.then232:                                       ; preds = %if.end227
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i64 0, i64 0)), !dbg !938
  call void @exit(i32 1) #11, !dbg !940
  unreachable, !dbg !940

if.end233:                                        ; preds = %if.end227
  %99 = load i32, i32* @do_chroot, align 4, !dbg !941
  %tobool234 = icmp ne i32 %99, 0, !dbg !941
  br i1 %tobool234, label %if.end236, label %if.then235, !dbg !943

if.then235:                                       ; preds = %if.end233
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 4, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @.str.37, i64 0, i64 0)), !dbg !944
  br label %if.end236, !dbg !944

if.end236:                                        ; preds = %if.then235, %if.end233
  br label %if.end237, !dbg !945

if.end237:                                        ; preds = %if.end236, %if.end207
  %100 = load i32, i32* @max_connects, align 4, !dbg !946
  %conv238 = sext i32 %100 to i64, !dbg !946
  %mul = mul i64 144, %conv238, !dbg !946
  %call239 = call i8* @malloc(i64 %mul) #14, !dbg !946
  %101 = bitcast i8* %call239 to %struct.connecttab*, !dbg !946
  store %struct.connecttab* %101, %struct.connecttab** @connects, align 8, !dbg !947
  %102 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !948
  %cmp240 = icmp eq %struct.connecttab* %102, null, !dbg !950
  br i1 %cmp240, label %if.then242, label %if.end243, !dbg !951

if.then242:                                       ; preds = %if.end237
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.38, i64 0, i64 0)), !dbg !952
  call void @exit(i32 1) #11, !dbg !954
  unreachable, !dbg !954

if.end243:                                        ; preds = %if.end237
  store i32 0, i32* %cnum, align 4, !dbg !955
  br label %for.cond, !dbg !957

for.cond:                                         ; preds = %for.inc, %if.end243
  %103 = load i32, i32* %cnum, align 4, !dbg !958
  %104 = load i32, i32* @max_connects, align 4, !dbg !960
  %cmp244 = icmp slt i32 %103, %104, !dbg !961
  br i1 %cmp244, label %for.body, label %for.end, !dbg !962

for.body:                                         ; preds = %for.cond
  %105 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !963
  %106 = load i32, i32* %cnum, align 4, !dbg !965
  %idxprom = sext i32 %106 to i64, !dbg !963
  %arrayidx246 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %105, i64 %idxprom, !dbg !963
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx246, i32 0, i32 0, !dbg !966
  store i32 0, i32* %conn_state, align 8, !dbg !967
  %107 = load i32, i32* %cnum, align 4, !dbg !968
  %add247 = add nsw i32 %107, 1, !dbg !969
  %108 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !970
  %109 = load i32, i32* %cnum, align 4, !dbg !971
  %idxprom248 = sext i32 %109 to i64, !dbg !970
  %arrayidx249 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %108, i64 %idxprom248, !dbg !970
  %next_free_connect = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx249, i32 0, i32 1, !dbg !972
  store i32 %add247, i32* %next_free_connect, align 4, !dbg !973
  %110 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !974
  %111 = load i32, i32* %cnum, align 4, !dbg !975
  %idxprom250 = sext i32 %111 to i64, !dbg !974
  %arrayidx251 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %110, i64 %idxprom250, !dbg !974
  %hc252 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx251, i32 0, i32 2, !dbg !976
  store %struct.httpd_conn* null, %struct.httpd_conn** %hc252, align 8, !dbg !977
  br label %for.inc, !dbg !978

for.inc:                                          ; preds = %for.body
  %112 = load i32, i32* %cnum, align 4, !dbg !979
  %inc = add nsw i32 %112, 1, !dbg !979
  store i32 %inc, i32* %cnum, align 4, !dbg !979
  br label %for.cond, !dbg !980, !llvm.loop !981

for.end:                                          ; preds = %for.cond
  %113 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !983
  %114 = load i32, i32* @max_connects, align 4, !dbg !984
  %sub253 = sub nsw i32 %114, 1, !dbg !985
  %idxprom254 = sext i32 %sub253 to i64, !dbg !983
  %arrayidx255 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %113, i64 %idxprom254, !dbg !983
  %next_free_connect256 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx255, i32 0, i32 1, !dbg !986
  store i32 -1, i32* %next_free_connect256, align 4, !dbg !987
  store i32 0, i32* @first_free_connect, align 4, !dbg !988
  store i32 0, i32* @num_connects, align 4, !dbg !989
  store i32 0, i32* @httpd_conn_count, align 4, !dbg !990
  %115 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !991
  %cmp257 = icmp ne %struct.httpd_server* %115, null, !dbg !993
  br i1 %cmp257, label %if.then259, label %if.end270, !dbg !994

if.then259:                                       ; preds = %for.end
  %116 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !995
  %listen4_fd = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %116, i32 0, i32 10, !dbg !998
  %117 = load i32, i32* %listen4_fd, align 8, !dbg !998
  %cmp260 = icmp ne i32 %117, -1, !dbg !999
  br i1 %cmp260, label %if.then262, label %if.end264, !dbg !1000

if.then262:                                       ; preds = %if.then259
  %118 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1001
  %listen4_fd263 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %118, i32 0, i32 10, !dbg !1002
  %119 = load i32, i32* %listen4_fd263, align 8, !dbg !1002
  call void @fdwatch_add_fd(i32 %119, i8* null, i32 0), !dbg !1003
  br label %if.end264, !dbg !1003

if.end264:                                        ; preds = %if.then262, %if.then259
  %120 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1004
  %listen6_fd = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %120, i32 0, i32 11, !dbg !1006
  %121 = load i32, i32* %listen6_fd, align 4, !dbg !1006
  %cmp265 = icmp ne i32 %121, -1, !dbg !1007
  br i1 %cmp265, label %if.then267, label %if.end269, !dbg !1008

if.then267:                                       ; preds = %if.end264
  %122 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1009
  %listen6_fd268 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %122, i32 0, i32 11, !dbg !1010
  %123 = load i32, i32* %listen6_fd268, align 4, !dbg !1010
  call void @fdwatch_add_fd(i32 %123, i8* null, i32 0), !dbg !1011
  br label %if.end269, !dbg !1011

if.end269:                                        ; preds = %if.then267, %if.end264
  br label %if.end270, !dbg !1012

if.end270:                                        ; preds = %if.end269, %for.end
  %call271 = call i32 @gettimeofday(%struct.timeval* %tv, i8* null), !dbg !1013
  br label %while.cond, !dbg !1014

while.cond:                                       ; preds = %if.end370, %if.then329, %if.then312, %if.then296, %if.then290, %if.end270
  %124 = load i32, i32* @terminate, align 4, !dbg !1015
  %tobool272 = icmp ne i32 %124, 0, !dbg !1015
  br i1 %tobool272, label %lor.rhs, label %lor.end, !dbg !1016

lor.rhs:                                          ; preds = %while.cond
  %125 = load i32, i32* @num_connects, align 4, !dbg !1017
  %cmp273 = icmp sgt i32 %125, 0, !dbg !1018
  br label %lor.end, !dbg !1016

lor.end:                                          ; preds = %lor.rhs, %while.cond
  %126 = phi i1 [ true, %while.cond ], [ %cmp273, %lor.rhs ]
  br i1 %126, label %while.body, label %while.end371, !dbg !1014

while.body:                                       ; preds = %lor.end
  %127 = load volatile i32, i32* @got_hup, align 4, !dbg !1019
  %tobool275 = icmp ne i32 %127, 0, !dbg !1019
  br i1 %tobool275, label %if.then276, label %if.end277, !dbg !1022

if.then276:                                       ; preds = %while.body
  call void @re_open_logfile(), !dbg !1023
  store volatile i32 0, i32* @got_hup, align 4, !dbg !1025
  br label %if.end277, !dbg !1026

if.end277:                                        ; preds = %if.then276, %while.body
  %call278 = call i64 @tmr_mstimeout(%struct.timeval* %tv), !dbg !1027
  %call279 = call i32 @fdwatch(i64 %call278), !dbg !1028
  store i32 %call279, i32* %num_ready, align 4, !dbg !1029
  %128 = load i32, i32* %num_ready, align 4, !dbg !1030
  %cmp280 = icmp slt i32 %128, 0, !dbg !1032
  br i1 %cmp280, label %if.then282, label %if.end292, !dbg !1033

if.then282:                                       ; preds = %if.end277
  %call283 = call i32* @__error(), !dbg !1034
  %129 = load i32, i32* %call283, align 4, !dbg !1034
  %cmp284 = icmp eq i32 %129, 4, !dbg !1037
  br i1 %cmp284, label %if.then290, label %lor.lhs.false286, !dbg !1038

lor.lhs.false286:                                 ; preds = %if.then282
  %call287 = call i32* @__error(), !dbg !1039
  %130 = load i32, i32* %call287, align 4, !dbg !1039
  %cmp288 = icmp eq i32 %130, 35, !dbg !1040
  br i1 %cmp288, label %if.then290, label %if.end291, !dbg !1041

if.then290:                                       ; preds = %lor.lhs.false286, %if.then282
  br label %while.cond, !dbg !1042, !llvm.loop !1043

if.end291:                                        ; preds = %lor.lhs.false286
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.39, i64 0, i64 0)), !dbg !1045
  call void @exit(i32 1) #11, !dbg !1046
  unreachable, !dbg !1046

if.end292:                                        ; preds = %if.end277
  %call293 = call i32 @gettimeofday(%struct.timeval* %tv, i8* null), !dbg !1047
  %131 = load i32, i32* %num_ready, align 4, !dbg !1048
  %cmp294 = icmp eq i32 %131, 0, !dbg !1050
  br i1 %cmp294, label %if.then296, label %if.end297, !dbg !1051

if.then296:                                       ; preds = %if.end292
  call void @tmr_run(%struct.timeval* %tv), !dbg !1052
  br label %while.cond, !dbg !1054, !llvm.loop !1043

if.end297:                                        ; preds = %if.end292
  %132 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1055
  %cmp298 = icmp ne %struct.httpd_server* %132, null, !dbg !1057
  br i1 %cmp298, label %land.lhs.true300, label %if.end314, !dbg !1058

land.lhs.true300:                                 ; preds = %if.end297
  %133 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1059
  %listen6_fd301 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %133, i32 0, i32 11, !dbg !1060
  %134 = load i32, i32* %listen6_fd301, align 4, !dbg !1060
  %cmp302 = icmp ne i32 %134, -1, !dbg !1061
  br i1 %cmp302, label %land.lhs.true304, label %if.end314, !dbg !1062

land.lhs.true304:                                 ; preds = %land.lhs.true300
  %135 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1063
  %listen6_fd305 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %135, i32 0, i32 11, !dbg !1064
  %136 = load i32, i32* %listen6_fd305, align 4, !dbg !1064
  %call306 = call i32 @fdwatch_check_fd(i32 %136), !dbg !1065
  %tobool307 = icmp ne i32 %call306, 0, !dbg !1065
  br i1 %tobool307, label %if.then308, label %if.end314, !dbg !1066

if.then308:                                       ; preds = %land.lhs.true304
  %137 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1067
  %listen6_fd309 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %137, i32 0, i32 11, !dbg !1070
  %138 = load i32, i32* %listen6_fd309, align 4, !dbg !1070
  %call310 = call i32 @handle_newconnect(%struct.timeval* %tv, i32 %138), !dbg !1071
  %tobool311 = icmp ne i32 %call310, 0, !dbg !1071
  br i1 %tobool311, label %if.then312, label %if.end313, !dbg !1072

if.then312:                                       ; preds = %if.then308
  br label %while.cond, !dbg !1073, !llvm.loop !1043

if.end313:                                        ; preds = %if.then308
  br label %if.end314, !dbg !1074

if.end314:                                        ; preds = %if.end313, %land.lhs.true304, %land.lhs.true300, %if.end297
  %139 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1075
  %cmp315 = icmp ne %struct.httpd_server* %139, null, !dbg !1077
  br i1 %cmp315, label %land.lhs.true317, label %if.end331, !dbg !1078

land.lhs.true317:                                 ; preds = %if.end314
  %140 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1079
  %listen4_fd318 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %140, i32 0, i32 10, !dbg !1080
  %141 = load i32, i32* %listen4_fd318, align 8, !dbg !1080
  %cmp319 = icmp ne i32 %141, -1, !dbg !1081
  br i1 %cmp319, label %land.lhs.true321, label %if.end331, !dbg !1082

land.lhs.true321:                                 ; preds = %land.lhs.true317
  %142 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1083
  %listen4_fd322 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %142, i32 0, i32 10, !dbg !1084
  %143 = load i32, i32* %listen4_fd322, align 8, !dbg !1084
  %call323 = call i32 @fdwatch_check_fd(i32 %143), !dbg !1085
  %tobool324 = icmp ne i32 %call323, 0, !dbg !1085
  br i1 %tobool324, label %if.then325, label %if.end331, !dbg !1086

if.then325:                                       ; preds = %land.lhs.true321
  %144 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1087
  %listen4_fd326 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %144, i32 0, i32 10, !dbg !1090
  %145 = load i32, i32* %listen4_fd326, align 8, !dbg !1090
  %call327 = call i32 @handle_newconnect(%struct.timeval* %tv, i32 %145), !dbg !1091
  %tobool328 = icmp ne i32 %call327, 0, !dbg !1091
  br i1 %tobool328, label %if.then329, label %if.end330, !dbg !1092

if.then329:                                       ; preds = %if.then325
  br label %while.cond, !dbg !1093, !llvm.loop !1043

if.end330:                                        ; preds = %if.then325
  br label %if.end331, !dbg !1094

if.end331:                                        ; preds = %if.end330, %land.lhs.true321, %land.lhs.true317, %if.end314
  br label %while.cond332, !dbg !1095

while.cond332:                                    ; preds = %if.end349, %if.then339, %if.end331
  %call333 = call i8* @fdwatch_get_next_client_data(), !dbg !1096
  %146 = bitcast i8* %call333 to %struct.connecttab*, !dbg !1097
  store %struct.connecttab* %146, %struct.connecttab** %c, align 8, !dbg !1098
  %cmp334 = icmp ne %struct.connecttab* %146, inttoptr (i64 -1 to %struct.connecttab*), !dbg !1099
  br i1 %cmp334, label %while.body336, label %while.end, !dbg !1095

while.body336:                                    ; preds = %while.cond332
  %147 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1100
  %cmp337 = icmp eq %struct.connecttab* %147, null, !dbg !1103
  br i1 %cmp337, label %if.then339, label %if.end340, !dbg !1104

if.then339:                                       ; preds = %while.body336
  br label %while.cond332, !dbg !1105, !llvm.loop !1106

if.end340:                                        ; preds = %while.body336
  %148 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1108
  %hc341 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %148, i32 0, i32 2, !dbg !1109
  %149 = load %struct.httpd_conn*, %struct.httpd_conn** %hc341, align 8, !dbg !1109
  store %struct.httpd_conn* %149, %struct.httpd_conn** %hc, align 8, !dbg !1110
  %150 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !1111
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %150, i32 0, i32 60, !dbg !1113
  %151 = load i32, i32* %conn_fd, align 8, !dbg !1113
  %call342 = call i32 @fdwatch_check_fd(i32 %151), !dbg !1114
  %tobool343 = icmp ne i32 %call342, 0, !dbg !1114
  br i1 %tobool343, label %if.else345, label %if.then344, !dbg !1115

if.then344:                                       ; preds = %if.end340
  %152 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1116
  call void @clear_connection(%struct.connecttab* %152, %struct.timeval* %tv), !dbg !1117
  br label %if.end349, !dbg !1117

if.else345:                                       ; preds = %if.end340
  %153 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1118
  %conn_state346 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %153, i32 0, i32 0, !dbg !1119
  %154 = load i32, i32* %conn_state346, align 8, !dbg !1119
  switch i32 %154, label %sw.epilog [
    i32 1, label %sw.bb
    i32 2, label %sw.bb347
    i32 4, label %sw.bb348
  ], !dbg !1120

sw.bb:                                            ; preds = %if.else345
  %155 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1121
  call void @handle_read(%struct.connecttab* %155, %struct.timeval* %tv), !dbg !1123
  br label %sw.epilog, !dbg !1124

sw.bb347:                                         ; preds = %if.else345
  %156 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1125
  call void @handle_send(%struct.connecttab* %156, %struct.timeval* %tv), !dbg !1126
  br label %sw.epilog, !dbg !1127

sw.bb348:                                         ; preds = %if.else345
  %157 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !1128
  call void @handle_linger(%struct.connecttab* %157, %struct.timeval* %tv), !dbg !1129
  br label %sw.epilog, !dbg !1130

sw.epilog:                                        ; preds = %if.else345, %sw.bb348, %sw.bb347, %sw.bb
  br label %if.end349

if.end349:                                        ; preds = %sw.epilog, %if.then344
  br label %while.cond332, !dbg !1095, !llvm.loop !1106

while.end:                                        ; preds = %while.cond332
  call void @tmr_run(%struct.timeval* %tv), !dbg !1131
  %158 = load volatile i32, i32* @got_usr1, align 4, !dbg !1132
  %tobool350 = icmp ne i32 %158, 0, !dbg !1132
  br i1 %tobool350, label %land.lhs.true351, label %if.end370, !dbg !1134

land.lhs.true351:                                 ; preds = %while.end
  %159 = load i32, i32* @terminate, align 4, !dbg !1135
  %tobool352 = icmp ne i32 %159, 0, !dbg !1135
  br i1 %tobool352, label %if.end370, label %if.then353, !dbg !1136

if.then353:                                       ; preds = %land.lhs.true351
  store i32 1, i32* @terminate, align 4, !dbg !1137
  %160 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1139
  %cmp354 = icmp ne %struct.httpd_server* %160, null, !dbg !1141
  br i1 %cmp354, label %if.then356, label %if.end369, !dbg !1142

if.then356:                                       ; preds = %if.then353
  %161 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1143
  %listen4_fd357 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %161, i32 0, i32 10, !dbg !1146
  %162 = load i32, i32* %listen4_fd357, align 8, !dbg !1146
  %cmp358 = icmp ne i32 %162, -1, !dbg !1147
  br i1 %cmp358, label %if.then360, label %if.end362, !dbg !1148

if.then360:                                       ; preds = %if.then356
  %163 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1149
  %listen4_fd361 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %163, i32 0, i32 10, !dbg !1150
  %164 = load i32, i32* %listen4_fd361, align 8, !dbg !1150
  call void @fdwatch_del_fd(i32 %164), !dbg !1151
  br label %if.end362, !dbg !1151

if.end362:                                        ; preds = %if.then360, %if.then356
  %165 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1152
  %listen6_fd363 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %165, i32 0, i32 11, !dbg !1154
  %166 = load i32, i32* %listen6_fd363, align 4, !dbg !1154
  %cmp364 = icmp ne i32 %166, -1, !dbg !1155
  br i1 %cmp364, label %if.then366, label %if.end368, !dbg !1156

if.then366:                                       ; preds = %if.end362
  %167 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1157
  %listen6_fd367 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %167, i32 0, i32 11, !dbg !1158
  %168 = load i32, i32* %listen6_fd367, align 4, !dbg !1158
  call void @fdwatch_del_fd(i32 %168), !dbg !1159
  br label %if.end368, !dbg !1159

if.end368:                                        ; preds = %if.then366, %if.end362
  %169 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1160
  call void @httpd_unlisten(%struct.httpd_server* %169), !dbg !1161
  br label %if.end369, !dbg !1162

if.end369:                                        ; preds = %if.end368, %if.then353
  br label %if.end370, !dbg !1163

if.end370:                                        ; preds = %if.end369, %land.lhs.true351, %while.end
  br label %while.cond, !dbg !1014, !llvm.loop !1043

while.end371:                                     ; preds = %lor.end
  call void @shut_down(), !dbg !1164
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.40, i64 0, i64 0)), !dbg !1165
  call void @closelog(), !dbg !1166
  call void @exit(i32 0) #11, !dbg !1167
  unreachable, !dbg !1167
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #2

declare i8* @strrchr(i8*, i32) #3

declare void @openlog(i8*, i32, i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @parse_args(i32 %argc, i8** %argv) #0 !dbg !1168 {
entry:
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %argn = alloca i32, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !1171, metadata !DIExpression()), !dbg !1172
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !1173, metadata !DIExpression()), !dbg !1174
  call void @llvm.dbg.declare(metadata i32* %argn, metadata !1175, metadata !DIExpression()), !dbg !1176
  store i32 0, i32* @debug, align 4, !dbg !1177
  store i16 80, i16* @port, align 2, !dbg !1178
  store i8* null, i8** @dir, align 8, !dbg !1179
  store i8* null, i8** @data_dir, align 8, !dbg !1180
  store i32 0, i32* @do_chroot, align 4, !dbg !1181
  store i32 0, i32* @no_log, align 4, !dbg !1182
  %0 = load i32, i32* @do_chroot, align 4, !dbg !1183
  store i32 %0, i32* @no_symlink_check, align 4, !dbg !1184
  store i32 0, i32* @do_vhost, align 4, !dbg !1185
  store i32 0, i32* @do_global_passwd, align 4, !dbg !1186
  store i8* null, i8** @cgi_pattern, align 8, !dbg !1187
  store i32 0, i32* @cgi_limit, align 4, !dbg !1188
  store i8* null, i8** @url_pattern, align 8, !dbg !1189
  store i32 0, i32* @no_empty_referrers, align 4, !dbg !1190
  store i8* null, i8** @local_pattern, align 8, !dbg !1191
  store i8* null, i8** @throttlefile, align 8, !dbg !1192
  store i8* null, i8** @hostname, align 8, !dbg !1193
  store i8* null, i8** @logfile, align 8, !dbg !1194
  store i8* null, i8** @pidfile, align 8, !dbg !1195
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.48, i64 0, i64 0), i8** @user, align 8, !dbg !1196
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.49, i64 0, i64 0), i8** @charset, align 8, !dbg !1197
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8** @p3p, align 8, !dbg !1198
  store i32 -1, i32* @max_age, align 4, !dbg !1199
  store i32 1, i32* %argn, align 4, !dbg !1200
  br label %while.cond, !dbg !1201

while.cond:                                       ; preds = %if.end275, %entry
  %1 = load i32, i32* %argn, align 4, !dbg !1202
  %2 = load i32, i32* %argc.addr, align 4, !dbg !1203
  %cmp = icmp slt i32 %1, %2, !dbg !1204
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1205

land.rhs:                                         ; preds = %while.cond
  %3 = load i8**, i8*** %argv.addr, align 8, !dbg !1206
  %4 = load i32, i32* %argn, align 4, !dbg !1207
  %idxprom = sext i32 %4 to i64, !dbg !1206
  %arrayidx = getelementptr inbounds i8*, i8** %3, i64 %idxprom, !dbg !1206
  %5 = load i8*, i8** %arrayidx, align 8, !dbg !1206
  %arrayidx1 = getelementptr inbounds i8, i8* %5, i64 0, !dbg !1206
  %6 = load i8, i8* %arrayidx1, align 1, !dbg !1206
  %conv = sext i8 %6 to i32, !dbg !1206
  %cmp2 = icmp eq i32 %conv, 45, !dbg !1208
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %7 = phi i1 [ false, %while.cond ], [ %cmp2, %land.rhs ], !dbg !1209
  br i1 %7, label %while.body, label %while.end, !dbg !1201

while.body:                                       ; preds = %land.end
  %8 = load i8**, i8*** %argv.addr, align 8, !dbg !1210
  %9 = load i32, i32* %argn, align 4, !dbg !1213
  %idxprom4 = sext i32 %9 to i64, !dbg !1210
  %arrayidx5 = getelementptr inbounds i8*, i8** %8, i64 %idxprom4, !dbg !1210
  %10 = load i8*, i8** %arrayidx5, align 8, !dbg !1210
  %call = call i32 @strcmp(i8* %10, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.51, i64 0, i64 0)), !dbg !1214
  %cmp6 = icmp eq i32 %call, 0, !dbg !1215
  br i1 %cmp6, label %if.then, label %if.else, !dbg !1216

if.then:                                          ; preds = %while.body
  %call8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.52, i64 0, i64 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.53, i64 0, i64 0)), !dbg !1217
  call void @exit(i32 0) #11, !dbg !1219
  unreachable, !dbg !1219

if.else:                                          ; preds = %while.body
  %11 = load i8**, i8*** %argv.addr, align 8, !dbg !1220
  %12 = load i32, i32* %argn, align 4, !dbg !1222
  %idxprom9 = sext i32 %12 to i64, !dbg !1220
  %arrayidx10 = getelementptr inbounds i8*, i8** %11, i64 %idxprom9, !dbg !1220
  %13 = load i8*, i8** %arrayidx10, align 8, !dbg !1220
  %call11 = call i32 @strcmp(i8* %13, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.54, i64 0, i64 0)), !dbg !1223
  %cmp12 = icmp eq i32 %call11, 0, !dbg !1224
  br i1 %cmp12, label %land.lhs.true, label %if.else19, !dbg !1225

land.lhs.true:                                    ; preds = %if.else
  %14 = load i32, i32* %argn, align 4, !dbg !1226
  %add = add nsw i32 %14, 1, !dbg !1227
  %15 = load i32, i32* %argc.addr, align 4, !dbg !1228
  %cmp14 = icmp slt i32 %add, %15, !dbg !1229
  br i1 %cmp14, label %if.then16, label %if.else19, !dbg !1230

if.then16:                                        ; preds = %land.lhs.true
  %16 = load i32, i32* %argn, align 4, !dbg !1231
  %inc = add nsw i32 %16, 1, !dbg !1231
  store i32 %inc, i32* %argn, align 4, !dbg !1231
  %17 = load i8**, i8*** %argv.addr, align 8, !dbg !1233
  %18 = load i32, i32* %argn, align 4, !dbg !1234
  %idxprom17 = sext i32 %18 to i64, !dbg !1233
  %arrayidx18 = getelementptr inbounds i8*, i8** %17, i64 %idxprom17, !dbg !1233
  %19 = load i8*, i8** %arrayidx18, align 8, !dbg !1233
  call void @read_config(i8* %19), !dbg !1235
  br label %if.end274, !dbg !1236

if.else19:                                        ; preds = %land.lhs.true, %if.else
  %20 = load i8**, i8*** %argv.addr, align 8, !dbg !1237
  %21 = load i32, i32* %argn, align 4, !dbg !1239
  %idxprom20 = sext i32 %21 to i64, !dbg !1237
  %arrayidx21 = getelementptr inbounds i8*, i8** %20, i64 %idxprom20, !dbg !1237
  %22 = load i8*, i8** %arrayidx21, align 8, !dbg !1237
  %call22 = call i32 @strcmp(i8* %22, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.55, i64 0, i64 0)), !dbg !1240
  %cmp23 = icmp eq i32 %call22, 0, !dbg !1241
  br i1 %cmp23, label %land.lhs.true25, label %if.else35, !dbg !1242

land.lhs.true25:                                  ; preds = %if.else19
  %23 = load i32, i32* %argn, align 4, !dbg !1243
  %add26 = add nsw i32 %23, 1, !dbg !1244
  %24 = load i32, i32* %argc.addr, align 4, !dbg !1245
  %cmp27 = icmp slt i32 %add26, %24, !dbg !1246
  br i1 %cmp27, label %if.then29, label %if.else35, !dbg !1247

if.then29:                                        ; preds = %land.lhs.true25
  %25 = load i32, i32* %argn, align 4, !dbg !1248
  %inc30 = add nsw i32 %25, 1, !dbg !1248
  store i32 %inc30, i32* %argn, align 4, !dbg !1248
  %26 = load i8**, i8*** %argv.addr, align 8, !dbg !1250
  %27 = load i32, i32* %argn, align 4, !dbg !1251
  %idxprom31 = sext i32 %27 to i64, !dbg !1250
  %arrayidx32 = getelementptr inbounds i8*, i8** %26, i64 %idxprom31, !dbg !1250
  %28 = load i8*, i8** %arrayidx32, align 8, !dbg !1250
  %call33 = call i32 @atoi(i8* %28), !dbg !1252
  %conv34 = trunc i32 %call33 to i16, !dbg !1253
  store i16 %conv34, i16* @port, align 2, !dbg !1254
  br label %if.end273, !dbg !1255

if.else35:                                        ; preds = %land.lhs.true25, %if.else19
  %29 = load i8**, i8*** %argv.addr, align 8, !dbg !1256
  %30 = load i32, i32* %argn, align 4, !dbg !1258
  %idxprom36 = sext i32 %30 to i64, !dbg !1256
  %arrayidx37 = getelementptr inbounds i8*, i8** %29, i64 %idxprom36, !dbg !1256
  %31 = load i8*, i8** %arrayidx37, align 8, !dbg !1256
  %call38 = call i32 @strcmp(i8* %31, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.56, i64 0, i64 0)), !dbg !1259
  %cmp39 = icmp eq i32 %call38, 0, !dbg !1260
  br i1 %cmp39, label %land.lhs.true41, label %if.else49, !dbg !1261

land.lhs.true41:                                  ; preds = %if.else35
  %32 = load i32, i32* %argn, align 4, !dbg !1262
  %add42 = add nsw i32 %32, 1, !dbg !1263
  %33 = load i32, i32* %argc.addr, align 4, !dbg !1264
  %cmp43 = icmp slt i32 %add42, %33, !dbg !1265
  br i1 %cmp43, label %if.then45, label %if.else49, !dbg !1266

if.then45:                                        ; preds = %land.lhs.true41
  %34 = load i32, i32* %argn, align 4, !dbg !1267
  %inc46 = add nsw i32 %34, 1, !dbg !1267
  store i32 %inc46, i32* %argn, align 4, !dbg !1267
  %35 = load i8**, i8*** %argv.addr, align 8, !dbg !1269
  %36 = load i32, i32* %argn, align 4, !dbg !1270
  %idxprom47 = sext i32 %36 to i64, !dbg !1269
  %arrayidx48 = getelementptr inbounds i8*, i8** %35, i64 %idxprom47, !dbg !1269
  %37 = load i8*, i8** %arrayidx48, align 8, !dbg !1269
  store i8* %37, i8** @dir, align 8, !dbg !1271
  br label %if.end272, !dbg !1272

if.else49:                                        ; preds = %land.lhs.true41, %if.else35
  %38 = load i8**, i8*** %argv.addr, align 8, !dbg !1273
  %39 = load i32, i32* %argn, align 4, !dbg !1275
  %idxprom50 = sext i32 %39 to i64, !dbg !1273
  %arrayidx51 = getelementptr inbounds i8*, i8** %38, i64 %idxprom50, !dbg !1273
  %40 = load i8*, i8** %arrayidx51, align 8, !dbg !1273
  %call52 = call i32 @strcmp(i8* %40, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.57, i64 0, i64 0)), !dbg !1276
  %cmp53 = icmp eq i32 %call52, 0, !dbg !1277
  br i1 %cmp53, label %if.then55, label %if.else56, !dbg !1278

if.then55:                                        ; preds = %if.else49
  store i32 1, i32* @do_chroot, align 4, !dbg !1279
  store i32 1, i32* @no_symlink_check, align 4, !dbg !1281
  br label %if.end271, !dbg !1282

if.else56:                                        ; preds = %if.else49
  %41 = load i8**, i8*** %argv.addr, align 8, !dbg !1283
  %42 = load i32, i32* %argn, align 4, !dbg !1285
  %idxprom57 = sext i32 %42 to i64, !dbg !1283
  %arrayidx58 = getelementptr inbounds i8*, i8** %41, i64 %idxprom57, !dbg !1283
  %43 = load i8*, i8** %arrayidx58, align 8, !dbg !1283
  %call59 = call i32 @strcmp(i8* %43, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.58, i64 0, i64 0)), !dbg !1286
  %cmp60 = icmp eq i32 %call59, 0, !dbg !1287
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !1288

if.then62:                                        ; preds = %if.else56
  store i32 0, i32* @do_chroot, align 4, !dbg !1289
  store i32 0, i32* @no_symlink_check, align 4, !dbg !1291
  br label %if.end270, !dbg !1292

if.else63:                                        ; preds = %if.else56
  %44 = load i8**, i8*** %argv.addr, align 8, !dbg !1293
  %45 = load i32, i32* %argn, align 4, !dbg !1295
  %idxprom64 = sext i32 %45 to i64, !dbg !1293
  %arrayidx65 = getelementptr inbounds i8*, i8** %44, i64 %idxprom64, !dbg !1293
  %46 = load i8*, i8** %arrayidx65, align 8, !dbg !1293
  %call66 = call i32 @strcmp(i8* %46, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.59, i64 0, i64 0)), !dbg !1296
  %cmp67 = icmp eq i32 %call66, 0, !dbg !1297
  br i1 %cmp67, label %land.lhs.true69, label %if.else77, !dbg !1298

land.lhs.true69:                                  ; preds = %if.else63
  %47 = load i32, i32* %argn, align 4, !dbg !1299
  %add70 = add nsw i32 %47, 1, !dbg !1300
  %48 = load i32, i32* %argc.addr, align 4, !dbg !1301
  %cmp71 = icmp slt i32 %add70, %48, !dbg !1302
  br i1 %cmp71, label %if.then73, label %if.else77, !dbg !1303

if.then73:                                        ; preds = %land.lhs.true69
  %49 = load i32, i32* %argn, align 4, !dbg !1304
  %inc74 = add nsw i32 %49, 1, !dbg !1304
  store i32 %inc74, i32* %argn, align 4, !dbg !1304
  %50 = load i8**, i8*** %argv.addr, align 8, !dbg !1306
  %51 = load i32, i32* %argn, align 4, !dbg !1307
  %idxprom75 = sext i32 %51 to i64, !dbg !1306
  %arrayidx76 = getelementptr inbounds i8*, i8** %50, i64 %idxprom75, !dbg !1306
  %52 = load i8*, i8** %arrayidx76, align 8, !dbg !1306
  store i8* %52, i8** @data_dir, align 8, !dbg !1308
  br label %if.end269, !dbg !1309

if.else77:                                        ; preds = %land.lhs.true69, %if.else63
  %53 = load i8**, i8*** %argv.addr, align 8, !dbg !1310
  %54 = load i32, i32* %argn, align 4, !dbg !1312
  %idxprom78 = sext i32 %54 to i64, !dbg !1310
  %arrayidx79 = getelementptr inbounds i8*, i8** %53, i64 %idxprom78, !dbg !1310
  %55 = load i8*, i8** %arrayidx79, align 8, !dbg !1310
  %call80 = call i32 @strcmp(i8* %55, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.60, i64 0, i64 0)), !dbg !1313
  %cmp81 = icmp eq i32 %call80, 0, !dbg !1314
  br i1 %cmp81, label %if.then83, label %if.else84, !dbg !1315

if.then83:                                        ; preds = %if.else77
  store i32 0, i32* @no_symlink_check, align 4, !dbg !1316
  br label %if.end268, !dbg !1317

if.else84:                                        ; preds = %if.else77
  %56 = load i8**, i8*** %argv.addr, align 8, !dbg !1318
  %57 = load i32, i32* %argn, align 4, !dbg !1320
  %idxprom85 = sext i32 %57 to i64, !dbg !1318
  %arrayidx86 = getelementptr inbounds i8*, i8** %56, i64 %idxprom85, !dbg !1318
  %58 = load i8*, i8** %arrayidx86, align 8, !dbg !1318
  %call87 = call i32 @strcmp(i8* %58, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.61, i64 0, i64 0)), !dbg !1321
  %cmp88 = icmp eq i32 %call87, 0, !dbg !1322
  br i1 %cmp88, label %if.then90, label %if.else91, !dbg !1323

if.then90:                                        ; preds = %if.else84
  store i32 1, i32* @no_symlink_check, align 4, !dbg !1324
  br label %if.end267, !dbg !1325

if.else91:                                        ; preds = %if.else84
  %59 = load i8**, i8*** %argv.addr, align 8, !dbg !1326
  %60 = load i32, i32* %argn, align 4, !dbg !1328
  %idxprom92 = sext i32 %60 to i64, !dbg !1326
  %arrayidx93 = getelementptr inbounds i8*, i8** %59, i64 %idxprom92, !dbg !1326
  %61 = load i8*, i8** %arrayidx93, align 8, !dbg !1326
  %call94 = call i32 @strcmp(i8* %61, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.62, i64 0, i64 0)), !dbg !1329
  %cmp95 = icmp eq i32 %call94, 0, !dbg !1330
  br i1 %cmp95, label %land.lhs.true97, label %if.else105, !dbg !1331

land.lhs.true97:                                  ; preds = %if.else91
  %62 = load i32, i32* %argn, align 4, !dbg !1332
  %add98 = add nsw i32 %62, 1, !dbg !1333
  %63 = load i32, i32* %argc.addr, align 4, !dbg !1334
  %cmp99 = icmp slt i32 %add98, %63, !dbg !1335
  br i1 %cmp99, label %if.then101, label %if.else105, !dbg !1336

if.then101:                                       ; preds = %land.lhs.true97
  %64 = load i32, i32* %argn, align 4, !dbg !1337
  %inc102 = add nsw i32 %64, 1, !dbg !1337
  store i32 %inc102, i32* %argn, align 4, !dbg !1337
  %65 = load i8**, i8*** %argv.addr, align 8, !dbg !1339
  %66 = load i32, i32* %argn, align 4, !dbg !1340
  %idxprom103 = sext i32 %66 to i64, !dbg !1339
  %arrayidx104 = getelementptr inbounds i8*, i8** %65, i64 %idxprom103, !dbg !1339
  %67 = load i8*, i8** %arrayidx104, align 8, !dbg !1339
  store i8* %67, i8** @user, align 8, !dbg !1341
  br label %if.end266, !dbg !1342

if.else105:                                       ; preds = %land.lhs.true97, %if.else91
  %68 = load i8**, i8*** %argv.addr, align 8, !dbg !1343
  %69 = load i32, i32* %argn, align 4, !dbg !1345
  %idxprom106 = sext i32 %69 to i64, !dbg !1343
  %arrayidx107 = getelementptr inbounds i8*, i8** %68, i64 %idxprom106, !dbg !1343
  %70 = load i8*, i8** %arrayidx107, align 8, !dbg !1343
  %call108 = call i32 @strcmp(i8* %70, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.63, i64 0, i64 0)), !dbg !1346
  %cmp109 = icmp eq i32 %call108, 0, !dbg !1347
  br i1 %cmp109, label %land.lhs.true111, label %if.else119, !dbg !1348

land.lhs.true111:                                 ; preds = %if.else105
  %71 = load i32, i32* %argn, align 4, !dbg !1349
  %add112 = add nsw i32 %71, 1, !dbg !1350
  %72 = load i32, i32* %argc.addr, align 4, !dbg !1351
  %cmp113 = icmp slt i32 %add112, %72, !dbg !1352
  br i1 %cmp113, label %if.then115, label %if.else119, !dbg !1353

if.then115:                                       ; preds = %land.lhs.true111
  %73 = load i32, i32* %argn, align 4, !dbg !1354
  %inc116 = add nsw i32 %73, 1, !dbg !1354
  store i32 %inc116, i32* %argn, align 4, !dbg !1354
  %74 = load i8**, i8*** %argv.addr, align 8, !dbg !1356
  %75 = load i32, i32* %argn, align 4, !dbg !1357
  %idxprom117 = sext i32 %75 to i64, !dbg !1356
  %arrayidx118 = getelementptr inbounds i8*, i8** %74, i64 %idxprom117, !dbg !1356
  %76 = load i8*, i8** %arrayidx118, align 8, !dbg !1356
  store i8* %76, i8** @cgi_pattern, align 8, !dbg !1358
  br label %if.end265, !dbg !1359

if.else119:                                       ; preds = %land.lhs.true111, %if.else105
  %77 = load i8**, i8*** %argv.addr, align 8, !dbg !1360
  %78 = load i32, i32* %argn, align 4, !dbg !1362
  %idxprom120 = sext i32 %78 to i64, !dbg !1360
  %arrayidx121 = getelementptr inbounds i8*, i8** %77, i64 %idxprom120, !dbg !1360
  %79 = load i8*, i8** %arrayidx121, align 8, !dbg !1360
  %call122 = call i32 @strcmp(i8* %79, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.64, i64 0, i64 0)), !dbg !1363
  %cmp123 = icmp eq i32 %call122, 0, !dbg !1364
  br i1 %cmp123, label %land.lhs.true125, label %if.else133, !dbg !1365

land.lhs.true125:                                 ; preds = %if.else119
  %80 = load i32, i32* %argn, align 4, !dbg !1366
  %add126 = add nsw i32 %80, 1, !dbg !1367
  %81 = load i32, i32* %argc.addr, align 4, !dbg !1368
  %cmp127 = icmp slt i32 %add126, %81, !dbg !1369
  br i1 %cmp127, label %if.then129, label %if.else133, !dbg !1370

if.then129:                                       ; preds = %land.lhs.true125
  %82 = load i32, i32* %argn, align 4, !dbg !1371
  %inc130 = add nsw i32 %82, 1, !dbg !1371
  store i32 %inc130, i32* %argn, align 4, !dbg !1371
  %83 = load i8**, i8*** %argv.addr, align 8, !dbg !1373
  %84 = load i32, i32* %argn, align 4, !dbg !1374
  %idxprom131 = sext i32 %84 to i64, !dbg !1373
  %arrayidx132 = getelementptr inbounds i8*, i8** %83, i64 %idxprom131, !dbg !1373
  %85 = load i8*, i8** %arrayidx132, align 8, !dbg !1373
  store i8* %85, i8** @throttlefile, align 8, !dbg !1375
  br label %if.end264, !dbg !1376

if.else133:                                       ; preds = %land.lhs.true125, %if.else119
  %86 = load i8**, i8*** %argv.addr, align 8, !dbg !1377
  %87 = load i32, i32* %argn, align 4, !dbg !1379
  %idxprom134 = sext i32 %87 to i64, !dbg !1377
  %arrayidx135 = getelementptr inbounds i8*, i8** %86, i64 %idxprom134, !dbg !1377
  %88 = load i8*, i8** %arrayidx135, align 8, !dbg !1377
  %call136 = call i32 @strcmp(i8* %88, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.65, i64 0, i64 0)), !dbg !1380
  %cmp137 = icmp eq i32 %call136, 0, !dbg !1381
  br i1 %cmp137, label %land.lhs.true139, label %if.else147, !dbg !1382

land.lhs.true139:                                 ; preds = %if.else133
  %89 = load i32, i32* %argn, align 4, !dbg !1383
  %add140 = add nsw i32 %89, 1, !dbg !1384
  %90 = load i32, i32* %argc.addr, align 4, !dbg !1385
  %cmp141 = icmp slt i32 %add140, %90, !dbg !1386
  br i1 %cmp141, label %if.then143, label %if.else147, !dbg !1387

if.then143:                                       ; preds = %land.lhs.true139
  %91 = load i32, i32* %argn, align 4, !dbg !1388
  %inc144 = add nsw i32 %91, 1, !dbg !1388
  store i32 %inc144, i32* %argn, align 4, !dbg !1388
  %92 = load i8**, i8*** %argv.addr, align 8, !dbg !1390
  %93 = load i32, i32* %argn, align 4, !dbg !1391
  %idxprom145 = sext i32 %93 to i64, !dbg !1390
  %arrayidx146 = getelementptr inbounds i8*, i8** %92, i64 %idxprom145, !dbg !1390
  %94 = load i8*, i8** %arrayidx146, align 8, !dbg !1390
  store i8* %94, i8** @hostname, align 8, !dbg !1392
  br label %if.end263, !dbg !1393

if.else147:                                       ; preds = %land.lhs.true139, %if.else133
  %95 = load i8**, i8*** %argv.addr, align 8, !dbg !1394
  %96 = load i32, i32* %argn, align 4, !dbg !1396
  %idxprom148 = sext i32 %96 to i64, !dbg !1394
  %arrayidx149 = getelementptr inbounds i8*, i8** %95, i64 %idxprom148, !dbg !1394
  %97 = load i8*, i8** %arrayidx149, align 8, !dbg !1394
  %call150 = call i32 @strcmp(i8* %97, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.66, i64 0, i64 0)), !dbg !1397
  %cmp151 = icmp eq i32 %call150, 0, !dbg !1398
  br i1 %cmp151, label %land.lhs.true153, label %if.else161, !dbg !1399

land.lhs.true153:                                 ; preds = %if.else147
  %98 = load i32, i32* %argn, align 4, !dbg !1400
  %add154 = add nsw i32 %98, 1, !dbg !1401
  %99 = load i32, i32* %argc.addr, align 4, !dbg !1402
  %cmp155 = icmp slt i32 %add154, %99, !dbg !1403
  br i1 %cmp155, label %if.then157, label %if.else161, !dbg !1404

if.then157:                                       ; preds = %land.lhs.true153
  %100 = load i32, i32* %argn, align 4, !dbg !1405
  %inc158 = add nsw i32 %100, 1, !dbg !1405
  store i32 %inc158, i32* %argn, align 4, !dbg !1405
  %101 = load i8**, i8*** %argv.addr, align 8, !dbg !1407
  %102 = load i32, i32* %argn, align 4, !dbg !1408
  %idxprom159 = sext i32 %102 to i64, !dbg !1407
  %arrayidx160 = getelementptr inbounds i8*, i8** %101, i64 %idxprom159, !dbg !1407
  %103 = load i8*, i8** %arrayidx160, align 8, !dbg !1407
  store i8* %103, i8** @logfile, align 8, !dbg !1409
  br label %if.end262, !dbg !1410

if.else161:                                       ; preds = %land.lhs.true153, %if.else147
  %104 = load i8**, i8*** %argv.addr, align 8, !dbg !1411
  %105 = load i32, i32* %argn, align 4, !dbg !1413
  %idxprom162 = sext i32 %105 to i64, !dbg !1411
  %arrayidx163 = getelementptr inbounds i8*, i8** %104, i64 %idxprom162, !dbg !1411
  %106 = load i8*, i8** %arrayidx163, align 8, !dbg !1411
  %call164 = call i32 @strcmp(i8* %106, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.67, i64 0, i64 0)), !dbg !1414
  %cmp165 = icmp eq i32 %call164, 0, !dbg !1415
  br i1 %cmp165, label %if.then167, label %if.else168, !dbg !1416

if.then167:                                       ; preds = %if.else161
  store i32 1, i32* @do_vhost, align 4, !dbg !1417
  br label %if.end261, !dbg !1418

if.else168:                                       ; preds = %if.else161
  %107 = load i8**, i8*** %argv.addr, align 8, !dbg !1419
  %108 = load i32, i32* %argn, align 4, !dbg !1421
  %idxprom169 = sext i32 %108 to i64, !dbg !1419
  %arrayidx170 = getelementptr inbounds i8*, i8** %107, i64 %idxprom169, !dbg !1419
  %109 = load i8*, i8** %arrayidx170, align 8, !dbg !1419
  %call171 = call i32 @strcmp(i8* %109, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.68, i64 0, i64 0)), !dbg !1422
  %cmp172 = icmp eq i32 %call171, 0, !dbg !1423
  br i1 %cmp172, label %if.then174, label %if.else175, !dbg !1424

if.then174:                                       ; preds = %if.else168
  store i32 0, i32* @do_vhost, align 4, !dbg !1425
  br label %if.end260, !dbg !1426

if.else175:                                       ; preds = %if.else168
  %110 = load i8**, i8*** %argv.addr, align 8, !dbg !1427
  %111 = load i32, i32* %argn, align 4, !dbg !1429
  %idxprom176 = sext i32 %111 to i64, !dbg !1427
  %arrayidx177 = getelementptr inbounds i8*, i8** %110, i64 %idxprom176, !dbg !1427
  %112 = load i8*, i8** %arrayidx177, align 8, !dbg !1427
  %call178 = call i32 @strcmp(i8* %112, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.69, i64 0, i64 0)), !dbg !1430
  %cmp179 = icmp eq i32 %call178, 0, !dbg !1431
  br i1 %cmp179, label %if.then181, label %if.else182, !dbg !1432

if.then181:                                       ; preds = %if.else175
  store i32 1, i32* @do_global_passwd, align 4, !dbg !1433
  br label %if.end259, !dbg !1434

if.else182:                                       ; preds = %if.else175
  %113 = load i8**, i8*** %argv.addr, align 8, !dbg !1435
  %114 = load i32, i32* %argn, align 4, !dbg !1437
  %idxprom183 = sext i32 %114 to i64, !dbg !1435
  %arrayidx184 = getelementptr inbounds i8*, i8** %113, i64 %idxprom183, !dbg !1435
  %115 = load i8*, i8** %arrayidx184, align 8, !dbg !1435
  %call185 = call i32 @strcmp(i8* %115, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.70, i64 0, i64 0)), !dbg !1438
  %cmp186 = icmp eq i32 %call185, 0, !dbg !1439
  br i1 %cmp186, label %if.then188, label %if.else189, !dbg !1440

if.then188:                                       ; preds = %if.else182
  store i32 0, i32* @do_global_passwd, align 4, !dbg !1441
  br label %if.end258, !dbg !1442

if.else189:                                       ; preds = %if.else182
  %116 = load i8**, i8*** %argv.addr, align 8, !dbg !1443
  %117 = load i32, i32* %argn, align 4, !dbg !1445
  %idxprom190 = sext i32 %117 to i64, !dbg !1443
  %arrayidx191 = getelementptr inbounds i8*, i8** %116, i64 %idxprom190, !dbg !1443
  %118 = load i8*, i8** %arrayidx191, align 8, !dbg !1443
  %call192 = call i32 @strcmp(i8* %118, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.71, i64 0, i64 0)), !dbg !1446
  %cmp193 = icmp eq i32 %call192, 0, !dbg !1447
  br i1 %cmp193, label %land.lhs.true195, label %if.else203, !dbg !1448

land.lhs.true195:                                 ; preds = %if.else189
  %119 = load i32, i32* %argn, align 4, !dbg !1449
  %add196 = add nsw i32 %119, 1, !dbg !1450
  %120 = load i32, i32* %argc.addr, align 4, !dbg !1451
  %cmp197 = icmp slt i32 %add196, %120, !dbg !1452
  br i1 %cmp197, label %if.then199, label %if.else203, !dbg !1453

if.then199:                                       ; preds = %land.lhs.true195
  %121 = load i32, i32* %argn, align 4, !dbg !1454
  %inc200 = add nsw i32 %121, 1, !dbg !1454
  store i32 %inc200, i32* %argn, align 4, !dbg !1454
  %122 = load i8**, i8*** %argv.addr, align 8, !dbg !1456
  %123 = load i32, i32* %argn, align 4, !dbg !1457
  %idxprom201 = sext i32 %123 to i64, !dbg !1456
  %arrayidx202 = getelementptr inbounds i8*, i8** %122, i64 %idxprom201, !dbg !1456
  %124 = load i8*, i8** %arrayidx202, align 8, !dbg !1456
  store i8* %124, i8** @pidfile, align 8, !dbg !1458
  br label %if.end257, !dbg !1459

if.else203:                                       ; preds = %land.lhs.true195, %if.else189
  %125 = load i8**, i8*** %argv.addr, align 8, !dbg !1460
  %126 = load i32, i32* %argn, align 4, !dbg !1462
  %idxprom204 = sext i32 %126 to i64, !dbg !1460
  %arrayidx205 = getelementptr inbounds i8*, i8** %125, i64 %idxprom204, !dbg !1460
  %127 = load i8*, i8** %arrayidx205, align 8, !dbg !1460
  %call206 = call i32 @strcmp(i8* %127, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.72, i64 0, i64 0)), !dbg !1463
  %cmp207 = icmp eq i32 %call206, 0, !dbg !1464
  br i1 %cmp207, label %land.lhs.true209, label %if.else217, !dbg !1465

land.lhs.true209:                                 ; preds = %if.else203
  %128 = load i32, i32* %argn, align 4, !dbg !1466
  %add210 = add nsw i32 %128, 1, !dbg !1467
  %129 = load i32, i32* %argc.addr, align 4, !dbg !1468
  %cmp211 = icmp slt i32 %add210, %129, !dbg !1469
  br i1 %cmp211, label %if.then213, label %if.else217, !dbg !1470

if.then213:                                       ; preds = %land.lhs.true209
  %130 = load i32, i32* %argn, align 4, !dbg !1471
  %inc214 = add nsw i32 %130, 1, !dbg !1471
  store i32 %inc214, i32* %argn, align 4, !dbg !1471
  %131 = load i8**, i8*** %argv.addr, align 8, !dbg !1473
  %132 = load i32, i32* %argn, align 4, !dbg !1474
  %idxprom215 = sext i32 %132 to i64, !dbg !1473
  %arrayidx216 = getelementptr inbounds i8*, i8** %131, i64 %idxprom215, !dbg !1473
  %133 = load i8*, i8** %arrayidx216, align 8, !dbg !1473
  store i8* %133, i8** @charset, align 8, !dbg !1475
  br label %if.end256, !dbg !1476

if.else217:                                       ; preds = %land.lhs.true209, %if.else203
  %134 = load i8**, i8*** %argv.addr, align 8, !dbg !1477
  %135 = load i32, i32* %argn, align 4, !dbg !1479
  %idxprom218 = sext i32 %135 to i64, !dbg !1477
  %arrayidx219 = getelementptr inbounds i8*, i8** %134, i64 %idxprom218, !dbg !1477
  %136 = load i8*, i8** %arrayidx219, align 8, !dbg !1477
  %call220 = call i32 @strcmp(i8* %136, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.73, i64 0, i64 0)), !dbg !1480
  %cmp221 = icmp eq i32 %call220, 0, !dbg !1481
  br i1 %cmp221, label %land.lhs.true223, label %if.else231, !dbg !1482

land.lhs.true223:                                 ; preds = %if.else217
  %137 = load i32, i32* %argn, align 4, !dbg !1483
  %add224 = add nsw i32 %137, 1, !dbg !1484
  %138 = load i32, i32* %argc.addr, align 4, !dbg !1485
  %cmp225 = icmp slt i32 %add224, %138, !dbg !1486
  br i1 %cmp225, label %if.then227, label %if.else231, !dbg !1487

if.then227:                                       ; preds = %land.lhs.true223
  %139 = load i32, i32* %argn, align 4, !dbg !1488
  %inc228 = add nsw i32 %139, 1, !dbg !1488
  store i32 %inc228, i32* %argn, align 4, !dbg !1488
  %140 = load i8**, i8*** %argv.addr, align 8, !dbg !1490
  %141 = load i32, i32* %argn, align 4, !dbg !1491
  %idxprom229 = sext i32 %141 to i64, !dbg !1490
  %arrayidx230 = getelementptr inbounds i8*, i8** %140, i64 %idxprom229, !dbg !1490
  %142 = load i8*, i8** %arrayidx230, align 8, !dbg !1490
  store i8* %142, i8** @p3p, align 8, !dbg !1492
  br label %if.end255, !dbg !1493

if.else231:                                       ; preds = %land.lhs.true223, %if.else217
  %143 = load i8**, i8*** %argv.addr, align 8, !dbg !1494
  %144 = load i32, i32* %argn, align 4, !dbg !1496
  %idxprom232 = sext i32 %144 to i64, !dbg !1494
  %arrayidx233 = getelementptr inbounds i8*, i8** %143, i64 %idxprom232, !dbg !1494
  %145 = load i8*, i8** %arrayidx233, align 8, !dbg !1494
  %call234 = call i32 @strcmp(i8* %145, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.74, i64 0, i64 0)), !dbg !1497
  %cmp235 = icmp eq i32 %call234, 0, !dbg !1498
  br i1 %cmp235, label %land.lhs.true237, label %if.else246, !dbg !1499

land.lhs.true237:                                 ; preds = %if.else231
  %146 = load i32, i32* %argn, align 4, !dbg !1500
  %add238 = add nsw i32 %146, 1, !dbg !1501
  %147 = load i32, i32* %argc.addr, align 4, !dbg !1502
  %cmp239 = icmp slt i32 %add238, %147, !dbg !1503
  br i1 %cmp239, label %if.then241, label %if.else246, !dbg !1504

if.then241:                                       ; preds = %land.lhs.true237
  %148 = load i32, i32* %argn, align 4, !dbg !1505
  %inc242 = add nsw i32 %148, 1, !dbg !1505
  store i32 %inc242, i32* %argn, align 4, !dbg !1505
  %149 = load i8**, i8*** %argv.addr, align 8, !dbg !1507
  %150 = load i32, i32* %argn, align 4, !dbg !1508
  %idxprom243 = sext i32 %150 to i64, !dbg !1507
  %arrayidx244 = getelementptr inbounds i8*, i8** %149, i64 %idxprom243, !dbg !1507
  %151 = load i8*, i8** %arrayidx244, align 8, !dbg !1507
  %call245 = call i32 @atoi(i8* %151), !dbg !1509
  store i32 %call245, i32* @max_age, align 4, !dbg !1510
  br label %if.end254, !dbg !1511

if.else246:                                       ; preds = %land.lhs.true237, %if.else231
  %152 = load i8**, i8*** %argv.addr, align 8, !dbg !1512
  %153 = load i32, i32* %argn, align 4, !dbg !1514
  %idxprom247 = sext i32 %153 to i64, !dbg !1512
  %arrayidx248 = getelementptr inbounds i8*, i8** %152, i64 %idxprom247, !dbg !1512
  %154 = load i8*, i8** %arrayidx248, align 8, !dbg !1512
  %call249 = call i32 @strcmp(i8* %154, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.75, i64 0, i64 0)), !dbg !1515
  %cmp250 = icmp eq i32 %call249, 0, !dbg !1516
  br i1 %cmp250, label %if.then252, label %if.else253, !dbg !1517

if.then252:                                       ; preds = %if.else246
  store i32 1, i32* @debug, align 4, !dbg !1518
  br label %if.end, !dbg !1519

if.else253:                                       ; preds = %if.else246
  call void @usage(), !dbg !1520
  br label %if.end

if.end:                                           ; preds = %if.else253, %if.then252
  br label %if.end254

if.end254:                                        ; preds = %if.end, %if.then241
  br label %if.end255

if.end255:                                        ; preds = %if.end254, %if.then227
  br label %if.end256

if.end256:                                        ; preds = %if.end255, %if.then213
  br label %if.end257

if.end257:                                        ; preds = %if.end256, %if.then199
  br label %if.end258

if.end258:                                        ; preds = %if.end257, %if.then188
  br label %if.end259

if.end259:                                        ; preds = %if.end258, %if.then181
  br label %if.end260

if.end260:                                        ; preds = %if.end259, %if.then174
  br label %if.end261

if.end261:                                        ; preds = %if.end260, %if.then167
  br label %if.end262

if.end262:                                        ; preds = %if.end261, %if.then157
  br label %if.end263

if.end263:                                        ; preds = %if.end262, %if.then143
  br label %if.end264

if.end264:                                        ; preds = %if.end263, %if.then129
  br label %if.end265

if.end265:                                        ; preds = %if.end264, %if.then115
  br label %if.end266

if.end266:                                        ; preds = %if.end265, %if.then101
  br label %if.end267

if.end267:                                        ; preds = %if.end266, %if.then90
  br label %if.end268

if.end268:                                        ; preds = %if.end267, %if.then83
  br label %if.end269

if.end269:                                        ; preds = %if.end268, %if.then73
  br label %if.end270

if.end270:                                        ; preds = %if.end269, %if.then62
  br label %if.end271

if.end271:                                        ; preds = %if.end270, %if.then55
  br label %if.end272

if.end272:                                        ; preds = %if.end271, %if.then45
  br label %if.end273

if.end273:                                        ; preds = %if.end272, %if.then29
  br label %if.end274

if.end274:                                        ; preds = %if.end273, %if.then16
  br label %if.end275

if.end275:                                        ; preds = %if.end274
  %155 = load i32, i32* %argn, align 4, !dbg !1521
  %inc276 = add nsw i32 %155, 1, !dbg !1521
  store i32 %inc276, i32* %argn, align 4, !dbg !1521
  br label %while.cond, !dbg !1201, !llvm.loop !1522

while.end:                                        ; preds = %land.end
  %156 = load i32, i32* %argn, align 4, !dbg !1524
  %157 = load i32, i32* %argc.addr, align 4, !dbg !1526
  %cmp277 = icmp ne i32 %156, %157, !dbg !1527
  br i1 %cmp277, label %if.then279, label %if.end280, !dbg !1528

if.then279:                                       ; preds = %while.end
  call void @usage(), !dbg !1529
  br label %if.end280, !dbg !1529

if.end280:                                        ; preds = %if.then279, %while.end
  ret void, !dbg !1530
}

declare void @tzset() #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @lookup_hostname(%union.httpd_sockaddr* %sa4P, i64 %sa4_len, i32* %gotv4P, %union.httpd_sockaddr* %sa6P, i64 %sa6_len, i32* %gotv6P) #0 !dbg !1531 {
entry:
  %sa4P.addr = alloca %union.httpd_sockaddr*, align 8
  %sa4_len.addr = alloca i64, align 8
  %gotv4P.addr = alloca i32*, align 8
  %sa6P.addr = alloca %union.httpd_sockaddr*, align 8
  %sa6_len.addr = alloca i64, align 8
  %gotv6P.addr = alloca i32*, align 8
  %hints = alloca %struct.addrinfo, align 8
  %portstr = alloca [10 x i8], align 1
  %gaierr = alloca i32, align 4
  %ai = alloca %struct.addrinfo*, align 8
  %ai2 = alloca %struct.addrinfo*, align 8
  %aiv6 = alloca %struct.addrinfo*, align 8
  %aiv4 = alloca %struct.addrinfo*, align 8
  store %union.httpd_sockaddr* %sa4P, %union.httpd_sockaddr** %sa4P.addr, align 8
  call void @llvm.dbg.declare(metadata %union.httpd_sockaddr** %sa4P.addr, metadata !1535, metadata !DIExpression()), !dbg !1536
  store i64 %sa4_len, i64* %sa4_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sa4_len.addr, metadata !1537, metadata !DIExpression()), !dbg !1538
  store i32* %gotv4P, i32** %gotv4P.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %gotv4P.addr, metadata !1539, metadata !DIExpression()), !dbg !1540
  store %union.httpd_sockaddr* %sa6P, %union.httpd_sockaddr** %sa6P.addr, align 8
  call void @llvm.dbg.declare(metadata %union.httpd_sockaddr** %sa6P.addr, metadata !1541, metadata !DIExpression()), !dbg !1542
  store i64 %sa6_len, i64* %sa6_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sa6_len.addr, metadata !1543, metadata !DIExpression()), !dbg !1544
  store i32* %gotv6P, i32** %gotv6P.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %gotv6P.addr, metadata !1545, metadata !DIExpression()), !dbg !1546
  call void @llvm.dbg.declare(metadata %struct.addrinfo* %hints, metadata !1547, metadata !DIExpression()), !dbg !1548
  call void @llvm.dbg.declare(metadata [10 x i8]* %portstr, metadata !1549, metadata !DIExpression()), !dbg !1551
  call void @llvm.dbg.declare(metadata i32* %gaierr, metadata !1552, metadata !DIExpression()), !dbg !1553
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %ai, metadata !1554, metadata !DIExpression()), !dbg !1555
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %ai2, metadata !1556, metadata !DIExpression()), !dbg !1557
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %aiv6, metadata !1558, metadata !DIExpression()), !dbg !1559
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %aiv4, metadata !1560, metadata !DIExpression()), !dbg !1561
  %0 = bitcast %struct.addrinfo* %hints to i8*, !dbg !1562
  call void @llvm.memset.p0i8.i64(i8* align 8 %0, i8 0, i64 48, i1 false), !dbg !1562
  %ai_family = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %hints, i32 0, i32 1, !dbg !1563
  store i32 0, i32* %ai_family, align 4, !dbg !1564
  %ai_flags = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %hints, i32 0, i32 0, !dbg !1565
  store i32 1, i32* %ai_flags, align 8, !dbg !1566
  %ai_socktype = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %hints, i32 0, i32 2, !dbg !1567
  store i32 1, i32* %ai_socktype, align 8, !dbg !1568
  %arraydecay = getelementptr inbounds [10 x i8], [10 x i8]* %portstr, i64 0, i64 0, !dbg !1569
  %1 = load i16, i16* @port, align 2, !dbg !1569
  %conv = zext i16 %1 to i32, !dbg !1569
  %call = call i32 (i8*, i64, i32, i64, i8*, ...) @__snprintf_chk(i8* %arraydecay, i64 10, i32 0, i64 10, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.109, i64 0, i64 0), i32 %conv), !dbg !1569
  %2 = load i8*, i8** @hostname, align 8, !dbg !1570
  %arraydecay1 = getelementptr inbounds [10 x i8], [10 x i8]* %portstr, i64 0, i64 0, !dbg !1572
  %call2 = call i32 @getaddrinfo(i8* %2, i8* %arraydecay1, %struct.addrinfo* %hints, %struct.addrinfo** %ai), !dbg !1573
  store i32 %call2, i32* %gaierr, align 4, !dbg !1574
  %cmp = icmp ne i32 %call2, 0, !dbg !1575
  br i1 %cmp, label %if.then, label %if.end, !dbg !1576

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** @hostname, align 8, !dbg !1577
  %4 = load i32, i32* %gaierr, align 4, !dbg !1579
  %call4 = call i8* @gai_strerror(i32 %4), !dbg !1580
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.110, i64 0, i64 0), i8* %3, i8* %call4), !dbg !1581
  %5 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !1582
  %6 = load i8*, i8** @argv0, align 8, !dbg !1583
  %7 = load i8*, i8** @hostname, align 8, !dbg !1584
  %8 = load i32, i32* %gaierr, align 4, !dbg !1585
  %call5 = call i8* @gai_strerror(i32 %8), !dbg !1586
  %call6 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %5, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.111, i64 0, i64 0), i8* %6, i8* %7, i8* %call5), !dbg !1587
  call void @exit(i32 1) #11, !dbg !1588
  unreachable, !dbg !1588

if.end:                                           ; preds = %entry
  store %struct.addrinfo* null, %struct.addrinfo** %aiv6, align 8, !dbg !1589
  store %struct.addrinfo* null, %struct.addrinfo** %aiv4, align 8, !dbg !1590
  %9 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !1591
  store %struct.addrinfo* %9, %struct.addrinfo** %ai2, align 8, !dbg !1593
  br label %for.cond, !dbg !1594

for.cond:                                         ; preds = %for.inc, %if.end
  %10 = load %struct.addrinfo*, %struct.addrinfo** %ai2, align 8, !dbg !1595
  %cmp7 = icmp ne %struct.addrinfo* %10, null, !dbg !1597
  br i1 %cmp7, label %for.body, label %for.end, !dbg !1598

for.body:                                         ; preds = %for.cond
  %11 = load %struct.addrinfo*, %struct.addrinfo** %ai2, align 8, !dbg !1599
  %ai_family9 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %11, i32 0, i32 1, !dbg !1601
  %12 = load i32, i32* %ai_family9, align 4, !dbg !1601
  switch i32 %12, label %sw.epilog [
    i32 30, label %sw.bb
    i32 2, label %sw.bb14
  ], !dbg !1602

sw.bb:                                            ; preds = %for.body
  %13 = load %struct.addrinfo*, %struct.addrinfo** %aiv6, align 8, !dbg !1603
  %cmp10 = icmp eq %struct.addrinfo* %13, null, !dbg !1606
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !1607

if.then12:                                        ; preds = %sw.bb
  %14 = load %struct.addrinfo*, %struct.addrinfo** %ai2, align 8, !dbg !1608
  store %struct.addrinfo* %14, %struct.addrinfo** %aiv6, align 8, !dbg !1609
  br label %if.end13, !dbg !1610

if.end13:                                         ; preds = %if.then12, %sw.bb
  br label %sw.epilog, !dbg !1611

sw.bb14:                                          ; preds = %for.body
  %15 = load %struct.addrinfo*, %struct.addrinfo** %aiv4, align 8, !dbg !1612
  %cmp15 = icmp eq %struct.addrinfo* %15, null, !dbg !1614
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !1615

if.then17:                                        ; preds = %sw.bb14
  %16 = load %struct.addrinfo*, %struct.addrinfo** %ai2, align 8, !dbg !1616
  store %struct.addrinfo* %16, %struct.addrinfo** %aiv4, align 8, !dbg !1617
  br label %if.end18, !dbg !1618

if.end18:                                         ; preds = %if.then17, %sw.bb14
  br label %sw.epilog, !dbg !1619

sw.epilog:                                        ; preds = %for.body, %if.end18, %if.end13
  br label %for.inc, !dbg !1620

for.inc:                                          ; preds = %sw.epilog
  %17 = load %struct.addrinfo*, %struct.addrinfo** %ai2, align 8, !dbg !1621
  %ai_next = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %17, i32 0, i32 7, !dbg !1622
  %18 = load %struct.addrinfo*, %struct.addrinfo** %ai_next, align 8, !dbg !1622
  store %struct.addrinfo* %18, %struct.addrinfo** %ai2, align 8, !dbg !1623
  br label %for.cond, !dbg !1624, !llvm.loop !1625

for.end:                                          ; preds = %for.cond
  %19 = load %struct.addrinfo*, %struct.addrinfo** %aiv6, align 8, !dbg !1627
  %cmp19 = icmp eq %struct.addrinfo* %19, null, !dbg !1629
  br i1 %cmp19, label %if.then21, label %if.else, !dbg !1630

if.then21:                                        ; preds = %for.end
  %20 = load i32*, i32** %gotv6P.addr, align 8, !dbg !1631
  store i32 0, i32* %20, align 4, !dbg !1632
  br label %if.end33, !dbg !1633

if.else:                                          ; preds = %for.end
  %21 = load i64, i64* %sa6_len.addr, align 8, !dbg !1634
  %22 = load %struct.addrinfo*, %struct.addrinfo** %aiv6, align 8, !dbg !1637
  %ai_addrlen = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %22, i32 0, i32 4, !dbg !1638
  %23 = load i32, i32* %ai_addrlen, align 8, !dbg !1638
  %conv22 = zext i32 %23 to i64, !dbg !1637
  %cmp23 = icmp ult i64 %21, %conv22, !dbg !1639
  br i1 %cmp23, label %if.then25, label %if.end28, !dbg !1640

if.then25:                                        ; preds = %if.else
  %24 = load i8*, i8** @hostname, align 8, !dbg !1641
  %25 = load i64, i64* %sa6_len.addr, align 8, !dbg !1643
  %26 = load %struct.addrinfo*, %struct.addrinfo** %aiv6, align 8, !dbg !1644
  %ai_addrlen26 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %26, i32 0, i32 4, !dbg !1645
  %27 = load i32, i32* %ai_addrlen26, align 8, !dbg !1645
  %conv27 = zext i32 %27 to i64, !dbg !1646
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.112, i64 0, i64 0), i8* %24, i64 %25, i64 %conv27), !dbg !1647
  call void @exit(i32 1) #11, !dbg !1648
  unreachable, !dbg !1648

if.end28:                                         ; preds = %if.else
  %28 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa6P.addr, align 8, !dbg !1649
  %29 = bitcast %union.httpd_sockaddr* %28 to i8*, !dbg !1649
  %30 = load i64, i64* %sa6_len.addr, align 8, !dbg !1649
  %31 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa6P.addr, align 8, !dbg !1649
  %32 = bitcast %union.httpd_sockaddr* %31 to i8*, !dbg !1649
  %33 = call i64 @llvm.objectsize.i64.p0i8(i8* %32, i1 false, i1 true, i1 false), !dbg !1649
  %call29 = call i8* @__memset_chk(i8* %29, i32 0, i64 %30, i64 %33) #13, !dbg !1649
  %34 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa6P.addr, align 8, !dbg !1650
  %35 = bitcast %union.httpd_sockaddr* %34 to i8*, !dbg !1650
  %36 = load %struct.addrinfo*, %struct.addrinfo** %aiv6, align 8, !dbg !1650
  %ai_addr = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %36, i32 0, i32 6, !dbg !1650
  %37 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr, align 8, !dbg !1650
  %38 = bitcast %struct.sockaddr* %37 to i8*, !dbg !1650
  %39 = load %struct.addrinfo*, %struct.addrinfo** %aiv6, align 8, !dbg !1650
  %ai_addrlen30 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %39, i32 0, i32 4, !dbg !1650
  %40 = load i32, i32* %ai_addrlen30, align 8, !dbg !1650
  %conv31 = zext i32 %40 to i64, !dbg !1650
  %41 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa6P.addr, align 8, !dbg !1650
  %42 = bitcast %union.httpd_sockaddr* %41 to i8*, !dbg !1650
  %43 = call i64 @llvm.objectsize.i64.p0i8(i8* %42, i1 false, i1 true, i1 false), !dbg !1650
  %call32 = call i8* @__memmove_chk(i8* %35, i8* %38, i64 %conv31, i64 %43) #13, !dbg !1650
  %44 = load i32*, i32** %gotv6P.addr, align 8, !dbg !1651
  store i32 1, i32* %44, align 4, !dbg !1652
  br label %if.end33

if.end33:                                         ; preds = %if.end28, %if.then21
  %45 = load %struct.addrinfo*, %struct.addrinfo** %aiv4, align 8, !dbg !1653
  %cmp34 = icmp eq %struct.addrinfo* %45, null, !dbg !1655
  br i1 %cmp34, label %if.then36, label %if.else37, !dbg !1656

if.then36:                                        ; preds = %if.end33
  %46 = load i32*, i32** %gotv4P.addr, align 8, !dbg !1657
  store i32 0, i32* %46, align 4, !dbg !1658
  br label %if.end51, !dbg !1659

if.else37:                                        ; preds = %if.end33
  %47 = load i64, i64* %sa4_len.addr, align 8, !dbg !1660
  %48 = load %struct.addrinfo*, %struct.addrinfo** %aiv4, align 8, !dbg !1663
  %ai_addrlen38 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %48, i32 0, i32 4, !dbg !1664
  %49 = load i32, i32* %ai_addrlen38, align 8, !dbg !1664
  %conv39 = zext i32 %49 to i64, !dbg !1663
  %cmp40 = icmp ult i64 %47, %conv39, !dbg !1665
  br i1 %cmp40, label %if.then42, label %if.end45, !dbg !1666

if.then42:                                        ; preds = %if.else37
  %50 = load i8*, i8** @hostname, align 8, !dbg !1667
  %51 = load i64, i64* %sa4_len.addr, align 8, !dbg !1669
  %52 = load %struct.addrinfo*, %struct.addrinfo** %aiv4, align 8, !dbg !1670
  %ai_addrlen43 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %52, i32 0, i32 4, !dbg !1671
  %53 = load i32, i32* %ai_addrlen43, align 8, !dbg !1671
  %conv44 = zext i32 %53 to i64, !dbg !1672
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.112, i64 0, i64 0), i8* %50, i64 %51, i64 %conv44), !dbg !1673
  call void @exit(i32 1) #11, !dbg !1674
  unreachable, !dbg !1674

if.end45:                                         ; preds = %if.else37
  %54 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa4P.addr, align 8, !dbg !1675
  %55 = bitcast %union.httpd_sockaddr* %54 to i8*, !dbg !1675
  %56 = load i64, i64* %sa4_len.addr, align 8, !dbg !1675
  %57 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa4P.addr, align 8, !dbg !1675
  %58 = bitcast %union.httpd_sockaddr* %57 to i8*, !dbg !1675
  %59 = call i64 @llvm.objectsize.i64.p0i8(i8* %58, i1 false, i1 true, i1 false), !dbg !1675
  %call46 = call i8* @__memset_chk(i8* %55, i32 0, i64 %56, i64 %59) #13, !dbg !1675
  %60 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa4P.addr, align 8, !dbg !1676
  %61 = bitcast %union.httpd_sockaddr* %60 to i8*, !dbg !1676
  %62 = load %struct.addrinfo*, %struct.addrinfo** %aiv4, align 8, !dbg !1676
  %ai_addr47 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %62, i32 0, i32 6, !dbg !1676
  %63 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr47, align 8, !dbg !1676
  %64 = bitcast %struct.sockaddr* %63 to i8*, !dbg !1676
  %65 = load %struct.addrinfo*, %struct.addrinfo** %aiv4, align 8, !dbg !1676
  %ai_addrlen48 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %65, i32 0, i32 4, !dbg !1676
  %66 = load i32, i32* %ai_addrlen48, align 8, !dbg !1676
  %conv49 = zext i32 %66 to i64, !dbg !1676
  %67 = load %union.httpd_sockaddr*, %union.httpd_sockaddr** %sa4P.addr, align 8, !dbg !1676
  %68 = bitcast %union.httpd_sockaddr* %67 to i8*, !dbg !1676
  %69 = call i64 @llvm.objectsize.i64.p0i8(i8* %68, i1 false, i1 true, i1 false), !dbg !1676
  %call50 = call i8* @__memmove_chk(i8* %61, i8* %64, i64 %conv49, i64 %69) #13, !dbg !1676
  %70 = load i32*, i32** %gotv4P.addr, align 8, !dbg !1677
  store i32 1, i32* %70, align 4, !dbg !1678
  br label %if.end51

if.end51:                                         ; preds = %if.end45, %if.then36
  %71 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !1679
  call void @freeaddrinfo(%struct.addrinfo* %71), !dbg !1680
  ret void, !dbg !1681
}

declare void @"\01_syslog$DARWIN_EXTSN"(i32, i8*, ...) #3

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #3

; Function Attrs: noreturn
declare void @exit(i32) #4

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @read_throttlefile(i8* %tf) #0 !dbg !1682 {
entry:
  %tf.addr = alloca i8*, align 8
  %fp = alloca %struct.__sFILE*, align 8
  %buf = alloca [5000 x i8], align 16
  %cp = alloca i8*, align 8
  %len = alloca i32, align 4
  %pattern = alloca [5000 x i8], align 16
  %max_limit = alloca i64, align 8
  %min_limit = alloca i64, align 8
  %tv = alloca %struct.timeval, align 8
  store i8* %tf, i8** %tf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %tf.addr, metadata !1685, metadata !DIExpression()), !dbg !1686
  call void @llvm.dbg.declare(metadata %struct.__sFILE** %fp, metadata !1687, metadata !DIExpression()), !dbg !1688
  call void @llvm.dbg.declare(metadata [5000 x i8]* %buf, metadata !1689, metadata !DIExpression()), !dbg !1693
  call void @llvm.dbg.declare(metadata i8** %cp, metadata !1694, metadata !DIExpression()), !dbg !1695
  call void @llvm.dbg.declare(metadata i32* %len, metadata !1696, metadata !DIExpression()), !dbg !1697
  call void @llvm.dbg.declare(metadata [5000 x i8]* %pattern, metadata !1698, metadata !DIExpression()), !dbg !1699
  call void @llvm.dbg.declare(metadata i64* %max_limit, metadata !1700, metadata !DIExpression()), !dbg !1701
  call void @llvm.dbg.declare(metadata i64* %min_limit, metadata !1702, metadata !DIExpression()), !dbg !1703
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !1704, metadata !DIExpression()), !dbg !1705
  %0 = load i8*, i8** %tf.addr, align 8, !dbg !1706
  %call = call %struct.__sFILE* @"\01_fopen"(i8* %0, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.76, i64 0, i64 0)), !dbg !1707
  store %struct.__sFILE* %call, %struct.__sFILE** %fp, align 8, !dbg !1708
  %1 = load %struct.__sFILE*, %struct.__sFILE** %fp, align 8, !dbg !1709
  %cmp = icmp eq %struct.__sFILE* %1, null, !dbg !1711
  br i1 %cmp, label %if.then, label %if.end, !dbg !1712

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %tf.addr, align 8, !dbg !1713
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i64 0, i64 0), i8* %2), !dbg !1715
  %3 = load i8*, i8** %tf.addr, align 8, !dbg !1716
  call void @perror(i8* %3) #12, !dbg !1717
  call void @exit(i32 1) #11, !dbg !1718
  unreachable, !dbg !1718

if.end:                                           ; preds = %entry
  %call1 = call i32 @gettimeofday(%struct.timeval* %tv, i8* null), !dbg !1719
  br label %while.cond, !dbg !1720

while.cond:                                       ; preds = %if.end104, %if.else55, %if.then41, %if.end
  %arraydecay = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1721
  %4 = load %struct.__sFILE*, %struct.__sFILE** %fp, align 8, !dbg !1722
  %call2 = call i8* @fgets(i8* %arraydecay, i32 5000, %struct.__sFILE* %4), !dbg !1723
  %cmp3 = icmp ne i8* %call2, null, !dbg !1724
  br i1 %cmp3, label %while.body, label %while.end122, !dbg !1720

while.body:                                       ; preds = %while.cond
  %arraydecay4 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1725
  %call5 = call i8* @strchr(i8* %arraydecay4, i32 35), !dbg !1727
  store i8* %call5, i8** %cp, align 8, !dbg !1728
  %5 = load i8*, i8** %cp, align 8, !dbg !1729
  %cmp6 = icmp ne i8* %5, null, !dbg !1731
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1732

if.then7:                                         ; preds = %while.body
  %6 = load i8*, i8** %cp, align 8, !dbg !1733
  store i8 0, i8* %6, align 1, !dbg !1734
  br label %if.end8, !dbg !1735

if.end8:                                          ; preds = %if.then7, %while.body
  %arraydecay9 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1736
  %call10 = call i64 @strlen(i8* %arraydecay9), !dbg !1737
  %conv = trunc i64 %call10 to i32, !dbg !1737
  store i32 %conv, i32* %len, align 4, !dbg !1738
  br label %while.cond11, !dbg !1739

while.cond11:                                     ; preds = %while.body36, %if.end8
  %7 = load i32, i32* %len, align 4, !dbg !1740
  %cmp12 = icmp sgt i32 %7, 0, !dbg !1741
  br i1 %cmp12, label %land.rhs, label %land.end, !dbg !1742

land.rhs:                                         ; preds = %while.cond11
  %8 = load i32, i32* %len, align 4, !dbg !1743
  %sub = sub nsw i32 %8, 1, !dbg !1744
  %idxprom = sext i32 %sub to i64, !dbg !1745
  %arrayidx = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 %idxprom, !dbg !1745
  %9 = load i8, i8* %arrayidx, align 1, !dbg !1745
  %conv14 = sext i8 %9 to i32, !dbg !1745
  %cmp15 = icmp eq i32 %conv14, 32, !dbg !1746
  br i1 %cmp15, label %lor.end, label %lor.lhs.false, !dbg !1747

lor.lhs.false:                                    ; preds = %land.rhs
  %10 = load i32, i32* %len, align 4, !dbg !1748
  %sub17 = sub nsw i32 %10, 1, !dbg !1749
  %idxprom18 = sext i32 %sub17 to i64, !dbg !1750
  %arrayidx19 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 %idxprom18, !dbg !1750
  %11 = load i8, i8* %arrayidx19, align 1, !dbg !1750
  %conv20 = sext i8 %11 to i32, !dbg !1750
  %cmp21 = icmp eq i32 %conv20, 9, !dbg !1751
  br i1 %cmp21, label %lor.end, label %lor.lhs.false23, !dbg !1752

lor.lhs.false23:                                  ; preds = %lor.lhs.false
  %12 = load i32, i32* %len, align 4, !dbg !1753
  %sub24 = sub nsw i32 %12, 1, !dbg !1754
  %idxprom25 = sext i32 %sub24 to i64, !dbg !1755
  %arrayidx26 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 %idxprom25, !dbg !1755
  %13 = load i8, i8* %arrayidx26, align 1, !dbg !1755
  %conv27 = sext i8 %13 to i32, !dbg !1755
  %cmp28 = icmp eq i32 %conv27, 10, !dbg !1756
  br i1 %cmp28, label %lor.end, label %lor.rhs, !dbg !1757

lor.rhs:                                          ; preds = %lor.lhs.false23
  %14 = load i32, i32* %len, align 4, !dbg !1758
  %sub30 = sub nsw i32 %14, 1, !dbg !1759
  %idxprom31 = sext i32 %sub30 to i64, !dbg !1760
  %arrayidx32 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 %idxprom31, !dbg !1760
  %15 = load i8, i8* %arrayidx32, align 1, !dbg !1760
  %conv33 = sext i8 %15 to i32, !dbg !1760
  %cmp34 = icmp eq i32 %conv33, 13, !dbg !1761
  br label %lor.end, !dbg !1757

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false23, %lor.lhs.false, %land.rhs
  %16 = phi i1 [ true, %lor.lhs.false23 ], [ true, %lor.lhs.false ], [ true, %land.rhs ], [ %cmp34, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond11
  %17 = phi i1 [ false, %while.cond11 ], [ %16, %lor.end ], !dbg !1762
  br i1 %17, label %while.body36, label %while.end, !dbg !1739

while.body36:                                     ; preds = %land.end
  %18 = load i32, i32* %len, align 4, !dbg !1763
  %dec = add nsw i32 %18, -1, !dbg !1763
  store i32 %dec, i32* %len, align 4, !dbg !1763
  %idxprom37 = sext i32 %dec to i64, !dbg !1764
  %arrayidx38 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 %idxprom37, !dbg !1764
  store i8 0, i8* %arrayidx38, align 1, !dbg !1765
  br label %while.cond11, !dbg !1739, !llvm.loop !1766

while.end:                                        ; preds = %land.end
  %19 = load i32, i32* %len, align 4, !dbg !1768
  %cmp39 = icmp eq i32 %19, 0, !dbg !1770
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !1771

if.then41:                                        ; preds = %while.end
  br label %while.cond, !dbg !1772, !llvm.loop !1773

if.end42:                                         ; preds = %while.end
  %arraydecay43 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1775
  %arraydecay44 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 0, !dbg !1777
  %call45 = call i32 (i8*, i8*, ...) @sscanf(i8* %arraydecay43, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.113, i64 0, i64 0), i8* %arraydecay44, i64* %min_limit, i64* %max_limit), !dbg !1778
  %cmp46 = icmp eq i32 %call45, 3, !dbg !1779
  br i1 %cmp46, label %if.then48, label %if.else, !dbg !1780

if.then48:                                        ; preds = %if.end42
  br label %if.end60, !dbg !1781

if.else:                                          ; preds = %if.end42
  %arraydecay49 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1783
  %arraydecay50 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 0, !dbg !1785
  %call51 = call i32 (i8*, i8*, ...) @sscanf(i8* %arraydecay49, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.114, i64 0, i64 0), i8* %arraydecay50, i64* %max_limit), !dbg !1786
  %cmp52 = icmp eq i32 %call51, 2, !dbg !1787
  br i1 %cmp52, label %if.then54, label %if.else55, !dbg !1788

if.then54:                                        ; preds = %if.else
  store i64 0, i64* %min_limit, align 8, !dbg !1789
  br label %if.end59, !dbg !1790

if.else55:                                        ; preds = %if.else
  %20 = load i8*, i8** %tf.addr, align 8, !dbg !1791
  %arraydecay56 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1793
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.115, i64 0, i64 0), i8* %20, i8* %arraydecay56), !dbg !1794
  %21 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !1795
  %22 = load i8*, i8** @argv0, align 8, !dbg !1796
  %23 = load i8*, i8** %tf.addr, align 8, !dbg !1797
  %arraydecay57 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 0, !dbg !1798
  %call58 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %21, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.116, i64 0, i64 0), i8* %22, i8* %23, i8* %arraydecay57), !dbg !1799
  br label %while.cond, !dbg !1800, !llvm.loop !1773

if.end59:                                         ; preds = %if.then54
  br label %if.end60

if.end60:                                         ; preds = %if.end59, %if.then48
  %arrayidx61 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 0, !dbg !1801
  %24 = load i8, i8* %arrayidx61, align 16, !dbg !1801
  %conv62 = sext i8 %24 to i32, !dbg !1801
  %cmp63 = icmp eq i32 %conv62, 47, !dbg !1803
  br i1 %cmp63, label %if.then65, label %if.end71, !dbg !1804

if.then65:                                        ; preds = %if.end60
  %arraydecay66 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 0, !dbg !1805
  %arrayidx67 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 1, !dbg !1805
  %arrayidx68 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 1, !dbg !1805
  %call69 = call i64 @strlen(i8* %arrayidx68), !dbg !1805
  %add = add i64 %call69, 1, !dbg !1805
  %call70 = call i8* @__memmove_chk(i8* %arraydecay66, i8* %arrayidx67, i64 %add, i64 5000) #13, !dbg !1805
  br label %if.end71, !dbg !1806

if.end71:                                         ; preds = %if.then65, %if.end60
  br label %while.cond72, !dbg !1807

while.cond72:                                     ; preds = %while.body77, %if.end71
  %arraydecay73 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 0, !dbg !1808
  %call74 = call i8* @strstr(i8* %arraydecay73, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.117, i64 0, i64 0)), !dbg !1809
  store i8* %call74, i8** %cp, align 8, !dbg !1810
  %cmp75 = icmp ne i8* %call74, null, !dbg !1811
  br i1 %cmp75, label %while.body77, label %while.end84, !dbg !1807

while.body77:                                     ; preds = %while.cond72
  %25 = load i8*, i8** %cp, align 8, !dbg !1812
  %add.ptr = getelementptr inbounds i8, i8* %25, i64 1, !dbg !1812
  %26 = load i8*, i8** %cp, align 8, !dbg !1812
  %add.ptr78 = getelementptr inbounds i8, i8* %26, i64 2, !dbg !1812
  %27 = load i8*, i8** %cp, align 8, !dbg !1812
  %add.ptr79 = getelementptr inbounds i8, i8* %27, i64 2, !dbg !1812
  %call80 = call i64 @strlen(i8* %add.ptr79), !dbg !1812
  %add81 = add i64 %call80, 1, !dbg !1812
  %28 = load i8*, i8** %cp, align 8, !dbg !1812
  %add.ptr82 = getelementptr inbounds i8, i8* %28, i64 1, !dbg !1812
  %29 = call i64 @llvm.objectsize.i64.p0i8(i8* %add.ptr82, i1 false, i1 true, i1 false), !dbg !1812
  %call83 = call i8* @__memmove_chk(i8* %add.ptr, i8* %add.ptr78, i64 %add81, i64 %29) #13, !dbg !1812
  br label %while.cond72, !dbg !1807, !llvm.loop !1813

while.end84:                                      ; preds = %while.cond72
  %30 = load i32, i32* @numthrottles, align 4, !dbg !1814
  %31 = load i32, i32* @maxthrottles, align 4, !dbg !1816
  %cmp85 = icmp sge i32 %30, %31, !dbg !1817
  br i1 %cmp85, label %if.then87, label %if.end104, !dbg !1818

if.then87:                                        ; preds = %while.end84
  %32 = load i32, i32* @maxthrottles, align 4, !dbg !1819
  %cmp88 = icmp eq i32 %32, 0, !dbg !1822
  br i1 %cmp88, label %if.then90, label %if.else93, !dbg !1823

if.then90:                                        ; preds = %if.then87
  store i32 100, i32* @maxthrottles, align 4, !dbg !1824
  %33 = load i32, i32* @maxthrottles, align 4, !dbg !1826
  %conv91 = sext i32 %33 to i64, !dbg !1826
  %mul = mul i64 48, %conv91, !dbg !1826
  %call92 = call i8* @malloc(i64 %mul) #14, !dbg !1826
  %34 = bitcast i8* %call92 to %struct.throttletab*, !dbg !1826
  store %struct.throttletab* %34, %struct.throttletab** @throttles, align 8, !dbg !1827
  br label %if.end98, !dbg !1828

if.else93:                                        ; preds = %if.then87
  %35 = load i32, i32* @maxthrottles, align 4, !dbg !1829
  %mul94 = mul nsw i32 %35, 2, !dbg !1829
  store i32 %mul94, i32* @maxthrottles, align 4, !dbg !1829
  %36 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1831
  %37 = bitcast %struct.throttletab* %36 to i8*, !dbg !1831
  %38 = load i32, i32* @maxthrottles, align 4, !dbg !1831
  %conv95 = sext i32 %38 to i64, !dbg !1831
  %mul96 = mul i64 48, %conv95, !dbg !1831
  %call97 = call i8* @realloc(i8* %37, i64 %mul96) #15, !dbg !1831
  %39 = bitcast i8* %call97 to %struct.throttletab*, !dbg !1831
  store %struct.throttletab* %39, %struct.throttletab** @throttles, align 8, !dbg !1832
  br label %if.end98

if.end98:                                         ; preds = %if.else93, %if.then90
  %40 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1833
  %cmp99 = icmp eq %struct.throttletab* %40, null, !dbg !1835
  br i1 %cmp99, label %if.then101, label %if.end103, !dbg !1836

if.then101:                                       ; preds = %if.end98
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.118, i64 0, i64 0)), !dbg !1837
  %41 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !1839
  %42 = load i8*, i8** @argv0, align 8, !dbg !1840
  %call102 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %41, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.119, i64 0, i64 0), i8* %42), !dbg !1841
  call void @exit(i32 1) #11, !dbg !1842
  unreachable, !dbg !1842

if.end103:                                        ; preds = %if.end98
  br label %if.end104, !dbg !1843

if.end104:                                        ; preds = %if.end103, %while.end84
  %arraydecay105 = getelementptr inbounds [5000 x i8], [5000 x i8]* %pattern, i64 0, i64 0, !dbg !1844
  %call106 = call i8* @e_strdup(i8* %arraydecay105), !dbg !1845
  %43 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1846
  %44 = load i32, i32* @numthrottles, align 4, !dbg !1847
  %idxprom107 = sext i32 %44 to i64, !dbg !1846
  %arrayidx108 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %43, i64 %idxprom107, !dbg !1846
  %pattern109 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx108, i32 0, i32 0, !dbg !1848
  store i8* %call106, i8** %pattern109, align 8, !dbg !1849
  %45 = load i64, i64* %max_limit, align 8, !dbg !1850
  %46 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1851
  %47 = load i32, i32* @numthrottles, align 4, !dbg !1852
  %idxprom110 = sext i32 %47 to i64, !dbg !1851
  %arrayidx111 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %46, i64 %idxprom110, !dbg !1851
  %max_limit112 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx111, i32 0, i32 1, !dbg !1853
  store i64 %45, i64* %max_limit112, align 8, !dbg !1854
  %48 = load i64, i64* %min_limit, align 8, !dbg !1855
  %49 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1856
  %50 = load i32, i32* @numthrottles, align 4, !dbg !1857
  %idxprom113 = sext i32 %50 to i64, !dbg !1856
  %arrayidx114 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %49, i64 %idxprom113, !dbg !1856
  %min_limit115 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx114, i32 0, i32 2, !dbg !1858
  store i64 %48, i64* %min_limit115, align 8, !dbg !1859
  %51 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1860
  %52 = load i32, i32* @numthrottles, align 4, !dbg !1861
  %idxprom116 = sext i32 %52 to i64, !dbg !1860
  %arrayidx117 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %51, i64 %idxprom116, !dbg !1860
  %rate = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx117, i32 0, i32 3, !dbg !1862
  store i64 0, i64* %rate, align 8, !dbg !1863
  %53 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1864
  %54 = load i32, i32* @numthrottles, align 4, !dbg !1865
  %idxprom118 = sext i32 %54 to i64, !dbg !1864
  %arrayidx119 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %53, i64 %idxprom118, !dbg !1864
  %bytes_since_avg = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx119, i32 0, i32 4, !dbg !1866
  store i64 0, i64* %bytes_since_avg, align 8, !dbg !1867
  %55 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !1868
  %56 = load i32, i32* @numthrottles, align 4, !dbg !1869
  %idxprom120 = sext i32 %56 to i64, !dbg !1868
  %arrayidx121 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %55, i64 %idxprom120, !dbg !1868
  %num_sending = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx121, i32 0, i32 5, !dbg !1870
  store i32 0, i32* %num_sending, align 8, !dbg !1871
  %57 = load i32, i32* @numthrottles, align 4, !dbg !1872
  %inc = add nsw i32 %57, 1, !dbg !1872
  store i32 %inc, i32* @numthrottles, align 4, !dbg !1872
  br label %while.cond, !dbg !1720, !llvm.loop !1773

while.end122:                                     ; preds = %while.cond
  %58 = load %struct.__sFILE*, %struct.__sFILE** %fp, align 8, !dbg !1873
  %call123 = call i32 @fclose(%struct.__sFILE* %58), !dbg !1874
  ret void, !dbg !1875
}

declare i32 @getuid() #3

declare %struct.passwd* @getpwnam(i8*) #3

declare i32 @strcmp(i8*, i8*) #3

declare %struct.__sFILE* @"\01_fopen"(i8*, i8*) #3

; Function Attrs: cold
declare void @perror(i8*) #5

declare i32 @"\01_fcntl"(i32, i32, ...) #3

declare i32 @fileno(%struct.__sFILE*) #3

declare i32 @fchown(i32, i32, i32) #3

declare i32 @chdir(i8*) #3

declare i8* @getcwd(i8*, i64) #3

declare i64 @strlen(i8*) #3

; Function Attrs: nounwind
declare i8* @__strcat_chk(i8*, i8*, i64) #6

declare i32 @fclose(%struct.__sFILE*) #3

declare i32 @"\01_daemon$1050"(i32, i32) #3

declare i32 @setsid() #3

declare i32 @getpid() #3

declare i32 @fdwatch_get_nfiles() #3

declare i32 @chroot(i8*) #3

declare i32 @strncmp(i8*, i8*, i64) #3

; Function Attrs: nounwind
declare i8* @__memmove_chk(i8*, i8*, i64, i64) #6

; Function Attrs: nounwind readnone speculatable willreturn
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1 immarg, i1 immarg, i1 immarg) #1

; Function Attrs: nounwind
declare i8* @__strcpy_chk(i8*, i8*, i64) #6

declare void (i32)* @sigset(i32, void (i32)*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_term(i32 %sig) #0 !dbg !1876 {
entry:
  %sig.addr = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !1877, metadata !DIExpression()), !dbg !1878
  call void @shut_down(), !dbg !1879
  %0 = load i32, i32* %sig.addr, align 4, !dbg !1880
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.41, i64 0, i64 0), i32 %0), !dbg !1881
  call void @closelog(), !dbg !1882
  call void @exit(i32 1) #11, !dbg !1883
  unreachable, !dbg !1883
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_chld(i32 %sig) #0 !dbg !1884 {
entry:
  %sig.addr = alloca i32, align 4
  %oerrno = alloca i32, align 4
  %pid = alloca i32, align 4
  %status = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !1885, metadata !DIExpression()), !dbg !1886
  call void @llvm.dbg.declare(metadata i32* %oerrno, metadata !1887, metadata !DIExpression()), !dbg !1889
  %call = call i32* @__error(), !dbg !1890
  %0 = load i32, i32* %call, align 4, !dbg !1890
  store i32 %0, i32* %oerrno, align 4, !dbg !1889
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !1891, metadata !DIExpression()), !dbg !1892
  call void @llvm.dbg.declare(metadata i32* %status, metadata !1893, metadata !DIExpression()), !dbg !1894
  br label %for.cond, !dbg !1895

for.cond:                                         ; preds = %if.end22, %if.then8, %entry
  %call1 = call i32 @"\01_waitpid"(i32 -1, i32* %status, i32 1), !dbg !1896
  store i32 %call1, i32* %pid, align 4, !dbg !1900
  %1 = load i32, i32* %pid, align 4, !dbg !1901
  %cmp = icmp eq i32 %1, 0, !dbg !1903
  br i1 %cmp, label %if.then, label %if.end, !dbg !1904

if.then:                                          ; preds = %for.cond
  br label %for.end, !dbg !1905

if.end:                                           ; preds = %for.cond
  %2 = load i32, i32* %pid, align 4, !dbg !1906
  %cmp2 = icmp slt i32 %2, 0, !dbg !1908
  br i1 %cmp2, label %if.then3, label %if.end14, !dbg !1909

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__error(), !dbg !1910
  %3 = load i32, i32* %call4, align 4, !dbg !1910
  %cmp5 = icmp eq i32 %3, 4, !dbg !1913
  br i1 %cmp5, label %if.then8, label %lor.lhs.false, !dbg !1914

lor.lhs.false:                                    ; preds = %if.then3
  %call6 = call i32* @__error(), !dbg !1915
  %4 = load i32, i32* %call6, align 4, !dbg !1915
  %cmp7 = icmp eq i32 %4, 35, !dbg !1916
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1917

if.then8:                                         ; preds = %lor.lhs.false, %if.then3
  br label %for.cond, !dbg !1918, !llvm.loop !1919

if.end9:                                          ; preds = %lor.lhs.false
  %call10 = call i32* @__error(), !dbg !1922
  %5 = load i32, i32* %call10, align 4, !dbg !1922
  %cmp11 = icmp ne i32 %5, 10, !dbg !1924
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1925

if.then12:                                        ; preds = %if.end9
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.42, i64 0, i64 0)), !dbg !1926
  br label %if.end13, !dbg !1926

if.end13:                                         ; preds = %if.then12, %if.end9
  br label %for.end, !dbg !1927

if.end14:                                         ; preds = %if.end
  %6 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1928
  %cmp15 = icmp ne %struct.httpd_server* %6, null, !dbg !1930
  br i1 %cmp15, label %if.then16, label %if.end22, !dbg !1931

if.then16:                                        ; preds = %if.end14
  %7 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1932
  %cgi_count = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %7, i32 0, i32 5, !dbg !1934
  %8 = load i32, i32* %cgi_count, align 4, !dbg !1935
  %dec = add nsw i32 %8, -1, !dbg !1935
  store i32 %dec, i32* %cgi_count, align 4, !dbg !1935
  %9 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1936
  %cgi_count17 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %9, i32 0, i32 5, !dbg !1938
  %10 = load i32, i32* %cgi_count17, align 4, !dbg !1938
  %cmp18 = icmp slt i32 %10, 0, !dbg !1939
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !1940

if.then19:                                        ; preds = %if.then16
  %11 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !1941
  %cgi_count20 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %11, i32 0, i32 5, !dbg !1942
  store i32 0, i32* %cgi_count20, align 4, !dbg !1943
  br label %if.end21, !dbg !1941

if.end21:                                         ; preds = %if.then19, %if.then16
  br label %if.end22, !dbg !1944

if.end22:                                         ; preds = %if.end21, %if.end14
  br label %for.cond, !dbg !1945, !llvm.loop !1919

for.end:                                          ; preds = %if.end13, %if.then
  %12 = load i32, i32* %oerrno, align 4, !dbg !1946
  %call23 = call i32* @__error(), !dbg !1947
  store i32 %12, i32* %call23, align 4, !dbg !1948
  ret void, !dbg !1949
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_hup(i32 %sig) #0 !dbg !1950 {
entry:
  %sig.addr = alloca i32, align 4
  %oerrno = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !1951, metadata !DIExpression()), !dbg !1952
  call void @llvm.dbg.declare(metadata i32* %oerrno, metadata !1953, metadata !DIExpression()), !dbg !1954
  %call = call i32* @__error(), !dbg !1955
  %0 = load i32, i32* %call, align 4, !dbg !1955
  store i32 %0, i32* %oerrno, align 4, !dbg !1954
  store volatile i32 1, i32* @got_hup, align 4, !dbg !1956
  %1 = load i32, i32* %oerrno, align 4, !dbg !1957
  %call1 = call i32* @__error(), !dbg !1958
  store i32 %1, i32* %call1, align 4, !dbg !1959
  ret void, !dbg !1960
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_usr1(i32 %sig) #0 !dbg !1961 {
entry:
  %sig.addr = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !1962, metadata !DIExpression()), !dbg !1963
  %0 = load i32, i32* @num_connects, align 4, !dbg !1964
  %cmp = icmp eq i32 %0, 0, !dbg !1966
  br i1 %cmp, label %if.then, label %if.end, !dbg !1967

if.then:                                          ; preds = %entry
  call void @shut_down(), !dbg !1968
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.40, i64 0, i64 0)), !dbg !1970
  call void @closelog(), !dbg !1971
  call void @exit(i32 0) #11, !dbg !1972
  unreachable, !dbg !1972

if.end:                                           ; preds = %entry
  store volatile i32 1, i32* @got_usr1, align 4, !dbg !1973
  ret void, !dbg !1974
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_usr2(i32 %sig) #0 !dbg !1975 {
entry:
  %sig.addr = alloca i32, align 4
  %oerrno = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !1976, metadata !DIExpression()), !dbg !1977
  call void @llvm.dbg.declare(metadata i32* %oerrno, metadata !1978, metadata !DIExpression()), !dbg !1979
  %call = call i32* @__error(), !dbg !1980
  %0 = load i32, i32* %call, align 4, !dbg !1980
  store i32 %0, i32* %oerrno, align 4, !dbg !1979
  call void @logstats(%struct.timeval* null), !dbg !1981
  %1 = load i32, i32* %oerrno, align 4, !dbg !1982
  %call1 = call i32* @__error(), !dbg !1983
  store i32 %1, i32* %call1, align 4, !dbg !1984
  ret void, !dbg !1985
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_alrm(i32 %sig) #0 !dbg !1986 {
entry:
  %sig.addr = alloca i32, align 4
  %oerrno = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !1987, metadata !DIExpression()), !dbg !1988
  call void @llvm.dbg.declare(metadata i32* %oerrno, metadata !1989, metadata !DIExpression()), !dbg !1990
  %call = call i32* @__error(), !dbg !1991
  %0 = load i32, i32* %call, align 4, !dbg !1991
  store i32 %0, i32* %oerrno, align 4, !dbg !1990
  %1 = load volatile i32, i32* @watchdog_flag, align 4, !dbg !1992
  %tobool = icmp ne i32 %1, 0, !dbg !1992
  br i1 %tobool, label %if.end, label %if.then, !dbg !1994

if.then:                                          ; preds = %entry
  %call1 = call i32 @chdir(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.45, i64 0, i64 0)), !dbg !1995
  call void @abort() #16, !dbg !1997
  unreachable, !dbg !1997

if.end:                                           ; preds = %entry
  store volatile i32 0, i32* @watchdog_flag, align 4, !dbg !1998
  %call2 = call i32 @alarm(i32 360), !dbg !1999
  %2 = load i32, i32* %oerrno, align 4, !dbg !2000
  %call3 = call i32* @__error(), !dbg !2001
  store i32 %2, i32* %call3, align 4, !dbg !2002
  ret void, !dbg !2003
}

declare i32 @alarm(i32) #3

declare void @tmr_init() #3

declare %struct.httpd_server* @httpd_initialize(i8*, %union.httpd_sockaddr*, %union.httpd_sockaddr*, i16 zeroext, i8*, i32, i8*, i8*, i32, i8*, i32, %struct.__sFILE*, i32, i32, i32, i8*, i8*, i32) #3

declare %struct.TimerStruct* @tmr_create(%struct.timeval*, void (i8*, %struct.timeval*)*, i8*, i64, i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @occasional(i8* %client_data.coerce, %struct.timeval* %nowP) #0 !dbg !2004 {
entry:
  %client_data = alloca %union.ClientData, align 8
  %nowP.addr = alloca %struct.timeval*, align 8
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0
  store i8* %client_data.coerce, i8** %coerce.dive, align 8
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2005, metadata !DIExpression()), !dbg !2006
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !2007, metadata !DIExpression()), !dbg !2008
  %0 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !2009
  call void @mmc_cleanup(%struct.timeval* %0), !dbg !2010
  call void @tmr_cleanup(), !dbg !2011
  store volatile i32 1, i32* @watchdog_flag, align 4, !dbg !2012
  ret void, !dbg !2013
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @idle(i8* %client_data.coerce, %struct.timeval* %nowP) #0 !dbg !2014 {
entry:
  %client_data = alloca %union.ClientData, align 8
  %nowP.addr = alloca %struct.timeval*, align 8
  %cnum = alloca i32, align 4
  %c = alloca %struct.connecttab*, align 8
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0
  store i8* %client_data.coerce, i8** %coerce.dive, align 8
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2015, metadata !DIExpression()), !dbg !2016
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !2017, metadata !DIExpression()), !dbg !2018
  call void @llvm.dbg.declare(metadata i32* %cnum, metadata !2019, metadata !DIExpression()), !dbg !2020
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c, metadata !2021, metadata !DIExpression()), !dbg !2022
  store i32 0, i32* %cnum, align 4, !dbg !2023
  br label %for.cond, !dbg !2025

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %cnum, align 4, !dbg !2026
  %1 = load i32, i32* @max_connects, align 4, !dbg !2028
  %cmp = icmp slt i32 %0, %1, !dbg !2029
  br i1 %cmp, label %for.body, label %for.end, !dbg !2030

for.body:                                         ; preds = %for.cond
  %2 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !2031
  %3 = load i32, i32* %cnum, align 4, !dbg !2033
  %idxprom = sext i32 %3 to i64, !dbg !2031
  %arrayidx = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i64 %idxprom, !dbg !2031
  store %struct.connecttab* %arrayidx, %struct.connecttab** %c, align 8, !dbg !2034
  %4 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2035
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %4, i32 0, i32 0, !dbg !2036
  %5 = load i32, i32* %conn_state, align 8, !dbg !2036
  switch i32 %5, label %sw.epilog [
    i32 1, label %sw.bb
    i32 2, label %sw.bb3
    i32 3, label %sw.bb3
  ], !dbg !2037

sw.bb:                                            ; preds = %for.body
  %6 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !2038
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %6, i32 0, i32 0, !dbg !2041
  %7 = load i64, i64* %tv_sec, align 8, !dbg !2041
  %8 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2042
  %active_at = getelementptr inbounds %struct.connecttab, %struct.connecttab* %8, i32 0, i32 8, !dbg !2043
  %9 = load i64, i64* %active_at, align 8, !dbg !2043
  %sub = sub nsw i64 %7, %9, !dbg !2044
  %cmp1 = icmp sge i64 %sub, 60, !dbg !2045
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2046

if.then:                                          ; preds = %sw.bb
  %10 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2047
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %10, i32 0, i32 2, !dbg !2049
  %11 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2049
  %client_addr = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %11, i32 0, i32 2, !dbg !2050
  %call = call i8* @httpd_ntoa(%union.httpd_sockaddr* %client_addr), !dbg !2051
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 6, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.132, i64 0, i64 0), i8* %call), !dbg !2052
  %12 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2053
  %hc2 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %12, i32 0, i32 2, !dbg !2054
  %13 = load %struct.httpd_conn*, %struct.httpd_conn** %hc2, align 8, !dbg !2054
  %14 = load i8*, i8** @httpd_err408title, align 8, !dbg !2055
  %15 = load i8*, i8** @httpd_err408form, align 8, !dbg !2056
  call void @httpd_send_err(%struct.httpd_conn* %13, i32 408, i8* %14, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8* %15, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0)), !dbg !2057
  %16 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2058
  %17 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !2059
  call void @finish_connection(%struct.connecttab* %16, %struct.timeval* %17), !dbg !2060
  br label %if.end, !dbg !2061

if.end:                                           ; preds = %if.then, %sw.bb
  br label %sw.epilog, !dbg !2062

sw.bb3:                                           ; preds = %for.body, %for.body
  %18 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !2063
  %tv_sec4 = getelementptr inbounds %struct.timeval, %struct.timeval* %18, i32 0, i32 0, !dbg !2065
  %19 = load i64, i64* %tv_sec4, align 8, !dbg !2065
  %20 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2066
  %active_at5 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %20, i32 0, i32 8, !dbg !2067
  %21 = load i64, i64* %active_at5, align 8, !dbg !2067
  %sub6 = sub nsw i64 %19, %21, !dbg !2068
  %cmp7 = icmp sge i64 %sub6, 300, !dbg !2069
  br i1 %cmp7, label %if.then8, label %if.end12, !dbg !2070

if.then8:                                         ; preds = %sw.bb3
  %22 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2071
  %hc9 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %22, i32 0, i32 2, !dbg !2073
  %23 = load %struct.httpd_conn*, %struct.httpd_conn** %hc9, align 8, !dbg !2073
  %client_addr10 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %23, i32 0, i32 2, !dbg !2074
  %call11 = call i8* @httpd_ntoa(%union.httpd_sockaddr* %client_addr10), !dbg !2075
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 6, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.133, i64 0, i64 0), i8* %call11), !dbg !2076
  %24 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2077
  %25 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !2078
  call void @clear_connection(%struct.connecttab* %24, %struct.timeval* %25), !dbg !2079
  br label %if.end12, !dbg !2080

if.end12:                                         ; preds = %if.then8, %sw.bb3
  br label %sw.epilog, !dbg !2081

sw.epilog:                                        ; preds = %for.body, %if.end12, %if.end
  br label %for.inc, !dbg !2082

for.inc:                                          ; preds = %sw.epilog
  %26 = load i32, i32* %cnum, align 4, !dbg !2083
  %inc = add nsw i32 %26, 1, !dbg !2083
  store i32 %inc, i32* %cnum, align 4, !dbg !2083
  br label %for.cond, !dbg !2084, !llvm.loop !2085

for.end:                                          ; preds = %for.cond
  ret void, !dbg !2087
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @update_throttles(i8* %client_data.coerce, %struct.timeval* %nowP) #0 !dbg !2088 {
entry:
  %client_data = alloca %union.ClientData, align 8
  %nowP.addr = alloca %struct.timeval*, align 8
  %tnum = alloca i32, align 4
  %tind = alloca i32, align 4
  %cnum = alloca i32, align 4
  %c = alloca %struct.connecttab*, align 8
  %l = alloca i64, align 8
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0
  store i8* %client_data.coerce, i8** %coerce.dive, align 8
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2089, metadata !DIExpression()), !dbg !2090
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !2091, metadata !DIExpression()), !dbg !2092
  call void @llvm.dbg.declare(metadata i32* %tnum, metadata !2093, metadata !DIExpression()), !dbg !2094
  call void @llvm.dbg.declare(metadata i32* %tind, metadata !2095, metadata !DIExpression()), !dbg !2096
  call void @llvm.dbg.declare(metadata i32* %cnum, metadata !2097, metadata !DIExpression()), !dbg !2098
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c, metadata !2099, metadata !DIExpression()), !dbg !2100
  call void @llvm.dbg.declare(metadata i64* %l, metadata !2101, metadata !DIExpression()), !dbg !2102
  store i32 0, i32* %tnum, align 4, !dbg !2103
  br label %for.cond, !dbg !2105

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %tnum, align 4, !dbg !2106
  %1 = load i32, i32* @numthrottles, align 4, !dbg !2108
  %cmp = icmp slt i32 %0, %1, !dbg !2109
  br i1 %cmp, label %for.body, label %for.end, !dbg !2110

for.body:                                         ; preds = %for.cond
  %2 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2111
  %3 = load i32, i32* %tnum, align 4, !dbg !2113
  %idxprom = sext i32 %3 to i64, !dbg !2111
  %arrayidx = getelementptr inbounds %struct.throttletab, %struct.throttletab* %2, i64 %idxprom, !dbg !2111
  %rate = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx, i32 0, i32 3, !dbg !2114
  %4 = load i64, i64* %rate, align 8, !dbg !2114
  %mul = mul nsw i64 2, %4, !dbg !2115
  %5 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2116
  %6 = load i32, i32* %tnum, align 4, !dbg !2117
  %idxprom1 = sext i32 %6 to i64, !dbg !2116
  %arrayidx2 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %5, i64 %idxprom1, !dbg !2116
  %bytes_since_avg = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx2, i32 0, i32 4, !dbg !2118
  %7 = load i64, i64* %bytes_since_avg, align 8, !dbg !2118
  %div = sdiv i64 %7, 2, !dbg !2119
  %add = add nsw i64 %mul, %div, !dbg !2120
  %div3 = sdiv i64 %add, 3, !dbg !2121
  %8 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2122
  %9 = load i32, i32* %tnum, align 4, !dbg !2123
  %idxprom4 = sext i32 %9 to i64, !dbg !2122
  %arrayidx5 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %8, i64 %idxprom4, !dbg !2122
  %rate6 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx5, i32 0, i32 3, !dbg !2124
  store i64 %div3, i64* %rate6, align 8, !dbg !2125
  %10 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2126
  %11 = load i32, i32* %tnum, align 4, !dbg !2127
  %idxprom7 = sext i32 %11 to i64, !dbg !2126
  %arrayidx8 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %10, i64 %idxprom7, !dbg !2126
  %bytes_since_avg9 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx8, i32 0, i32 4, !dbg !2128
  store i64 0, i64* %bytes_since_avg9, align 8, !dbg !2129
  %12 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2130
  %13 = load i32, i32* %tnum, align 4, !dbg !2132
  %idxprom10 = sext i32 %13 to i64, !dbg !2130
  %arrayidx11 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %12, i64 %idxprom10, !dbg !2130
  %rate12 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx11, i32 0, i32 3, !dbg !2133
  %14 = load i64, i64* %rate12, align 8, !dbg !2133
  %15 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2134
  %16 = load i32, i32* %tnum, align 4, !dbg !2135
  %idxprom13 = sext i32 %16 to i64, !dbg !2134
  %arrayidx14 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %15, i64 %idxprom13, !dbg !2134
  %max_limit = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx14, i32 0, i32 1, !dbg !2136
  %17 = load i64, i64* %max_limit, align 8, !dbg !2136
  %cmp15 = icmp sgt i64 %14, %17, !dbg !2137
  br i1 %cmp15, label %land.lhs.true, label %if.end51, !dbg !2138

land.lhs.true:                                    ; preds = %for.body
  %18 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2139
  %19 = load i32, i32* %tnum, align 4, !dbg !2140
  %idxprom16 = sext i32 %19 to i64, !dbg !2139
  %arrayidx17 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %18, i64 %idxprom16, !dbg !2139
  %num_sending = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx17, i32 0, i32 5, !dbg !2141
  %20 = load i32, i32* %num_sending, align 8, !dbg !2141
  %cmp18 = icmp ne i32 %20, 0, !dbg !2142
  br i1 %cmp18, label %if.then, label %if.end51, !dbg !2143

if.then:                                          ; preds = %land.lhs.true
  %21 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2144
  %22 = load i32, i32* %tnum, align 4, !dbg !2147
  %idxprom19 = sext i32 %22 to i64, !dbg !2144
  %arrayidx20 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %21, i64 %idxprom19, !dbg !2144
  %rate21 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx20, i32 0, i32 3, !dbg !2148
  %23 = load i64, i64* %rate21, align 8, !dbg !2148
  %24 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2149
  %25 = load i32, i32* %tnum, align 4, !dbg !2150
  %idxprom22 = sext i32 %25 to i64, !dbg !2149
  %arrayidx23 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %24, i64 %idxprom22, !dbg !2149
  %max_limit24 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx23, i32 0, i32 1, !dbg !2151
  %26 = load i64, i64* %max_limit24, align 8, !dbg !2151
  %mul25 = mul nsw i64 %26, 2, !dbg !2152
  %cmp26 = icmp sgt i64 %23, %mul25, !dbg !2153
  br i1 %cmp26, label %if.then27, label %if.else, !dbg !2154

if.then27:                                        ; preds = %if.then
  %27 = load i32, i32* %tnum, align 4, !dbg !2155
  %28 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2156
  %29 = load i32, i32* %tnum, align 4, !dbg !2157
  %idxprom28 = sext i32 %29 to i64, !dbg !2156
  %arrayidx29 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %28, i64 %idxprom28, !dbg !2156
  %pattern = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx29, i32 0, i32 0, !dbg !2158
  %30 = load i8*, i8** %pattern, align 8, !dbg !2158
  %31 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2159
  %32 = load i32, i32* %tnum, align 4, !dbg !2160
  %idxprom30 = sext i32 %32 to i64, !dbg !2159
  %arrayidx31 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %31, i64 %idxprom30, !dbg !2159
  %rate32 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx31, i32 0, i32 3, !dbg !2161
  %33 = load i64, i64* %rate32, align 8, !dbg !2161
  %34 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2162
  %35 = load i32, i32* %tnum, align 4, !dbg !2163
  %idxprom33 = sext i32 %35 to i64, !dbg !2162
  %arrayidx34 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %34, i64 %idxprom33, !dbg !2162
  %max_limit35 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx34, i32 0, i32 1, !dbg !2164
  %36 = load i64, i64* %max_limit35, align 8, !dbg !2164
  %37 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2165
  %38 = load i32, i32* %tnum, align 4, !dbg !2166
  %idxprom36 = sext i32 %38 to i64, !dbg !2165
  %arrayidx37 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %37, i64 %idxprom36, !dbg !2165
  %num_sending38 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx37, i32 0, i32 5, !dbg !2167
  %39 = load i32, i32* %num_sending38, align 8, !dbg !2167
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.127, i64 0, i64 0), i32 %27, i8* %30, i64 %33, i64 %36, i32 %39), !dbg !2168
  br label %if.end, !dbg !2168

if.else:                                          ; preds = %if.then
  %40 = load i32, i32* %tnum, align 4, !dbg !2169
  %41 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2170
  %42 = load i32, i32* %tnum, align 4, !dbg !2171
  %idxprom39 = sext i32 %42 to i64, !dbg !2170
  %arrayidx40 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %41, i64 %idxprom39, !dbg !2170
  %pattern41 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx40, i32 0, i32 0, !dbg !2172
  %43 = load i8*, i8** %pattern41, align 8, !dbg !2172
  %44 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2173
  %45 = load i32, i32* %tnum, align 4, !dbg !2174
  %idxprom42 = sext i32 %45 to i64, !dbg !2173
  %arrayidx43 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %44, i64 %idxprom42, !dbg !2173
  %rate44 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx43, i32 0, i32 3, !dbg !2175
  %46 = load i64, i64* %rate44, align 8, !dbg !2175
  %47 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2176
  %48 = load i32, i32* %tnum, align 4, !dbg !2177
  %idxprom45 = sext i32 %48 to i64, !dbg !2176
  %arrayidx46 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %47, i64 %idxprom45, !dbg !2176
  %max_limit47 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx46, i32 0, i32 1, !dbg !2178
  %49 = load i64, i64* %max_limit47, align 8, !dbg !2178
  %50 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2179
  %51 = load i32, i32* %tnum, align 4, !dbg !2180
  %idxprom48 = sext i32 %51 to i64, !dbg !2179
  %arrayidx49 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %50, i64 %idxprom48, !dbg !2179
  %num_sending50 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx49, i32 0, i32 5, !dbg !2181
  %52 = load i32, i32* %num_sending50, align 8, !dbg !2181
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 6, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.128, i64 0, i64 0), i32 %40, i8* %43, i64 %46, i64 %49, i32 %52), !dbg !2182
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then27
  br label %if.end51, !dbg !2183

if.end51:                                         ; preds = %if.end, %land.lhs.true, %for.body
  %53 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2184
  %54 = load i32, i32* %tnum, align 4, !dbg !2186
  %idxprom52 = sext i32 %54 to i64, !dbg !2184
  %arrayidx53 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %53, i64 %idxprom52, !dbg !2184
  %rate54 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx53, i32 0, i32 3, !dbg !2187
  %55 = load i64, i64* %rate54, align 8, !dbg !2187
  %56 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2188
  %57 = load i32, i32* %tnum, align 4, !dbg !2189
  %idxprom55 = sext i32 %57 to i64, !dbg !2188
  %arrayidx56 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %56, i64 %idxprom55, !dbg !2188
  %min_limit = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx56, i32 0, i32 2, !dbg !2190
  %58 = load i64, i64* %min_limit, align 8, !dbg !2190
  %cmp57 = icmp slt i64 %55, %58, !dbg !2191
  br i1 %cmp57, label %land.lhs.true58, label %if.end76, !dbg !2192

land.lhs.true58:                                  ; preds = %if.end51
  %59 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2193
  %60 = load i32, i32* %tnum, align 4, !dbg !2194
  %idxprom59 = sext i32 %60 to i64, !dbg !2193
  %arrayidx60 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %59, i64 %idxprom59, !dbg !2193
  %num_sending61 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx60, i32 0, i32 5, !dbg !2195
  %61 = load i32, i32* %num_sending61, align 8, !dbg !2195
  %cmp62 = icmp ne i32 %61, 0, !dbg !2196
  br i1 %cmp62, label %if.then63, label %if.end76, !dbg !2197

if.then63:                                        ; preds = %land.lhs.true58
  %62 = load i32, i32* %tnum, align 4, !dbg !2198
  %63 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2200
  %64 = load i32, i32* %tnum, align 4, !dbg !2201
  %idxprom64 = sext i32 %64 to i64, !dbg !2200
  %arrayidx65 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %63, i64 %idxprom64, !dbg !2200
  %pattern66 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx65, i32 0, i32 0, !dbg !2202
  %65 = load i8*, i8** %pattern66, align 8, !dbg !2202
  %66 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2203
  %67 = load i32, i32* %tnum, align 4, !dbg !2204
  %idxprom67 = sext i32 %67 to i64, !dbg !2203
  %arrayidx68 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %66, i64 %idxprom67, !dbg !2203
  %rate69 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx68, i32 0, i32 3, !dbg !2205
  %68 = load i64, i64* %rate69, align 8, !dbg !2205
  %69 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2206
  %70 = load i32, i32* %tnum, align 4, !dbg !2207
  %idxprom70 = sext i32 %70 to i64, !dbg !2206
  %arrayidx71 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %69, i64 %idxprom70, !dbg !2206
  %min_limit72 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx71, i32 0, i32 2, !dbg !2208
  %71 = load i64, i64* %min_limit72, align 8, !dbg !2208
  %72 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2209
  %73 = load i32, i32* %tnum, align 4, !dbg !2210
  %idxprom73 = sext i32 %73 to i64, !dbg !2209
  %arrayidx74 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %72, i64 %idxprom73, !dbg !2209
  %num_sending75 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx74, i32 0, i32 5, !dbg !2211
  %74 = load i32, i32* %num_sending75, align 8, !dbg !2211
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([65 x i8], [65 x i8]* @.str.129, i64 0, i64 0), i32 %62, i8* %65, i64 %68, i64 %71, i32 %74), !dbg !2212
  br label %if.end76, !dbg !2213

if.end76:                                         ; preds = %if.then63, %land.lhs.true58, %if.end51
  br label %for.inc, !dbg !2214

for.inc:                                          ; preds = %if.end76
  %75 = load i32, i32* %tnum, align 4, !dbg !2215
  %inc = add nsw i32 %75, 1, !dbg !2215
  store i32 %inc, i32* %tnum, align 4, !dbg !2215
  br label %for.cond, !dbg !2216, !llvm.loop !2217

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %cnum, align 4, !dbg !2219
  br label %for.cond77, !dbg !2221

for.cond77:                                       ; preds = %for.inc115, %for.end
  %76 = load i32, i32* %cnum, align 4, !dbg !2222
  %77 = load i32, i32* @max_connects, align 4, !dbg !2224
  %cmp78 = icmp slt i32 %76, %77, !dbg !2225
  br i1 %cmp78, label %for.body79, label %for.end117, !dbg !2226

for.body79:                                       ; preds = %for.cond77
  %78 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !2227
  %79 = load i32, i32* %cnum, align 4, !dbg !2229
  %idxprom80 = sext i32 %79 to i64, !dbg !2227
  %arrayidx81 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %78, i64 %idxprom80, !dbg !2227
  store %struct.connecttab* %arrayidx81, %struct.connecttab** %c, align 8, !dbg !2230
  %80 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2231
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %80, i32 0, i32 0, !dbg !2233
  %81 = load i32, i32* %conn_state, align 8, !dbg !2233
  %cmp82 = icmp eq i32 %81, 2, !dbg !2234
  br i1 %cmp82, label %if.then85, label %lor.lhs.false, !dbg !2235

lor.lhs.false:                                    ; preds = %for.body79
  %82 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2236
  %conn_state83 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %82, i32 0, i32 0, !dbg !2237
  %83 = load i32, i32* %conn_state83, align 8, !dbg !2237
  %cmp84 = icmp eq i32 %83, 3, !dbg !2238
  br i1 %cmp84, label %if.then85, label %if.end114, !dbg !2239

if.then85:                                        ; preds = %lor.lhs.false, %for.body79
  %84 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2240
  %max_limit86 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %84, i32 0, i32 5, !dbg !2242
  store i64 -1, i64* %max_limit86, align 8, !dbg !2243
  store i32 0, i32* %tind, align 4, !dbg !2244
  br label %for.cond87, !dbg !2246

for.cond87:                                       ; preds = %for.inc111, %if.then85
  %85 = load i32, i32* %tind, align 4, !dbg !2247
  %86 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2249
  %numtnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %86, i32 0, i32 4, !dbg !2250
  %87 = load i32, i32* %numtnums, align 8, !dbg !2250
  %cmp88 = icmp slt i32 %85, %87, !dbg !2251
  br i1 %cmp88, label %for.body89, label %for.end113, !dbg !2252

for.body89:                                       ; preds = %for.cond87
  %88 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2253
  %tnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %88, i32 0, i32 3, !dbg !2255
  %89 = load i32, i32* %tind, align 4, !dbg !2256
  %idxprom90 = sext i32 %89 to i64, !dbg !2253
  %arrayidx91 = getelementptr inbounds [10 x i32], [10 x i32]* %tnums, i64 0, i64 %idxprom90, !dbg !2253
  %90 = load i32, i32* %arrayidx91, align 4, !dbg !2253
  store i32 %90, i32* %tnum, align 4, !dbg !2257
  %91 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2258
  %92 = load i32, i32* %tnum, align 4, !dbg !2259
  %idxprom92 = sext i32 %92 to i64, !dbg !2258
  %arrayidx93 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %91, i64 %idxprom92, !dbg !2258
  %max_limit94 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx93, i32 0, i32 1, !dbg !2260
  %93 = load i64, i64* %max_limit94, align 8, !dbg !2260
  %94 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2261
  %95 = load i32, i32* %tnum, align 4, !dbg !2262
  %idxprom95 = sext i32 %95 to i64, !dbg !2261
  %arrayidx96 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %94, i64 %idxprom95, !dbg !2261
  %num_sending97 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx96, i32 0, i32 5, !dbg !2263
  %96 = load i32, i32* %num_sending97, align 8, !dbg !2263
  %conv = sext i32 %96 to i64, !dbg !2261
  %div98 = sdiv i64 %93, %conv, !dbg !2264
  store i64 %div98, i64* %l, align 8, !dbg !2265
  %97 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2266
  %max_limit99 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %97, i32 0, i32 5, !dbg !2268
  %98 = load i64, i64* %max_limit99, align 8, !dbg !2268
  %cmp100 = icmp eq i64 %98, -1, !dbg !2269
  br i1 %cmp100, label %if.then102, label %if.else104, !dbg !2270

if.then102:                                       ; preds = %for.body89
  %99 = load i64, i64* %l, align 8, !dbg !2271
  %100 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2272
  %max_limit103 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %100, i32 0, i32 5, !dbg !2273
  store i64 %99, i64* %max_limit103, align 8, !dbg !2274
  br label %if.end110, !dbg !2272

if.else104:                                       ; preds = %for.body89
  %101 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2275
  %max_limit105 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %101, i32 0, i32 5, !dbg !2275
  %102 = load i64, i64* %max_limit105, align 8, !dbg !2275
  %103 = load i64, i64* %l, align 8, !dbg !2275
  %cmp106 = icmp slt i64 %102, %103, !dbg !2275
  br i1 %cmp106, label %cond.true, label %cond.false, !dbg !2275

cond.true:                                        ; preds = %if.else104
  %104 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2275
  %max_limit108 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %104, i32 0, i32 5, !dbg !2275
  %105 = load i64, i64* %max_limit108, align 8, !dbg !2275
  br label %cond.end, !dbg !2275

cond.false:                                       ; preds = %if.else104
  %106 = load i64, i64* %l, align 8, !dbg !2275
  br label %cond.end, !dbg !2275

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %105, %cond.true ], [ %106, %cond.false ], !dbg !2275
  %107 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2276
  %max_limit109 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %107, i32 0, i32 5, !dbg !2277
  store i64 %cond, i64* %max_limit109, align 8, !dbg !2278
  br label %if.end110

if.end110:                                        ; preds = %cond.end, %if.then102
  br label %for.inc111, !dbg !2279

for.inc111:                                       ; preds = %if.end110
  %108 = load i32, i32* %tind, align 4, !dbg !2280
  %inc112 = add nsw i32 %108, 1, !dbg !2280
  store i32 %inc112, i32* %tind, align 4, !dbg !2280
  br label %for.cond87, !dbg !2281, !llvm.loop !2282

for.end113:                                       ; preds = %for.cond87
  br label %if.end114, !dbg !2284

if.end114:                                        ; preds = %for.end113, %lor.lhs.false
  br label %for.inc115, !dbg !2285

for.inc115:                                       ; preds = %if.end114
  %109 = load i32, i32* %cnum, align 4, !dbg !2286
  %inc116 = add nsw i32 %109, 1, !dbg !2286
  store i32 %inc116, i32* %cnum, align 4, !dbg !2286
  br label %for.cond77, !dbg !2287, !llvm.loop !2288

for.end117:                                       ; preds = %for.cond77
  ret void, !dbg !2290
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @show_stats(i8* %client_data.coerce, %struct.timeval* %nowP) #0 !dbg !2291 {
entry:
  %client_data = alloca %union.ClientData, align 8
  %nowP.addr = alloca %struct.timeval*, align 8
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0
  store i8* %client_data.coerce, i8** %coerce.dive, align 8
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2292, metadata !DIExpression()), !dbg !2293
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !2294, metadata !DIExpression()), !dbg !2295
  %0 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !2296
  call void @logstats(%struct.timeval* %0), !dbg !2297
  ret void, !dbg !2298
}

declare i64 @time(i64*) #3

declare i32 @setgroups(i32, i32*) #3

declare i32 @setgid(i32) #3

declare i32 @initgroups(i8*, i32) #3

declare i32 @setlogin(i8*) #3

declare i32 @setuid(i32) #3

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #7

declare void @fdwatch_add_fd(i32, i8*, i32) #3

declare i32 @gettimeofday(%struct.timeval*, i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @re_open_logfile() #0 !dbg !2299 {
entry:
  %logfp = alloca %struct.__sFILE*, align 8
  call void @llvm.dbg.declare(metadata %struct.__sFILE** %logfp, metadata !2302, metadata !DIExpression()), !dbg !2303
  %0 = load i32, i32* @no_log, align 4, !dbg !2304
  %tobool = icmp ne i32 %0, 0, !dbg !2304
  br i1 %tobool, label %if.then, label %lor.lhs.false, !dbg !2306

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !2307
  %cmp = icmp eq %struct.httpd_server* %1, null, !dbg !2308
  br i1 %cmp, label %if.then, label %if.end, !dbg !2309

if.then:                                          ; preds = %lor.lhs.false, %entry
  br label %if.end10, !dbg !2310

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i8*, i8** @logfile, align 8, !dbg !2311
  %cmp1 = icmp ne i8* %2, null, !dbg !2313
  br i1 %cmp1, label %land.lhs.true, label %if.end10, !dbg !2314

land.lhs.true:                                    ; preds = %if.end
  %3 = load i8*, i8** @logfile, align 8, !dbg !2315
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.7, i64 0, i64 0)), !dbg !2316
  %cmp2 = icmp ne i32 %call, 0, !dbg !2317
  br i1 %cmp2, label %if.then3, label %if.end10, !dbg !2318

if.then3:                                         ; preds = %land.lhs.true
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.46, i64 0, i64 0)), !dbg !2319
  %4 = load i8*, i8** @logfile, align 8, !dbg !2321
  %call4 = call %struct.__sFILE* @"\01_fopen"(i8* %4, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.8, i64 0, i64 0)), !dbg !2322
  store %struct.__sFILE* %call4, %struct.__sFILE** %logfp, align 8, !dbg !2323
  %5 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !2324
  %cmp5 = icmp eq %struct.__sFILE* %5, null, !dbg !2326
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2327

if.then6:                                         ; preds = %if.then3
  %6 = load i8*, i8** @logfile, align 8, !dbg !2328
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.47, i64 0, i64 0), i8* %6), !dbg !2330
  br label %if.end10, !dbg !2331

if.end7:                                          ; preds = %if.then3
  %7 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !2332
  %call8 = call i32 @fileno(%struct.__sFILE* %7), !dbg !2333
  %call9 = call i32 (i32, i32, ...) @"\01_fcntl"(i32 %call8, i32 2, i32 1), !dbg !2334
  %8 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !2335
  %9 = load %struct.__sFILE*, %struct.__sFILE** %logfp, align 8, !dbg !2336
  call void @httpd_set_logfp(%struct.httpd_server* %8, %struct.__sFILE* %9), !dbg !2337
  br label %if.end10, !dbg !2338

if.end10:                                         ; preds = %if.then, %if.then6, %if.end7, %land.lhs.true, %if.end
  ret void, !dbg !2339
}

declare i32 @fdwatch(i64) #3

declare i64 @tmr_mstimeout(%struct.timeval*) #3

declare i32* @__error() #3

declare void @tmr_run(%struct.timeval*) #3

declare i32 @fdwatch_check_fd(i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal i32 @handle_newconnect(%struct.timeval* %tvP, i32 %listen_fd) #0 !dbg !2340 {
entry:
  %retval = alloca i32, align 4
  %tvP.addr = alloca %struct.timeval*, align 8
  %listen_fd.addr = alloca i32, align 4
  %c = alloca %struct.connecttab*, align 8
  %client_data = alloca %union.ClientData, align 8
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !2343, metadata !DIExpression()), !dbg !2344
  store i32 %listen_fd, i32* %listen_fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %listen_fd.addr, metadata !2345, metadata !DIExpression()), !dbg !2346
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c, metadata !2347, metadata !DIExpression()), !dbg !2348
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2349, metadata !DIExpression()), !dbg !2350
  br label %for.cond, !dbg !2351

for.cond:                                         ; preds = %if.end28, %entry
  %0 = load i32, i32* @num_connects, align 4, !dbg !2352
  %1 = load i32, i32* @max_connects, align 4, !dbg !2357
  %cmp = icmp sge i32 %0, %1, !dbg !2358
  br i1 %cmp, label %if.then, label %if.end, !dbg !2359

if.then:                                          ; preds = %for.cond
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 4, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.120, i64 0, i64 0)), !dbg !2360
  %2 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2362
  call void @tmr_run(%struct.timeval* %2), !dbg !2363
  store i32 0, i32* %retval, align 4, !dbg !2364
  br label %return, !dbg !2364

if.end:                                           ; preds = %for.cond
  %3 = load i32, i32* @first_free_connect, align 4, !dbg !2365
  %cmp1 = icmp eq i32 %3, -1, !dbg !2367
  br i1 %cmp1, label %if.then3, label %lor.lhs.false, !dbg !2368

lor.lhs.false:                                    ; preds = %if.end
  %4 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !2369
  %5 = load i32, i32* @first_free_connect, align 4, !dbg !2370
  %idxprom = sext i32 %5 to i64, !dbg !2369
  %arrayidx = getelementptr inbounds %struct.connecttab, %struct.connecttab* %4, i64 %idxprom, !dbg !2369
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx, i32 0, i32 0, !dbg !2371
  %6 = load i32, i32* %conn_state, align 8, !dbg !2371
  %cmp2 = icmp ne i32 %6, 0, !dbg !2372
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2373

if.then3:                                         ; preds = %lor.lhs.false, %if.end
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.121, i64 0, i64 0)), !dbg !2374
  call void @exit(i32 1) #11, !dbg !2376
  unreachable, !dbg !2376

if.end4:                                          ; preds = %lor.lhs.false
  %7 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !2377
  %8 = load i32, i32* @first_free_connect, align 4, !dbg !2378
  %idxprom5 = sext i32 %8 to i64, !dbg !2377
  %arrayidx6 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %7, i64 %idxprom5, !dbg !2377
  store %struct.connecttab* %arrayidx6, %struct.connecttab** %c, align 8, !dbg !2379
  %9 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2380
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %9, i32 0, i32 2, !dbg !2382
  %10 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2382
  %cmp7 = icmp eq %struct.httpd_conn* %10, null, !dbg !2383
  br i1 %cmp7, label %if.then8, label %if.end15, !dbg !2384

if.then8:                                         ; preds = %if.end4
  %call = call i8* @malloc(i64 720) #14, !dbg !2385
  %11 = bitcast i8* %call to %struct.httpd_conn*, !dbg !2385
  %12 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2387
  %hc9 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %12, i32 0, i32 2, !dbg !2388
  store %struct.httpd_conn* %11, %struct.httpd_conn** %hc9, align 8, !dbg !2389
  %13 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2390
  %hc10 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %13, i32 0, i32 2, !dbg !2392
  %14 = load %struct.httpd_conn*, %struct.httpd_conn** %hc10, align 8, !dbg !2392
  %cmp11 = icmp eq %struct.httpd_conn* %14, null, !dbg !2393
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !2394

if.then12:                                        ; preds = %if.then8
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.122, i64 0, i64 0)), !dbg !2395
  call void @exit(i32 1) #11, !dbg !2397
  unreachable, !dbg !2397

if.end13:                                         ; preds = %if.then8
  %15 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2398
  %hc14 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %15, i32 0, i32 2, !dbg !2399
  %16 = load %struct.httpd_conn*, %struct.httpd_conn** %hc14, align 8, !dbg !2399
  %initialized = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %16, i32 0, i32 0, !dbg !2400
  store i32 0, i32* %initialized, align 8, !dbg !2401
  %17 = load i32, i32* @httpd_conn_count, align 4, !dbg !2402
  %inc = add nsw i32 %17, 1, !dbg !2402
  store i32 %inc, i32* @httpd_conn_count, align 4, !dbg !2402
  br label %if.end15, !dbg !2403

if.end15:                                         ; preds = %if.end13, %if.end4
  %18 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !2404
  %19 = load i32, i32* %listen_fd.addr, align 4, !dbg !2405
  %20 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2406
  %hc16 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %20, i32 0, i32 2, !dbg !2407
  %21 = load %struct.httpd_conn*, %struct.httpd_conn** %hc16, align 8, !dbg !2407
  %call17 = call i32 @httpd_get_conn(%struct.httpd_server* %18, i32 %19, %struct.httpd_conn* %21), !dbg !2408
  switch i32 %call17, label %sw.epilog [
    i32 0, label %sw.bb
    i32 2, label %sw.bb18
  ], !dbg !2409

sw.bb:                                            ; preds = %if.end15
  %22 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2410
  call void @tmr_run(%struct.timeval* %22), !dbg !2412
  store i32 0, i32* %retval, align 4, !dbg !2413
  br label %return, !dbg !2413

sw.bb18:                                          ; preds = %if.end15
  store i32 1, i32* %retval, align 4, !dbg !2414
  br label %return, !dbg !2414

sw.epilog:                                        ; preds = %if.end15
  %23 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2415
  %conn_state19 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %23, i32 0, i32 0, !dbg !2416
  store i32 1, i32* %conn_state19, align 8, !dbg !2417
  %24 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2418
  %next_free_connect = getelementptr inbounds %struct.connecttab, %struct.connecttab* %24, i32 0, i32 1, !dbg !2419
  %25 = load i32, i32* %next_free_connect, align 4, !dbg !2419
  store i32 %25, i32* @first_free_connect, align 4, !dbg !2420
  %26 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2421
  %next_free_connect20 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %26, i32 0, i32 1, !dbg !2422
  store i32 -1, i32* %next_free_connect20, align 4, !dbg !2423
  %27 = load i32, i32* @num_connects, align 4, !dbg !2424
  %inc21 = add nsw i32 %27, 1, !dbg !2424
  store i32 %inc21, i32* @num_connects, align 4, !dbg !2424
  %28 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2425
  %29 = bitcast %struct.connecttab* %28 to i8*, !dbg !2425
  %p = bitcast %union.ClientData* %client_data to i8**, !dbg !2426
  store i8* %29, i8** %p, align 8, !dbg !2427
  %30 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2428
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %30, i32 0, i32 0, !dbg !2429
  %31 = load i64, i64* %tv_sec, align 8, !dbg !2429
  %32 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2430
  %active_at = getelementptr inbounds %struct.connecttab, %struct.connecttab* %32, i32 0, i32 8, !dbg !2431
  store i64 %31, i64* %active_at, align 8, !dbg !2432
  %33 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2433
  %wakeup_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %33, i32 0, i32 9, !dbg !2434
  store %struct.TimerStruct* null, %struct.TimerStruct** %wakeup_timer, align 8, !dbg !2435
  %34 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2436
  %linger_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %34, i32 0, i32 10, !dbg !2437
  store %struct.TimerStruct* null, %struct.TimerStruct** %linger_timer, align 8, !dbg !2438
  %35 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2439
  %next_byte_index = getelementptr inbounds %struct.connecttab, %struct.connecttab* %35, i32 0, i32 14, !dbg !2440
  store i64 0, i64* %next_byte_index, align 8, !dbg !2441
  %36 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2442
  %numtnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %36, i32 0, i32 4, !dbg !2443
  store i32 0, i32* %numtnums, align 8, !dbg !2444
  %37 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2445
  %hc22 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %37, i32 0, i32 2, !dbg !2446
  %38 = load %struct.httpd_conn*, %struct.httpd_conn** %hc22, align 8, !dbg !2446
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %38, i32 0, i32 60, !dbg !2447
  %39 = load i32, i32* %conn_fd, align 8, !dbg !2447
  call void @httpd_set_ndelay(i32 %39), !dbg !2448
  %40 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2449
  %hc23 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %40, i32 0, i32 2, !dbg !2450
  %41 = load %struct.httpd_conn*, %struct.httpd_conn** %hc23, align 8, !dbg !2450
  %conn_fd24 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %41, i32 0, i32 60, !dbg !2451
  %42 = load i32, i32* %conn_fd24, align 8, !dbg !2451
  %43 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !2452
  %44 = bitcast %struct.connecttab* %43 to i8*, !dbg !2452
  call void @fdwatch_add_fd(i32 %42, i8* %44, i32 0), !dbg !2453
  %45 = load i64, i64* @stats_connections, align 8, !dbg !2454
  %inc25 = add nsw i64 %45, 1, !dbg !2454
  store i64 %inc25, i64* @stats_connections, align 8, !dbg !2454
  %46 = load i32, i32* @num_connects, align 4, !dbg !2455
  %47 = load i32, i32* @stats_simultaneous, align 4, !dbg !2457
  %cmp26 = icmp sgt i32 %46, %47, !dbg !2458
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !2459

if.then27:                                        ; preds = %sw.epilog
  %48 = load i32, i32* @num_connects, align 4, !dbg !2460
  store i32 %48, i32* @stats_simultaneous, align 4, !dbg !2461
  br label %if.end28, !dbg !2462

if.end28:                                         ; preds = %if.then27, %sw.epilog
  br label %for.cond, !dbg !2463, !llvm.loop !2464

return:                                           ; preds = %sw.bb18, %sw.bb, %if.then
  %49 = load i32, i32* %retval, align 4, !dbg !2467
  ret i32 %49, !dbg !2467
}

declare i8* @fdwatch_get_next_client_data() #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @clear_connection(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !2468 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  %client_data = alloca %union.ClientData, align 8
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !2471, metadata !DIExpression()), !dbg !2472
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !2473, metadata !DIExpression()), !dbg !2474
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2475, metadata !DIExpression()), !dbg !2476
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2477
  %wakeup_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 9, !dbg !2479
  %1 = load %struct.TimerStruct*, %struct.TimerStruct** %wakeup_timer, align 8, !dbg !2479
  %cmp = icmp ne %struct.TimerStruct* %1, null, !dbg !2480
  br i1 %cmp, label %if.then, label %if.end, !dbg !2481

if.then:                                          ; preds = %entry
  %2 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2482
  %wakeup_timer1 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i32 0, i32 9, !dbg !2484
  %3 = load %struct.TimerStruct*, %struct.TimerStruct** %wakeup_timer1, align 8, !dbg !2484
  call void @tmr_cancel(%struct.TimerStruct* %3), !dbg !2485
  %4 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2486
  %wakeup_timer2 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %4, i32 0, i32 9, !dbg !2487
  store %struct.TimerStruct* null, %struct.TimerStruct** %wakeup_timer2, align 8, !dbg !2488
  br label %if.end, !dbg !2489

if.end:                                           ; preds = %if.then, %entry
  %5 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2490
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %5, i32 0, i32 0, !dbg !2492
  %6 = load i32, i32* %conn_state, align 8, !dbg !2492
  %cmp3 = icmp eq i32 %6, 4, !dbg !2493
  br i1 %cmp3, label %if.then4, label %if.end6, !dbg !2494

if.then4:                                         ; preds = %if.end
  %7 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2495
  %linger_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %7, i32 0, i32 10, !dbg !2497
  %8 = load %struct.TimerStruct*, %struct.TimerStruct** %linger_timer, align 8, !dbg !2497
  call void @tmr_cancel(%struct.TimerStruct* %8), !dbg !2498
  %9 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2499
  %linger_timer5 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %9, i32 0, i32 10, !dbg !2500
  store %struct.TimerStruct* null, %struct.TimerStruct** %linger_timer5, align 8, !dbg !2501
  %10 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2502
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %10, i32 0, i32 2, !dbg !2503
  %11 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2503
  %should_linger = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %11, i32 0, i32 58, !dbg !2504
  store i32 0, i32* %should_linger, align 4, !dbg !2505
  br label %if.end6, !dbg !2506

if.end6:                                          ; preds = %if.then4, %if.end
  %12 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2507
  %hc7 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %12, i32 0, i32 2, !dbg !2509
  %13 = load %struct.httpd_conn*, %struct.httpd_conn** %hc7, align 8, !dbg !2509
  %should_linger8 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %13, i32 0, i32 58, !dbg !2510
  %14 = load i32, i32* %should_linger8, align 4, !dbg !2510
  %tobool = icmp ne i32 %14, 0, !dbg !2507
  br i1 %tobool, label %if.then9, label %if.else, !dbg !2511

if.then9:                                         ; preds = %if.end6
  %15 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2512
  %conn_state10 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %15, i32 0, i32 0, !dbg !2515
  %16 = load i32, i32* %conn_state10, align 8, !dbg !2515
  %cmp11 = icmp ne i32 %16, 3, !dbg !2516
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !2517

if.then12:                                        ; preds = %if.then9
  %17 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2518
  %hc13 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %17, i32 0, i32 2, !dbg !2519
  %18 = load %struct.httpd_conn*, %struct.httpd_conn** %hc13, align 8, !dbg !2519
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %18, i32 0, i32 60, !dbg !2520
  %19 = load i32, i32* %conn_fd, align 8, !dbg !2520
  call void @fdwatch_del_fd(i32 %19), !dbg !2521
  br label %if.end14, !dbg !2521

if.end14:                                         ; preds = %if.then12, %if.then9
  %20 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2522
  %conn_state15 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %20, i32 0, i32 0, !dbg !2523
  store i32 4, i32* %conn_state15, align 8, !dbg !2524
  %21 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2525
  %hc16 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %21, i32 0, i32 2, !dbg !2526
  %22 = load %struct.httpd_conn*, %struct.httpd_conn** %hc16, align 8, !dbg !2526
  %conn_fd17 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %22, i32 0, i32 60, !dbg !2527
  %23 = load i32, i32* %conn_fd17, align 8, !dbg !2527
  %call = call i32 @shutdown(i32 %23, i32 1), !dbg !2528
  %24 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2529
  %hc18 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %24, i32 0, i32 2, !dbg !2530
  %25 = load %struct.httpd_conn*, %struct.httpd_conn** %hc18, align 8, !dbg !2530
  %conn_fd19 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %25, i32 0, i32 60, !dbg !2531
  %26 = load i32, i32* %conn_fd19, align 8, !dbg !2531
  %27 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2532
  %28 = bitcast %struct.connecttab* %27 to i8*, !dbg !2532
  call void @fdwatch_add_fd(i32 %26, i8* %28, i32 0), !dbg !2533
  %29 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2534
  %30 = bitcast %struct.connecttab* %29 to i8*, !dbg !2534
  %p = bitcast %union.ClientData* %client_data to i8**, !dbg !2535
  store i8* %30, i8** %p, align 8, !dbg !2536
  %31 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2537
  %linger_timer20 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %31, i32 0, i32 10, !dbg !2539
  %32 = load %struct.TimerStruct*, %struct.TimerStruct** %linger_timer20, align 8, !dbg !2539
  %cmp21 = icmp ne %struct.TimerStruct* %32, null, !dbg !2540
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !2541

if.then22:                                        ; preds = %if.end14
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.130, i64 0, i64 0)), !dbg !2542
  br label %if.end23, !dbg !2542

if.end23:                                         ; preds = %if.then22, %if.end14
  %33 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2543
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0, !dbg !2544
  %34 = load i8*, i8** %coerce.dive, align 8, !dbg !2544
  %call24 = call %struct.TimerStruct* @tmr_create(%struct.timeval* %33, void (i8*, %struct.timeval*)* @linger_clear_connection, i8* %34, i64 500, i32 0), !dbg !2544
  %35 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2545
  %linger_timer25 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %35, i32 0, i32 10, !dbg !2546
  store %struct.TimerStruct* %call24, %struct.TimerStruct** %linger_timer25, align 8, !dbg !2547
  %36 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2548
  %linger_timer26 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %36, i32 0, i32 10, !dbg !2550
  %37 = load %struct.TimerStruct*, %struct.TimerStruct** %linger_timer26, align 8, !dbg !2550
  %cmp27 = icmp eq %struct.TimerStruct* %37, null, !dbg !2551
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !2552

if.then28:                                        ; preds = %if.end23
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.131, i64 0, i64 0)), !dbg !2553
  call void @exit(i32 1) #11, !dbg !2555
  unreachable, !dbg !2555

if.end29:                                         ; preds = %if.end23
  br label %if.end30, !dbg !2556

if.else:                                          ; preds = %if.end6
  %38 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2557
  %39 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2558
  call void @really_clear_connection(%struct.connecttab* %38, %struct.timeval* %39), !dbg !2559
  br label %if.end30

if.end30:                                         ; preds = %if.else, %if.end29
  ret void, !dbg !2560
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_read(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !2561 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  %sz = alloca i32, align 4
  %client_data = alloca %union.ClientData, align 8
  %hc = alloca %struct.httpd_conn*, align 8
  %tind = alloca i32, align 4
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !2562, metadata !DIExpression()), !dbg !2563
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !2564, metadata !DIExpression()), !dbg !2565
  call void @llvm.dbg.declare(metadata i32* %sz, metadata !2566, metadata !DIExpression()), !dbg !2567
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2568, metadata !DIExpression()), !dbg !2569
  call void @llvm.dbg.declare(metadata %struct.httpd_conn** %hc, metadata !2570, metadata !DIExpression()), !dbg !2571
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2572
  %hc1 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 2, !dbg !2573
  %1 = load %struct.httpd_conn*, %struct.httpd_conn** %hc1, align 8, !dbg !2573
  store %struct.httpd_conn* %1, %struct.httpd_conn** %hc, align 8, !dbg !2571
  %2 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2574
  %read_idx = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %2, i32 0, i32 5, !dbg !2576
  %3 = load i64, i64* %read_idx, align 8, !dbg !2576
  %4 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2577
  %read_size = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %4, i32 0, i32 4, !dbg !2578
  %5 = load i64, i64* %read_size, align 8, !dbg !2578
  %cmp = icmp uge i64 %3, %5, !dbg !2579
  br i1 %cmp, label %if.then, label %if.end7, !dbg !2580

if.then:                                          ; preds = %entry
  %6 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2581
  %read_size2 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %6, i32 0, i32 4, !dbg !2584
  %7 = load i64, i64* %read_size2, align 8, !dbg !2584
  %cmp3 = icmp ugt i64 %7, 5000, !dbg !2585
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2586

if.then4:                                         ; preds = %if.then
  %8 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2587
  %9 = load i8*, i8** @httpd_err400title, align 8, !dbg !2589
  %10 = load i8*, i8** @httpd_err400form, align 8, !dbg !2590
  call void @httpd_send_err(%struct.httpd_conn* %8, i32 400, i8* %9, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8* %10, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0)), !dbg !2591
  %11 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2592
  %12 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2593
  call void @finish_connection(%struct.connecttab* %11, %struct.timeval* %12), !dbg !2594
  br label %return, !dbg !2595

if.end:                                           ; preds = %if.then
  %13 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2596
  %read_buf = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %13, i32 0, i32 3, !dbg !2597
  %14 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2598
  %read_size5 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %14, i32 0, i32 4, !dbg !2599
  %15 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2600
  %read_size6 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %15, i32 0, i32 4, !dbg !2601
  %16 = load i64, i64* %read_size6, align 8, !dbg !2601
  %add = add i64 %16, 1000, !dbg !2602
  call void @httpd_realloc_str(i8** %read_buf, i64* %read_size5, i64 %add), !dbg !2603
  br label %if.end7, !dbg !2604

if.end7:                                          ; preds = %if.end, %entry
  %17 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2605
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %17, i32 0, i32 60, !dbg !2606
  %18 = load i32, i32* %conn_fd, align 8, !dbg !2606
  %19 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2607
  %read_buf8 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %19, i32 0, i32 3, !dbg !2608
  %20 = load i8*, i8** %read_buf8, align 8, !dbg !2608
  %21 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2609
  %read_idx9 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %21, i32 0, i32 5, !dbg !2610
  %22 = load i64, i64* %read_idx9, align 8, !dbg !2610
  %arrayidx = getelementptr inbounds i8, i8* %20, i64 %22, !dbg !2607
  %23 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2611
  %read_size10 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %23, i32 0, i32 4, !dbg !2612
  %24 = load i64, i64* %read_size10, align 8, !dbg !2612
  %25 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2613
  %read_idx11 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %25, i32 0, i32 5, !dbg !2614
  %26 = load i64, i64* %read_idx11, align 8, !dbg !2614
  %sub = sub i64 %24, %26, !dbg !2615
  %call = call i64 @"\01_read"(i32 %18, i8* %arrayidx, i64 %sub), !dbg !2616
  %conv = trunc i64 %call to i32, !dbg !2616
  store i32 %conv, i32* %sz, align 4, !dbg !2617
  %27 = load i32, i32* %sz, align 4, !dbg !2618
  %cmp12 = icmp eq i32 %27, 0, !dbg !2620
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !2621

if.then14:                                        ; preds = %if.end7
  %28 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2622
  %29 = load i8*, i8** @httpd_err400title, align 8, !dbg !2624
  %30 = load i8*, i8** @httpd_err400form, align 8, !dbg !2625
  call void @httpd_send_err(%struct.httpd_conn* %28, i32 400, i8* %29, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8* %30, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0)), !dbg !2626
  %31 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2627
  %32 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2628
  call void @finish_connection(%struct.connecttab* %31, %struct.timeval* %32), !dbg !2629
  br label %return, !dbg !2630

if.end15:                                         ; preds = %if.end7
  %33 = load i32, i32* %sz, align 4, !dbg !2631
  %cmp16 = icmp slt i32 %33, 0, !dbg !2633
  br i1 %cmp16, label %if.then18, label %if.end31, !dbg !2634

if.then18:                                        ; preds = %if.end15
  %call19 = call i32* @__error(), !dbg !2635
  %34 = load i32, i32* %call19, align 4, !dbg !2635
  %cmp20 = icmp eq i32 %34, 4, !dbg !2638
  br i1 %cmp20, label %if.then29, label %lor.lhs.false, !dbg !2639

lor.lhs.false:                                    ; preds = %if.then18
  %call22 = call i32* @__error(), !dbg !2640
  %35 = load i32, i32* %call22, align 4, !dbg !2640
  %cmp23 = icmp eq i32 %35, 35, !dbg !2641
  br i1 %cmp23, label %if.then29, label %lor.lhs.false25, !dbg !2642

lor.lhs.false25:                                  ; preds = %lor.lhs.false
  %call26 = call i32* @__error(), !dbg !2643
  %36 = load i32, i32* %call26, align 4, !dbg !2643
  %cmp27 = icmp eq i32 %36, 35, !dbg !2644
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !2645

if.then29:                                        ; preds = %lor.lhs.false25, %lor.lhs.false, %if.then18
  br label %return, !dbg !2646

if.end30:                                         ; preds = %lor.lhs.false25
  %37 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2647
  %38 = load i8*, i8** @httpd_err400title, align 8, !dbg !2648
  %39 = load i8*, i8** @httpd_err400form, align 8, !dbg !2649
  call void @httpd_send_err(%struct.httpd_conn* %37, i32 400, i8* %38, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8* %39, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0)), !dbg !2650
  %40 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2651
  %41 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2652
  call void @finish_connection(%struct.connecttab* %40, %struct.timeval* %41), !dbg !2653
  br label %return, !dbg !2654

if.end31:                                         ; preds = %if.end15
  %42 = load i32, i32* %sz, align 4, !dbg !2655
  %conv32 = sext i32 %42 to i64, !dbg !2655
  %43 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2656
  %read_idx33 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %43, i32 0, i32 5, !dbg !2657
  %44 = load i64, i64* %read_idx33, align 8, !dbg !2658
  %add34 = add i64 %44, %conv32, !dbg !2658
  store i64 %add34, i64* %read_idx33, align 8, !dbg !2658
  %45 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2659
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %45, i32 0, i32 0, !dbg !2660
  %46 = load i64, i64* %tv_sec, align 8, !dbg !2660
  %47 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2661
  %active_at = getelementptr inbounds %struct.connecttab, %struct.connecttab* %47, i32 0, i32 8, !dbg !2662
  store i64 %46, i64* %active_at, align 8, !dbg !2663
  %48 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2664
  %call35 = call i32 @httpd_got_request(%struct.httpd_conn* %48), !dbg !2665
  switch i32 %call35, label %sw.epilog [
    i32 0, label %sw.bb
    i32 2, label %sw.bb36
  ], !dbg !2666

sw.bb:                                            ; preds = %if.end31
  br label %return, !dbg !2667

sw.bb36:                                          ; preds = %if.end31
  %49 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2669
  %50 = load i8*, i8** @httpd_err400title, align 8, !dbg !2670
  %51 = load i8*, i8** @httpd_err400form, align 8, !dbg !2671
  call void @httpd_send_err(%struct.httpd_conn* %49, i32 400, i8* %50, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8* %51, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0)), !dbg !2672
  %52 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2673
  %53 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2674
  call void @finish_connection(%struct.connecttab* %52, %struct.timeval* %53), !dbg !2675
  br label %return, !dbg !2676

sw.epilog:                                        ; preds = %if.end31
  %54 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2677
  %call37 = call i32 @httpd_parse_request(%struct.httpd_conn* %54), !dbg !2679
  %cmp38 = icmp slt i32 %call37, 0, !dbg !2680
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !2681

if.then40:                                        ; preds = %sw.epilog
  %55 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2682
  %56 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2684
  call void @finish_connection(%struct.connecttab* %55, %struct.timeval* %56), !dbg !2685
  br label %return, !dbg !2686

if.end41:                                         ; preds = %sw.epilog
  %57 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2687
  %call42 = call i32 @check_throttles(%struct.connecttab* %57), !dbg !2689
  %tobool = icmp ne i32 %call42, 0, !dbg !2689
  br i1 %tobool, label %if.end44, label %if.then43, !dbg !2690

if.then43:                                        ; preds = %if.end41
  %58 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2691
  %59 = load i8*, i8** @httpd_err503title, align 8, !dbg !2693
  %60 = load i8*, i8** @httpd_err503form, align 8, !dbg !2694
  %61 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2695
  %encodedurl = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %61, i32 0, i32 12, !dbg !2696
  %62 = load i8*, i8** %encodedurl, align 8, !dbg !2696
  call void @httpd_send_err(%struct.httpd_conn* %58, i32 503, i8* %59, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.50, i64 0, i64 0), i8* %60, i8* %62), !dbg !2697
  %63 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2698
  %64 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2699
  call void @finish_connection(%struct.connecttab* %63, %struct.timeval* %64), !dbg !2700
  br label %return, !dbg !2701

if.end44:                                         ; preds = %if.end41
  %65 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2702
  %66 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2704
  %call45 = call i32 @httpd_start_request(%struct.httpd_conn* %65, %struct.timeval* %66), !dbg !2705
  %cmp46 = icmp slt i32 %call45, 0, !dbg !2706
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !2707

if.then48:                                        ; preds = %if.end44
  %67 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2708
  %68 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2710
  call void @finish_connection(%struct.connecttab* %67, %struct.timeval* %68), !dbg !2711
  br label %return, !dbg !2712

if.end49:                                         ; preds = %if.end44
  %69 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2713
  %got_range = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %69, i32 0, i32 53, !dbg !2715
  %70 = load i32, i32* %got_range, align 8, !dbg !2715
  %tobool50 = icmp ne i32 %70, 0, !dbg !2713
  br i1 %tobool50, label %if.then51, label %if.else, !dbg !2716

if.then51:                                        ; preds = %if.end49
  %71 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2717
  %first_byte_index = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %71, i32 0, i32 55, !dbg !2719
  %72 = load i64, i64* %first_byte_index, align 8, !dbg !2719
  %73 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2720
  %next_byte_index = getelementptr inbounds %struct.connecttab, %struct.connecttab* %73, i32 0, i32 14, !dbg !2721
  store i64 %72, i64* %next_byte_index, align 8, !dbg !2722
  %74 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2723
  %last_byte_index = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %74, i32 0, i32 56, !dbg !2724
  %75 = load i64, i64* %last_byte_index, align 8, !dbg !2724
  %add52 = add nsw i64 %75, 1, !dbg !2725
  %76 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2726
  %end_byte_index = getelementptr inbounds %struct.connecttab, %struct.connecttab* %76, i32 0, i32 13, !dbg !2727
  store i64 %add52, i64* %end_byte_index, align 8, !dbg !2728
  br label %if.end61, !dbg !2729

if.else:                                          ; preds = %if.end49
  %77 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2730
  %bytes_to_send = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %77, i32 0, i32 10, !dbg !2732
  %78 = load i64, i64* %bytes_to_send, align 8, !dbg !2732
  %cmp53 = icmp slt i64 %78, 0, !dbg !2733
  br i1 %cmp53, label %if.then55, label %if.else57, !dbg !2734

if.then55:                                        ; preds = %if.else
  %79 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2735
  %end_byte_index56 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %79, i32 0, i32 13, !dbg !2736
  store i64 0, i64* %end_byte_index56, align 8, !dbg !2737
  br label %if.end60, !dbg !2735

if.else57:                                        ; preds = %if.else
  %80 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2738
  %bytes_to_send58 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %80, i32 0, i32 10, !dbg !2739
  %81 = load i64, i64* %bytes_to_send58, align 8, !dbg !2739
  %82 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2740
  %end_byte_index59 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %82, i32 0, i32 13, !dbg !2741
  store i64 %81, i64* %end_byte_index59, align 8, !dbg !2742
  br label %if.end60

if.end60:                                         ; preds = %if.else57, %if.then55
  br label %if.end61

if.end61:                                         ; preds = %if.end60, %if.then51
  %83 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2743
  %file_address = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %83, i32 0, i32 61, !dbg !2745
  %84 = load i8*, i8** %file_address, align 8, !dbg !2745
  %cmp62 = icmp eq i8* %84, null, !dbg !2746
  br i1 %cmp62, label %if.then64, label %if.end73, !dbg !2747

if.then64:                                        ; preds = %if.end61
  call void @llvm.dbg.declare(metadata i32* %tind, metadata !2748, metadata !DIExpression()), !dbg !2750
  store i32 0, i32* %tind, align 4, !dbg !2751
  br label %for.cond, !dbg !2753

for.cond:                                         ; preds = %for.inc, %if.then64
  %85 = load i32, i32* %tind, align 4, !dbg !2754
  %86 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2756
  %numtnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %86, i32 0, i32 4, !dbg !2757
  %87 = load i32, i32* %numtnums, align 8, !dbg !2757
  %cmp65 = icmp slt i32 %85, %87, !dbg !2758
  br i1 %cmp65, label %for.body, label %for.end, !dbg !2759

for.body:                                         ; preds = %for.cond
  %88 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2760
  %bytes_sent = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %88, i32 0, i32 11, !dbg !2761
  %89 = load i64, i64* %bytes_sent, align 8, !dbg !2761
  %90 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !2762
  %91 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2763
  %tnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %91, i32 0, i32 3, !dbg !2764
  %92 = load i32, i32* %tind, align 4, !dbg !2765
  %idxprom = sext i32 %92 to i64, !dbg !2763
  %arrayidx67 = getelementptr inbounds [10 x i32], [10 x i32]* %tnums, i64 0, i64 %idxprom, !dbg !2763
  %93 = load i32, i32* %arrayidx67, align 4, !dbg !2763
  %idxprom68 = sext i32 %93 to i64, !dbg !2762
  %arrayidx69 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %90, i64 %idxprom68, !dbg !2762
  %bytes_since_avg = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx69, i32 0, i32 4, !dbg !2766
  %94 = load i64, i64* %bytes_since_avg, align 8, !dbg !2767
  %add70 = add nsw i64 %94, %89, !dbg !2767
  store i64 %add70, i64* %bytes_since_avg, align 8, !dbg !2767
  br label %for.inc, !dbg !2762

for.inc:                                          ; preds = %for.body
  %95 = load i32, i32* %tind, align 4, !dbg !2768
  %inc = add nsw i32 %95, 1, !dbg !2768
  store i32 %inc, i32* %tind, align 4, !dbg !2768
  br label %for.cond, !dbg !2769, !llvm.loop !2770

for.end:                                          ; preds = %for.cond
  %96 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2772
  %bytes_sent71 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %96, i32 0, i32 11, !dbg !2773
  %97 = load i64, i64* %bytes_sent71, align 8, !dbg !2773
  %98 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2774
  %next_byte_index72 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %98, i32 0, i32 14, !dbg !2775
  store i64 %97, i64* %next_byte_index72, align 8, !dbg !2776
  %99 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2777
  %100 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2778
  call void @finish_connection(%struct.connecttab* %99, %struct.timeval* %100), !dbg !2779
  br label %return, !dbg !2780

if.end73:                                         ; preds = %if.end61
  %101 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2781
  %next_byte_index74 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %101, i32 0, i32 14, !dbg !2783
  %102 = load i64, i64* %next_byte_index74, align 8, !dbg !2783
  %103 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2784
  %end_byte_index75 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %103, i32 0, i32 13, !dbg !2785
  %104 = load i64, i64* %end_byte_index75, align 8, !dbg !2785
  %cmp76 = icmp sge i64 %102, %104, !dbg !2786
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !2787

if.then78:                                        ; preds = %if.end73
  %105 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2788
  %106 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2790
  call void @finish_connection(%struct.connecttab* %105, %struct.timeval* %106), !dbg !2791
  br label %return, !dbg !2792

if.end79:                                         ; preds = %if.end73
  %107 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2793
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %107, i32 0, i32 0, !dbg !2794
  store i32 2, i32* %conn_state, align 8, !dbg !2795
  %108 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2796
  %tv_sec80 = getelementptr inbounds %struct.timeval, %struct.timeval* %108, i32 0, i32 0, !dbg !2797
  %109 = load i64, i64* %tv_sec80, align 8, !dbg !2797
  %110 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2798
  %started_at = getelementptr inbounds %struct.connecttab, %struct.connecttab* %110, i32 0, i32 7, !dbg !2799
  store i64 %109, i64* %started_at, align 8, !dbg !2800
  %111 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2801
  %wouldblock_delay = getelementptr inbounds %struct.connecttab, %struct.connecttab* %111, i32 0, i32 11, !dbg !2802
  store i64 0, i64* %wouldblock_delay, align 8, !dbg !2803
  %112 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2804
  %113 = bitcast %struct.connecttab* %112 to i8*, !dbg !2804
  %p = bitcast %union.ClientData* %client_data to i8**, !dbg !2805
  store i8* %113, i8** %p, align 8, !dbg !2806
  %114 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2807
  %conn_fd81 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %114, i32 0, i32 60, !dbg !2808
  %115 = load i32, i32* %conn_fd81, align 8, !dbg !2808
  call void @fdwatch_del_fd(i32 %115), !dbg !2809
  %116 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2810
  %conn_fd82 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %116, i32 0, i32 60, !dbg !2811
  %117 = load i32, i32* %conn_fd82, align 8, !dbg !2811
  %118 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2812
  %119 = bitcast %struct.connecttab* %118 to i8*, !dbg !2812
  call void @fdwatch_add_fd(i32 %117, i8* %119, i32 1), !dbg !2813
  br label %return, !dbg !2814

return:                                           ; preds = %if.end79, %if.then78, %for.end, %if.then48, %if.then43, %if.then40, %sw.bb36, %sw.bb, %if.end30, %if.then29, %if.then14, %if.then4
  ret void, !dbg !2814
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_send(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !2815 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  %max_bytes = alloca i64, align 8
  %sz = alloca i32, align 4
  %coast = alloca i32, align 4
  %client_data = alloca %union.ClientData, align 8
  %elapsed = alloca i64, align 8
  %hc = alloca %struct.httpd_conn*, align 8
  %tind = alloca i32, align 4
  %iv = alloca [2 x %struct.iovec], align 16
  %newlen = alloca i32, align 4
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !2816, metadata !DIExpression()), !dbg !2817
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !2818, metadata !DIExpression()), !dbg !2819
  call void @llvm.dbg.declare(metadata i64* %max_bytes, metadata !2820, metadata !DIExpression()), !dbg !2821
  call void @llvm.dbg.declare(metadata i32* %sz, metadata !2822, metadata !DIExpression()), !dbg !2823
  call void @llvm.dbg.declare(metadata i32* %coast, metadata !2824, metadata !DIExpression()), !dbg !2825
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !2826, metadata !DIExpression()), !dbg !2827
  call void @llvm.dbg.declare(metadata i64* %elapsed, metadata !2828, metadata !DIExpression()), !dbg !2829
  call void @llvm.dbg.declare(metadata %struct.httpd_conn** %hc, metadata !2830, metadata !DIExpression()), !dbg !2831
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2832
  %hc1 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 2, !dbg !2833
  %1 = load %struct.httpd_conn*, %struct.httpd_conn** %hc1, align 8, !dbg !2833
  store %struct.httpd_conn* %1, %struct.httpd_conn** %hc, align 8, !dbg !2831
  call void @llvm.dbg.declare(metadata i32* %tind, metadata !2834, metadata !DIExpression()), !dbg !2835
  %2 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2836
  %max_limit = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i32 0, i32 5, !dbg !2838
  %3 = load i64, i64* %max_limit, align 8, !dbg !2838
  %cmp = icmp eq i64 %3, -1, !dbg !2839
  br i1 %cmp, label %if.then, label %if.else, !dbg !2840

if.then:                                          ; preds = %entry
  store i64 1000000000, i64* %max_bytes, align 8, !dbg !2841
  br label %if.end, !dbg !2842

if.else:                                          ; preds = %entry
  %4 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2843
  %max_limit2 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %4, i32 0, i32 5, !dbg !2844
  %5 = load i64, i64* %max_limit2, align 8, !dbg !2844
  %div = sdiv i64 %5, 4, !dbg !2845
  store i64 %div, i64* %max_bytes, align 8, !dbg !2846
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %6 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2847
  %responselen = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %6, i32 0, i32 45, !dbg !2849
  %7 = load i64, i64* %responselen, align 8, !dbg !2849
  %cmp3 = icmp eq i64 %7, 0, !dbg !2850
  br i1 %cmp3, label %if.then4, label %if.else10, !dbg !2851

if.then4:                                         ; preds = %if.end
  %8 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2852
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %8, i32 0, i32 60, !dbg !2854
  %9 = load i32, i32* %conn_fd, align 8, !dbg !2854
  %10 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2855
  %file_address = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %10, i32 0, i32 61, !dbg !2856
  %11 = load i8*, i8** %file_address, align 8, !dbg !2856
  %12 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2857
  %next_byte_index = getelementptr inbounds %struct.connecttab, %struct.connecttab* %12, i32 0, i32 14, !dbg !2858
  %13 = load i64, i64* %next_byte_index, align 8, !dbg !2858
  %arrayidx = getelementptr inbounds i8, i8* %11, i64 %13, !dbg !2855
  %14 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2859
  %end_byte_index = getelementptr inbounds %struct.connecttab, %struct.connecttab* %14, i32 0, i32 13, !dbg !2859
  %15 = load i64, i64* %end_byte_index, align 8, !dbg !2859
  %16 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2859
  %next_byte_index5 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %16, i32 0, i32 14, !dbg !2859
  %17 = load i64, i64* %next_byte_index5, align 8, !dbg !2859
  %sub = sub nsw i64 %15, %17, !dbg !2859
  %18 = load i64, i64* %max_bytes, align 8, !dbg !2859
  %cmp6 = icmp ult i64 %sub, %18, !dbg !2859
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !2859

cond.true:                                        ; preds = %if.then4
  %19 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2859
  %end_byte_index7 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %19, i32 0, i32 13, !dbg !2859
  %20 = load i64, i64* %end_byte_index7, align 8, !dbg !2859
  %21 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2859
  %next_byte_index8 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %21, i32 0, i32 14, !dbg !2859
  %22 = load i64, i64* %next_byte_index8, align 8, !dbg !2859
  %sub9 = sub nsw i64 %20, %22, !dbg !2859
  br label %cond.end, !dbg !2859

cond.false:                                       ; preds = %if.then4
  %23 = load i64, i64* %max_bytes, align 8, !dbg !2859
  br label %cond.end, !dbg !2859

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %sub9, %cond.true ], [ %23, %cond.false ], !dbg !2859
  %call = call i64 @"\01_write"(i32 %9, i8* %arrayidx, i64 %cond), !dbg !2860
  %conv = trunc i64 %call to i32, !dbg !2860
  store i32 %conv, i32* %sz, align 4, !dbg !2861
  br label %if.end36, !dbg !2862

if.else10:                                        ; preds = %if.end
  call void @llvm.dbg.declare(metadata [2 x %struct.iovec]* %iv, metadata !2863, metadata !DIExpression()), !dbg !2871
  %24 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2872
  %response = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %24, i32 0, i32 32, !dbg !2873
  %25 = load i8*, i8** %response, align 8, !dbg !2873
  %arrayidx11 = getelementptr inbounds [2 x %struct.iovec], [2 x %struct.iovec]* %iv, i64 0, i64 0, !dbg !2874
  %iov_base = getelementptr inbounds %struct.iovec, %struct.iovec* %arrayidx11, i32 0, i32 0, !dbg !2875
  store i8* %25, i8** %iov_base, align 16, !dbg !2876
  %26 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2877
  %responselen12 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %26, i32 0, i32 45, !dbg !2878
  %27 = load i64, i64* %responselen12, align 8, !dbg !2878
  %arrayidx13 = getelementptr inbounds [2 x %struct.iovec], [2 x %struct.iovec]* %iv, i64 0, i64 0, !dbg !2879
  %iov_len = getelementptr inbounds %struct.iovec, %struct.iovec* %arrayidx13, i32 0, i32 1, !dbg !2880
  store i64 %27, i64* %iov_len, align 8, !dbg !2881
  %28 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2882
  %file_address14 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %28, i32 0, i32 61, !dbg !2883
  %29 = load i8*, i8** %file_address14, align 8, !dbg !2883
  %30 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2884
  %next_byte_index15 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %30, i32 0, i32 14, !dbg !2885
  %31 = load i64, i64* %next_byte_index15, align 8, !dbg !2885
  %arrayidx16 = getelementptr inbounds i8, i8* %29, i64 %31, !dbg !2882
  %arrayidx17 = getelementptr inbounds [2 x %struct.iovec], [2 x %struct.iovec]* %iv, i64 0, i64 1, !dbg !2886
  %iov_base18 = getelementptr inbounds %struct.iovec, %struct.iovec* %arrayidx17, i32 0, i32 0, !dbg !2887
  store i8* %arrayidx16, i8** %iov_base18, align 16, !dbg !2888
  %32 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2889
  %end_byte_index19 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %32, i32 0, i32 13, !dbg !2889
  %33 = load i64, i64* %end_byte_index19, align 8, !dbg !2889
  %34 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2889
  %next_byte_index20 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %34, i32 0, i32 14, !dbg !2889
  %35 = load i64, i64* %next_byte_index20, align 8, !dbg !2889
  %sub21 = sub nsw i64 %33, %35, !dbg !2889
  %36 = load i64, i64* %max_bytes, align 8, !dbg !2889
  %cmp22 = icmp ult i64 %sub21, %36, !dbg !2889
  br i1 %cmp22, label %cond.true24, label %cond.false28, !dbg !2889

cond.true24:                                      ; preds = %if.else10
  %37 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2889
  %end_byte_index25 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %37, i32 0, i32 13, !dbg !2889
  %38 = load i64, i64* %end_byte_index25, align 8, !dbg !2889
  %39 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2889
  %next_byte_index26 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %39, i32 0, i32 14, !dbg !2889
  %40 = load i64, i64* %next_byte_index26, align 8, !dbg !2889
  %sub27 = sub nsw i64 %38, %40, !dbg !2889
  br label %cond.end29, !dbg !2889

cond.false28:                                     ; preds = %if.else10
  %41 = load i64, i64* %max_bytes, align 8, !dbg !2889
  br label %cond.end29, !dbg !2889

cond.end29:                                       ; preds = %cond.false28, %cond.true24
  %cond30 = phi i64 [ %sub27, %cond.true24 ], [ %41, %cond.false28 ], !dbg !2889
  %arrayidx31 = getelementptr inbounds [2 x %struct.iovec], [2 x %struct.iovec]* %iv, i64 0, i64 1, !dbg !2890
  %iov_len32 = getelementptr inbounds %struct.iovec, %struct.iovec* %arrayidx31, i32 0, i32 1, !dbg !2891
  store i64 %cond30, i64* %iov_len32, align 8, !dbg !2892
  %42 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2893
  %conn_fd33 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %42, i32 0, i32 60, !dbg !2894
  %43 = load i32, i32* %conn_fd33, align 8, !dbg !2894
  %arraydecay = getelementptr inbounds [2 x %struct.iovec], [2 x %struct.iovec]* %iv, i64 0, i64 0, !dbg !2895
  %call34 = call i64 @"\01_writev"(i32 %43, %struct.iovec* %arraydecay, i32 2), !dbg !2896
  %conv35 = trunc i64 %call34 to i32, !dbg !2896
  store i32 %conv35, i32* %sz, align 4, !dbg !2897
  br label %if.end36

if.end36:                                         ; preds = %cond.end29, %cond.end
  %44 = load i32, i32* %sz, align 4, !dbg !2898
  %cmp37 = icmp slt i32 %44, 0, !dbg !2900
  br i1 %cmp37, label %land.lhs.true, label %if.end43, !dbg !2901

land.lhs.true:                                    ; preds = %if.end36
  %call39 = call i32* @__error(), !dbg !2902
  %45 = load i32, i32* %call39, align 4, !dbg !2902
  %cmp40 = icmp eq i32 %45, 4, !dbg !2903
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !2904

if.then42:                                        ; preds = %land.lhs.true
  br label %if.end191, !dbg !2905

if.end43:                                         ; preds = %land.lhs.true, %if.end36
  %46 = load i32, i32* %sz, align 4, !dbg !2906
  %cmp44 = icmp eq i32 %46, 0, !dbg !2908
  br i1 %cmp44, label %if.then56, label %lor.lhs.false, !dbg !2909

lor.lhs.false:                                    ; preds = %if.end43
  %47 = load i32, i32* %sz, align 4, !dbg !2910
  %cmp46 = icmp slt i32 %47, 0, !dbg !2911
  br i1 %cmp46, label %land.lhs.true48, label %if.end70, !dbg !2912

land.lhs.true48:                                  ; preds = %lor.lhs.false
  %call49 = call i32* @__error(), !dbg !2913
  %48 = load i32, i32* %call49, align 4, !dbg !2913
  %cmp50 = icmp eq i32 %48, 35, !dbg !2914
  br i1 %cmp50, label %if.then56, label %lor.lhs.false52, !dbg !2915

lor.lhs.false52:                                  ; preds = %land.lhs.true48
  %call53 = call i32* @__error(), !dbg !2916
  %49 = load i32, i32* %call53, align 4, !dbg !2916
  %cmp54 = icmp eq i32 %49, 35, !dbg !2917
  br i1 %cmp54, label %if.then56, label %if.end70, !dbg !2918

if.then56:                                        ; preds = %lor.lhs.false52, %land.lhs.true48, %if.end43
  %50 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2919
  %wouldblock_delay = getelementptr inbounds %struct.connecttab, %struct.connecttab* %50, i32 0, i32 11, !dbg !2921
  %51 = load i64, i64* %wouldblock_delay, align 8, !dbg !2922
  %add = add nsw i64 %51, 100, !dbg !2922
  store i64 %add, i64* %wouldblock_delay, align 8, !dbg !2922
  %52 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2923
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %52, i32 0, i32 0, !dbg !2924
  store i32 3, i32* %conn_state, align 8, !dbg !2925
  %53 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2926
  %conn_fd57 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %53, i32 0, i32 60, !dbg !2927
  %54 = load i32, i32* %conn_fd57, align 8, !dbg !2927
  call void @fdwatch_del_fd(i32 %54), !dbg !2928
  %55 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2929
  %56 = bitcast %struct.connecttab* %55 to i8*, !dbg !2929
  %p = bitcast %union.ClientData* %client_data to i8**, !dbg !2930
  store i8* %56, i8** %p, align 8, !dbg !2931
  %57 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2932
  %wakeup_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %57, i32 0, i32 9, !dbg !2934
  %58 = load %struct.TimerStruct*, %struct.TimerStruct** %wakeup_timer, align 8, !dbg !2934
  %cmp58 = icmp ne %struct.TimerStruct* %58, null, !dbg !2935
  br i1 %cmp58, label %if.then60, label %if.end61, !dbg !2936

if.then60:                                        ; preds = %if.then56
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.124, i64 0, i64 0)), !dbg !2937
  br label %if.end61, !dbg !2937

if.end61:                                         ; preds = %if.then60, %if.then56
  %59 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2938
  %60 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2939
  %wouldblock_delay62 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %60, i32 0, i32 11, !dbg !2940
  %61 = load i64, i64* %wouldblock_delay62, align 8, !dbg !2940
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0, !dbg !2941
  %62 = load i8*, i8** %coerce.dive, align 8, !dbg !2941
  %call63 = call %struct.TimerStruct* @tmr_create(%struct.timeval* %59, void (i8*, %struct.timeval*)* @wakeup_connection, i8* %62, i64 %61, i32 0), !dbg !2941
  %63 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2942
  %wakeup_timer64 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %63, i32 0, i32 9, !dbg !2943
  store %struct.TimerStruct* %call63, %struct.TimerStruct** %wakeup_timer64, align 8, !dbg !2944
  %64 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2945
  %wakeup_timer65 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %64, i32 0, i32 9, !dbg !2947
  %65 = load %struct.TimerStruct*, %struct.TimerStruct** %wakeup_timer65, align 8, !dbg !2947
  %cmp66 = icmp eq %struct.TimerStruct* %65, null, !dbg !2948
  br i1 %cmp66, label %if.then68, label %if.end69, !dbg !2949

if.then68:                                        ; preds = %if.end61
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.125, i64 0, i64 0)), !dbg !2950
  call void @exit(i32 1) #11, !dbg !2952
  unreachable, !dbg !2952

if.end69:                                         ; preds = %if.end61
  br label %if.end191, !dbg !2953

if.end70:                                         ; preds = %lor.lhs.false52, %lor.lhs.false
  %66 = load i32, i32* %sz, align 4, !dbg !2954
  %cmp71 = icmp slt i32 %66, 0, !dbg !2956
  br i1 %cmp71, label %if.then73, label %if.end87, !dbg !2957

if.then73:                                        ; preds = %if.end70
  %call74 = call i32* @__error(), !dbg !2958
  %67 = load i32, i32* %call74, align 4, !dbg !2958
  %cmp75 = icmp ne i32 %67, 32, !dbg !2961
  br i1 %cmp75, label %land.lhs.true77, label %if.end86, !dbg !2962

land.lhs.true77:                                  ; preds = %if.then73
  %call78 = call i32* @__error(), !dbg !2963
  %68 = load i32, i32* %call78, align 4, !dbg !2963
  %cmp79 = icmp ne i32 %68, 22, !dbg !2964
  br i1 %cmp79, label %land.lhs.true81, label %if.end86, !dbg !2965

land.lhs.true81:                                  ; preds = %land.lhs.true77
  %call82 = call i32* @__error(), !dbg !2966
  %69 = load i32, i32* %call82, align 4, !dbg !2966
  %cmp83 = icmp ne i32 %69, 54, !dbg !2967
  br i1 %cmp83, label %if.then85, label %if.end86, !dbg !2968

if.then85:                                        ; preds = %land.lhs.true81
  %70 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2969
  %encodedurl = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %70, i32 0, i32 12, !dbg !2970
  %71 = load i8*, i8** %encodedurl, align 8, !dbg !2970
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.126, i64 0, i64 0), i8* %71), !dbg !2971
  br label %if.end86, !dbg !2971

if.end86:                                         ; preds = %if.then85, %land.lhs.true81, %land.lhs.true77, %if.then73
  %72 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2972
  %73 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2973
  call void @clear_connection(%struct.connecttab* %72, %struct.timeval* %73), !dbg !2974
  br label %if.end191, !dbg !2975

if.end87:                                         ; preds = %if.end70
  %74 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !2976
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %74, i32 0, i32 0, !dbg !2977
  %75 = load i64, i64* %tv_sec, align 8, !dbg !2977
  %76 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !2978
  %active_at = getelementptr inbounds %struct.connecttab, %struct.connecttab* %76, i32 0, i32 8, !dbg !2979
  store i64 %75, i64* %active_at, align 8, !dbg !2980
  %77 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2981
  %responselen88 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %77, i32 0, i32 45, !dbg !2983
  %78 = load i64, i64* %responselen88, align 8, !dbg !2983
  %cmp89 = icmp ugt i64 %78, 0, !dbg !2984
  br i1 %cmp89, label %if.then91, label %if.end116, !dbg !2985

if.then91:                                        ; preds = %if.end87
  %79 = load i32, i32* %sz, align 4, !dbg !2986
  %conv92 = sext i32 %79 to i64, !dbg !2986
  %80 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2989
  %responselen93 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %80, i32 0, i32 45, !dbg !2990
  %81 = load i64, i64* %responselen93, align 8, !dbg !2990
  %cmp94 = icmp ult i64 %conv92, %81, !dbg !2991
  br i1 %cmp94, label %if.then96, label %if.else109, !dbg !2992

if.then96:                                        ; preds = %if.then91
  call void @llvm.dbg.declare(metadata i32* %newlen, metadata !2993, metadata !DIExpression()), !dbg !2995
  %82 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !2996
  %responselen97 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %82, i32 0, i32 45, !dbg !2997
  %83 = load i64, i64* %responselen97, align 8, !dbg !2997
  %84 = load i32, i32* %sz, align 4, !dbg !2998
  %conv98 = sext i32 %84 to i64, !dbg !2998
  %sub99 = sub i64 %83, %conv98, !dbg !2999
  %conv100 = trunc i64 %sub99 to i32, !dbg !2996
  store i32 %conv100, i32* %newlen, align 4, !dbg !2995
  %85 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3000
  %response101 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %85, i32 0, i32 32, !dbg !3000
  %86 = load i8*, i8** %response101, align 8, !dbg !3000
  %87 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3000
  %response102 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %87, i32 0, i32 32, !dbg !3000
  %88 = load i8*, i8** %response102, align 8, !dbg !3000
  %89 = load i32, i32* %sz, align 4, !dbg !3000
  %idxprom = sext i32 %89 to i64, !dbg !3000
  %arrayidx103 = getelementptr inbounds i8, i8* %88, i64 %idxprom, !dbg !3000
  %90 = load i32, i32* %newlen, align 4, !dbg !3000
  %conv104 = sext i32 %90 to i64, !dbg !3000
  %91 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3000
  %response105 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %91, i32 0, i32 32, !dbg !3000
  %92 = load i8*, i8** %response105, align 8, !dbg !3000
  %93 = call i64 @llvm.objectsize.i64.p0i8(i8* %92, i1 false, i1 true, i1 false), !dbg !3000
  %call106 = call i8* @__memmove_chk(i8* %86, i8* %arrayidx103, i64 %conv104, i64 %93) #13, !dbg !3000
  %94 = load i32, i32* %newlen, align 4, !dbg !3001
  %conv107 = sext i32 %94 to i64, !dbg !3001
  %95 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3002
  %responselen108 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %95, i32 0, i32 45, !dbg !3003
  store i64 %conv107, i64* %responselen108, align 8, !dbg !3004
  store i32 0, i32* %sz, align 4, !dbg !3005
  br label %if.end115, !dbg !3006

if.else109:                                       ; preds = %if.then91
  %96 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3007
  %responselen110 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %96, i32 0, i32 45, !dbg !3009
  %97 = load i64, i64* %responselen110, align 8, !dbg !3009
  %98 = load i32, i32* %sz, align 4, !dbg !3010
  %conv111 = sext i32 %98 to i64, !dbg !3010
  %sub112 = sub i64 %conv111, %97, !dbg !3010
  %conv113 = trunc i64 %sub112 to i32, !dbg !3010
  store i32 %conv113, i32* %sz, align 4, !dbg !3010
  %99 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3011
  %responselen114 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %99, i32 0, i32 45, !dbg !3012
  store i64 0, i64* %responselen114, align 8, !dbg !3013
  br label %if.end115

if.end115:                                        ; preds = %if.else109, %if.then96
  br label %if.end116, !dbg !3014

if.end116:                                        ; preds = %if.end115, %if.end87
  %100 = load i32, i32* %sz, align 4, !dbg !3015
  %conv117 = sext i32 %100 to i64, !dbg !3015
  %101 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3016
  %next_byte_index118 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %101, i32 0, i32 14, !dbg !3017
  %102 = load i64, i64* %next_byte_index118, align 8, !dbg !3018
  %add119 = add nsw i64 %102, %conv117, !dbg !3018
  store i64 %add119, i64* %next_byte_index118, align 8, !dbg !3018
  %103 = load i32, i32* %sz, align 4, !dbg !3019
  %conv120 = sext i32 %103 to i64, !dbg !3019
  %104 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3020
  %hc121 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %104, i32 0, i32 2, !dbg !3021
  %105 = load %struct.httpd_conn*, %struct.httpd_conn** %hc121, align 8, !dbg !3021
  %bytes_sent = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %105, i32 0, i32 11, !dbg !3022
  %106 = load i64, i64* %bytes_sent, align 8, !dbg !3023
  %add122 = add nsw i64 %106, %conv120, !dbg !3023
  store i64 %add122, i64* %bytes_sent, align 8, !dbg !3023
  store i32 0, i32* %tind, align 4, !dbg !3024
  br label %for.cond, !dbg !3026

for.cond:                                         ; preds = %for.inc, %if.end116
  %107 = load i32, i32* %tind, align 4, !dbg !3027
  %108 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3029
  %numtnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %108, i32 0, i32 4, !dbg !3030
  %109 = load i32, i32* %numtnums, align 8, !dbg !3030
  %cmp123 = icmp slt i32 %107, %109, !dbg !3031
  br i1 %cmp123, label %for.body, label %for.end, !dbg !3032

for.body:                                         ; preds = %for.cond
  %110 = load i32, i32* %sz, align 4, !dbg !3033
  %conv125 = sext i32 %110 to i64, !dbg !3033
  %111 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3034
  %112 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3035
  %tnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %112, i32 0, i32 3, !dbg !3036
  %113 = load i32, i32* %tind, align 4, !dbg !3037
  %idxprom126 = sext i32 %113 to i64, !dbg !3035
  %arrayidx127 = getelementptr inbounds [10 x i32], [10 x i32]* %tnums, i64 0, i64 %idxprom126, !dbg !3035
  %114 = load i32, i32* %arrayidx127, align 4, !dbg !3035
  %idxprom128 = sext i32 %114 to i64, !dbg !3034
  %arrayidx129 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %111, i64 %idxprom128, !dbg !3034
  %bytes_since_avg = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx129, i32 0, i32 4, !dbg !3038
  %115 = load i64, i64* %bytes_since_avg, align 8, !dbg !3039
  %add130 = add nsw i64 %115, %conv125, !dbg !3039
  store i64 %add130, i64* %bytes_since_avg, align 8, !dbg !3039
  br label %for.inc, !dbg !3034

for.inc:                                          ; preds = %for.body
  %116 = load i32, i32* %tind, align 4, !dbg !3040
  %inc = add nsw i32 %116, 1, !dbg !3040
  store i32 %inc, i32* %tind, align 4, !dbg !3040
  br label %for.cond, !dbg !3041, !llvm.loop !3042

for.end:                                          ; preds = %for.cond
  %117 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3044
  %next_byte_index131 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %117, i32 0, i32 14, !dbg !3046
  %118 = load i64, i64* %next_byte_index131, align 8, !dbg !3046
  %119 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3047
  %end_byte_index132 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %119, i32 0, i32 13, !dbg !3048
  %120 = load i64, i64* %end_byte_index132, align 8, !dbg !3048
  %cmp133 = icmp sge i64 %118, %120, !dbg !3049
  br i1 %cmp133, label %if.then135, label %if.end136, !dbg !3050

if.then135:                                       ; preds = %for.end
  %121 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3051
  %122 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !3053
  call void @finish_connection(%struct.connecttab* %121, %struct.timeval* %122), !dbg !3054
  br label %if.end191, !dbg !3055

if.end136:                                        ; preds = %for.end
  %123 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3056
  %wouldblock_delay137 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %123, i32 0, i32 11, !dbg !3058
  %124 = load i64, i64* %wouldblock_delay137, align 8, !dbg !3058
  %cmp138 = icmp sgt i64 %124, 100, !dbg !3059
  br i1 %cmp138, label %if.then140, label %if.end143, !dbg !3060

if.then140:                                       ; preds = %if.end136
  %125 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3061
  %wouldblock_delay141 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %125, i32 0, i32 11, !dbg !3062
  %126 = load i64, i64* %wouldblock_delay141, align 8, !dbg !3063
  %sub142 = sub nsw i64 %126, 100, !dbg !3063
  store i64 %sub142, i64* %wouldblock_delay141, align 8, !dbg !3063
  br label %if.end143, !dbg !3061

if.end143:                                        ; preds = %if.then140, %if.end136
  %127 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3064
  %max_limit144 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %127, i32 0, i32 5, !dbg !3066
  %128 = load i64, i64* %max_limit144, align 8, !dbg !3066
  %cmp145 = icmp ne i64 %128, -1, !dbg !3067
  br i1 %cmp145, label %if.then147, label %if.end191, !dbg !3068

if.then147:                                       ; preds = %if.end143
  %129 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !3069
  %tv_sec148 = getelementptr inbounds %struct.timeval, %struct.timeval* %129, i32 0, i32 0, !dbg !3071
  %130 = load i64, i64* %tv_sec148, align 8, !dbg !3071
  %131 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3072
  %started_at = getelementptr inbounds %struct.connecttab, %struct.connecttab* %131, i32 0, i32 7, !dbg !3073
  %132 = load i64, i64* %started_at, align 8, !dbg !3073
  %sub149 = sub nsw i64 %130, %132, !dbg !3074
  store i64 %sub149, i64* %elapsed, align 8, !dbg !3075
  %133 = load i64, i64* %elapsed, align 8, !dbg !3076
  %cmp150 = icmp eq i64 %133, 0, !dbg !3078
  br i1 %cmp150, label %if.then152, label %if.end153, !dbg !3079

if.then152:                                       ; preds = %if.then147
  store i64 1, i64* %elapsed, align 8, !dbg !3080
  br label %if.end153, !dbg !3081

if.end153:                                        ; preds = %if.then152, %if.then147
  %134 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3082
  %hc154 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %134, i32 0, i32 2, !dbg !3084
  %135 = load %struct.httpd_conn*, %struct.httpd_conn** %hc154, align 8, !dbg !3084
  %bytes_sent155 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %135, i32 0, i32 11, !dbg !3085
  %136 = load i64, i64* %bytes_sent155, align 8, !dbg !3085
  %137 = load i64, i64* %elapsed, align 8, !dbg !3086
  %div156 = sdiv i64 %136, %137, !dbg !3087
  %138 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3088
  %max_limit157 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %138, i32 0, i32 5, !dbg !3089
  %139 = load i64, i64* %max_limit157, align 8, !dbg !3089
  %cmp158 = icmp sgt i64 %div156, %139, !dbg !3090
  br i1 %cmp158, label %if.then160, label %if.end190, !dbg !3091

if.then160:                                       ; preds = %if.end153
  %140 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3092
  %conn_state161 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %140, i32 0, i32 0, !dbg !3094
  store i32 3, i32* %conn_state161, align 8, !dbg !3095
  %141 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3096
  %conn_fd162 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %141, i32 0, i32 60, !dbg !3097
  %142 = load i32, i32* %conn_fd162, align 8, !dbg !3097
  call void @fdwatch_del_fd(i32 %142), !dbg !3098
  %143 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3099
  %hc163 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %143, i32 0, i32 2, !dbg !3100
  %144 = load %struct.httpd_conn*, %struct.httpd_conn** %hc163, align 8, !dbg !3100
  %bytes_sent164 = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %144, i32 0, i32 11, !dbg !3101
  %145 = load i64, i64* %bytes_sent164, align 8, !dbg !3101
  %146 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3102
  %max_limit165 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %146, i32 0, i32 5, !dbg !3103
  %147 = load i64, i64* %max_limit165, align 8, !dbg !3103
  %div166 = sdiv i64 %145, %147, !dbg !3104
  %148 = load i64, i64* %elapsed, align 8, !dbg !3105
  %sub167 = sub nsw i64 %div166, %148, !dbg !3106
  %conv168 = trunc i64 %sub167 to i32, !dbg !3099
  store i32 %conv168, i32* %coast, align 4, !dbg !3107
  %149 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3108
  %150 = bitcast %struct.connecttab* %149 to i8*, !dbg !3108
  %p169 = bitcast %union.ClientData* %client_data to i8**, !dbg !3109
  store i8* %150, i8** %p169, align 8, !dbg !3110
  %151 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3111
  %wakeup_timer170 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %151, i32 0, i32 9, !dbg !3113
  %152 = load %struct.TimerStruct*, %struct.TimerStruct** %wakeup_timer170, align 8, !dbg !3113
  %cmp171 = icmp ne %struct.TimerStruct* %152, null, !dbg !3114
  br i1 %cmp171, label %if.then173, label %if.end174, !dbg !3115

if.then173:                                       ; preds = %if.then160
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.124, i64 0, i64 0)), !dbg !3116
  br label %if.end174, !dbg !3116

if.end174:                                        ; preds = %if.then173, %if.then160
  %153 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !3117
  %154 = load i32, i32* %coast, align 4, !dbg !3118
  %cmp175 = icmp sgt i32 %154, 0, !dbg !3119
  br i1 %cmp175, label %cond.true177, label %cond.false179, !dbg !3118

cond.true177:                                     ; preds = %if.end174
  %155 = load i32, i32* %coast, align 4, !dbg !3120
  %conv178 = sext i32 %155 to i64, !dbg !3120
  %mul = mul nsw i64 %conv178, 1000, !dbg !3121
  br label %cond.end180, !dbg !3118

cond.false179:                                    ; preds = %if.end174
  br label %cond.end180, !dbg !3118

cond.end180:                                      ; preds = %cond.false179, %cond.true177
  %cond181 = phi i64 [ %mul, %cond.true177 ], [ 500, %cond.false179 ], !dbg !3118
  %coerce.dive182 = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0, !dbg !3122
  %156 = load i8*, i8** %coerce.dive182, align 8, !dbg !3122
  %call183 = call %struct.TimerStruct* @tmr_create(%struct.timeval* %153, void (i8*, %struct.timeval*)* @wakeup_connection, i8* %156, i64 %cond181, i32 0), !dbg !3122
  %157 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3123
  %wakeup_timer184 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %157, i32 0, i32 9, !dbg !3124
  store %struct.TimerStruct* %call183, %struct.TimerStruct** %wakeup_timer184, align 8, !dbg !3125
  %158 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3126
  %wakeup_timer185 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %158, i32 0, i32 9, !dbg !3128
  %159 = load %struct.TimerStruct*, %struct.TimerStruct** %wakeup_timer185, align 8, !dbg !3128
  %cmp186 = icmp eq %struct.TimerStruct* %159, null, !dbg !3129
  br i1 %cmp186, label %if.then188, label %if.end189, !dbg !3130

if.then188:                                       ; preds = %cond.end180
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.125, i64 0, i64 0)), !dbg !3131
  call void @exit(i32 1) #11, !dbg !3133
  unreachable, !dbg !3133

if.end189:                                        ; preds = %cond.end180
  br label %if.end190, !dbg !3134

if.end190:                                        ; preds = %if.end189, %if.end153
  br label %if.end191, !dbg !3135

if.end191:                                        ; preds = %if.then42, %if.end69, %if.end86, %if.then135, %if.end190, %if.end143
  ret void, !dbg !3136
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @handle_linger(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !3137 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  %buf = alloca [4096 x i8], align 16
  %r = alloca i32, align 4
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !3138, metadata !DIExpression()), !dbg !3139
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !3140, metadata !DIExpression()), !dbg !3141
  call void @llvm.dbg.declare(metadata [4096 x i8]* %buf, metadata !3142, metadata !DIExpression()), !dbg !3146
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3147, metadata !DIExpression()), !dbg !3148
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3149
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 2, !dbg !3150
  %1 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3150
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %1, i32 0, i32 60, !dbg !3151
  %2 = load i32, i32* %conn_fd, align 8, !dbg !3151
  %arraydecay = getelementptr inbounds [4096 x i8], [4096 x i8]* %buf, i64 0, i64 0, !dbg !3152
  %call = call i64 @"\01_read"(i32 %2, i8* %arraydecay, i64 4096), !dbg !3153
  %conv = trunc i64 %call to i32, !dbg !3153
  store i32 %conv, i32* %r, align 4, !dbg !3154
  %3 = load i32, i32* %r, align 4, !dbg !3155
  %cmp = icmp slt i32 %3, 0, !dbg !3157
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3158

land.lhs.true:                                    ; preds = %entry
  %call2 = call i32* @__error(), !dbg !3159
  %4 = load i32, i32* %call2, align 4, !dbg !3159
  %cmp3 = icmp eq i32 %4, 4, !dbg !3160
  br i1 %cmp3, label %if.then, label %lor.lhs.false, !dbg !3161

lor.lhs.false:                                    ; preds = %land.lhs.true
  %call5 = call i32* @__error(), !dbg !3162
  %5 = load i32, i32* %call5, align 4, !dbg !3162
  %cmp6 = icmp eq i32 %5, 35, !dbg !3163
  br i1 %cmp6, label %if.then, label %if.end, !dbg !3164

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  br label %if.end11, !dbg !3165

if.end:                                           ; preds = %lor.lhs.false, %entry
  %6 = load i32, i32* %r, align 4, !dbg !3166
  %cmp8 = icmp sle i32 %6, 0, !dbg !3168
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !3169

if.then10:                                        ; preds = %if.end
  %7 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3170
  %8 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !3171
  call void @really_clear_connection(%struct.connecttab* %7, %struct.timeval* %8), !dbg !3172
  br label %if.end11, !dbg !3172

if.end11:                                         ; preds = %if.then, %if.then10, %if.end
  ret void, !dbg !3173
}

declare void @fdwatch_del_fd(i32) #3

declare void @httpd_unlisten(%struct.httpd_server*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @shut_down() #0 !dbg !3174 {
entry:
  %cnum = alloca i32, align 4
  %tv = alloca %struct.timeval, align 8
  %ths = alloca %struct.httpd_server*, align 8
  call void @llvm.dbg.declare(metadata i32* %cnum, metadata !3175, metadata !DIExpression()), !dbg !3176
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !3177, metadata !DIExpression()), !dbg !3178
  %call = call i32 @gettimeofday(%struct.timeval* %tv, i8* null), !dbg !3179
  call void @logstats(%struct.timeval* %tv), !dbg !3180
  store i32 0, i32* %cnum, align 4, !dbg !3181
  br label %for.cond, !dbg !3183

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %cnum, align 4, !dbg !3184
  %1 = load i32, i32* @max_connects, align 4, !dbg !3186
  %cmp = icmp slt i32 %0, %1, !dbg !3187
  br i1 %cmp, label %for.body, label %for.end, !dbg !3188

for.body:                                         ; preds = %for.cond
  %2 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3189
  %3 = load i32, i32* %cnum, align 4, !dbg !3192
  %idxprom = sext i32 %3 to i64, !dbg !3189
  %arrayidx = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i64 %idxprom, !dbg !3189
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx, i32 0, i32 0, !dbg !3193
  %4 = load i32, i32* %conn_state, align 8, !dbg !3193
  %cmp1 = icmp ne i32 %4, 0, !dbg !3194
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3195

if.then:                                          ; preds = %for.body
  %5 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3196
  %6 = load i32, i32* %cnum, align 4, !dbg !3197
  %idxprom2 = sext i32 %6 to i64, !dbg !3196
  %arrayidx3 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %5, i64 %idxprom2, !dbg !3196
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx3, i32 0, i32 2, !dbg !3198
  %7 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3198
  call void @httpd_close_conn(%struct.httpd_conn* %7, %struct.timeval* %tv), !dbg !3199
  br label %if.end, !dbg !3199

if.end:                                           ; preds = %if.then, %for.body
  %8 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3200
  %9 = load i32, i32* %cnum, align 4, !dbg !3202
  %idxprom4 = sext i32 %9 to i64, !dbg !3200
  %arrayidx5 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %8, i64 %idxprom4, !dbg !3200
  %hc6 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx5, i32 0, i32 2, !dbg !3203
  %10 = load %struct.httpd_conn*, %struct.httpd_conn** %hc6, align 8, !dbg !3203
  %cmp7 = icmp ne %struct.httpd_conn* %10, null, !dbg !3204
  br i1 %cmp7, label %if.then8, label %if.end18, !dbg !3205

if.then8:                                         ; preds = %if.end
  %11 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3206
  %12 = load i32, i32* %cnum, align 4, !dbg !3208
  %idxprom9 = sext i32 %12 to i64, !dbg !3206
  %arrayidx10 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %11, i64 %idxprom9, !dbg !3206
  %hc11 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx10, i32 0, i32 2, !dbg !3209
  %13 = load %struct.httpd_conn*, %struct.httpd_conn** %hc11, align 8, !dbg !3209
  call void @httpd_destroy_conn(%struct.httpd_conn* %13), !dbg !3210
  %14 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3211
  %15 = load i32, i32* %cnum, align 4, !dbg !3212
  %idxprom12 = sext i32 %15 to i64, !dbg !3211
  %arrayidx13 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %14, i64 %idxprom12, !dbg !3211
  %hc14 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx13, i32 0, i32 2, !dbg !3213
  %16 = load %struct.httpd_conn*, %struct.httpd_conn** %hc14, align 8, !dbg !3213
  %17 = bitcast %struct.httpd_conn* %16 to i8*, !dbg !3214
  call void @free(i8* %17), !dbg !3215
  %18 = load i32, i32* @httpd_conn_count, align 4, !dbg !3216
  %dec = add nsw i32 %18, -1, !dbg !3216
  store i32 %dec, i32* @httpd_conn_count, align 4, !dbg !3216
  %19 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3217
  %20 = load i32, i32* %cnum, align 4, !dbg !3218
  %idxprom15 = sext i32 %20 to i64, !dbg !3217
  %arrayidx16 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %19, i64 %idxprom15, !dbg !3217
  %hc17 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %arrayidx16, i32 0, i32 2, !dbg !3219
  store %struct.httpd_conn* null, %struct.httpd_conn** %hc17, align 8, !dbg !3220
  br label %if.end18, !dbg !3221

if.end18:                                         ; preds = %if.then8, %if.end
  br label %for.inc, !dbg !3222

for.inc:                                          ; preds = %if.end18
  %21 = load i32, i32* %cnum, align 4, !dbg !3223
  %inc = add nsw i32 %21, 1, !dbg !3223
  store i32 %inc, i32* %cnum, align 4, !dbg !3223
  br label %for.cond, !dbg !3224, !llvm.loop !3225

for.end:                                          ; preds = %for.cond
  %22 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !3227
  %cmp19 = icmp ne %struct.httpd_server* %22, null, !dbg !3229
  br i1 %cmp19, label %if.then20, label %if.end29, !dbg !3230

if.then20:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata %struct.httpd_server** %ths, metadata !3231, metadata !DIExpression()), !dbg !3233
  %23 = load %struct.httpd_server*, %struct.httpd_server** @hs, align 8, !dbg !3234
  store %struct.httpd_server* %23, %struct.httpd_server** %ths, align 8, !dbg !3233
  store %struct.httpd_server* null, %struct.httpd_server** @hs, align 8, !dbg !3235
  %24 = load %struct.httpd_server*, %struct.httpd_server** %ths, align 8, !dbg !3236
  %listen4_fd = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %24, i32 0, i32 10, !dbg !3238
  %25 = load i32, i32* %listen4_fd, align 8, !dbg !3238
  %cmp21 = icmp ne i32 %25, -1, !dbg !3239
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !3240

if.then22:                                        ; preds = %if.then20
  %26 = load %struct.httpd_server*, %struct.httpd_server** %ths, align 8, !dbg !3241
  %listen4_fd23 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %26, i32 0, i32 10, !dbg !3242
  %27 = load i32, i32* %listen4_fd23, align 8, !dbg !3242
  call void @fdwatch_del_fd(i32 %27), !dbg !3243
  br label %if.end24, !dbg !3243

if.end24:                                         ; preds = %if.then22, %if.then20
  %28 = load %struct.httpd_server*, %struct.httpd_server** %ths, align 8, !dbg !3244
  %listen6_fd = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %28, i32 0, i32 11, !dbg !3246
  %29 = load i32, i32* %listen6_fd, align 4, !dbg !3246
  %cmp25 = icmp ne i32 %29, -1, !dbg !3247
  br i1 %cmp25, label %if.then26, label %if.end28, !dbg !3248

if.then26:                                        ; preds = %if.end24
  %30 = load %struct.httpd_server*, %struct.httpd_server** %ths, align 8, !dbg !3249
  %listen6_fd27 = getelementptr inbounds %struct.httpd_server, %struct.httpd_server* %30, i32 0, i32 11, !dbg !3250
  %31 = load i32, i32* %listen6_fd27, align 4, !dbg !3250
  call void @fdwatch_del_fd(i32 %31), !dbg !3251
  br label %if.end28, !dbg !3251

if.end28:                                         ; preds = %if.then26, %if.end24
  %32 = load %struct.httpd_server*, %struct.httpd_server** %ths, align 8, !dbg !3252
  call void @httpd_terminate(%struct.httpd_server* %32), !dbg !3253
  br label %if.end29, !dbg !3254

if.end29:                                         ; preds = %if.end28, %for.end
  call void @mmc_term(), !dbg !3255
  call void @tmr_term(), !dbg !3256
  %33 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !3257
  %34 = bitcast %struct.connecttab* %33 to i8*, !dbg !3258
  call void @free(i8* %34), !dbg !3259
  %35 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3260
  %cmp30 = icmp ne %struct.throttletab* %35, null, !dbg !3262
  br i1 %cmp30, label %if.then31, label %if.end32, !dbg !3263

if.then31:                                        ; preds = %if.end29
  %36 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3264
  %37 = bitcast %struct.throttletab* %36 to i8*, !dbg !3265
  call void @free(i8* %37), !dbg !3266
  br label %if.end32, !dbg !3266

if.end32:                                         ; preds = %if.then31, %if.end29
  ret void, !dbg !3267
}

declare void @closelog() #3

declare i32 @"\01_waitpid"(i32, i32*, i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @logstats(%struct.timeval* %nowP) #0 !dbg !3268 {
entry:
  %nowP.addr = alloca %struct.timeval*, align 8
  %tv = alloca %struct.timeval, align 8
  %now = alloca i64, align 8
  %up_secs = alloca i64, align 8
  %stats_secs = alloca i64, align 8
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !3271, metadata !DIExpression()), !dbg !3272
  call void @llvm.dbg.declare(metadata %struct.timeval* %tv, metadata !3273, metadata !DIExpression()), !dbg !3274
  call void @llvm.dbg.declare(metadata i64* %now, metadata !3275, metadata !DIExpression()), !dbg !3276
  call void @llvm.dbg.declare(metadata i64* %up_secs, metadata !3277, metadata !DIExpression()), !dbg !3278
  call void @llvm.dbg.declare(metadata i64* %stats_secs, metadata !3279, metadata !DIExpression()), !dbg !3280
  %0 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !3281
  %cmp = icmp eq %struct.timeval* %0, null, !dbg !3283
  br i1 %cmp, label %if.then, label %if.end, !dbg !3284

if.then:                                          ; preds = %entry
  %call = call i32 @gettimeofday(%struct.timeval* %tv, i8* null), !dbg !3285
  store %struct.timeval* %tv, %struct.timeval** %nowP.addr, align 8, !dbg !3287
  br label %if.end, !dbg !3288

if.end:                                           ; preds = %if.then, %entry
  %1 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !3289
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %1, i32 0, i32 0, !dbg !3290
  %2 = load i64, i64* %tv_sec, align 8, !dbg !3290
  store i64 %2, i64* %now, align 8, !dbg !3291
  %3 = load i64, i64* %now, align 8, !dbg !3292
  %4 = load i64, i64* @start_time, align 8, !dbg !3293
  %sub = sub nsw i64 %3, %4, !dbg !3294
  store i64 %sub, i64* %up_secs, align 8, !dbg !3295
  %5 = load i64, i64* %now, align 8, !dbg !3296
  %6 = load i64, i64* @stats_time, align 8, !dbg !3297
  %sub1 = sub nsw i64 %5, %6, !dbg !3298
  store i64 %sub1, i64* %stats_secs, align 8, !dbg !3299
  %7 = load i64, i64* %stats_secs, align 8, !dbg !3300
  %cmp2 = icmp eq i64 %7, 0, !dbg !3302
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !3303

if.then3:                                         ; preds = %if.end
  store i64 1, i64* %stats_secs, align 8, !dbg !3304
  br label %if.end4, !dbg !3305

if.end4:                                          ; preds = %if.then3, %if.end
  %8 = load i64, i64* %now, align 8, !dbg !3306
  store i64 %8, i64* @stats_time, align 8, !dbg !3307
  %9 = load i64, i64* %up_secs, align 8, !dbg !3308
  %10 = load i64, i64* %stats_secs, align 8, !dbg !3309
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.43, i64 0, i64 0), i64 %9, i64 %10), !dbg !3310
  %11 = load i64, i64* %stats_secs, align 8, !dbg !3311
  call void @thttpd_logstats(i64 %11), !dbg !3312
  %12 = load i64, i64* %stats_secs, align 8, !dbg !3313
  call void @httpd_logstats(i64 %12), !dbg !3314
  %13 = load i64, i64* %stats_secs, align 8, !dbg !3315
  call void @mmc_logstats(i64 %13), !dbg !3316
  %14 = load i64, i64* %stats_secs, align 8, !dbg !3317
  call void @fdwatch_logstats(i64 %14), !dbg !3318
  %15 = load i64, i64* %stats_secs, align 8, !dbg !3319
  call void @tmr_logstats(i64 %15), !dbg !3320
  ret void, !dbg !3321
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @thttpd_logstats(i64 %secs) #0 !dbg !3322 {
entry:
  %secs.addr = alloca i64, align 8
  store i64 %secs, i64* %secs.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %secs.addr, metadata !3325, metadata !DIExpression()), !dbg !3326
  %0 = load i64, i64* %secs.addr, align 8, !dbg !3327
  %cmp = icmp sgt i64 %0, 0, !dbg !3329
  br i1 %cmp, label %if.then, label %if.end, !dbg !3330

if.then:                                          ; preds = %entry
  %1 = load i64, i64* @stats_connections, align 8, !dbg !3331
  %2 = load i64, i64* @stats_connections, align 8, !dbg !3332
  %conv = sitofp i64 %2 to float, !dbg !3333
  %3 = load i64, i64* %secs.addr, align 8, !dbg !3334
  %conv1 = sitofp i64 %3 to float, !dbg !3334
  %div = fdiv float %conv, %conv1, !dbg !3335
  %conv2 = fpext float %div to double, !dbg !3333
  %4 = load i32, i32* @stats_simultaneous, align 4, !dbg !3336
  %5 = load i64, i64* @stats_bytes, align 8, !dbg !3337
  %6 = load i64, i64* @stats_bytes, align 8, !dbg !3338
  %conv3 = sitofp i64 %6 to float, !dbg !3339
  %7 = load i64, i64* %secs.addr, align 8, !dbg !3340
  %conv4 = sitofp i64 %7 to float, !dbg !3340
  %div5 = fdiv float %conv3, %conv4, !dbg !3341
  %conv6 = fpext float %div5 to double, !dbg !3339
  %8 = load i32, i32* @httpd_conn_count, align 4, !dbg !3342
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 5, i8* getelementptr inbounds ([104 x i8], [104 x i8]* @.str.44, i64 0, i64 0), i64 %1, double %conv2, i32 %4, i64 %5, double %conv6, i32 %8), !dbg !3343
  br label %if.end, !dbg !3343

if.end:                                           ; preds = %if.then, %entry
  store i64 0, i64* @stats_connections, align 8, !dbg !3344
  store i64 0, i64* @stats_bytes, align 8, !dbg !3345
  store i32 0, i32* @stats_simultaneous, align 4, !dbg !3346
  ret void, !dbg !3347
}

declare void @httpd_logstats(i64) #3

declare void @mmc_logstats(i64) #3

declare void @fdwatch_logstats(i64) #3

declare void @tmr_logstats(i64) #3

; Function Attrs: cold noreturn
declare void @abort() #8

declare void @httpd_set_logfp(%struct.httpd_server*, %struct.__sFILE*) #3

declare i32 @printf(i8*, ...) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @read_config(i8* %filename) #0 !dbg !3348 {
entry:
  %filename.addr = alloca i8*, align 8
  %fp = alloca %struct.__sFILE*, align 8
  %line = alloca [10000 x i8], align 16
  %cp = alloca i8*, align 8
  %cp2 = alloca i8*, align 8
  %name = alloca i8*, align 8
  %value = alloca i8*, align 8
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !3349, metadata !DIExpression()), !dbg !3350
  call void @llvm.dbg.declare(metadata %struct.__sFILE** %fp, metadata !3351, metadata !DIExpression()), !dbg !3352
  call void @llvm.dbg.declare(metadata [10000 x i8]* %line, metadata !3353, metadata !DIExpression()), !dbg !3357
  call void @llvm.dbg.declare(metadata i8** %cp, metadata !3358, metadata !DIExpression()), !dbg !3359
  call void @llvm.dbg.declare(metadata i8** %cp2, metadata !3360, metadata !DIExpression()), !dbg !3361
  call void @llvm.dbg.declare(metadata i8** %name, metadata !3362, metadata !DIExpression()), !dbg !3363
  call void @llvm.dbg.declare(metadata i8** %value, metadata !3364, metadata !DIExpression()), !dbg !3365
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !3366
  %call = call %struct.__sFILE* @"\01_fopen"(i8* %0, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.76, i64 0, i64 0)), !dbg !3367
  store %struct.__sFILE* %call, %struct.__sFILE** %fp, align 8, !dbg !3368
  %1 = load %struct.__sFILE*, %struct.__sFILE** %fp, align 8, !dbg !3369
  %cmp = icmp eq %struct.__sFILE* %1, null, !dbg !3371
  br i1 %cmp, label %if.then, label %if.end, !dbg !3372

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %filename.addr, align 8, !dbg !3373
  call void @perror(i8* %2) #12, !dbg !3375
  call void @exit(i32 1) #11, !dbg !3376
  unreachable, !dbg !3376

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !3377

while.cond:                                       ; preds = %while.end209, %if.end
  %arraydecay = getelementptr inbounds [10000 x i8], [10000 x i8]* %line, i64 0, i64 0, !dbg !3378
  %3 = load %struct.__sFILE*, %struct.__sFILE** %fp, align 8, !dbg !3379
  %call1 = call i8* @fgets(i8* %arraydecay, i32 10000, %struct.__sFILE* %3), !dbg !3380
  %cmp2 = icmp ne i8* %call1, null, !dbg !3381
  br i1 %cmp2, label %while.body, label %while.end210, !dbg !3377

while.body:                                       ; preds = %while.cond
  %arraydecay3 = getelementptr inbounds [10000 x i8], [10000 x i8]* %line, i64 0, i64 0, !dbg !3382
  %call4 = call i8* @strchr(i8* %arraydecay3, i32 35), !dbg !3385
  store i8* %call4, i8** %cp, align 8, !dbg !3386
  %cmp5 = icmp ne i8* %call4, null, !dbg !3387
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !3388

if.then6:                                         ; preds = %while.body
  %4 = load i8*, i8** %cp, align 8, !dbg !3389
  store i8 0, i8* %4, align 1, !dbg !3390
  br label %if.end7, !dbg !3391

if.end7:                                          ; preds = %if.then6, %while.body
  %arraydecay8 = getelementptr inbounds [10000 x i8], [10000 x i8]* %line, i64 0, i64 0, !dbg !3392
  store i8* %arraydecay8, i8** %cp, align 8, !dbg !3393
  %5 = load i8*, i8** %cp, align 8, !dbg !3394
  %call9 = call i64 @strspn(i8* %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.77, i64 0, i64 0)), !dbg !3395
  %6 = load i8*, i8** %cp, align 8, !dbg !3396
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %call9, !dbg !3396
  store i8* %add.ptr, i8** %cp, align 8, !dbg !3396
  br label %while.cond10, !dbg !3397

while.cond10:                                     ; preds = %if.end206, %if.end7
  %7 = load i8*, i8** %cp, align 8, !dbg !3398
  %8 = load i8, i8* %7, align 1, !dbg !3399
  %conv = sext i8 %8 to i32, !dbg !3399
  %cmp11 = icmp ne i32 %conv, 0, !dbg !3400
  br i1 %cmp11, label %while.body13, label %while.end209, !dbg !3397

while.body13:                                     ; preds = %while.cond10
  %9 = load i8*, i8** %cp, align 8, !dbg !3401
  %10 = load i8*, i8** %cp, align 8, !dbg !3403
  %call14 = call i64 @strcspn(i8* %10, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.77, i64 0, i64 0)), !dbg !3404
  %add.ptr15 = getelementptr inbounds i8, i8* %9, i64 %call14, !dbg !3405
  store i8* %add.ptr15, i8** %cp2, align 8, !dbg !3406
  br label %while.cond16, !dbg !3407

while.cond16:                                     ; preds = %while.body30, %while.body13
  %11 = load i8*, i8** %cp2, align 8, !dbg !3408
  %12 = load i8, i8* %11, align 1, !dbg !3409
  %conv17 = sext i8 %12 to i32, !dbg !3409
  %cmp18 = icmp eq i32 %conv17, 32, !dbg !3410
  br i1 %cmp18, label %lor.end, label %lor.lhs.false, !dbg !3411

lor.lhs.false:                                    ; preds = %while.cond16
  %13 = load i8*, i8** %cp2, align 8, !dbg !3412
  %14 = load i8, i8* %13, align 1, !dbg !3413
  %conv20 = sext i8 %14 to i32, !dbg !3413
  %cmp21 = icmp eq i32 %conv20, 9, !dbg !3414
  br i1 %cmp21, label %lor.end, label %lor.lhs.false23, !dbg !3415

lor.lhs.false23:                                  ; preds = %lor.lhs.false
  %15 = load i8*, i8** %cp2, align 8, !dbg !3416
  %16 = load i8, i8* %15, align 1, !dbg !3417
  %conv24 = sext i8 %16 to i32, !dbg !3417
  %cmp25 = icmp eq i32 %conv24, 10, !dbg !3418
  br i1 %cmp25, label %lor.end, label %lor.rhs, !dbg !3419

lor.rhs:                                          ; preds = %lor.lhs.false23
  %17 = load i8*, i8** %cp2, align 8, !dbg !3420
  %18 = load i8, i8* %17, align 1, !dbg !3421
  %conv27 = sext i8 %18 to i32, !dbg !3421
  %cmp28 = icmp eq i32 %conv27, 13, !dbg !3422
  br label %lor.end, !dbg !3419

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false23, %lor.lhs.false, %while.cond16
  %19 = phi i1 [ true, %lor.lhs.false23 ], [ true, %lor.lhs.false ], [ true, %while.cond16 ], [ %cmp28, %lor.rhs ]
  br i1 %19, label %while.body30, label %while.end, !dbg !3407

while.body30:                                     ; preds = %lor.end
  %20 = load i8*, i8** %cp2, align 8, !dbg !3423
  %incdec.ptr = getelementptr inbounds i8, i8* %20, i32 1, !dbg !3423
  store i8* %incdec.ptr, i8** %cp2, align 8, !dbg !3423
  store i8 0, i8* %20, align 1, !dbg !3424
  br label %while.cond16, !dbg !3407, !llvm.loop !3425

while.end:                                        ; preds = %lor.end
  %21 = load i8*, i8** %cp, align 8, !dbg !3427
  store i8* %21, i8** %name, align 8, !dbg !3428
  %22 = load i8*, i8** %name, align 8, !dbg !3429
  %call31 = call i8* @strchr(i8* %22, i32 61), !dbg !3430
  store i8* %call31, i8** %value, align 8, !dbg !3431
  %23 = load i8*, i8** %value, align 8, !dbg !3432
  %cmp32 = icmp ne i8* %23, null, !dbg !3434
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !3435

if.then34:                                        ; preds = %while.end
  %24 = load i8*, i8** %value, align 8, !dbg !3436
  %incdec.ptr35 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !3436
  store i8* %incdec.ptr35, i8** %value, align 8, !dbg !3436
  store i8 0, i8* %24, align 1, !dbg !3437
  br label %if.end36, !dbg !3438

if.end36:                                         ; preds = %if.then34, %while.end
  %25 = load i8*, i8** %name, align 8, !dbg !3439
  %call37 = call i32 @strcasecmp(i8* %25, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.78, i64 0, i64 0)), !dbg !3441
  %cmp38 = icmp eq i32 %call37, 0, !dbg !3442
  br i1 %cmp38, label %if.then40, label %if.else, !dbg !3443

if.then40:                                        ; preds = %if.end36
  %26 = load i8*, i8** %name, align 8, !dbg !3444
  %27 = load i8*, i8** %value, align 8, !dbg !3446
  call void @no_value_required(i8* %26, i8* %27), !dbg !3447
  store i32 1, i32* @debug, align 4, !dbg !3448
  br label %if.end206, !dbg !3449

if.else:                                          ; preds = %if.end36
  %28 = load i8*, i8** %name, align 8, !dbg !3450
  %call41 = call i32 @strcasecmp(i8* %28, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.79, i64 0, i64 0)), !dbg !3452
  %cmp42 = icmp eq i32 %call41, 0, !dbg !3453
  br i1 %cmp42, label %if.then44, label %if.else47, !dbg !3454

if.then44:                                        ; preds = %if.else
  %29 = load i8*, i8** %name, align 8, !dbg !3455
  %30 = load i8*, i8** %value, align 8, !dbg !3457
  call void @value_required(i8* %29, i8* %30), !dbg !3458
  %31 = load i8*, i8** %value, align 8, !dbg !3459
  %call45 = call i32 @atoi(i8* %31), !dbg !3460
  %conv46 = trunc i32 %call45 to i16, !dbg !3461
  store i16 %conv46, i16* @port, align 2, !dbg !3462
  br label %if.end205, !dbg !3463

if.else47:                                        ; preds = %if.else
  %32 = load i8*, i8** %name, align 8, !dbg !3464
  %call48 = call i32 @strcasecmp(i8* %32, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.80, i64 0, i64 0)), !dbg !3466
  %cmp49 = icmp eq i32 %call48, 0, !dbg !3467
  br i1 %cmp49, label %if.then51, label %if.else53, !dbg !3468

if.then51:                                        ; preds = %if.else47
  %33 = load i8*, i8** %name, align 8, !dbg !3469
  %34 = load i8*, i8** %value, align 8, !dbg !3471
  call void @value_required(i8* %33, i8* %34), !dbg !3472
  %35 = load i8*, i8** %value, align 8, !dbg !3473
  %call52 = call i8* @e_strdup(i8* %35), !dbg !3474
  store i8* %call52, i8** @dir, align 8, !dbg !3475
  br label %if.end204, !dbg !3476

if.else53:                                        ; preds = %if.else47
  %36 = load i8*, i8** %name, align 8, !dbg !3477
  %call54 = call i32 @strcasecmp(i8* %36, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.22, i64 0, i64 0)), !dbg !3479
  %cmp55 = icmp eq i32 %call54, 0, !dbg !3480
  br i1 %cmp55, label %if.then57, label %if.else58, !dbg !3481

if.then57:                                        ; preds = %if.else53
  %37 = load i8*, i8** %name, align 8, !dbg !3482
  %38 = load i8*, i8** %value, align 8, !dbg !3484
  call void @no_value_required(i8* %37, i8* %38), !dbg !3485
  store i32 1, i32* @do_chroot, align 4, !dbg !3486
  store i32 1, i32* @no_symlink_check, align 4, !dbg !3487
  br label %if.end203, !dbg !3488

if.else58:                                        ; preds = %if.else53
  %39 = load i8*, i8** %name, align 8, !dbg !3489
  %call59 = call i32 @strcasecmp(i8* %39, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.81, i64 0, i64 0)), !dbg !3491
  %cmp60 = icmp eq i32 %call59, 0, !dbg !3492
  br i1 %cmp60, label %if.then62, label %if.else63, !dbg !3493

if.then62:                                        ; preds = %if.else58
  %40 = load i8*, i8** %name, align 8, !dbg !3494
  %41 = load i8*, i8** %value, align 8, !dbg !3496
  call void @no_value_required(i8* %40, i8* %41), !dbg !3497
  store i32 0, i32* @do_chroot, align 4, !dbg !3498
  store i32 0, i32* @no_symlink_check, align 4, !dbg !3499
  br label %if.end202, !dbg !3500

if.else63:                                        ; preds = %if.else58
  %42 = load i8*, i8** %name, align 8, !dbg !3501
  %call64 = call i32 @strcasecmp(i8* %42, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.82, i64 0, i64 0)), !dbg !3503
  %cmp65 = icmp eq i32 %call64, 0, !dbg !3504
  br i1 %cmp65, label %if.then67, label %if.else69, !dbg !3505

if.then67:                                        ; preds = %if.else63
  %43 = load i8*, i8** %name, align 8, !dbg !3506
  %44 = load i8*, i8** %value, align 8, !dbg !3508
  call void @value_required(i8* %43, i8* %44), !dbg !3509
  %45 = load i8*, i8** %value, align 8, !dbg !3510
  %call68 = call i8* @e_strdup(i8* %45), !dbg !3511
  store i8* %call68, i8** @data_dir, align 8, !dbg !3512
  br label %if.end201, !dbg !3513

if.else69:                                        ; preds = %if.else63
  %46 = load i8*, i8** %name, align 8, !dbg !3514
  %call70 = call i32 @strcasecmp(i8* %46, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.83, i64 0, i64 0)), !dbg !3516
  %cmp71 = icmp eq i32 %call70, 0, !dbg !3517
  br i1 %cmp71, label %if.then73, label %if.else74, !dbg !3518

if.then73:                                        ; preds = %if.else69
  %47 = load i8*, i8** %name, align 8, !dbg !3519
  %48 = load i8*, i8** %value, align 8, !dbg !3521
  call void @no_value_required(i8* %47, i8* %48), !dbg !3522
  store i32 1, i32* @no_symlink_check, align 4, !dbg !3523
  br label %if.end200, !dbg !3524

if.else74:                                        ; preds = %if.else69
  %49 = load i8*, i8** %name, align 8, !dbg !3525
  %call75 = call i32 @strcasecmp(i8* %49, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.84, i64 0, i64 0)), !dbg !3527
  %cmp76 = icmp eq i32 %call75, 0, !dbg !3528
  br i1 %cmp76, label %if.then78, label %if.else79, !dbg !3529

if.then78:                                        ; preds = %if.else74
  %50 = load i8*, i8** %name, align 8, !dbg !3530
  %51 = load i8*, i8** %value, align 8, !dbg !3532
  call void @no_value_required(i8* %50, i8* %51), !dbg !3533
  store i32 0, i32* @no_symlink_check, align 4, !dbg !3534
  br label %if.end199, !dbg !3535

if.else79:                                        ; preds = %if.else74
  %52 = load i8*, i8** %name, align 8, !dbg !3536
  %call80 = call i32 @strcasecmp(i8* %52, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.85, i64 0, i64 0)), !dbg !3538
  %cmp81 = icmp eq i32 %call80, 0, !dbg !3539
  br i1 %cmp81, label %if.then83, label %if.else85, !dbg !3540

if.then83:                                        ; preds = %if.else79
  %53 = load i8*, i8** %name, align 8, !dbg !3541
  %54 = load i8*, i8** %value, align 8, !dbg !3543
  call void @value_required(i8* %53, i8* %54), !dbg !3544
  %55 = load i8*, i8** %value, align 8, !dbg !3545
  %call84 = call i8* @e_strdup(i8* %55), !dbg !3546
  store i8* %call84, i8** @user, align 8, !dbg !3547
  br label %if.end198, !dbg !3548

if.else85:                                        ; preds = %if.else79
  %56 = load i8*, i8** %name, align 8, !dbg !3549
  %call86 = call i32 @strcasecmp(i8* %56, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.86, i64 0, i64 0)), !dbg !3551
  %cmp87 = icmp eq i32 %call86, 0, !dbg !3552
  br i1 %cmp87, label %if.then89, label %if.else91, !dbg !3553

if.then89:                                        ; preds = %if.else85
  %57 = load i8*, i8** %name, align 8, !dbg !3554
  %58 = load i8*, i8** %value, align 8, !dbg !3556
  call void @value_required(i8* %57, i8* %58), !dbg !3557
  %59 = load i8*, i8** %value, align 8, !dbg !3558
  %call90 = call i8* @e_strdup(i8* %59), !dbg !3559
  store i8* %call90, i8** @cgi_pattern, align 8, !dbg !3560
  br label %if.end197, !dbg !3561

if.else91:                                        ; preds = %if.else85
  %60 = load i8*, i8** %name, align 8, !dbg !3562
  %call92 = call i32 @strcasecmp(i8* %60, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.87, i64 0, i64 0)), !dbg !3564
  %cmp93 = icmp eq i32 %call92, 0, !dbg !3565
  br i1 %cmp93, label %if.then95, label %if.else97, !dbg !3566

if.then95:                                        ; preds = %if.else91
  %61 = load i8*, i8** %name, align 8, !dbg !3567
  %62 = load i8*, i8** %value, align 8, !dbg !3569
  call void @value_required(i8* %61, i8* %62), !dbg !3570
  %63 = load i8*, i8** %value, align 8, !dbg !3571
  %call96 = call i32 @atoi(i8* %63), !dbg !3572
  store i32 %call96, i32* @cgi_limit, align 4, !dbg !3573
  br label %if.end196, !dbg !3574

if.else97:                                        ; preds = %if.else91
  %64 = load i8*, i8** %name, align 8, !dbg !3575
  %call98 = call i32 @strcasecmp(i8* %64, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.88, i64 0, i64 0)), !dbg !3577
  %cmp99 = icmp eq i32 %call98, 0, !dbg !3578
  br i1 %cmp99, label %if.then101, label %if.else103, !dbg !3579

if.then101:                                       ; preds = %if.else97
  %65 = load i8*, i8** %name, align 8, !dbg !3580
  %66 = load i8*, i8** %value, align 8, !dbg !3582
  call void @value_required(i8* %65, i8* %66), !dbg !3583
  %67 = load i8*, i8** %value, align 8, !dbg !3584
  %call102 = call i8* @e_strdup(i8* %67), !dbg !3585
  store i8* %call102, i8** @url_pattern, align 8, !dbg !3586
  br label %if.end195, !dbg !3587

if.else103:                                       ; preds = %if.else97
  %68 = load i8*, i8** %name, align 8, !dbg !3588
  %call104 = call i32 @strcasecmp(i8* %68, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.89, i64 0, i64 0)), !dbg !3590
  %cmp105 = icmp eq i32 %call104, 0, !dbg !3591
  br i1 %cmp105, label %if.then111, label %lor.lhs.false107, !dbg !3592

lor.lhs.false107:                                 ; preds = %if.else103
  %69 = load i8*, i8** %name, align 8, !dbg !3593
  %call108 = call i32 @strcasecmp(i8* %69, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.90, i64 0, i64 0)), !dbg !3594
  %cmp109 = icmp eq i32 %call108, 0, !dbg !3595
  br i1 %cmp109, label %if.then111, label %if.else112, !dbg !3596

if.then111:                                       ; preds = %lor.lhs.false107, %if.else103
  %70 = load i8*, i8** %name, align 8, !dbg !3597
  %71 = load i8*, i8** %value, align 8, !dbg !3599
  call void @no_value_required(i8* %70, i8* %71), !dbg !3600
  store i32 1, i32* @no_empty_referrers, align 4, !dbg !3601
  br label %if.end194, !dbg !3602

if.else112:                                       ; preds = %lor.lhs.false107
  %72 = load i8*, i8** %name, align 8, !dbg !3603
  %call113 = call i32 @strcasecmp(i8* %72, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.91, i64 0, i64 0)), !dbg !3605
  %cmp114 = icmp eq i32 %call113, 0, !dbg !3606
  br i1 %cmp114, label %if.then116, label %if.else118, !dbg !3607

if.then116:                                       ; preds = %if.else112
  %73 = load i8*, i8** %name, align 8, !dbg !3608
  %74 = load i8*, i8** %value, align 8, !dbg !3610
  call void @value_required(i8* %73, i8* %74), !dbg !3611
  %75 = load i8*, i8** %value, align 8, !dbg !3612
  %call117 = call i8* @e_strdup(i8* %75), !dbg !3613
  store i8* %call117, i8** @local_pattern, align 8, !dbg !3614
  br label %if.end193, !dbg !3615

if.else118:                                       ; preds = %if.else112
  %76 = load i8*, i8** %name, align 8, !dbg !3616
  %call119 = call i32 @strcasecmp(i8* %76, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.92, i64 0, i64 0)), !dbg !3618
  %cmp120 = icmp eq i32 %call119, 0, !dbg !3619
  br i1 %cmp120, label %if.then122, label %if.else124, !dbg !3620

if.then122:                                       ; preds = %if.else118
  %77 = load i8*, i8** %name, align 8, !dbg !3621
  %78 = load i8*, i8** %value, align 8, !dbg !3623
  call void @value_required(i8* %77, i8* %78), !dbg !3624
  %79 = load i8*, i8** %value, align 8, !dbg !3625
  %call123 = call i8* @e_strdup(i8* %79), !dbg !3626
  store i8* %call123, i8** @throttlefile, align 8, !dbg !3627
  br label %if.end192, !dbg !3628

if.else124:                                       ; preds = %if.else118
  %80 = load i8*, i8** %name, align 8, !dbg !3629
  %call125 = call i32 @strcasecmp(i8* %80, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.93, i64 0, i64 0)), !dbg !3631
  %cmp126 = icmp eq i32 %call125, 0, !dbg !3632
  br i1 %cmp126, label %if.then128, label %if.else130, !dbg !3633

if.then128:                                       ; preds = %if.else124
  %81 = load i8*, i8** %name, align 8, !dbg !3634
  %82 = load i8*, i8** %value, align 8, !dbg !3636
  call void @value_required(i8* %81, i8* %82), !dbg !3637
  %83 = load i8*, i8** %value, align 8, !dbg !3638
  %call129 = call i8* @e_strdup(i8* %83), !dbg !3639
  store i8* %call129, i8** @hostname, align 8, !dbg !3640
  br label %if.end191, !dbg !3641

if.else130:                                       ; preds = %if.else124
  %84 = load i8*, i8** %name, align 8, !dbg !3642
  %call131 = call i32 @strcasecmp(i8* %84, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.94, i64 0, i64 0)), !dbg !3644
  %cmp132 = icmp eq i32 %call131, 0, !dbg !3645
  br i1 %cmp132, label %if.then134, label %if.else136, !dbg !3646

if.then134:                                       ; preds = %if.else130
  %85 = load i8*, i8** %name, align 8, !dbg !3647
  %86 = load i8*, i8** %value, align 8, !dbg !3649
  call void @value_required(i8* %85, i8* %86), !dbg !3650
  %87 = load i8*, i8** %value, align 8, !dbg !3651
  %call135 = call i8* @e_strdup(i8* %87), !dbg !3652
  store i8* %call135, i8** @logfile, align 8, !dbg !3653
  br label %if.end190, !dbg !3654

if.else136:                                       ; preds = %if.else130
  %88 = load i8*, i8** %name, align 8, !dbg !3655
  %call137 = call i32 @strcasecmp(i8* %88, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.95, i64 0, i64 0)), !dbg !3657
  %cmp138 = icmp eq i32 %call137, 0, !dbg !3658
  br i1 %cmp138, label %if.then140, label %if.else141, !dbg !3659

if.then140:                                       ; preds = %if.else136
  %89 = load i8*, i8** %name, align 8, !dbg !3660
  %90 = load i8*, i8** %value, align 8, !dbg !3662
  call void @no_value_required(i8* %89, i8* %90), !dbg !3663
  store i32 1, i32* @do_vhost, align 4, !dbg !3664
  br label %if.end189, !dbg !3665

if.else141:                                       ; preds = %if.else136
  %91 = load i8*, i8** %name, align 8, !dbg !3666
  %call142 = call i32 @strcasecmp(i8* %91, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.96, i64 0, i64 0)), !dbg !3668
  %cmp143 = icmp eq i32 %call142, 0, !dbg !3669
  br i1 %cmp143, label %if.then145, label %if.else146, !dbg !3670

if.then145:                                       ; preds = %if.else141
  %92 = load i8*, i8** %name, align 8, !dbg !3671
  %93 = load i8*, i8** %value, align 8, !dbg !3673
  call void @no_value_required(i8* %92, i8* %93), !dbg !3674
  store i32 0, i32* @do_vhost, align 4, !dbg !3675
  br label %if.end188, !dbg !3676

if.else146:                                       ; preds = %if.else141
  %94 = load i8*, i8** %name, align 8, !dbg !3677
  %call147 = call i32 @strcasecmp(i8* %94, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.97, i64 0, i64 0)), !dbg !3679
  %cmp148 = icmp eq i32 %call147, 0, !dbg !3680
  br i1 %cmp148, label %if.then150, label %if.else151, !dbg !3681

if.then150:                                       ; preds = %if.else146
  %95 = load i8*, i8** %name, align 8, !dbg !3682
  %96 = load i8*, i8** %value, align 8, !dbg !3684
  call void @no_value_required(i8* %95, i8* %96), !dbg !3685
  store i32 1, i32* @do_global_passwd, align 4, !dbg !3686
  br label %if.end187, !dbg !3687

if.else151:                                       ; preds = %if.else146
  %97 = load i8*, i8** %name, align 8, !dbg !3688
  %call152 = call i32 @strcasecmp(i8* %97, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.98, i64 0, i64 0)), !dbg !3690
  %cmp153 = icmp eq i32 %call152, 0, !dbg !3691
  br i1 %cmp153, label %if.then155, label %if.else156, !dbg !3692

if.then155:                                       ; preds = %if.else151
  %98 = load i8*, i8** %name, align 8, !dbg !3693
  %99 = load i8*, i8** %value, align 8, !dbg !3695
  call void @no_value_required(i8* %98, i8* %99), !dbg !3696
  store i32 0, i32* @do_global_passwd, align 4, !dbg !3697
  br label %if.end186, !dbg !3698

if.else156:                                       ; preds = %if.else151
  %100 = load i8*, i8** %name, align 8, !dbg !3699
  %call157 = call i32 @strcasecmp(i8* %100, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.99, i64 0, i64 0)), !dbg !3701
  %cmp158 = icmp eq i32 %call157, 0, !dbg !3702
  br i1 %cmp158, label %if.then160, label %if.else162, !dbg !3703

if.then160:                                       ; preds = %if.else156
  %101 = load i8*, i8** %name, align 8, !dbg !3704
  %102 = load i8*, i8** %value, align 8, !dbg !3706
  call void @value_required(i8* %101, i8* %102), !dbg !3707
  %103 = load i8*, i8** %value, align 8, !dbg !3708
  %call161 = call i8* @e_strdup(i8* %103), !dbg !3709
  store i8* %call161, i8** @pidfile, align 8, !dbg !3710
  br label %if.end185, !dbg !3711

if.else162:                                       ; preds = %if.else156
  %104 = load i8*, i8** %name, align 8, !dbg !3712
  %call163 = call i32 @strcasecmp(i8* %104, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.100, i64 0, i64 0)), !dbg !3714
  %cmp164 = icmp eq i32 %call163, 0, !dbg !3715
  br i1 %cmp164, label %if.then166, label %if.else168, !dbg !3716

if.then166:                                       ; preds = %if.else162
  %105 = load i8*, i8** %name, align 8, !dbg !3717
  %106 = load i8*, i8** %value, align 8, !dbg !3719
  call void @value_required(i8* %105, i8* %106), !dbg !3720
  %107 = load i8*, i8** %value, align 8, !dbg !3721
  %call167 = call i8* @e_strdup(i8* %107), !dbg !3722
  store i8* %call167, i8** @charset, align 8, !dbg !3723
  br label %if.end184, !dbg !3724

if.else168:                                       ; preds = %if.else162
  %108 = load i8*, i8** %name, align 8, !dbg !3725
  %call169 = call i32 @strcasecmp(i8* %108, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.101, i64 0, i64 0)), !dbg !3727
  %cmp170 = icmp eq i32 %call169, 0, !dbg !3728
  br i1 %cmp170, label %if.then172, label %if.else174, !dbg !3729

if.then172:                                       ; preds = %if.else168
  %109 = load i8*, i8** %name, align 8, !dbg !3730
  %110 = load i8*, i8** %value, align 8, !dbg !3732
  call void @value_required(i8* %109, i8* %110), !dbg !3733
  %111 = load i8*, i8** %value, align 8, !dbg !3734
  %call173 = call i8* @e_strdup(i8* %111), !dbg !3735
  store i8* %call173, i8** @p3p, align 8, !dbg !3736
  br label %if.end183, !dbg !3737

if.else174:                                       ; preds = %if.else168
  %112 = load i8*, i8** %name, align 8, !dbg !3738
  %call175 = call i32 @strcasecmp(i8* %112, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.102, i64 0, i64 0)), !dbg !3740
  %cmp176 = icmp eq i32 %call175, 0, !dbg !3741
  br i1 %cmp176, label %if.then178, label %if.else180, !dbg !3742

if.then178:                                       ; preds = %if.else174
  %113 = load i8*, i8** %name, align 8, !dbg !3743
  %114 = load i8*, i8** %value, align 8, !dbg !3745
  call void @value_required(i8* %113, i8* %114), !dbg !3746
  %115 = load i8*, i8** %value, align 8, !dbg !3747
  %call179 = call i32 @atoi(i8* %115), !dbg !3748
  store i32 %call179, i32* @max_age, align 4, !dbg !3749
  br label %if.end182, !dbg !3750

if.else180:                                       ; preds = %if.else174
  %116 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !3751
  %117 = load i8*, i8** @argv0, align 8, !dbg !3753
  %118 = load i8*, i8** %name, align 8, !dbg !3754
  %call181 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %116, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.103, i64 0, i64 0), i8* %117, i8* %118), !dbg !3755
  call void @exit(i32 1) #11, !dbg !3756
  unreachable, !dbg !3756

if.end182:                                        ; preds = %if.then178
  br label %if.end183

if.end183:                                        ; preds = %if.end182, %if.then172
  br label %if.end184

if.end184:                                        ; preds = %if.end183, %if.then166
  br label %if.end185

if.end185:                                        ; preds = %if.end184, %if.then160
  br label %if.end186

if.end186:                                        ; preds = %if.end185, %if.then155
  br label %if.end187

if.end187:                                        ; preds = %if.end186, %if.then150
  br label %if.end188

if.end188:                                        ; preds = %if.end187, %if.then145
  br label %if.end189

if.end189:                                        ; preds = %if.end188, %if.then140
  br label %if.end190

if.end190:                                        ; preds = %if.end189, %if.then134
  br label %if.end191

if.end191:                                        ; preds = %if.end190, %if.then128
  br label %if.end192

if.end192:                                        ; preds = %if.end191, %if.then122
  br label %if.end193

if.end193:                                        ; preds = %if.end192, %if.then116
  br label %if.end194

if.end194:                                        ; preds = %if.end193, %if.then111
  br label %if.end195

if.end195:                                        ; preds = %if.end194, %if.then101
  br label %if.end196

if.end196:                                        ; preds = %if.end195, %if.then95
  br label %if.end197

if.end197:                                        ; preds = %if.end196, %if.then89
  br label %if.end198

if.end198:                                        ; preds = %if.end197, %if.then83
  br label %if.end199

if.end199:                                        ; preds = %if.end198, %if.then78
  br label %if.end200

if.end200:                                        ; preds = %if.end199, %if.then73
  br label %if.end201

if.end201:                                        ; preds = %if.end200, %if.then67
  br label %if.end202

if.end202:                                        ; preds = %if.end201, %if.then62
  br label %if.end203

if.end203:                                        ; preds = %if.end202, %if.then57
  br label %if.end204

if.end204:                                        ; preds = %if.end203, %if.then51
  br label %if.end205

if.end205:                                        ; preds = %if.end204, %if.then44
  br label %if.end206

if.end206:                                        ; preds = %if.end205, %if.then40
  %119 = load i8*, i8** %cp2, align 8, !dbg !3757
  store i8* %119, i8** %cp, align 8, !dbg !3758
  %120 = load i8*, i8** %cp, align 8, !dbg !3759
  %call207 = call i64 @strspn(i8* %120, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.77, i64 0, i64 0)), !dbg !3760
  %121 = load i8*, i8** %cp, align 8, !dbg !3761
  %add.ptr208 = getelementptr inbounds i8, i8* %121, i64 %call207, !dbg !3761
  store i8* %add.ptr208, i8** %cp, align 8, !dbg !3761
  br label %while.cond10, !dbg !3397, !llvm.loop !3762

while.end209:                                     ; preds = %while.cond10
  br label %while.cond, !dbg !3377, !llvm.loop !3764

while.end210:                                     ; preds = %while.cond
  %122 = load %struct.__sFILE*, %struct.__sFILE** %fp, align 8, !dbg !3766
  %call211 = call i32 @fclose(%struct.__sFILE* %122), !dbg !3767
  ret void, !dbg !3768
}

declare i32 @atoi(i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @usage() #0 !dbg !3769 {
entry:
  %0 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !3770
  %1 = load i8*, i8** @argv0, align 8, !dbg !3771
  %call = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %0, i8* getelementptr inbounds ([219 x i8], [219 x i8]* @.str.108, i64 0, i64 0), i8* %1), !dbg !3772
  call void @exit(i32 1) #11, !dbg !3773
  unreachable, !dbg !3773
}

declare i8* @fgets(i8*, i32, %struct.__sFILE*) #3

declare i8* @strchr(i8*, i32) #3

declare i64 @strspn(i8*, i8*) #3

declare i64 @strcspn(i8*, i8*) #3

declare i32 @strcasecmp(i8*, i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @no_value_required(i8* %name, i8* %value) #0 !dbg !3774 {
entry:
  %name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3777, metadata !DIExpression()), !dbg !3778
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3779, metadata !DIExpression()), !dbg !3780
  %0 = load i8*, i8** %value.addr, align 8, !dbg !3781
  %cmp = icmp ne i8* %0, null, !dbg !3783
  br i1 %cmp, label %if.then, label %if.end, !dbg !3784

if.then:                                          ; preds = %entry
  %1 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !3785
  %2 = load i8*, i8** @argv0, align 8, !dbg !3787
  %3 = load i8*, i8** %name.addr, align 8, !dbg !3788
  %call = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %1, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.104, i64 0, i64 0), i8* %2, i8* %3), !dbg !3789
  call void @exit(i32 1) #11, !dbg !3790
  unreachable, !dbg !3790

if.end:                                           ; preds = %entry
  ret void, !dbg !3791
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @value_required(i8* %name, i8* %value) #0 !dbg !3792 {
entry:
  %name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3793, metadata !DIExpression()), !dbg !3794
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3795, metadata !DIExpression()), !dbg !3796
  %0 = load i8*, i8** %value.addr, align 8, !dbg !3797
  %cmp = icmp eq i8* %0, null, !dbg !3799
  br i1 %cmp, label %if.then, label %if.end, !dbg !3800

if.then:                                          ; preds = %entry
  %1 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !3801
  %2 = load i8*, i8** @argv0, align 8, !dbg !3803
  %3 = load i8*, i8** %name.addr, align 8, !dbg !3804
  %call = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.105, i64 0, i64 0), i8* %2, i8* %3), !dbg !3805
  call void @exit(i32 1) #11, !dbg !3806
  unreachable, !dbg !3806

if.end:                                           ; preds = %entry
  ret void, !dbg !3807
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal i8* @e_strdup(i8* %oldstr) #0 !dbg !3808 {
entry:
  %oldstr.addr = alloca i8*, align 8
  %newstr = alloca i8*, align 8
  store i8* %oldstr, i8** %oldstr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %oldstr.addr, metadata !3811, metadata !DIExpression()), !dbg !3812
  call void @llvm.dbg.declare(metadata i8** %newstr, metadata !3813, metadata !DIExpression()), !dbg !3814
  %0 = load i8*, i8** %oldstr.addr, align 8, !dbg !3815
  %call = call i8* @strdup(i8* %0), !dbg !3816
  store i8* %call, i8** %newstr, align 8, !dbg !3817
  %1 = load i8*, i8** %newstr, align 8, !dbg !3818
  %cmp = icmp eq i8* %1, null, !dbg !3820
  br i1 %cmp, label %if.then, label %if.end, !dbg !3821

if.then:                                          ; preds = %entry
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 2, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.106, i64 0, i64 0)), !dbg !3822
  %2 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !dbg !3824
  %3 = load i8*, i8** @argv0, align 8, !dbg !3825
  %call1 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %2, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.107, i64 0, i64 0), i8* %3), !dbg !3826
  call void @exit(i32 1) #11, !dbg !3827
  unreachable, !dbg !3827

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %newstr, align 8, !dbg !3828
  ret i8* %4, !dbg !3829
}

declare i8* @strdup(i8*) #3

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #9

declare i32 @__snprintf_chk(i8*, i64, i32, i64, i8*, ...) #3

declare i32 @getaddrinfo(i8*, i8*, %struct.addrinfo*, %struct.addrinfo**) #3

declare i8* @gai_strerror(i32) #3

; Function Attrs: nounwind
declare i8* @__memset_chk(i8*, i32, i64, i64) #6

declare void @freeaddrinfo(%struct.addrinfo*) #3

declare i32 @sscanf(i8*, i8*, ...) #3

declare i8* @strstr(i8*, i8*) #3

; Function Attrs: allocsize(1)
declare i8* @realloc(i8*, i64) #10

declare void @httpd_close_conn(%struct.httpd_conn*, %struct.timeval*) #3

declare void @httpd_destroy_conn(%struct.httpd_conn*) #3

declare void @free(i8*) #3

declare void @httpd_terminate(%struct.httpd_server*) #3

declare void @mmc_term() #3

declare void @tmr_term() #3

declare i32 @httpd_get_conn(%struct.httpd_server*, i32, %struct.httpd_conn*) #3

declare void @httpd_set_ndelay(i32) #3

declare void @httpd_send_err(%struct.httpd_conn*, i32, i8*, i8*, i8*, i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @finish_connection(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !3830 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !3831, metadata !DIExpression()), !dbg !3832
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !3833, metadata !DIExpression()), !dbg !3834
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3835
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 2, !dbg !3836
  %1 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3836
  call void @httpd_write_response(%struct.httpd_conn* %1), !dbg !3837
  %2 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3838
  %3 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !3839
  call void @clear_connection(%struct.connecttab* %2, %struct.timeval* %3), !dbg !3840
  ret void, !dbg !3841
}

declare void @httpd_realloc_str(i8**, i64*, i64) #3

declare i64 @"\01_read"(i32, i8*, i64) #3

declare i32 @httpd_got_request(%struct.httpd_conn*) #3

declare i32 @httpd_parse_request(%struct.httpd_conn*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal i32 @check_throttles(%struct.connecttab* %c) #0 !dbg !3842 {
entry:
  %retval = alloca i32, align 4
  %c.addr = alloca %struct.connecttab*, align 8
  %tnum = alloca i32, align 4
  %l = alloca i64, align 8
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !3845, metadata !DIExpression()), !dbg !3846
  call void @llvm.dbg.declare(metadata i32* %tnum, metadata !3847, metadata !DIExpression()), !dbg !3848
  call void @llvm.dbg.declare(metadata i64* %l, metadata !3849, metadata !DIExpression()), !dbg !3850
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3851
  %numtnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 4, !dbg !3852
  store i32 0, i32* %numtnums, align 8, !dbg !3853
  %1 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3854
  %min_limit = getelementptr inbounds %struct.connecttab, %struct.connecttab* %1, i32 0, i32 6, !dbg !3855
  store i64 -1, i64* %min_limit, align 8, !dbg !3856
  %2 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3857
  %max_limit = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i32 0, i32 5, !dbg !3858
  store i64 -1, i64* %max_limit, align 8, !dbg !3859
  store i32 0, i32* %tnum, align 4, !dbg !3860
  br label %for.cond, !dbg !3862

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i32, i32* %tnum, align 4, !dbg !3863
  %4 = load i32, i32* @numthrottles, align 4, !dbg !3865
  %cmp = icmp slt i32 %3, %4, !dbg !3866
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !3867

land.rhs:                                         ; preds = %for.cond
  %5 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3868
  %numtnums1 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %5, i32 0, i32 4, !dbg !3869
  %6 = load i32, i32* %numtnums1, align 8, !dbg !3869
  %cmp2 = icmp slt i32 %6, 10, !dbg !3870
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %7 = phi i1 [ false, %for.cond ], [ %cmp2, %land.rhs ], !dbg !3871
  br i1 %7, label %for.body, label %for.end, !dbg !3872

for.body:                                         ; preds = %land.end
  %8 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3873
  %9 = load i32, i32* %tnum, align 4, !dbg !3875
  %idxprom = sext i32 %9 to i64, !dbg !3873
  %arrayidx = getelementptr inbounds %struct.throttletab, %struct.throttletab* %8, i64 %idxprom, !dbg !3873
  %pattern = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx, i32 0, i32 0, !dbg !3876
  %10 = load i8*, i8** %pattern, align 8, !dbg !3876
  %11 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3877
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %11, i32 0, i32 2, !dbg !3878
  %12 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3878
  %expnfilename = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %12, i32 0, i32 16, !dbg !3879
  %13 = load i8*, i8** %expnfilename, align 8, !dbg !3879
  %call = call i32 @match(i8* %10, i8* %13), !dbg !3880
  %tobool = icmp ne i32 %call, 0, !dbg !3880
  br i1 %tobool, label %if.then, label %if.end70, !dbg !3881

if.then:                                          ; preds = %for.body
  %14 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3882
  %15 = load i32, i32* %tnum, align 4, !dbg !3885
  %idxprom3 = sext i32 %15 to i64, !dbg !3882
  %arrayidx4 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %14, i64 %idxprom3, !dbg !3882
  %rate = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx4, i32 0, i32 3, !dbg !3886
  %16 = load i64, i64* %rate, align 8, !dbg !3886
  %17 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3887
  %18 = load i32, i32* %tnum, align 4, !dbg !3888
  %idxprom5 = sext i32 %18 to i64, !dbg !3887
  %arrayidx6 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %17, i64 %idxprom5, !dbg !3887
  %max_limit7 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx6, i32 0, i32 1, !dbg !3889
  %19 = load i64, i64* %max_limit7, align 8, !dbg !3889
  %mul = mul nsw i64 %19, 2, !dbg !3890
  %cmp8 = icmp sgt i64 %16, %mul, !dbg !3891
  br i1 %cmp8, label %if.then9, label %if.end, !dbg !3892

if.then9:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !3893
  br label %return, !dbg !3893

if.end:                                           ; preds = %if.then
  %20 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3894
  %21 = load i32, i32* %tnum, align 4, !dbg !3896
  %idxprom10 = sext i32 %21 to i64, !dbg !3894
  %arrayidx11 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %20, i64 %idxprom10, !dbg !3894
  %rate12 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx11, i32 0, i32 3, !dbg !3897
  %22 = load i64, i64* %rate12, align 8, !dbg !3897
  %23 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3898
  %24 = load i32, i32* %tnum, align 4, !dbg !3899
  %idxprom13 = sext i32 %24 to i64, !dbg !3898
  %arrayidx14 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %23, i64 %idxprom13, !dbg !3898
  %min_limit15 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx14, i32 0, i32 2, !dbg !3900
  %25 = load i64, i64* %min_limit15, align 8, !dbg !3900
  %cmp16 = icmp slt i64 %22, %25, !dbg !3901
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !3902

if.then17:                                        ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !3903
  br label %return, !dbg !3903

if.end18:                                         ; preds = %if.end
  %26 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3904
  %27 = load i32, i32* %tnum, align 4, !dbg !3906
  %idxprom19 = sext i32 %27 to i64, !dbg !3904
  %arrayidx20 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %26, i64 %idxprom19, !dbg !3904
  %num_sending = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx20, i32 0, i32 5, !dbg !3907
  %28 = load i32, i32* %num_sending, align 8, !dbg !3907
  %cmp21 = icmp slt i32 %28, 0, !dbg !3908
  br i1 %cmp21, label %if.then22, label %if.end26, !dbg !3909

if.then22:                                        ; preds = %if.end18
  notail call void (i32, i8*, ...) @"\01_syslog$DARWIN_EXTSN"(i32 3, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.123, i64 0, i64 0)), !dbg !3910
  %29 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3912
  %30 = load i32, i32* %tnum, align 4, !dbg !3913
  %idxprom23 = sext i32 %30 to i64, !dbg !3912
  %arrayidx24 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %29, i64 %idxprom23, !dbg !3912
  %num_sending25 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx24, i32 0, i32 5, !dbg !3914
  store i32 0, i32* %num_sending25, align 8, !dbg !3915
  br label %if.end26, !dbg !3916

if.end26:                                         ; preds = %if.then22, %if.end18
  %31 = load i32, i32* %tnum, align 4, !dbg !3917
  %32 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3918
  %tnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %32, i32 0, i32 3, !dbg !3919
  %33 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3920
  %numtnums27 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %33, i32 0, i32 4, !dbg !3921
  %34 = load i32, i32* %numtnums27, align 8, !dbg !3922
  %inc = add nsw i32 %34, 1, !dbg !3922
  store i32 %inc, i32* %numtnums27, align 8, !dbg !3922
  %idxprom28 = sext i32 %34 to i64, !dbg !3918
  %arrayidx29 = getelementptr inbounds [10 x i32], [10 x i32]* %tnums, i64 0, i64 %idxprom28, !dbg !3918
  store i32 %31, i32* %arrayidx29, align 4, !dbg !3923
  %35 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3924
  %36 = load i32, i32* %tnum, align 4, !dbg !3925
  %idxprom30 = sext i32 %36 to i64, !dbg !3924
  %arrayidx31 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %35, i64 %idxprom30, !dbg !3924
  %num_sending32 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx31, i32 0, i32 5, !dbg !3926
  %37 = load i32, i32* %num_sending32, align 8, !dbg !3927
  %inc33 = add nsw i32 %37, 1, !dbg !3927
  store i32 %inc33, i32* %num_sending32, align 8, !dbg !3927
  %38 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3928
  %39 = load i32, i32* %tnum, align 4, !dbg !3929
  %idxprom34 = sext i32 %39 to i64, !dbg !3928
  %arrayidx35 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %38, i64 %idxprom34, !dbg !3928
  %max_limit36 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx35, i32 0, i32 1, !dbg !3930
  %40 = load i64, i64* %max_limit36, align 8, !dbg !3930
  %41 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3931
  %42 = load i32, i32* %tnum, align 4, !dbg !3932
  %idxprom37 = sext i32 %42 to i64, !dbg !3931
  %arrayidx38 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %41, i64 %idxprom37, !dbg !3931
  %num_sending39 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx38, i32 0, i32 5, !dbg !3933
  %43 = load i32, i32* %num_sending39, align 8, !dbg !3933
  %conv = sext i32 %43 to i64, !dbg !3931
  %div = sdiv i64 %40, %conv, !dbg !3934
  store i64 %div, i64* %l, align 8, !dbg !3935
  %44 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3936
  %max_limit40 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %44, i32 0, i32 5, !dbg !3938
  %45 = load i64, i64* %max_limit40, align 8, !dbg !3938
  %cmp41 = icmp eq i64 %45, -1, !dbg !3939
  br i1 %cmp41, label %if.then43, label %if.else, !dbg !3940

if.then43:                                        ; preds = %if.end26
  %46 = load i64, i64* %l, align 8, !dbg !3941
  %47 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3942
  %max_limit44 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %47, i32 0, i32 5, !dbg !3943
  store i64 %46, i64* %max_limit44, align 8, !dbg !3944
  br label %if.end50, !dbg !3942

if.else:                                          ; preds = %if.end26
  %48 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3945
  %max_limit45 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %48, i32 0, i32 5, !dbg !3945
  %49 = load i64, i64* %max_limit45, align 8, !dbg !3945
  %50 = load i64, i64* %l, align 8, !dbg !3945
  %cmp46 = icmp slt i64 %49, %50, !dbg !3945
  br i1 %cmp46, label %cond.true, label %cond.false, !dbg !3945

cond.true:                                        ; preds = %if.else
  %51 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3945
  %max_limit48 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %51, i32 0, i32 5, !dbg !3945
  %52 = load i64, i64* %max_limit48, align 8, !dbg !3945
  br label %cond.end, !dbg !3945

cond.false:                                       ; preds = %if.else
  %53 = load i64, i64* %l, align 8, !dbg !3945
  br label %cond.end, !dbg !3945

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %52, %cond.true ], [ %53, %cond.false ], !dbg !3945
  %54 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3946
  %max_limit49 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %54, i32 0, i32 5, !dbg !3947
  store i64 %cond, i64* %max_limit49, align 8, !dbg !3948
  br label %if.end50

if.end50:                                         ; preds = %cond.end, %if.then43
  %55 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !3949
  %56 = load i32, i32* %tnum, align 4, !dbg !3950
  %idxprom51 = sext i32 %56 to i64, !dbg !3949
  %arrayidx52 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %55, i64 %idxprom51, !dbg !3949
  %min_limit53 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx52, i32 0, i32 2, !dbg !3951
  %57 = load i64, i64* %min_limit53, align 8, !dbg !3951
  store i64 %57, i64* %l, align 8, !dbg !3952
  %58 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3953
  %min_limit54 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %58, i32 0, i32 6, !dbg !3955
  %59 = load i64, i64* %min_limit54, align 8, !dbg !3955
  %cmp55 = icmp eq i64 %59, -1, !dbg !3956
  br i1 %cmp55, label %if.then57, label %if.else59, !dbg !3957

if.then57:                                        ; preds = %if.end50
  %60 = load i64, i64* %l, align 8, !dbg !3958
  %61 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3959
  %min_limit58 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %61, i32 0, i32 6, !dbg !3960
  store i64 %60, i64* %min_limit58, align 8, !dbg !3961
  br label %if.end69, !dbg !3959

if.else59:                                        ; preds = %if.end50
  %62 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3962
  %min_limit60 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %62, i32 0, i32 6, !dbg !3962
  %63 = load i64, i64* %min_limit60, align 8, !dbg !3962
  %64 = load i64, i64* %l, align 8, !dbg !3962
  %cmp61 = icmp sgt i64 %63, %64, !dbg !3962
  br i1 %cmp61, label %cond.true63, label %cond.false65, !dbg !3962

cond.true63:                                      ; preds = %if.else59
  %65 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3962
  %min_limit64 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %65, i32 0, i32 6, !dbg !3962
  %66 = load i64, i64* %min_limit64, align 8, !dbg !3962
  br label %cond.end66, !dbg !3962

cond.false65:                                     ; preds = %if.else59
  %67 = load i64, i64* %l, align 8, !dbg !3962
  br label %cond.end66, !dbg !3962

cond.end66:                                       ; preds = %cond.false65, %cond.true63
  %cond67 = phi i64 [ %66, %cond.true63 ], [ %67, %cond.false65 ], !dbg !3962
  %68 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !3963
  %min_limit68 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %68, i32 0, i32 6, !dbg !3964
  store i64 %cond67, i64* %min_limit68, align 8, !dbg !3965
  br label %if.end69

if.end69:                                         ; preds = %cond.end66, %if.then57
  br label %if.end70, !dbg !3966

if.end70:                                         ; preds = %if.end69, %for.body
  br label %for.inc, !dbg !3967

for.inc:                                          ; preds = %if.end70
  %69 = load i32, i32* %tnum, align 4, !dbg !3968
  %inc71 = add nsw i32 %69, 1, !dbg !3968
  store i32 %inc71, i32* %tnum, align 4, !dbg !3968
  br label %for.cond, !dbg !3969, !llvm.loop !3970

for.end:                                          ; preds = %land.end
  store i32 1, i32* %retval, align 4, !dbg !3972
  br label %return, !dbg !3972

return:                                           ; preds = %for.end, %if.then17, %if.then9
  %70 = load i32, i32* %retval, align 4, !dbg !3973
  ret i32 %70, !dbg !3973
}

declare i32 @httpd_start_request(%struct.httpd_conn*, %struct.timeval*) #3

declare void @httpd_write_response(%struct.httpd_conn*) #3

declare i32 @match(i8*, i8*) #3

declare i64 @"\01_write"(i32, i8*, i64) #3

declare i64 @"\01_writev"(i32, %struct.iovec*, i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @wakeup_connection(i8* %client_data.coerce, %struct.timeval* %nowP) #0 !dbg !3974 {
entry:
  %client_data = alloca %union.ClientData, align 8
  %nowP.addr = alloca %struct.timeval*, align 8
  %c = alloca %struct.connecttab*, align 8
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0
  store i8* %client_data.coerce, i8** %coerce.dive, align 8
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !3975, metadata !DIExpression()), !dbg !3976
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !3977, metadata !DIExpression()), !dbg !3978
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c, metadata !3979, metadata !DIExpression()), !dbg !3980
  %p = bitcast %union.ClientData* %client_data to i8**, !dbg !3981
  %0 = load i8*, i8** %p, align 8, !dbg !3981
  %1 = bitcast i8* %0 to %struct.connecttab*, !dbg !3982
  store %struct.connecttab* %1, %struct.connecttab** %c, align 8, !dbg !3983
  %2 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !3984
  %wakeup_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i32 0, i32 9, !dbg !3985
  store %struct.TimerStruct* null, %struct.TimerStruct** %wakeup_timer, align 8, !dbg !3986
  %3 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !3987
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %3, i32 0, i32 0, !dbg !3989
  %4 = load i32, i32* %conn_state, align 8, !dbg !3989
  %cmp = icmp eq i32 %4, 3, !dbg !3990
  br i1 %cmp, label %if.then, label %if.end, !dbg !3991

if.then:                                          ; preds = %entry
  %5 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !3992
  %conn_state1 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %5, i32 0, i32 0, !dbg !3994
  store i32 2, i32* %conn_state1, align 8, !dbg !3995
  %6 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !3996
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %6, i32 0, i32 2, !dbg !3997
  %7 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !3997
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %7, i32 0, i32 60, !dbg !3998
  %8 = load i32, i32* %conn_fd, align 8, !dbg !3998
  %9 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !3999
  %10 = bitcast %struct.connecttab* %9 to i8*, !dbg !3999
  call void @fdwatch_add_fd(i32 %8, i8* %10, i32 1), !dbg !4000
  br label %if.end, !dbg !4001

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !4002
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @really_clear_connection(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !4003 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !4004, metadata !DIExpression()), !dbg !4005
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !4006, metadata !DIExpression()), !dbg !4007
  %0 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4008
  %hc = getelementptr inbounds %struct.connecttab, %struct.connecttab* %0, i32 0, i32 2, !dbg !4009
  %1 = load %struct.httpd_conn*, %struct.httpd_conn** %hc, align 8, !dbg !4009
  %bytes_sent = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %1, i32 0, i32 11, !dbg !4010
  %2 = load i64, i64* %bytes_sent, align 8, !dbg !4010
  %3 = load i64, i64* @stats_bytes, align 8, !dbg !4011
  %add = add nsw i64 %3, %2, !dbg !4011
  store i64 %add, i64* @stats_bytes, align 8, !dbg !4011
  %4 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4012
  %conn_state = getelementptr inbounds %struct.connecttab, %struct.connecttab* %4, i32 0, i32 0, !dbg !4014
  %5 = load i32, i32* %conn_state, align 8, !dbg !4014
  %cmp = icmp ne i32 %5, 3, !dbg !4015
  br i1 %cmp, label %if.then, label %if.end, !dbg !4016

if.then:                                          ; preds = %entry
  %6 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4017
  %hc1 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %6, i32 0, i32 2, !dbg !4018
  %7 = load %struct.httpd_conn*, %struct.httpd_conn** %hc1, align 8, !dbg !4018
  %conn_fd = getelementptr inbounds %struct.httpd_conn, %struct.httpd_conn* %7, i32 0, i32 60, !dbg !4019
  %8 = load i32, i32* %conn_fd, align 8, !dbg !4019
  call void @fdwatch_del_fd(i32 %8), !dbg !4020
  br label %if.end, !dbg !4020

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4021
  %hc2 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %9, i32 0, i32 2, !dbg !4022
  %10 = load %struct.httpd_conn*, %struct.httpd_conn** %hc2, align 8, !dbg !4022
  %11 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !4023
  call void @httpd_close_conn(%struct.httpd_conn* %10, %struct.timeval* %11), !dbg !4024
  %12 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4025
  %13 = load %struct.timeval*, %struct.timeval** %tvP.addr, align 8, !dbg !4026
  call void @clear_throttles(%struct.connecttab* %12, %struct.timeval* %13), !dbg !4027
  %14 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4028
  %linger_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %14, i32 0, i32 10, !dbg !4030
  %15 = load %struct.TimerStruct*, %struct.TimerStruct** %linger_timer, align 8, !dbg !4030
  %cmp3 = icmp ne %struct.TimerStruct* %15, null, !dbg !4031
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !4032

if.then4:                                         ; preds = %if.end
  %16 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4033
  %linger_timer5 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %16, i32 0, i32 10, !dbg !4035
  %17 = load %struct.TimerStruct*, %struct.TimerStruct** %linger_timer5, align 8, !dbg !4035
  call void @tmr_cancel(%struct.TimerStruct* %17), !dbg !4036
  %18 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4037
  %linger_timer6 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %18, i32 0, i32 10, !dbg !4038
  store %struct.TimerStruct* null, %struct.TimerStruct** %linger_timer6, align 8, !dbg !4039
  br label %if.end7, !dbg !4040

if.end7:                                          ; preds = %if.then4, %if.end
  %19 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4041
  %conn_state8 = getelementptr inbounds %struct.connecttab, %struct.connecttab* %19, i32 0, i32 0, !dbg !4042
  store i32 0, i32* %conn_state8, align 8, !dbg !4043
  %20 = load i32, i32* @first_free_connect, align 4, !dbg !4044
  %21 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4045
  %next_free_connect = getelementptr inbounds %struct.connecttab, %struct.connecttab* %21, i32 0, i32 1, !dbg !4046
  store i32 %20, i32* %next_free_connect, align 4, !dbg !4047
  %22 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4048
  %23 = load %struct.connecttab*, %struct.connecttab** @connects, align 8, !dbg !4049
  %sub.ptr.lhs.cast = ptrtoint %struct.connecttab* %22 to i64, !dbg !4050
  %sub.ptr.rhs.cast = ptrtoint %struct.connecttab* %23 to i64, !dbg !4050
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !4050
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 144, !dbg !4050
  %conv = trunc i64 %sub.ptr.div to i32, !dbg !4048
  store i32 %conv, i32* @first_free_connect, align 4, !dbg !4051
  %24 = load i32, i32* @num_connects, align 4, !dbg !4052
  %dec = add nsw i32 %24, -1, !dbg !4052
  store i32 %dec, i32* @num_connects, align 4, !dbg !4052
  ret void, !dbg !4053
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @clear_throttles(%struct.connecttab* %c, %struct.timeval* %tvP) #0 !dbg !4054 {
entry:
  %c.addr = alloca %struct.connecttab*, align 8
  %tvP.addr = alloca %struct.timeval*, align 8
  %tind = alloca i32, align 4
  store %struct.connecttab* %c, %struct.connecttab** %c.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c.addr, metadata !4055, metadata !DIExpression()), !dbg !4056
  store %struct.timeval* %tvP, %struct.timeval** %tvP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %tvP.addr, metadata !4057, metadata !DIExpression()), !dbg !4058
  call void @llvm.dbg.declare(metadata i32* %tind, metadata !4059, metadata !DIExpression()), !dbg !4060
  store i32 0, i32* %tind, align 4, !dbg !4061
  br label %for.cond, !dbg !4063

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %tind, align 4, !dbg !4064
  %1 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4066
  %numtnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %1, i32 0, i32 4, !dbg !4067
  %2 = load i32, i32* %numtnums, align 8, !dbg !4067
  %cmp = icmp slt i32 %0, %2, !dbg !4068
  br i1 %cmp, label %for.body, label %for.end, !dbg !4069

for.body:                                         ; preds = %for.cond
  %3 = load %struct.throttletab*, %struct.throttletab** @throttles, align 8, !dbg !4070
  %4 = load %struct.connecttab*, %struct.connecttab** %c.addr, align 8, !dbg !4071
  %tnums = getelementptr inbounds %struct.connecttab, %struct.connecttab* %4, i32 0, i32 3, !dbg !4072
  %5 = load i32, i32* %tind, align 4, !dbg !4073
  %idxprom = sext i32 %5 to i64, !dbg !4071
  %arrayidx = getelementptr inbounds [10 x i32], [10 x i32]* %tnums, i64 0, i64 %idxprom, !dbg !4071
  %6 = load i32, i32* %arrayidx, align 4, !dbg !4071
  %idxprom1 = sext i32 %6 to i64, !dbg !4070
  %arrayidx2 = getelementptr inbounds %struct.throttletab, %struct.throttletab* %3, i64 %idxprom1, !dbg !4070
  %num_sending = getelementptr inbounds %struct.throttletab, %struct.throttletab* %arrayidx2, i32 0, i32 5, !dbg !4074
  %7 = load i32, i32* %num_sending, align 8, !dbg !4075
  %dec = add nsw i32 %7, -1, !dbg !4075
  store i32 %dec, i32* %num_sending, align 8, !dbg !4075
  br label %for.inc, !dbg !4075

for.inc:                                          ; preds = %for.body
  %8 = load i32, i32* %tind, align 4, !dbg !4076
  %inc = add nsw i32 %8, 1, !dbg !4076
  store i32 %inc, i32* %tind, align 4, !dbg !4076
  br label %for.cond, !dbg !4077, !llvm.loop !4078

for.end:                                          ; preds = %for.cond
  ret void, !dbg !4080
}

declare void @tmr_cancel(%struct.TimerStruct*) #3

declare i32 @shutdown(i32, i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @linger_clear_connection(i8* %client_data.coerce, %struct.timeval* %nowP) #0 !dbg !4081 {
entry:
  %client_data = alloca %union.ClientData, align 8
  %nowP.addr = alloca %struct.timeval*, align 8
  %c = alloca %struct.connecttab*, align 8
  %coerce.dive = getelementptr inbounds %union.ClientData, %union.ClientData* %client_data, i32 0, i32 0
  store i8* %client_data.coerce, i8** %coerce.dive, align 8
  call void @llvm.dbg.declare(metadata %union.ClientData* %client_data, metadata !4082, metadata !DIExpression()), !dbg !4083
  store %struct.timeval* %nowP, %struct.timeval** %nowP.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowP.addr, metadata !4084, metadata !DIExpression()), !dbg !4085
  call void @llvm.dbg.declare(metadata %struct.connecttab** %c, metadata !4086, metadata !DIExpression()), !dbg !4087
  %p = bitcast %union.ClientData* %client_data to i8**, !dbg !4088
  %0 = load i8*, i8** %p, align 8, !dbg !4088
  %1 = bitcast i8* %0 to %struct.connecttab*, !dbg !4089
  store %struct.connecttab* %1, %struct.connecttab** %c, align 8, !dbg !4090
  %2 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !4091
  %linger_timer = getelementptr inbounds %struct.connecttab, %struct.connecttab* %2, i32 0, i32 10, !dbg !4092
  store %struct.TimerStruct* null, %struct.TimerStruct** %linger_timer, align 8, !dbg !4093
  %3 = load %struct.connecttab*, %struct.connecttab** %c, align 8, !dbg !4094
  %4 = load %struct.timeval*, %struct.timeval** %nowP.addr, align 8, !dbg !4095
  call void @really_clear_connection(%struct.connecttab* %3, %struct.timeval* %4), !dbg !4096
  ret void, !dbg !4097
}

declare i8* @httpd_ntoa(%union.httpd_sockaddr*) #3

declare void @mmc_cleanup(%struct.timeval*) #3

declare void @tmr_cleanup() #3

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { nounwind willreturn }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { cold "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { allocsize(0) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { cold noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { argmemonly nounwind willreturn }
attributes #10 = { allocsize(1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #11 = { noreturn }
attributes #12 = { cold }
attributes #13 = { nounwind }
attributes #14 = { allocsize(0) }
attributes #15 = { allocsize(1) }
attributes #16 = { cold noreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!494, !495, !496, !497}
!llvm.ident = !{!498}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "terminate", scope: !2, file: !3, line: 134, type: !26, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !5, globals: !412, nameTableKind: None)
!3 = !DIFile(filename: "thttpd.c", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/thttpd-2.29")
!4 = !{}
!5 = !{!6, !8, !27, !50, !26, !106, !109, !187, !211, !219, !243, !246, !248, !255, !70, !386, !392, !395, !24, !137, !396, !267}
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!7 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "throttletab", file: !3, line: 99, baseType: !10)
!10 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !3, line: 93, size: 384, elements: !11)
!11 = !{!12, !13, !15, !16, !17, !25}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !10, file: !3, line: 94, baseType: !6, size: 64)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "max_limit", scope: !10, file: !3, line: 95, baseType: !14, size: 64, offset: 64)
!14 = !DIBasicType(name: "long int", size: 64, encoding: DW_ATE_signed)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "min_limit", scope: !10, file: !3, line: 95, baseType: !14, size: 64, offset: 128)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "rate", scope: !10, file: !3, line: 96, baseType: !14, size: 64, offset: 192)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_since_avg", scope: !10, file: !3, line: 97, baseType: !18, size: 64, offset: 256)
!18 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !19, line: 31, baseType: !20)
!19 = !DIFile(filename: "/usr/include/sys/_types/_off_t.h", directory: "")
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_off_t", file: !21, line: 71, baseType: !22)
!21 = !DIFile(filename: "/usr/include/sys/_types.h", directory: "")
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "__int64_t", file: !23, line: 46, baseType: !24)
!23 = !DIFile(filename: "/usr/include/i386/_types.h", directory: "")
!24 = !DIBasicType(name: "long long int", size: 64, encoding: DW_ATE_signed)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "num_sending", scope: !10, file: !3, line: 98, baseType: !26, size: 32, offset: 320)
!26 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64)
!28 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !29, line: 84, size: 576, elements: !30)
!29 = !DIFile(filename: "/usr/include/pwd.h", directory: "")
!30 = !{!31, !32, !33, !39, !43, !45, !46, !47, !48, !49}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !28, file: !29, line: 85, baseType: !6, size: 64)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !28, file: !29, line: 86, baseType: !6, size: 64, offset: 64)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !28, file: !29, line: 87, baseType: !34, size: 32, offset: 128)
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !35, line: 31, baseType: !36)
!35 = !DIFile(filename: "/usr/include/sys/_types/_uid_t.h", directory: "")
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_uid_t", file: !21, line: 75, baseType: !37)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint32_t", file: !23, line: 45, baseType: !38)
!38 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !28, file: !29, line: 88, baseType: !40, size: 32, offset: 160)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !41, line: 31, baseType: !42)
!41 = !DIFile(filename: "/usr/include/sys/_types/_gid_t.h", directory: "")
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_gid_t", file: !21, line: 60, baseType: !37)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "pw_change", scope: !28, file: !29, line: 89, baseType: !44, size: 64, offset: 192)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_time_t", file: !23, line: 120, baseType: !14)
!45 = !DIDerivedType(tag: DW_TAG_member, name: "pw_class", scope: !28, file: !29, line: 90, baseType: !6, size: 64, offset: 256)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !28, file: !29, line: 91, baseType: !6, size: 64, offset: 320)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !28, file: !29, line: 92, baseType: !6, size: 64, offset: 384)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !28, file: !29, line: 93, baseType: !6, size: 64, offset: 448)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "pw_expire", scope: !28, file: !29, line: 94, baseType: !44, size: 64, offset: 512)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !52, line: 157, baseType: !53)
!52 = !DIFile(filename: "/usr/include/_stdio.h", directory: "")
!53 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "__sFILE", file: !52, line: 126, size: 1216, elements: !54)
!54 = !{!55, !58, !59, !60, !62, !63, !68, !69, !71, !75, !79, !84, !90, !91, !94, !95, !99, !103, !104, !105}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_p", scope: !53, file: !52, line: 127, baseType: !56, size: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64)
!57 = !DIBasicType(name: "unsigned char", size: 8, encoding: DW_ATE_unsigned_char)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_r", scope: !53, file: !52, line: 128, baseType: !26, size: 32, offset: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_w", scope: !53, file: !52, line: 129, baseType: !26, size: 32, offset: 96)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !53, file: !52, line: 130, baseType: !61, size: 16, offset: 128)
!61 = !DIBasicType(name: "short", size: 16, encoding: DW_ATE_signed)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_file", scope: !53, file: !52, line: 131, baseType: !61, size: 16, offset: 144)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "_bf", scope: !53, file: !52, line: 132, baseType: !64, size: 128, offset: 192)
!64 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "__sbuf", file: !52, line: 92, size: 128, elements: !65)
!65 = !{!66, !67}
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_base", scope: !64, file: !52, line: 93, baseType: !56, size: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_size", scope: !64, file: !52, line: 94, baseType: !26, size: 32, offset: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_lbfsize", scope: !53, file: !52, line: 133, baseType: !26, size: 32, offset: 320)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "_cookie", scope: !53, file: !52, line: 136, baseType: !70, size: 64, offset: 384)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "_close", scope: !53, file: !52, line: 137, baseType: !72, size: 64, offset: 448)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !73, size: 64)
!73 = !DISubroutineType(types: !74)
!74 = !{!26, !70}
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_read", scope: !53, file: !52, line: 138, baseType: !76, size: 64, offset: 512)
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64)
!77 = !DISubroutineType(types: !78)
!78 = !{!26, !70, !6, !26}
!79 = !DIDerivedType(tag: DW_TAG_member, name: "_seek", scope: !53, file: !52, line: 139, baseType: !80, size: 64, offset: 576)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64)
!81 = !DISubroutineType(types: !82)
!82 = !{!83, !70, !83, !26}
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "fpos_t", file: !52, line: 81, baseType: !20)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "_write", scope: !53, file: !52, line: 140, baseType: !85, size: 64, offset: 640)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!26, !70, !88, !26}
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64)
!89 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !7)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "_ub", scope: !53, file: !52, line: 143, baseType: !64, size: 128, offset: 704)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "_extra", scope: !53, file: !52, line: 144, baseType: !92, size: 64, offset: 832)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64)
!93 = !DICompositeType(tag: DW_TAG_structure_type, name: "__sFILEX", file: !52, line: 98, flags: DIFlagFwdDecl)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "_ur", scope: !53, file: !52, line: 145, baseType: !26, size: 32, offset: 896)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "_ubuf", scope: !53, file: !52, line: 148, baseType: !96, size: 24, offset: 928)
!96 = !DICompositeType(tag: DW_TAG_array_type, baseType: !57, size: 24, elements: !97)
!97 = !{!98}
!98 = !DISubrange(count: 3)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "_nbuf", scope: !53, file: !52, line: 149, baseType: !100, size: 8, offset: 952)
!100 = !DICompositeType(tag: DW_TAG_array_type, baseType: !57, size: 8, elements: !101)
!101 = !{!102}
!102 = !DISubrange(count: 1)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "_lb", scope: !53, file: !52, line: 152, baseType: !64, size: 128, offset: 960)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "_blksize", scope: !53, file: !52, line: 155, baseType: !26, size: 32, offset: 1088)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !53, file: !52, line: 156, baseType: !83, size: 64, offset: 1152)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64)
!107 = !DISubroutineType(types: !108)
!108 = !{null, !26}
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64)
!110 = !DIDerivedType(tag: DW_TAG_typedef, name: "httpd_sockaddr", file: !111, line: 69, baseType: !112)
!111 = !DIFile(filename: "./libhttpd.h", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/thttpd-2.29")
!112 = distinct !DICompositeType(tag: DW_TAG_union_type, file: !111, line: 62, size: 1024, elements: !113)
!113 = !{!114, !127, !148, !173}
!114 = !DIDerivedType(tag: DW_TAG_member, name: "sa", scope: !112, file: !111, line: 63, baseType: !115, size: 128)
!115 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !116, line: 407, size: 128, elements: !117)
!116 = !DIFile(filename: "/usr/include/sys/socket.h", directory: "")
!117 = !{!118, !120, !123}
!118 = !DIDerivedType(tag: DW_TAG_member, name: "sa_len", scope: !115, file: !116, line: 408, baseType: !119, size: 8)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint8_t", file: !23, line: 41, baseType: !57)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !115, file: !116, line: 409, baseType: !121, size: 8, offset: 8)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !122, line: 31, baseType: !119)
!122 = !DIFile(filename: "/usr/include/sys/_types/_sa_family_t.h", directory: "")
!123 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !115, file: !116, line: 410, baseType: !124, size: 112, offset: 16)
!124 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 112, elements: !125)
!125 = !{!126}
!126 = !DISubrange(count: 14)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "sa_in", scope: !112, file: !111, line: 64, baseType: !128, size: 128)
!128 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !129, line: 375, size: 128, elements: !130)
!129 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "")
!130 = !{!131, !132, !133, !138, !144}
!131 = !DIDerivedType(tag: DW_TAG_member, name: "sin_len", scope: !128, file: !129, line: 376, baseType: !119, size: 8)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !128, file: !129, line: 377, baseType: !121, size: 8, offset: 8)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !128, file: !129, line: 378, baseType: !134, size: 16, offset: 16)
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !135, line: 31, baseType: !136)
!135 = !DIFile(filename: "/usr/include/sys/_types/_in_port_t.h", directory: "")
!136 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint16_t", file: !23, line: 43, baseType: !137)
!137 = !DIBasicType(name: "unsigned short", size: 16, encoding: DW_ATE_unsigned)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !128, file: !129, line: 379, baseType: !139, size: 32, offset: 32)
!139 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !129, line: 301, size: 32, elements: !140)
!140 = !{!141}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !139, file: !129, line: 302, baseType: !142, size: 32)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !143, line: 31, baseType: !37)
!143 = !DIFile(filename: "/usr/include/sys/_types/_in_addr_t.h", directory: "")
!144 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !128, file: !129, line: 380, baseType: !145, size: 64, offset: 64)
!145 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 64, elements: !146)
!146 = !{!147}
!147 = !DISubrange(count: 8)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "sa_in6", scope: !112, file: !111, line: 66, baseType: !149, size: 224)
!149 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in6", file: !150, line: 169, size: 224, elements: !151)
!150 = !DIFile(filename: "/usr/include/netinet6/in6.h", directory: "")
!151 = !{!152, !153, !154, !155, !156, !172}
!152 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_len", scope: !149, file: !150, line: 170, baseType: !119, size: 8)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_family", scope: !149, file: !150, line: 171, baseType: !121, size: 8, offset: 8)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_port", scope: !149, file: !150, line: 172, baseType: !134, size: 16, offset: 16)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_flowinfo", scope: !149, file: !150, line: 173, baseType: !37, size: 32, offset: 32)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_addr", scope: !149, file: !150, line: 174, baseType: !157, size: 128, offset: 64)
!157 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "in6_addr", file: !150, line: 151, size: 128, elements: !158)
!158 = !{!159}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr", scope: !157, file: !150, line: 156, baseType: !160, size: 128)
!160 = distinct !DICompositeType(tag: DW_TAG_union_type, scope: !157, file: !150, line: 152, size: 128, elements: !161)
!161 = !{!162, !166, !168}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr8", scope: !160, file: !150, line: 153, baseType: !163, size: 128)
!163 = !DICompositeType(tag: DW_TAG_array_type, baseType: !119, size: 128, elements: !164)
!164 = !{!165}
!165 = !DISubrange(count: 16)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr16", scope: !160, file: !150, line: 154, baseType: !167, size: 128)
!167 = !DICompositeType(tag: DW_TAG_array_type, baseType: !136, size: 128, elements: !146)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "__u6_addr32", scope: !160, file: !150, line: 155, baseType: !169, size: 128)
!169 = !DICompositeType(tag: DW_TAG_array_type, baseType: !37, size: 128, elements: !170)
!170 = !{!171}
!171 = !DISubrange(count: 4)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "sin6_scope_id", scope: !149, file: !150, line: 175, baseType: !37, size: 32, offset: 192)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "sa_stor", scope: !112, file: !111, line: 67, baseType: !174, size: 1024)
!174 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !116, line: 440, size: 1024, elements: !175)
!175 = !{!176, !177, !178, !182, !183}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "ss_len", scope: !174, file: !116, line: 441, baseType: !119, size: 8)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !174, file: !116, line: 442, baseType: !121, size: 8, offset: 8)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_pad1", scope: !174, file: !116, line: 443, baseType: !179, size: 48, offset: 16)
!179 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 48, elements: !180)
!180 = !{!181}
!181 = !DISubrange(count: 6)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !174, file: !116, line: 444, baseType: !22, size: 64, offset: 64)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_pad2", scope: !174, file: !116, line: 445, baseType: !184, size: 896, offset: 128)
!184 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 896, elements: !185)
!185 = !{!186}
!186 = !DISubrange(count: 112)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "httpd_server", file: !111, line: 91, baseType: !189)
!189 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !111, line: 72, size: 1088, elements: !190)
!190 = !{!191, !192, !193, !194, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "binding_hostname", scope: !189, file: !111, line: 73, baseType: !6, size: 64)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "server_hostname", scope: !189, file: !111, line: 74, baseType: !6, size: 64, offset: 64)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !189, file: !111, line: 75, baseType: !137, size: 16, offset: 128)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "cgi_pattern", scope: !189, file: !111, line: 76, baseType: !6, size: 64, offset: 192)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "cgi_limit", scope: !189, file: !111, line: 77, baseType: !26, size: 32, offset: 256)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "cgi_count", scope: !189, file: !111, line: 77, baseType: !26, size: 32, offset: 288)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "charset", scope: !189, file: !111, line: 78, baseType: !6, size: 64, offset: 320)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "p3p", scope: !189, file: !111, line: 79, baseType: !6, size: 64, offset: 384)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "max_age", scope: !189, file: !111, line: 80, baseType: !26, size: 32, offset: 448)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "cwd", scope: !189, file: !111, line: 81, baseType: !6, size: 64, offset: 512)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "listen4_fd", scope: !189, file: !111, line: 82, baseType: !26, size: 32, offset: 576)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "listen6_fd", scope: !189, file: !111, line: 82, baseType: !26, size: 32, offset: 608)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "no_log", scope: !189, file: !111, line: 83, baseType: !26, size: 32, offset: 640)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "logfp", scope: !189, file: !111, line: 84, baseType: !50, size: 64, offset: 704)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "no_symlink_check", scope: !189, file: !111, line: 85, baseType: !26, size: 32, offset: 768)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "vhost", scope: !189, file: !111, line: 86, baseType: !26, size: 32, offset: 800)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "global_passwd", scope: !189, file: !111, line: 87, baseType: !26, size: 32, offset: 832)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "url_pattern", scope: !189, file: !111, line: 88, baseType: !6, size: 64, offset: 896)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "local_pattern", scope: !189, file: !111, line: 89, baseType: !6, size: 64, offset: 960)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "no_empty_referrers", scope: !189, file: !111, line: 90, baseType: !26, size: 32, offset: 1024)
!211 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !212, size: 64)
!212 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !213, line: 34, size: 128, elements: !214)
!213 = !DIFile(filename: "/usr/include/sys/_types/_timeval.h", directory: "")
!214 = !{!215, !216}
!215 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !212, file: !213, line: 36, baseType: !44, size: 64)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !212, file: !213, line: 37, baseType: !217, size: 32, offset: 64)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_suseconds_t", file: !21, line: 74, baseType: !218)
!218 = !DIDerivedType(tag: DW_TAG_typedef, name: "__int32_t", file: !23, line: 44, baseType: !26)
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !220, size: 64)
!220 = !DIDerivedType(tag: DW_TAG_typedef, name: "Timer", file: !221, line: 65, baseType: !222)
!221 = !DIFile(filename: "./timers.h", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph/benchmarks/thttpd-2.29")
!222 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "TimerStruct", file: !221, line: 56, size: 576, elements: !223)
!223 = !{!224, !235, !236, !237, !238, !239, !241, !242}
!224 = !DIDerivedType(tag: DW_TAG_member, name: "timer_proc", scope: !222, file: !221, line: 57, baseType: !225, size: 64)
!225 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !226, size: 64)
!226 = !DIDerivedType(tag: DW_TAG_typedef, name: "TimerProc", file: !221, line: 53, baseType: !227)
!227 = !DISubroutineType(types: !228)
!228 = !{null, !229, !211}
!229 = !DIDerivedType(tag: DW_TAG_typedef, name: "ClientData", file: !221, line: 45, baseType: !230)
!230 = distinct !DICompositeType(tag: DW_TAG_union_type, file: !221, line: 41, size: 64, elements: !231)
!231 = !{!232, !233, !234}
!232 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !230, file: !221, line: 42, baseType: !70, size: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "i", scope: !230, file: !221, line: 43, baseType: !26, size: 32)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "l", scope: !230, file: !221, line: 44, baseType: !14, size: 64)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !222, file: !221, line: 58, baseType: !229, size: 64, offset: 64)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "msecs", scope: !222, file: !221, line: 59, baseType: !14, size: 64, offset: 128)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "periodic", scope: !222, file: !221, line: 60, baseType: !26, size: 32, offset: 192)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !222, file: !221, line: 61, baseType: !212, size: 128, offset: 256)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !222, file: !221, line: 62, baseType: !240, size: 64, offset: 384)
!240 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !222, size: 64)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !222, file: !221, line: 63, baseType: !240, size: 64, offset: 448)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !222, file: !221, line: 64, baseType: !26, size: 32, offset: 512)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !244, size: 64)
!244 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !245, line: 31, baseType: !44)
!245 = !DIFile(filename: "/usr/include/sys/_types/_time_t.h", directory: "")
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64)
!247 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !40)
!248 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !249, size: 64)
!249 = !DIDerivedType(tag: DW_TAG_typedef, name: "connecttab", file: !3, line: 120, baseType: !250)
!250 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !3, line: 106, size: 1152, elements: !251)
!251 = !{!252, !253, !254, !371, !375, !376, !377, !378, !379, !380, !381, !382, !383, !384, !385}
!252 = !DIDerivedType(tag: DW_TAG_member, name: "conn_state", scope: !250, file: !3, line: 107, baseType: !26, size: 32)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "next_free_connect", scope: !250, file: !3, line: 108, baseType: !26, size: 32, offset: 32)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "hc", scope: !250, file: !3, line: 109, baseType: !255, size: 64, offset: 64)
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64)
!256 = !DIDerivedType(tag: DW_TAG_typedef, name: "httpd_conn", file: !111, line: 148, baseType: !257)
!257 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !111, line: 94, size: 5760, elements: !258)
!258 = !{!259, !260, !261, !262, !263, !268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287, !288, !289, !290, !291, !292, !293, !294, !295, !296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !314, !315, !316, !317, !318, !319, !320, !321, !322, !369, !370}
!259 = !DIDerivedType(tag: DW_TAG_member, name: "initialized", scope: !257, file: !111, line: 95, baseType: !26, size: 32)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "hs", scope: !257, file: !111, line: 96, baseType: !187, size: 64, offset: 64)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "client_addr", scope: !257, file: !111, line: 97, baseType: !110, size: 1024, offset: 128)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "read_buf", scope: !257, file: !111, line: 98, baseType: !6, size: 64, offset: 1152)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "read_size", scope: !257, file: !111, line: 99, baseType: !264, size: 64, offset: 1216)
!264 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !265, line: 31, baseType: !266)
!265 = !DIFile(filename: "/usr/include/sys/_types/_size_t.h", directory: "")
!266 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_size_t", file: !23, line: 92, baseType: !267)
!267 = !DIBasicType(name: "long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "read_idx", scope: !257, file: !111, line: 99, baseType: !264, size: 64, offset: 1280)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "checked_idx", scope: !257, file: !111, line: 99, baseType: !264, size: 64, offset: 1344)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "checked_state", scope: !257, file: !111, line: 100, baseType: !26, size: 32, offset: 1408)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "method", scope: !257, file: !111, line: 101, baseType: !26, size: 32, offset: 1440)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !257, file: !111, line: 102, baseType: !26, size: 32, offset: 1472)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_to_send", scope: !257, file: !111, line: 103, baseType: !18, size: 64, offset: 1536)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_sent", scope: !257, file: !111, line: 104, baseType: !18, size: 64, offset: 1600)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "encodedurl", scope: !257, file: !111, line: 105, baseType: !6, size: 64, offset: 1664)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "decodedurl", scope: !257, file: !111, line: 106, baseType: !6, size: 64, offset: 1728)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !257, file: !111, line: 107, baseType: !6, size: 64, offset: 1792)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "origfilename", scope: !257, file: !111, line: 108, baseType: !6, size: 64, offset: 1856)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "expnfilename", scope: !257, file: !111, line: 109, baseType: !6, size: 64, offset: 1920)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "encodings", scope: !257, file: !111, line: 110, baseType: !6, size: 64, offset: 1984)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "pathinfo", scope: !257, file: !111, line: 111, baseType: !6, size: 64, offset: 2048)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "query", scope: !257, file: !111, line: 112, baseType: !6, size: 64, offset: 2112)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "referrer", scope: !257, file: !111, line: 113, baseType: !6, size: 64, offset: 2176)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "useragent", scope: !257, file: !111, line: 114, baseType: !6, size: 64, offset: 2240)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "accept", scope: !257, file: !111, line: 115, baseType: !6, size: 64, offset: 2304)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "accepte", scope: !257, file: !111, line: 116, baseType: !6, size: 64, offset: 2368)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "acceptl", scope: !257, file: !111, line: 117, baseType: !6, size: 64, offset: 2432)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "cookie", scope: !257, file: !111, line: 118, baseType: !6, size: 64, offset: 2496)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !257, file: !111, line: 119, baseType: !6, size: 64, offset: 2560)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "reqhost", scope: !257, file: !111, line: 120, baseType: !6, size: 64, offset: 2624)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "hdrhost", scope: !257, file: !111, line: 121, baseType: !6, size: 64, offset: 2688)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "hostdir", scope: !257, file: !111, line: 122, baseType: !6, size: 64, offset: 2752)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "authorization", scope: !257, file: !111, line: 123, baseType: !6, size: 64, offset: 2816)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "remoteuser", scope: !257, file: !111, line: 124, baseType: !6, size: 64, offset: 2880)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !257, file: !111, line: 125, baseType: !6, size: 64, offset: 2944)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "maxdecodedurl", scope: !257, file: !111, line: 126, baseType: !264, size: 64, offset: 3008)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "maxorigfilename", scope: !257, file: !111, line: 126, baseType: !264, size: 64, offset: 3072)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "maxexpnfilename", scope: !257, file: !111, line: 126, baseType: !264, size: 64, offset: 3136)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "maxencodings", scope: !257, file: !111, line: 126, baseType: !264, size: 64, offset: 3200)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "maxpathinfo", scope: !257, file: !111, line: 127, baseType: !264, size: 64, offset: 3264)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "maxquery", scope: !257, file: !111, line: 127, baseType: !264, size: 64, offset: 3328)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "maxaccept", scope: !257, file: !111, line: 127, baseType: !264, size: 64, offset: 3392)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "maxaccepte", scope: !257, file: !111, line: 127, baseType: !264, size: 64, offset: 3456)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "maxreqhost", scope: !257, file: !111, line: 127, baseType: !264, size: 64, offset: 3520)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "maxhostdir", scope: !257, file: !111, line: 127, baseType: !264, size: 64, offset: 3584)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "maxremoteuser", scope: !257, file: !111, line: 128, baseType: !264, size: 64, offset: 3648)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "maxresponse", scope: !257, file: !111, line: 128, baseType: !264, size: 64, offset: 3712)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "responselen", scope: !257, file: !111, line: 133, baseType: !264, size: 64, offset: 3776)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "if_modified_since", scope: !257, file: !111, line: 134, baseType: !244, size: 64, offset: 3840)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "range_if", scope: !257, file: !111, line: 134, baseType: !244, size: 64, offset: 3904)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "contentlength", scope: !257, file: !111, line: 135, baseType: !264, size: 64, offset: 3968)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !257, file: !111, line: 136, baseType: !6, size: 64, offset: 4032)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "hostname", scope: !257, file: !111, line: 137, baseType: !6, size: 64, offset: 4096)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "mime_flag", scope: !257, file: !111, line: 138, baseType: !26, size: 32, offset: 4160)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "one_one", scope: !257, file: !111, line: 139, baseType: !26, size: 32, offset: 4192)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "got_range", scope: !257, file: !111, line: 140, baseType: !26, size: 32, offset: 4224)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "tildemapped", scope: !257, file: !111, line: 141, baseType: !26, size: 32, offset: 4256)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "first_byte_index", scope: !257, file: !111, line: 142, baseType: !18, size: 64, offset: 4288)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "last_byte_index", scope: !257, file: !111, line: 142, baseType: !18, size: 64, offset: 4352)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "keep_alive", scope: !257, file: !111, line: 143, baseType: !26, size: 32, offset: 4416)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "should_linger", scope: !257, file: !111, line: 144, baseType: !26, size: 32, offset: 4448)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "sb", scope: !257, file: !111, line: 145, baseType: !323, size: 1152, offset: 4480)
!323 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !324, line: 182, size: 1152, elements: !325)
!324 = !DIFile(filename: "/usr/include/sys/stat.h", directory: "")
!325 = !{!326, !330, !334, !337, !341, !342, !343, !344, !350, !351, !352, !353, !354, !358, !362, !363, !364, !365}
!326 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !323, file: !324, line: 182, baseType: !327, size: 32)
!327 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !328, line: 31, baseType: !329)
!328 = !DIFile(filename: "/usr/include/sys/_types/_dev_t.h", directory: "")
!329 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_dev_t", file: !21, line: 57, baseType: !218)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !323, file: !324, line: 182, baseType: !331, size: 16, offset: 32)
!331 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !332, line: 31, baseType: !333)
!332 = !DIFile(filename: "/usr/include/sys/_types/_mode_t.h", directory: "")
!333 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_mode_t", file: !21, line: 70, baseType: !136)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !323, file: !324, line: 182, baseType: !335, size: 16, offset: 48)
!335 = !DIDerivedType(tag: DW_TAG_typedef, name: "nlink_t", file: !336, line: 31, baseType: !136)
!336 = !DIFile(filename: "/usr/include/sys/_types/_nlink_t.h", directory: "")
!337 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !323, file: !324, line: 182, baseType: !338, size: 64, offset: 64)
!338 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_ino64_t", file: !21, line: 62, baseType: !339)
!339 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uint64_t", file: !23, line: 47, baseType: !340)
!340 = !DIBasicType(name: "long long unsigned int", size: 64, encoding: DW_ATE_unsigned)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !323, file: !324, line: 182, baseType: !34, size: 32, offset: 128)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !323, file: !324, line: 182, baseType: !40, size: 32, offset: 160)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !323, file: !324, line: 182, baseType: !327, size: 32, offset: 192)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "st_atimespec", scope: !323, file: !324, line: 182, baseType: !345, size: 128, offset: 256)
!345 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !346, line: 33, size: 128, elements: !347)
!346 = !DIFile(filename: "/usr/include/sys/_types/_timespec.h", directory: "")
!347 = !{!348, !349}
!348 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !345, file: !346, line: 35, baseType: !44, size: 64)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !345, file: !346, line: 36, baseType: !14, size: 64, offset: 64)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtimespec", scope: !323, file: !324, line: 182, baseType: !345, size: 128, offset: 384)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctimespec", scope: !323, file: !324, line: 182, baseType: !345, size: 128, offset: 512)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "st_birthtimespec", scope: !323, file: !324, line: 182, baseType: !345, size: 128, offset: 640)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !323, file: !324, line: 182, baseType: !18, size: 64, offset: 768)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !323, file: !324, line: 182, baseType: !355, size: 64, offset: 832)
!355 = !DIDerivedType(tag: DW_TAG_typedef, name: "blkcnt_t", file: !356, line: 31, baseType: !357)
!356 = !DIFile(filename: "/usr/include/sys/_types/_blkcnt_t.h", directory: "")
!357 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_blkcnt_t", file: !21, line: 55, baseType: !22)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !323, file: !324, line: 182, baseType: !359, size: 32, offset: 896)
!359 = !DIDerivedType(tag: DW_TAG_typedef, name: "blksize_t", file: !360, line: 31, baseType: !361)
!360 = !DIFile(filename: "/usr/include/sys/_types/_blksize_t.h", directory: "")
!361 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_blksize_t", file: !21, line: 56, baseType: !218)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "st_flags", scope: !323, file: !324, line: 182, baseType: !37, size: 32, offset: 928)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "st_gen", scope: !323, file: !324, line: 182, baseType: !37, size: 32, offset: 960)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "st_lspare", scope: !323, file: !324, line: 182, baseType: !218, size: 32, offset: 992)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "st_qspare", scope: !323, file: !324, line: 182, baseType: !366, size: 128, offset: 1024)
!366 = !DICompositeType(tag: DW_TAG_array_type, baseType: !22, size: 128, elements: !367)
!367 = !{!368}
!368 = !DISubrange(count: 2)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "conn_fd", scope: !257, file: !111, line: 146, baseType: !26, size: 32, offset: 5632)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "file_address", scope: !257, file: !111, line: 147, baseType: !6, size: 64, offset: 5696)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "tnums", scope: !250, file: !3, line: 110, baseType: !372, size: 320, offset: 128)
!372 = !DICompositeType(tag: DW_TAG_array_type, baseType: !26, size: 320, elements: !373)
!373 = !{!374}
!374 = !DISubrange(count: 10)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "numtnums", scope: !250, file: !3, line: 111, baseType: !26, size: 32, offset: 448)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "max_limit", scope: !250, file: !3, line: 112, baseType: !14, size: 64, offset: 512)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "min_limit", scope: !250, file: !3, line: 112, baseType: !14, size: 64, offset: 576)
!378 = !DIDerivedType(tag: DW_TAG_member, name: "started_at", scope: !250, file: !3, line: 113, baseType: !244, size: 64, offset: 640)
!379 = !DIDerivedType(tag: DW_TAG_member, name: "active_at", scope: !250, file: !3, line: 113, baseType: !244, size: 64, offset: 704)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "wakeup_timer", scope: !250, file: !3, line: 114, baseType: !219, size: 64, offset: 768)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "linger_timer", scope: !250, file: !3, line: 115, baseType: !219, size: 64, offset: 832)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "wouldblock_delay", scope: !250, file: !3, line: 116, baseType: !14, size: 64, offset: 896)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "bytes", scope: !250, file: !3, line: 117, baseType: !18, size: 64, offset: 960)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "end_byte_index", scope: !250, file: !3, line: 118, baseType: !18, size: 64, offset: 1024)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "next_byte_index", scope: !250, file: !3, line: 119, baseType: !18, size: 64, offset: 1088)
!386 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !387, size: 64)
!387 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "timezone", file: !388, line: 129, size: 64, elements: !389)
!388 = !DIFile(filename: "/usr/include/sys/time.h", directory: "")
!389 = !{!390, !391}
!390 = !DIDerivedType(tag: DW_TAG_member, name: "tz_minuteswest", scope: !387, file: !388, line: 130, baseType: !26, size: 32)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "tz_dsttime", scope: !387, file: !388, line: 131, baseType: !26, size: 32, offset: 32)
!392 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !393, line: 31, baseType: !394)
!393 = !DIFile(filename: "/usr/include/sys/_types/_pid_t.h", directory: "")
!394 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_pid_t", file: !21, line: 72, baseType: !218)
!395 = !DIBasicType(name: "float", size: 32, encoding: DW_ATE_float)
!396 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !397, size: 64)
!397 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "addrinfo", file: !398, line: 147, size: 384, elements: !399)
!398 = !DIFile(filename: "/usr/include/netdb.h", directory: "")
!399 = !{!400, !401, !402, !403, !404, !408, !409, !411}
!400 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !397, file: !398, line: 148, baseType: !26, size: 32)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !397, file: !398, line: 149, baseType: !26, size: 32, offset: 32)
!402 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !397, file: !398, line: 150, baseType: !26, size: 32, offset: 64)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !397, file: !398, line: 151, baseType: !26, size: 32, offset: 96)
!404 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !397, file: !398, line: 152, baseType: !405, size: 32, offset: 128)
!405 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !406, line: 31, baseType: !407)
!406 = !DIFile(filename: "/usr/include/sys/_types/_socklen_t.h", directory: "")
!407 = !DIDerivedType(tag: DW_TAG_typedef, name: "__darwin_socklen_t", file: !23, line: 118, baseType: !37)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !397, file: !398, line: 153, baseType: !6, size: 64, offset: 192)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !397, file: !398, line: 154, baseType: !410, size: 64, offset: 256)
!410 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !397, file: !398, line: 155, baseType: !396, size: 64, offset: 320)
!412 = !{!0, !413, !415, !417, !419, !421, !423, !425, !427, !429, !431, !433, !435, !437, !439, !441, !443, !445, !447, !449, !451, !453, !455, !457, !459, !461, !463, !465, !467, !469, !471, !473, !475, !477, !479, !481, !483, !485, !488, !490, !492}
!413 = !DIGlobalVariableExpression(var: !414, expr: !DIExpression())
!414 = distinct !DIGlobalVariable(name: "argv0", scope: !2, file: !3, line: 72, type: !6, isLocal: true, isDefinition: true)
!415 = !DIGlobalVariableExpression(var: !416, expr: !DIExpression())
!416 = distinct !DIGlobalVariable(name: "debug", scope: !2, file: !3, line: 73, type: !26, isLocal: true, isDefinition: true)
!417 = !DIGlobalVariableExpression(var: !418, expr: !DIExpression())
!418 = distinct !DIGlobalVariable(name: "port", scope: !2, file: !3, line: 74, type: !137, isLocal: true, isDefinition: true)
!419 = !DIGlobalVariableExpression(var: !420, expr: !DIExpression())
!420 = distinct !DIGlobalVariable(name: "dir", scope: !2, file: !3, line: 75, type: !6, isLocal: true, isDefinition: true)
!421 = !DIGlobalVariableExpression(var: !422, expr: !DIExpression())
!422 = distinct !DIGlobalVariable(name: "data_dir", scope: !2, file: !3, line: 76, type: !6, isLocal: true, isDefinition: true)
!423 = !DIGlobalVariableExpression(var: !424, expr: !DIExpression())
!424 = distinct !DIGlobalVariable(name: "do_chroot", scope: !2, file: !3, line: 77, type: !26, isLocal: true, isDefinition: true)
!425 = !DIGlobalVariableExpression(var: !426, expr: !DIExpression())
!426 = distinct !DIGlobalVariable(name: "no_log", scope: !2, file: !3, line: 77, type: !26, isLocal: true, isDefinition: true)
!427 = !DIGlobalVariableExpression(var: !428, expr: !DIExpression())
!428 = distinct !DIGlobalVariable(name: "no_symlink_check", scope: !2, file: !3, line: 77, type: !26, isLocal: true, isDefinition: true)
!429 = !DIGlobalVariableExpression(var: !430, expr: !DIExpression())
!430 = distinct !DIGlobalVariable(name: "do_vhost", scope: !2, file: !3, line: 77, type: !26, isLocal: true, isDefinition: true)
!431 = !DIGlobalVariableExpression(var: !432, expr: !DIExpression())
!432 = distinct !DIGlobalVariable(name: "do_global_passwd", scope: !2, file: !3, line: 77, type: !26, isLocal: true, isDefinition: true)
!433 = !DIGlobalVariableExpression(var: !434, expr: !DIExpression())
!434 = distinct !DIGlobalVariable(name: "cgi_pattern", scope: !2, file: !3, line: 78, type: !6, isLocal: true, isDefinition: true)
!435 = !DIGlobalVariableExpression(var: !436, expr: !DIExpression())
!436 = distinct !DIGlobalVariable(name: "cgi_limit", scope: !2, file: !3, line: 79, type: !26, isLocal: true, isDefinition: true)
!437 = !DIGlobalVariableExpression(var: !438, expr: !DIExpression())
!438 = distinct !DIGlobalVariable(name: "url_pattern", scope: !2, file: !3, line: 80, type: !6, isLocal: true, isDefinition: true)
!439 = !DIGlobalVariableExpression(var: !440, expr: !DIExpression())
!440 = distinct !DIGlobalVariable(name: "no_empty_referrers", scope: !2, file: !3, line: 81, type: !26, isLocal: true, isDefinition: true)
!441 = !DIGlobalVariableExpression(var: !442, expr: !DIExpression())
!442 = distinct !DIGlobalVariable(name: "local_pattern", scope: !2, file: !3, line: 82, type: !6, isLocal: true, isDefinition: true)
!443 = !DIGlobalVariableExpression(var: !444, expr: !DIExpression())
!444 = distinct !DIGlobalVariable(name: "logfile", scope: !2, file: !3, line: 83, type: !6, isLocal: true, isDefinition: true)
!445 = !DIGlobalVariableExpression(var: !446, expr: !DIExpression())
!446 = distinct !DIGlobalVariable(name: "throttlefile", scope: !2, file: !3, line: 84, type: !6, isLocal: true, isDefinition: true)
!447 = !DIGlobalVariableExpression(var: !448, expr: !DIExpression())
!448 = distinct !DIGlobalVariable(name: "hostname", scope: !2, file: !3, line: 85, type: !6, isLocal: true, isDefinition: true)
!449 = !DIGlobalVariableExpression(var: !450, expr: !DIExpression())
!450 = distinct !DIGlobalVariable(name: "pidfile", scope: !2, file: !3, line: 86, type: !6, isLocal: true, isDefinition: true)
!451 = !DIGlobalVariableExpression(var: !452, expr: !DIExpression())
!452 = distinct !DIGlobalVariable(name: "user", scope: !2, file: !3, line: 87, type: !6, isLocal: true, isDefinition: true)
!453 = !DIGlobalVariableExpression(var: !454, expr: !DIExpression())
!454 = distinct !DIGlobalVariable(name: "charset", scope: !2, file: !3, line: 88, type: !6, isLocal: true, isDefinition: true)
!455 = !DIGlobalVariableExpression(var: !456, expr: !DIExpression())
!456 = distinct !DIGlobalVariable(name: "p3p", scope: !2, file: !3, line: 89, type: !6, isLocal: true, isDefinition: true)
!457 = !DIGlobalVariableExpression(var: !458, expr: !DIExpression())
!458 = distinct !DIGlobalVariable(name: "max_age", scope: !2, file: !3, line: 90, type: !26, isLocal: true, isDefinition: true)
!459 = !DIGlobalVariableExpression(var: !460, expr: !DIExpression())
!460 = distinct !DIGlobalVariable(name: "throttles", scope: !2, file: !3, line: 100, type: !8, isLocal: true, isDefinition: true)
!461 = !DIGlobalVariableExpression(var: !462, expr: !DIExpression())
!462 = distinct !DIGlobalVariable(name: "numthrottles", scope: !2, file: !3, line: 101, type: !26, isLocal: true, isDefinition: true)
!463 = !DIGlobalVariableExpression(var: !464, expr: !DIExpression())
!464 = distinct !DIGlobalVariable(name: "maxthrottles", scope: !2, file: !3, line: 101, type: !26, isLocal: true, isDefinition: true)
!465 = !DIGlobalVariableExpression(var: !466, expr: !DIExpression())
!466 = distinct !DIGlobalVariable(name: "connects", scope: !2, file: !3, line: 121, type: !248, isLocal: true, isDefinition: true)
!467 = !DIGlobalVariableExpression(var: !468, expr: !DIExpression())
!468 = distinct !DIGlobalVariable(name: "num_connects", scope: !2, file: !3, line: 122, type: !26, isLocal: true, isDefinition: true)
!469 = !DIGlobalVariableExpression(var: !470, expr: !DIExpression())
!470 = distinct !DIGlobalVariable(name: "max_connects", scope: !2, file: !3, line: 122, type: !26, isLocal: true, isDefinition: true)
!471 = !DIGlobalVariableExpression(var: !472, expr: !DIExpression())
!472 = distinct !DIGlobalVariable(name: "first_free_connect", scope: !2, file: !3, line: 122, type: !26, isLocal: true, isDefinition: true)
!473 = !DIGlobalVariableExpression(var: !474, expr: !DIExpression())
!474 = distinct !DIGlobalVariable(name: "httpd_conn_count", scope: !2, file: !3, line: 123, type: !26, isLocal: true, isDefinition: true)
!475 = !DIGlobalVariableExpression(var: !476, expr: !DIExpression())
!476 = distinct !DIGlobalVariable(name: "start_time", scope: !2, file: !3, line: 135, type: !244, isLocal: false, isDefinition: true)
!477 = !DIGlobalVariableExpression(var: !478, expr: !DIExpression())
!478 = distinct !DIGlobalVariable(name: "stats_time", scope: !2, file: !3, line: 135, type: !244, isLocal: false, isDefinition: true)
!479 = !DIGlobalVariableExpression(var: !480, expr: !DIExpression())
!480 = distinct !DIGlobalVariable(name: "stats_connections", scope: !2, file: !3, line: 136, type: !14, isLocal: false, isDefinition: true)
!481 = !DIGlobalVariableExpression(var: !482, expr: !DIExpression())
!482 = distinct !DIGlobalVariable(name: "stats_bytes", scope: !2, file: !3, line: 137, type: !18, isLocal: false, isDefinition: true)
!483 = !DIGlobalVariableExpression(var: !484, expr: !DIExpression())
!484 = distinct !DIGlobalVariable(name: "stats_simultaneous", scope: !2, file: !3, line: 138, type: !26, isLocal: false, isDefinition: true)
!485 = !DIGlobalVariableExpression(var: !486, expr: !DIExpression())
!486 = distinct !DIGlobalVariable(name: "got_hup", scope: !2, file: !3, line: 140, type: !487, isLocal: true, isDefinition: true)
!487 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !26)
!488 = !DIGlobalVariableExpression(var: !489, expr: !DIExpression())
!489 = distinct !DIGlobalVariable(name: "got_usr1", scope: !2, file: !3, line: 140, type: !487, isLocal: true, isDefinition: true)
!490 = !DIGlobalVariableExpression(var: !491, expr: !DIExpression())
!491 = distinct !DIGlobalVariable(name: "watchdog_flag", scope: !2, file: !3, line: 140, type: !487, isLocal: true, isDefinition: true)
!492 = !DIGlobalVariableExpression(var: !493, expr: !DIExpression())
!493 = distinct !DIGlobalVariable(name: "hs", scope: !2, file: !3, line: 133, type: !187, isLocal: true, isDefinition: true)
!494 = !{i32 7, !"Dwarf Version", i32 4}
!495 = !{i32 2, !"Debug Info Version", i32 3}
!496 = !{i32 1, !"wchar_size", i32 4}
!497 = !{i32 7, !"PIC Level", i32 2}
!498 = !{!"clang version 10.0.0 "}
!499 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 355, type: !500, scopeLine: 356, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!500 = !DISubroutineType(types: !501)
!501 = !{!26, !26, !502}
!502 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!503 = !DILocalVariable(name: "argc", arg: 1, scope: !499, file: !3, line: 355, type: !26)
!504 = !DILocation(line: 355, column: 11, scope: !499)
!505 = !DILocalVariable(name: "argv", arg: 2, scope: !499, file: !3, line: 355, type: !502)
!506 = !DILocation(line: 355, column: 24, scope: !499)
!507 = !DILocalVariable(name: "cp", scope: !499, file: !3, line: 357, type: !6)
!508 = !DILocation(line: 357, column: 11, scope: !499)
!509 = !DILocalVariable(name: "pwd", scope: !499, file: !3, line: 358, type: !27)
!510 = !DILocation(line: 358, column: 60, scope: !499)
!511 = !DILocation(line: 358, column: 5, scope: !499)
!512 = !DILocalVariable(name: "uid", scope: !499, file: !3, line: 359, type: !34)
!513 = !DILocation(line: 359, column: 11, scope: !499)
!514 = !DILocalVariable(name: "gid", scope: !499, file: !3, line: 360, type: !40)
!515 = !DILocation(line: 360, column: 11, scope: !499)
!516 = !DILocalVariable(name: "cwd", scope: !499, file: !3, line: 361, type: !517)
!517 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 8200, elements: !518)
!518 = !{!519}
!519 = !DISubrange(count: 1025)
!520 = !DILocation(line: 361, column: 10, scope: !499)
!521 = !DILocalVariable(name: "logfp", scope: !499, file: !3, line: 362, type: !50)
!522 = !DILocation(line: 362, column: 11, scope: !499)
!523 = !DILocalVariable(name: "num_ready", scope: !499, file: !3, line: 363, type: !26)
!524 = !DILocation(line: 363, column: 9, scope: !499)
!525 = !DILocalVariable(name: "cnum", scope: !499, file: !3, line: 364, type: !26)
!526 = !DILocation(line: 364, column: 9, scope: !499)
!527 = !DILocalVariable(name: "c", scope: !499, file: !3, line: 365, type: !248)
!528 = !DILocation(line: 365, column: 17, scope: !499)
!529 = !DILocalVariable(name: "hc", scope: !499, file: !3, line: 366, type: !255)
!530 = !DILocation(line: 366, column: 17, scope: !499)
!531 = !DILocalVariable(name: "sa4", scope: !499, file: !3, line: 367, type: !110)
!532 = !DILocation(line: 367, column: 20, scope: !499)
!533 = !DILocalVariable(name: "sa6", scope: !499, file: !3, line: 368, type: !110)
!534 = !DILocation(line: 368, column: 20, scope: !499)
!535 = !DILocalVariable(name: "gotv4", scope: !499, file: !3, line: 369, type: !26)
!536 = !DILocation(line: 369, column: 9, scope: !499)
!537 = !DILocalVariable(name: "gotv6", scope: !499, file: !3, line: 369, type: !26)
!538 = !DILocation(line: 369, column: 16, scope: !499)
!539 = !DILocalVariable(name: "tv", scope: !499, file: !3, line: 370, type: !212)
!540 = !DILocation(line: 370, column: 20, scope: !499)
!541 = !DILocation(line: 372, column: 13, scope: !499)
!542 = !DILocation(line: 372, column: 11, scope: !499)
!543 = !DILocation(line: 374, column: 19, scope: !499)
!544 = !DILocation(line: 374, column: 10, scope: !499)
!545 = !DILocation(line: 374, column: 8, scope: !499)
!546 = !DILocation(line: 375, column: 10, scope: !547)
!547 = distinct !DILexicalBlock(scope: !499, file: !3, line: 375, column: 10)
!548 = !DILocation(line: 375, column: 13, scope: !547)
!549 = !DILocation(line: 375, column: 10, scope: !499)
!550 = !DILocation(line: 376, column: 2, scope: !547)
!551 = !DILocation(line: 378, column: 7, scope: !547)
!552 = !DILocation(line: 378, column: 5, scope: !547)
!553 = !DILocation(line: 379, column: 14, scope: !499)
!554 = !DILocation(line: 379, column: 5, scope: !499)
!555 = !DILocation(line: 382, column: 17, scope: !499)
!556 = !DILocation(line: 382, column: 23, scope: !499)
!557 = !DILocation(line: 382, column: 5, scope: !499)
!558 = !DILocation(line: 385, column: 5, scope: !499)
!559 = !DILocation(line: 388, column: 5, scope: !499)
!560 = !DILocation(line: 389, column: 14, scope: !561)
!561 = distinct !DILexicalBlock(scope: !499, file: !3, line: 389, column: 10)
!562 = !DILocation(line: 389, column: 20, scope: !561)
!563 = !DILocation(line: 389, column: 23, scope: !561)
!564 = !DILocation(line: 389, column: 10, scope: !499)
!565 = !DILocation(line: 391, column: 2, scope: !566)
!566 = distinct !DILexicalBlock(scope: !561, file: !3, line: 390, column: 2)
!567 = !DILocation(line: 392, column: 18, scope: !566)
!568 = !DILocation(line: 392, column: 64, scope: !566)
!569 = !DILocation(line: 392, column: 9, scope: !566)
!570 = !DILocation(line: 393, column: 2, scope: !566)
!571 = !DILocation(line: 397, column: 18, scope: !499)
!572 = !DILocation(line: 398, column: 18, scope: !499)
!573 = !DILocation(line: 399, column: 15, scope: !499)
!574 = !DILocation(line: 400, column: 10, scope: !575)
!575 = distinct !DILexicalBlock(scope: !499, file: !3, line: 400, column: 10)
!576 = !DILocation(line: 400, column: 23, scope: !575)
!577 = !DILocation(line: 400, column: 10, scope: !499)
!578 = !DILocation(line: 401, column: 21, scope: !575)
!579 = !DILocation(line: 401, column: 2, scope: !575)
!580 = !DILocation(line: 406, column: 10, scope: !581)
!581 = distinct !DILexicalBlock(scope: !499, file: !3, line: 406, column: 10)
!582 = !DILocation(line: 406, column: 19, scope: !581)
!583 = !DILocation(line: 406, column: 10, scope: !499)
!584 = !DILocation(line: 408, column: 18, scope: !585)
!585 = distinct !DILexicalBlock(scope: !581, file: !3, line: 407, column: 2)
!586 = !DILocation(line: 408, column: 8, scope: !585)
!587 = !DILocation(line: 408, column: 6, scope: !585)
!588 = !DILocation(line: 409, column: 7, scope: !589)
!589 = distinct !DILexicalBlock(scope: !585, file: !3, line: 409, column: 7)
!590 = !DILocation(line: 409, column: 11, scope: !589)
!591 = !DILocation(line: 409, column: 7, scope: !585)
!592 = !DILocation(line: 411, column: 50, scope: !593)
!593 = distinct !DILexicalBlock(scope: !589, file: !3, line: 410, column: 6)
!594 = !DILocation(line: 411, column: 6, scope: !593)
!595 = !DILocation(line: 412, column: 22, scope: !593)
!596 = !DILocation(line: 412, column: 59, scope: !593)
!597 = !DILocation(line: 412, column: 66, scope: !593)
!598 = !DILocation(line: 412, column: 13, scope: !593)
!599 = !DILocation(line: 413, column: 6, scope: !593)
!600 = !DILocation(line: 415, column: 8, scope: !585)
!601 = !DILocation(line: 415, column: 13, scope: !585)
!602 = !DILocation(line: 415, column: 6, scope: !585)
!603 = !DILocation(line: 416, column: 8, scope: !585)
!604 = !DILocation(line: 416, column: 13, scope: !585)
!605 = !DILocation(line: 416, column: 6, scope: !585)
!606 = !DILocation(line: 417, column: 2, scope: !585)
!607 = !DILocation(line: 420, column: 10, scope: !608)
!608 = distinct !DILexicalBlock(scope: !499, file: !3, line: 420, column: 10)
!609 = !DILocation(line: 420, column: 18, scope: !608)
!610 = !DILocation(line: 420, column: 10, scope: !499)
!611 = !DILocation(line: 422, column: 15, scope: !612)
!612 = distinct !DILexicalBlock(scope: !613, file: !3, line: 422, column: 7)
!613 = distinct !DILexicalBlock(scope: !608, file: !3, line: 421, column: 2)
!614 = !DILocation(line: 422, column: 7, scope: !612)
!615 = !DILocation(line: 422, column: 38, scope: !612)
!616 = !DILocation(line: 422, column: 7, scope: !613)
!617 = !DILocation(line: 424, column: 13, scope: !618)
!618 = distinct !DILexicalBlock(scope: !612, file: !3, line: 423, column: 6)
!619 = !DILocation(line: 425, column: 12, scope: !618)
!620 = !DILocation(line: 426, column: 6, scope: !618)
!621 = !DILocation(line: 427, column: 20, scope: !622)
!622 = distinct !DILexicalBlock(scope: !612, file: !3, line: 427, column: 12)
!623 = !DILocation(line: 427, column: 12, scope: !622)
!624 = !DILocation(line: 427, column: 35, scope: !622)
!625 = !DILocation(line: 427, column: 12, scope: !612)
!626 = !DILocation(line: 428, column: 14, scope: !622)
!627 = !DILocation(line: 428, column: 12, scope: !622)
!628 = !DILocation(line: 428, column: 6, scope: !622)
!629 = !DILocation(line: 431, column: 21, scope: !630)
!630 = distinct !DILexicalBlock(scope: !622, file: !3, line: 430, column: 6)
!631 = !DILocation(line: 431, column: 14, scope: !630)
!632 = !DILocation(line: 431, column: 12, scope: !630)
!633 = !DILocation(line: 432, column: 11, scope: !634)
!634 = distinct !DILexicalBlock(scope: !630, file: !3, line: 432, column: 11)
!635 = !DILocation(line: 432, column: 17, scope: !634)
!636 = !DILocation(line: 432, column: 11, scope: !630)
!637 = !DILocation(line: 434, column: 35, scope: !638)
!638 = distinct !DILexicalBlock(scope: !634, file: !3, line: 433, column: 3)
!639 = !DILocation(line: 434, column: 3, scope: !638)
!640 = !DILocation(line: 435, column: 11, scope: !638)
!641 = !DILocation(line: 435, column: 3, scope: !638)
!642 = !DILocation(line: 436, column: 3, scope: !638)
!643 = !DILocation(line: 438, column: 11, scope: !644)
!644 = distinct !DILexicalBlock(scope: !630, file: !3, line: 438, column: 11)
!645 = !DILocation(line: 438, column: 22, scope: !644)
!646 = !DILocation(line: 438, column: 11, scope: !630)
!647 = !DILocation(line: 440, column: 3, scope: !648)
!648 = distinct !DILexicalBlock(scope: !644, file: !3, line: 439, column: 3)
!649 = !DILocation(line: 441, column: 19, scope: !648)
!650 = !DILocation(line: 441, column: 103, scope: !648)
!651 = !DILocation(line: 441, column: 10, scope: !648)
!652 = !DILocation(line: 442, column: 3, scope: !648)
!653 = !DILocation(line: 443, column: 28, scope: !630)
!654 = !DILocation(line: 443, column: 20, scope: !630)
!655 = !DILocation(line: 443, column: 13, scope: !630)
!656 = !DILocation(line: 444, column: 11, scope: !657)
!657 = distinct !DILexicalBlock(scope: !630, file: !3, line: 444, column: 11)
!658 = !DILocation(line: 444, column: 20, scope: !657)
!659 = !DILocation(line: 444, column: 11, scope: !630)
!660 = !DILocation(line: 449, column: 24, scope: !661)
!661 = distinct !DILexicalBlock(scope: !662, file: !3, line: 449, column: 8)
!662 = distinct !DILexicalBlock(scope: !657, file: !3, line: 445, column: 3)
!663 = !DILocation(line: 449, column: 16, scope: !661)
!664 = !DILocation(line: 449, column: 33, scope: !661)
!665 = !DILocation(line: 449, column: 38, scope: !661)
!666 = !DILocation(line: 449, column: 8, scope: !661)
!667 = !DILocation(line: 449, column: 44, scope: !661)
!668 = !DILocation(line: 449, column: 8, scope: !662)
!669 = !DILocation(line: 451, column: 7, scope: !670)
!670 = distinct !DILexicalBlock(scope: !661, file: !3, line: 450, column: 7)
!671 = !DILocation(line: 452, column: 7, scope: !670)
!672 = !DILocation(line: 453, column: 7, scope: !670)
!673 = !DILocation(line: 454, column: 3, scope: !662)
!674 = !DILocation(line: 456, column: 2, scope: !613)
!675 = !DILocation(line: 458, column: 8, scope: !608)
!676 = !DILocation(line: 461, column: 10, scope: !677)
!677 = distinct !DILexicalBlock(scope: !499, file: !3, line: 461, column: 10)
!678 = !DILocation(line: 461, column: 14, scope: !677)
!679 = !DILocation(line: 461, column: 10, scope: !499)
!680 = !DILocation(line: 463, column: 14, scope: !681)
!681 = distinct !DILexicalBlock(scope: !682, file: !3, line: 463, column: 7)
!682 = distinct !DILexicalBlock(scope: !677, file: !3, line: 462, column: 2)
!683 = !DILocation(line: 463, column: 7, scope: !681)
!684 = !DILocation(line: 463, column: 20, scope: !681)
!685 = !DILocation(line: 463, column: 7, scope: !682)
!686 = !DILocation(line: 465, column: 6, scope: !687)
!687 = distinct !DILexicalBlock(scope: !681, file: !3, line: 464, column: 6)
!688 = !DILocation(line: 466, column: 6, scope: !687)
!689 = !DILocation(line: 467, column: 6, scope: !687)
!690 = !DILocation(line: 469, column: 2, scope: !682)
!691 = !DILocation(line: 487, column: 20, scope: !499)
!692 = !DILocation(line: 487, column: 12, scope: !499)
!693 = !DILocation(line: 488, column: 22, scope: !694)
!694 = distinct !DILexicalBlock(scope: !499, file: !3, line: 488, column: 10)
!695 = !DILocation(line: 488, column: 14, scope: !694)
!696 = !DILocation(line: 488, column: 28, scope: !694)
!697 = !DILocation(line: 488, column: 10, scope: !694)
!698 = !DILocation(line: 488, column: 33, scope: !694)
!699 = !DILocation(line: 488, column: 10, scope: !499)
!700 = !DILocation(line: 489, column: 9, scope: !694)
!701 = !DILocation(line: 489, column: 2, scope: !694)
!702 = !DILocation(line: 491, column: 12, scope: !703)
!703 = distinct !DILexicalBlock(scope: !499, file: !3, line: 491, column: 10)
!704 = !DILocation(line: 491, column: 10, scope: !499)
!705 = !DILocation(line: 496, column: 17, scope: !706)
!706 = distinct !DILexicalBlock(scope: !703, file: !3, line: 492, column: 2)
!707 = !DILocation(line: 496, column: 9, scope: !706)
!708 = !DILocation(line: 497, column: 7, scope: !709)
!709 = distinct !DILexicalBlock(scope: !706, file: !3, line: 497, column: 7)
!710 = !DILocation(line: 497, column: 16, scope: !709)
!711 = !DILocation(line: 497, column: 13, scope: !709)
!712 = !DILocation(line: 497, column: 7, scope: !706)
!713 = !DILocation(line: 498, column: 21, scope: !709)
!714 = !DILocation(line: 498, column: 13, scope: !709)
!715 = !DILocation(line: 498, column: 6, scope: !709)
!716 = !DILocation(line: 499, column: 17, scope: !706)
!717 = !DILocation(line: 499, column: 9, scope: !706)
!718 = !DILocation(line: 503, column: 7, scope: !719)
!719 = distinct !DILexicalBlock(scope: !706, file: !3, line: 503, column: 7)
!720 = !DILocation(line: 503, column: 22, scope: !719)
!721 = !DILocation(line: 503, column: 7, scope: !706)
!722 = !DILocation(line: 505, column: 6, scope: !723)
!723 = distinct !DILexicalBlock(scope: !719, file: !3, line: 504, column: 6)
!724 = !DILocation(line: 506, column: 6, scope: !723)
!725 = !DILocation(line: 523, column: 2, scope: !706)
!726 = !DILocation(line: 530, column: 16, scope: !727)
!727 = distinct !DILexicalBlock(scope: !703, file: !3, line: 525, column: 2)
!728 = !DILocation(line: 534, column: 10, scope: !729)
!729 = distinct !DILexicalBlock(scope: !499, file: !3, line: 534, column: 10)
!730 = !DILocation(line: 534, column: 18, scope: !729)
!731 = !DILocation(line: 534, column: 10, scope: !499)
!732 = !DILocalVariable(name: "pidfp", scope: !733, file: !3, line: 537, type: !50)
!733 = distinct !DILexicalBlock(scope: !729, file: !3, line: 535, column: 2)
!734 = !DILocation(line: 537, column: 8, scope: !733)
!735 = !DILocation(line: 537, column: 23, scope: !733)
!736 = !DILocation(line: 537, column: 16, scope: !733)
!737 = !DILocation(line: 538, column: 7, scope: !738)
!738 = distinct !DILexicalBlock(scope: !733, file: !3, line: 538, column: 7)
!739 = !DILocation(line: 538, column: 13, scope: !738)
!740 = !DILocation(line: 538, column: 7, scope: !733)
!741 = !DILocation(line: 540, column: 38, scope: !742)
!742 = distinct !DILexicalBlock(scope: !738, file: !3, line: 539, column: 6)
!743 = !DILocation(line: 540, column: 6, scope: !742)
!744 = !DILocation(line: 541, column: 6, scope: !742)
!745 = !DILocation(line: 543, column: 18, scope: !733)
!746 = !DILocation(line: 543, column: 39, scope: !733)
!747 = !DILocation(line: 543, column: 9, scope: !733)
!748 = !DILocation(line: 544, column: 17, scope: !733)
!749 = !DILocation(line: 544, column: 9, scope: !733)
!750 = !DILocation(line: 545, column: 2, scope: !733)
!751 = !DILocation(line: 550, column: 20, scope: !499)
!752 = !DILocation(line: 550, column: 18, scope: !499)
!753 = !DILocation(line: 551, column: 10, scope: !754)
!754 = distinct !DILexicalBlock(scope: !499, file: !3, line: 551, column: 10)
!755 = !DILocation(line: 551, column: 23, scope: !754)
!756 = !DILocation(line: 551, column: 10, scope: !499)
!757 = !DILocation(line: 553, column: 2, scope: !758)
!758 = distinct !DILexicalBlock(scope: !754, file: !3, line: 552, column: 2)
!759 = !DILocation(line: 554, column: 2, scope: !758)
!760 = !DILocation(line: 556, column: 18, scope: !499)
!761 = !DILocation(line: 559, column: 10, scope: !762)
!762 = distinct !DILexicalBlock(scope: !499, file: !3, line: 559, column: 10)
!763 = !DILocation(line: 559, column: 10, scope: !499)
!764 = !DILocation(line: 561, column: 15, scope: !765)
!765 = distinct !DILexicalBlock(scope: !766, file: !3, line: 561, column: 7)
!766 = distinct !DILexicalBlock(scope: !762, file: !3, line: 560, column: 2)
!767 = !DILocation(line: 561, column: 7, scope: !765)
!768 = !DILocation(line: 561, column: 21, scope: !765)
!769 = !DILocation(line: 561, column: 7, scope: !766)
!770 = !DILocation(line: 563, column: 6, scope: !771)
!771 = distinct !DILexicalBlock(scope: !765, file: !3, line: 562, column: 6)
!772 = !DILocation(line: 564, column: 6, scope: !771)
!773 = !DILocation(line: 565, column: 6, scope: !771)
!774 = !DILocation(line: 572, column: 7, scope: !775)
!775 = distinct !DILexicalBlock(scope: !766, file: !3, line: 572, column: 7)
!776 = !DILocation(line: 572, column: 15, scope: !775)
!777 = !DILocation(line: 572, column: 28, scope: !775)
!778 = !DILocation(line: 572, column: 39, scope: !775)
!779 = !DILocation(line: 572, column: 31, scope: !775)
!780 = !DILocation(line: 572, column: 54, scope: !775)
!781 = !DILocation(line: 572, column: 7, scope: !766)
!782 = !DILocation(line: 574, column: 20, scope: !783)
!783 = distinct !DILexicalBlock(scope: !784, file: !3, line: 574, column: 11)
!784 = distinct !DILexicalBlock(scope: !775, file: !3, line: 573, column: 6)
!785 = !DILocation(line: 574, column: 29, scope: !783)
!786 = !DILocation(line: 574, column: 42, scope: !783)
!787 = !DILocation(line: 574, column: 34, scope: !783)
!788 = !DILocation(line: 574, column: 11, scope: !783)
!789 = !DILocation(line: 574, column: 50, scope: !783)
!790 = !DILocation(line: 574, column: 11, scope: !784)
!791 = !DILocation(line: 576, column: 10, scope: !792)
!792 = distinct !DILexicalBlock(scope: !783, file: !3, line: 575, column: 3)
!793 = !DILocation(line: 581, column: 3, scope: !792)
!794 = !DILocation(line: 584, column: 3, scope: !795)
!795 = distinct !DILexicalBlock(scope: !783, file: !3, line: 583, column: 3)
!796 = !DILocation(line: 585, column: 19, scope: !795)
!797 = !DILocation(line: 585, column: 110, scope: !795)
!798 = !DILocation(line: 585, column: 10, scope: !795)
!799 = !DILocation(line: 587, column: 6, scope: !784)
!800 = !DILocation(line: 588, column: 9, scope: !766)
!801 = !DILocation(line: 590, column: 14, scope: !802)
!802 = distinct !DILexicalBlock(scope: !766, file: !3, line: 590, column: 7)
!803 = !DILocation(line: 590, column: 7, scope: !802)
!804 = !DILocation(line: 590, column: 20, scope: !802)
!805 = !DILocation(line: 590, column: 7, scope: !766)
!806 = !DILocation(line: 592, column: 6, scope: !807)
!807 = distinct !DILexicalBlock(scope: !802, file: !3, line: 591, column: 6)
!808 = !DILocation(line: 593, column: 6, scope: !807)
!809 = !DILocation(line: 594, column: 6, scope: !807)
!810 = !DILocation(line: 596, column: 2, scope: !766)
!811 = !DILocation(line: 599, column: 10, scope: !812)
!812 = distinct !DILexicalBlock(scope: !499, file: !3, line: 599, column: 10)
!813 = !DILocation(line: 599, column: 19, scope: !812)
!814 = !DILocation(line: 599, column: 10, scope: !499)
!815 = !DILocation(line: 601, column: 14, scope: !816)
!816 = distinct !DILexicalBlock(scope: !817, file: !3, line: 601, column: 7)
!817 = distinct !DILexicalBlock(scope: !812, file: !3, line: 600, column: 2)
!818 = !DILocation(line: 601, column: 7, scope: !816)
!819 = !DILocation(line: 601, column: 25, scope: !816)
!820 = !DILocation(line: 601, column: 7, scope: !817)
!821 = !DILocation(line: 603, column: 6, scope: !822)
!822 = distinct !DILexicalBlock(scope: !816, file: !3, line: 602, column: 6)
!823 = !DILocation(line: 604, column: 6, scope: !822)
!824 = !DILocation(line: 605, column: 6, scope: !822)
!825 = !DILocation(line: 607, column: 2, scope: !817)
!826 = !DILocation(line: 611, column: 12, scope: !499)
!827 = !DILocation(line: 612, column: 12, scope: !499)
!828 = !DILocation(line: 613, column: 12, scope: !499)
!829 = !DILocation(line: 614, column: 12, scope: !499)
!830 = !DILocation(line: 615, column: 12, scope: !499)
!831 = !DILocation(line: 616, column: 12, scope: !499)
!832 = !DILocation(line: 617, column: 12, scope: !499)
!833 = !DILocation(line: 618, column: 12, scope: !499)
!834 = !DILocation(line: 629, column: 13, scope: !499)
!835 = !DILocation(line: 630, column: 14, scope: !499)
!836 = !DILocation(line: 631, column: 19, scope: !499)
!837 = !DILocation(line: 632, column: 12, scope: !499)
!838 = !DILocation(line: 635, column: 5, scope: !499)
!839 = !DILocation(line: 641, column: 2, scope: !499)
!840 = !DILocation(line: 642, column: 2, scope: !499)
!841 = !DILocation(line: 642, column: 38, scope: !499)
!842 = !DILocation(line: 643, column: 2, scope: !499)
!843 = !DILocation(line: 643, column: 8, scope: !499)
!844 = !DILocation(line: 643, column: 21, scope: !499)
!845 = !DILocation(line: 643, column: 32, scope: !499)
!846 = !DILocation(line: 643, column: 41, scope: !499)
!847 = !DILocation(line: 643, column: 46, scope: !499)
!848 = !DILocation(line: 643, column: 55, scope: !499)
!849 = !DILocation(line: 643, column: 60, scope: !499)
!850 = !DILocation(line: 643, column: 68, scope: !499)
!851 = !DILocation(line: 644, column: 2, scope: !499)
!852 = !DILocation(line: 644, column: 20, scope: !499)
!853 = !DILocation(line: 644, column: 30, scope: !499)
!854 = !DILocation(line: 644, column: 48, scope: !499)
!855 = !DILocation(line: 645, column: 2, scope: !499)
!856 = !DILocation(line: 645, column: 17, scope: !499)
!857 = !DILocation(line: 640, column: 10, scope: !499)
!858 = !DILocation(line: 640, column: 8, scope: !499)
!859 = !DILocation(line: 646, column: 10, scope: !860)
!860 = distinct !DILexicalBlock(scope: !499, file: !3, line: 646, column: 10)
!861 = !DILocation(line: 646, column: 13, scope: !860)
!862 = !DILocation(line: 646, column: 10, scope: !499)
!863 = !DILocation(line: 647, column: 2, scope: !860)
!864 = !DILocation(line: 650, column: 10, scope: !865)
!865 = distinct !DILexicalBlock(scope: !499, file: !3, line: 650, column: 10)
!866 = !DILocation(line: 650, column: 100, scope: !865)
!867 = !DILocation(line: 650, column: 10, scope: !499)
!868 = !DILocation(line: 652, column: 2, scope: !869)
!869 = distinct !DILexicalBlock(scope: !865, file: !3, line: 651, column: 2)
!870 = !DILocation(line: 653, column: 2, scope: !869)
!871 = !DILocation(line: 656, column: 10, scope: !872)
!872 = distinct !DILexicalBlock(scope: !499, file: !3, line: 656, column: 10)
!873 = !DILocation(line: 656, column: 80, scope: !872)
!874 = !DILocation(line: 656, column: 10, scope: !499)
!875 = !DILocation(line: 658, column: 2, scope: !876)
!876 = distinct !DILexicalBlock(scope: !872, file: !3, line: 657, column: 2)
!877 = !DILocation(line: 659, column: 2, scope: !876)
!878 = !DILocation(line: 661, column: 10, scope: !879)
!879 = distinct !DILexicalBlock(scope: !499, file: !3, line: 661, column: 10)
!880 = !DILocation(line: 661, column: 23, scope: !879)
!881 = !DILocation(line: 661, column: 10, scope: !499)
!882 = !DILocation(line: 664, column: 7, scope: !883)
!883 = distinct !DILexicalBlock(scope: !884, file: !3, line: 664, column: 7)
!884 = distinct !DILexicalBlock(scope: !879, file: !3, line: 662, column: 2)
!885 = !DILocation(line: 664, column: 101, scope: !883)
!886 = !DILocation(line: 664, column: 7, scope: !884)
!887 = !DILocation(line: 666, column: 6, scope: !888)
!888 = distinct !DILexicalBlock(scope: !883, file: !3, line: 665, column: 6)
!889 = !DILocation(line: 667, column: 6, scope: !888)
!890 = !DILocation(line: 669, column: 2, scope: !884)
!891 = !DILocation(line: 672, column: 10, scope: !892)
!892 = distinct !DILexicalBlock(scope: !499, file: !3, line: 672, column: 10)
!893 = !DILocation(line: 672, column: 95, scope: !892)
!894 = !DILocation(line: 672, column: 10, scope: !499)
!895 = !DILocation(line: 674, column: 2, scope: !896)
!896 = distinct !DILexicalBlock(scope: !892, file: !3, line: 673, column: 2)
!897 = !DILocation(line: 675, column: 2, scope: !896)
!898 = !DILocation(line: 678, column: 31, scope: !499)
!899 = !DILocation(line: 678, column: 29, scope: !499)
!900 = !DILocation(line: 678, column: 16, scope: !499)
!901 = !DILocation(line: 679, column: 23, scope: !499)
!902 = !DILocation(line: 680, column: 17, scope: !499)
!903 = !DILocation(line: 681, column: 24, scope: !499)
!904 = !DILocation(line: 684, column: 10, scope: !905)
!905 = distinct !DILexicalBlock(scope: !499, file: !3, line: 684, column: 10)
!906 = !DILocation(line: 684, column: 19, scope: !905)
!907 = !DILocation(line: 684, column: 10, scope: !499)
!908 = !DILocation(line: 687, column: 7, scope: !909)
!909 = distinct !DILexicalBlock(scope: !910, file: !3, line: 687, column: 7)
!910 = distinct !DILexicalBlock(scope: !905, file: !3, line: 685, column: 2)
!911 = !DILocation(line: 687, column: 40, scope: !909)
!912 = !DILocation(line: 687, column: 7, scope: !910)
!913 = !DILocation(line: 689, column: 6, scope: !914)
!914 = distinct !DILexicalBlock(scope: !909, file: !3, line: 688, column: 6)
!915 = !DILocation(line: 690, column: 6, scope: !914)
!916 = !DILocation(line: 693, column: 15, scope: !917)
!917 = distinct !DILexicalBlock(scope: !910, file: !3, line: 693, column: 7)
!918 = !DILocation(line: 693, column: 7, scope: !917)
!919 = !DILocation(line: 693, column: 21, scope: !917)
!920 = !DILocation(line: 693, column: 7, scope: !910)
!921 = !DILocation(line: 695, column: 6, scope: !922)
!922 = distinct !DILexicalBlock(scope: !917, file: !3, line: 694, column: 6)
!923 = !DILocation(line: 696, column: 6, scope: !922)
!924 = !DILocation(line: 699, column: 19, scope: !925)
!925 = distinct !DILexicalBlock(scope: !910, file: !3, line: 699, column: 7)
!926 = !DILocation(line: 699, column: 25, scope: !925)
!927 = !DILocation(line: 699, column: 7, scope: !925)
!928 = !DILocation(line: 699, column: 31, scope: !925)
!929 = !DILocation(line: 699, column: 7, scope: !910)
!930 = !DILocation(line: 700, column: 6, scope: !925)
!931 = !DILocation(line: 703, column: 26, scope: !910)
!932 = !DILocation(line: 703, column: 16, scope: !910)
!933 = !DILocation(line: 706, column: 15, scope: !934)
!934 = distinct !DILexicalBlock(scope: !910, file: !3, line: 706, column: 7)
!935 = !DILocation(line: 706, column: 7, scope: !934)
!936 = !DILocation(line: 706, column: 21, scope: !934)
!937 = !DILocation(line: 706, column: 7, scope: !910)
!938 = !DILocation(line: 708, column: 6, scope: !939)
!939 = distinct !DILexicalBlock(scope: !934, file: !3, line: 707, column: 6)
!940 = !DILocation(line: 709, column: 6, scope: !939)
!941 = !DILocation(line: 712, column: 9, scope: !942)
!942 = distinct !DILexicalBlock(scope: !910, file: !3, line: 712, column: 7)
!943 = !DILocation(line: 712, column: 7, scope: !910)
!944 = !DILocation(line: 713, column: 6, scope: !942)
!945 = !DILocation(line: 716, column: 2, scope: !910)
!946 = !DILocation(line: 719, column: 16, scope: !499)
!947 = !DILocation(line: 719, column: 14, scope: !499)
!948 = !DILocation(line: 720, column: 10, scope: !949)
!949 = distinct !DILexicalBlock(scope: !499, file: !3, line: 720, column: 10)
!950 = !DILocation(line: 720, column: 19, scope: !949)
!951 = !DILocation(line: 720, column: 10, scope: !499)
!952 = !DILocation(line: 722, column: 2, scope: !953)
!953 = distinct !DILexicalBlock(scope: !949, file: !3, line: 721, column: 2)
!954 = !DILocation(line: 723, column: 2, scope: !953)
!955 = !DILocation(line: 725, column: 16, scope: !956)
!956 = distinct !DILexicalBlock(scope: !499, file: !3, line: 725, column: 5)
!957 = !DILocation(line: 725, column: 11, scope: !956)
!958 = !DILocation(line: 725, column: 21, scope: !959)
!959 = distinct !DILexicalBlock(scope: !956, file: !3, line: 725, column: 5)
!960 = !DILocation(line: 725, column: 28, scope: !959)
!961 = !DILocation(line: 725, column: 26, scope: !959)
!962 = !DILocation(line: 725, column: 5, scope: !956)
!963 = !DILocation(line: 727, column: 2, scope: !964)
!964 = distinct !DILexicalBlock(scope: !959, file: !3, line: 726, column: 2)
!965 = !DILocation(line: 727, column: 11, scope: !964)
!966 = !DILocation(line: 727, column: 17, scope: !964)
!967 = !DILocation(line: 727, column: 28, scope: !964)
!968 = !DILocation(line: 728, column: 37, scope: !964)
!969 = !DILocation(line: 728, column: 42, scope: !964)
!970 = !DILocation(line: 728, column: 2, scope: !964)
!971 = !DILocation(line: 728, column: 11, scope: !964)
!972 = !DILocation(line: 728, column: 17, scope: !964)
!973 = !DILocation(line: 728, column: 35, scope: !964)
!974 = !DILocation(line: 729, column: 2, scope: !964)
!975 = !DILocation(line: 729, column: 11, scope: !964)
!976 = !DILocation(line: 729, column: 17, scope: !964)
!977 = !DILocation(line: 729, column: 20, scope: !964)
!978 = !DILocation(line: 730, column: 2, scope: !964)
!979 = !DILocation(line: 725, column: 42, scope: !959)
!980 = !DILocation(line: 725, column: 5, scope: !959)
!981 = distinct !{!981, !962, !982}
!982 = !DILocation(line: 730, column: 2, scope: !956)
!983 = !DILocation(line: 731, column: 5, scope: !499)
!984 = !DILocation(line: 731, column: 14, scope: !499)
!985 = !DILocation(line: 731, column: 27, scope: !499)
!986 = !DILocation(line: 731, column: 32, scope: !499)
!987 = !DILocation(line: 731, column: 50, scope: !499)
!988 = !DILocation(line: 732, column: 24, scope: !499)
!989 = !DILocation(line: 733, column: 18, scope: !499)
!990 = !DILocation(line: 734, column: 22, scope: !499)
!991 = !DILocation(line: 736, column: 10, scope: !992)
!992 = distinct !DILexicalBlock(scope: !499, file: !3, line: 736, column: 10)
!993 = !DILocation(line: 736, column: 13, scope: !992)
!994 = !DILocation(line: 736, column: 10, scope: !499)
!995 = !DILocation(line: 738, column: 7, scope: !996)
!996 = distinct !DILexicalBlock(scope: !997, file: !3, line: 738, column: 7)
!997 = distinct !DILexicalBlock(scope: !992, file: !3, line: 737, column: 2)
!998 = !DILocation(line: 738, column: 11, scope: !996)
!999 = !DILocation(line: 738, column: 22, scope: !996)
!1000 = !DILocation(line: 738, column: 7, scope: !997)
!1001 = !DILocation(line: 739, column: 22, scope: !996)
!1002 = !DILocation(line: 739, column: 26, scope: !996)
!1003 = !DILocation(line: 739, column: 6, scope: !996)
!1004 = !DILocation(line: 740, column: 7, scope: !1005)
!1005 = distinct !DILexicalBlock(scope: !997, file: !3, line: 740, column: 7)
!1006 = !DILocation(line: 740, column: 11, scope: !1005)
!1007 = !DILocation(line: 740, column: 22, scope: !1005)
!1008 = !DILocation(line: 740, column: 7, scope: !997)
!1009 = !DILocation(line: 741, column: 22, scope: !1005)
!1010 = !DILocation(line: 741, column: 26, scope: !1005)
!1011 = !DILocation(line: 741, column: 6, scope: !1005)
!1012 = !DILocation(line: 742, column: 2, scope: !997)
!1013 = !DILocation(line: 745, column: 12, scope: !499)
!1014 = !DILocation(line: 746, column: 5, scope: !499)
!1015 = !DILocation(line: 746, column: 17, scope: !499)
!1016 = !DILocation(line: 746, column: 29, scope: !499)
!1017 = !DILocation(line: 746, column: 32, scope: !499)
!1018 = !DILocation(line: 746, column: 45, scope: !499)
!1019 = !DILocation(line: 749, column: 7, scope: !1020)
!1020 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 749, column: 7)
!1021 = distinct !DILexicalBlock(scope: !499, file: !3, line: 747, column: 2)
!1022 = !DILocation(line: 749, column: 7, scope: !1021)
!1023 = !DILocation(line: 751, column: 6, scope: !1024)
!1024 = distinct !DILexicalBlock(scope: !1020, file: !3, line: 750, column: 6)
!1025 = !DILocation(line: 752, column: 14, scope: !1024)
!1026 = !DILocation(line: 753, column: 6, scope: !1024)
!1027 = !DILocation(line: 756, column: 23, scope: !1021)
!1028 = !DILocation(line: 756, column: 14, scope: !1021)
!1029 = !DILocation(line: 756, column: 12, scope: !1021)
!1030 = !DILocation(line: 757, column: 7, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 757, column: 7)
!1032 = !DILocation(line: 757, column: 17, scope: !1031)
!1033 = !DILocation(line: 757, column: 7, scope: !1021)
!1034 = !DILocation(line: 759, column: 11, scope: !1035)
!1035 = distinct !DILexicalBlock(scope: !1036, file: !3, line: 759, column: 11)
!1036 = distinct !DILexicalBlock(scope: !1031, file: !3, line: 758, column: 6)
!1037 = !DILocation(line: 759, column: 17, scope: !1035)
!1038 = !DILocation(line: 759, column: 26, scope: !1035)
!1039 = !DILocation(line: 759, column: 29, scope: !1035)
!1040 = !DILocation(line: 759, column: 35, scope: !1035)
!1041 = !DILocation(line: 759, column: 11, scope: !1036)
!1042 = !DILocation(line: 760, column: 3, scope: !1035)
!1043 = distinct !{!1043, !1014, !1044}
!1044 = !DILocation(line: 826, column: 2, scope: !499)
!1045 = !DILocation(line: 761, column: 6, scope: !1036)
!1046 = !DILocation(line: 762, column: 6, scope: !1036)
!1047 = !DILocation(line: 764, column: 9, scope: !1021)
!1048 = !DILocation(line: 766, column: 7, scope: !1049)
!1049 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 766, column: 7)
!1050 = !DILocation(line: 766, column: 17, scope: !1049)
!1051 = !DILocation(line: 766, column: 7, scope: !1021)
!1052 = !DILocation(line: 769, column: 6, scope: !1053)
!1053 = distinct !DILexicalBlock(scope: !1049, file: !3, line: 767, column: 6)
!1054 = !DILocation(line: 770, column: 6, scope: !1053)
!1055 = !DILocation(line: 774, column: 7, scope: !1056)
!1056 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 774, column: 7)
!1057 = !DILocation(line: 774, column: 10, scope: !1056)
!1058 = !DILocation(line: 774, column: 31, scope: !1056)
!1059 = !DILocation(line: 774, column: 34, scope: !1056)
!1060 = !DILocation(line: 774, column: 38, scope: !1056)
!1061 = !DILocation(line: 774, column: 49, scope: !1056)
!1062 = !DILocation(line: 774, column: 55, scope: !1056)
!1063 = !DILocation(line: 775, column: 25, scope: !1056)
!1064 = !DILocation(line: 775, column: 29, scope: !1056)
!1065 = !DILocation(line: 775, column: 7, scope: !1056)
!1066 = !DILocation(line: 774, column: 7, scope: !1021)
!1067 = !DILocation(line: 777, column: 35, scope: !1068)
!1068 = distinct !DILexicalBlock(scope: !1069, file: !3, line: 777, column: 11)
!1069 = distinct !DILexicalBlock(scope: !1056, file: !3, line: 776, column: 6)
!1070 = !DILocation(line: 777, column: 39, scope: !1068)
!1071 = !DILocation(line: 777, column: 11, scope: !1068)
!1072 = !DILocation(line: 777, column: 11, scope: !1069)
!1073 = !DILocation(line: 782, column: 3, scope: !1068)
!1074 = !DILocation(line: 783, column: 6, scope: !1069)
!1075 = !DILocation(line: 784, column: 7, scope: !1076)
!1076 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 784, column: 7)
!1077 = !DILocation(line: 784, column: 10, scope: !1076)
!1078 = !DILocation(line: 784, column: 31, scope: !1076)
!1079 = !DILocation(line: 784, column: 34, scope: !1076)
!1080 = !DILocation(line: 784, column: 38, scope: !1076)
!1081 = !DILocation(line: 784, column: 49, scope: !1076)
!1082 = !DILocation(line: 784, column: 55, scope: !1076)
!1083 = !DILocation(line: 785, column: 25, scope: !1076)
!1084 = !DILocation(line: 785, column: 29, scope: !1076)
!1085 = !DILocation(line: 785, column: 7, scope: !1076)
!1086 = !DILocation(line: 784, column: 7, scope: !1021)
!1087 = !DILocation(line: 787, column: 35, scope: !1088)
!1088 = distinct !DILexicalBlock(scope: !1089, file: !3, line: 787, column: 11)
!1089 = distinct !DILexicalBlock(scope: !1076, file: !3, line: 786, column: 6)
!1090 = !DILocation(line: 787, column: 39, scope: !1088)
!1091 = !DILocation(line: 787, column: 11, scope: !1088)
!1092 = !DILocation(line: 787, column: 11, scope: !1089)
!1093 = !DILocation(line: 792, column: 3, scope: !1088)
!1094 = !DILocation(line: 793, column: 6, scope: !1089)
!1095 = !DILocation(line: 796, column: 2, scope: !1021)
!1096 = !DILocation(line: 796, column: 30, scope: !1021)
!1097 = !DILocation(line: 796, column: 16, scope: !1021)
!1098 = !DILocation(line: 796, column: 14, scope: !1021)
!1099 = !DILocation(line: 796, column: 63, scope: !1021)
!1100 = !DILocation(line: 798, column: 11, scope: !1101)
!1101 = distinct !DILexicalBlock(scope: !1102, file: !3, line: 798, column: 11)
!1102 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 797, column: 6)
!1103 = !DILocation(line: 798, column: 13, scope: !1101)
!1104 = !DILocation(line: 798, column: 11, scope: !1102)
!1105 = !DILocation(line: 799, column: 3, scope: !1101)
!1106 = distinct !{!1106, !1095, !1107}
!1107 = !DILocation(line: 811, column: 6, scope: !1021)
!1108 = !DILocation(line: 800, column: 11, scope: !1102)
!1109 = !DILocation(line: 800, column: 14, scope: !1102)
!1110 = !DILocation(line: 800, column: 9, scope: !1102)
!1111 = !DILocation(line: 801, column: 31, scope: !1112)
!1112 = distinct !DILexicalBlock(scope: !1102, file: !3, line: 801, column: 11)
!1113 = !DILocation(line: 801, column: 35, scope: !1112)
!1114 = !DILocation(line: 801, column: 13, scope: !1112)
!1115 = !DILocation(line: 801, column: 11, scope: !1102)
!1116 = !DILocation(line: 803, column: 21, scope: !1112)
!1117 = !DILocation(line: 803, column: 3, scope: !1112)
!1118 = !DILocation(line: 805, column: 12, scope: !1112)
!1119 = !DILocation(line: 805, column: 15, scope: !1112)
!1120 = !DILocation(line: 805, column: 3, scope: !1112)
!1121 = !DILocation(line: 807, column: 39, scope: !1122)
!1122 = distinct !DILexicalBlock(scope: !1112, file: !3, line: 806, column: 7)
!1123 = !DILocation(line: 807, column: 26, scope: !1122)
!1124 = !DILocation(line: 807, column: 49, scope: !1122)
!1125 = !DILocation(line: 808, column: 39, scope: !1122)
!1126 = !DILocation(line: 808, column: 26, scope: !1122)
!1127 = !DILocation(line: 808, column: 49, scope: !1122)
!1128 = !DILocation(line: 809, column: 43, scope: !1122)
!1129 = !DILocation(line: 809, column: 28, scope: !1122)
!1130 = !DILocation(line: 809, column: 53, scope: !1122)
!1131 = !DILocation(line: 812, column: 2, scope: !1021)
!1132 = !DILocation(line: 814, column: 7, scope: !1133)
!1133 = distinct !DILexicalBlock(scope: !1021, file: !3, line: 814, column: 7)
!1134 = !DILocation(line: 814, column: 16, scope: !1133)
!1135 = !DILocation(line: 814, column: 21, scope: !1133)
!1136 = !DILocation(line: 814, column: 7, scope: !1021)
!1137 = !DILocation(line: 816, column: 16, scope: !1138)
!1138 = distinct !DILexicalBlock(scope: !1133, file: !3, line: 815, column: 6)
!1139 = !DILocation(line: 817, column: 11, scope: !1140)
!1140 = distinct !DILexicalBlock(scope: !1138, file: !3, line: 817, column: 11)
!1141 = !DILocation(line: 817, column: 14, scope: !1140)
!1142 = !DILocation(line: 817, column: 11, scope: !1138)
!1143 = !DILocation(line: 819, column: 8, scope: !1144)
!1144 = distinct !DILexicalBlock(scope: !1145, file: !3, line: 819, column: 8)
!1145 = distinct !DILexicalBlock(scope: !1140, file: !3, line: 818, column: 3)
!1146 = !DILocation(line: 819, column: 12, scope: !1144)
!1147 = !DILocation(line: 819, column: 23, scope: !1144)
!1148 = !DILocation(line: 819, column: 8, scope: !1145)
!1149 = !DILocation(line: 820, column: 23, scope: !1144)
!1150 = !DILocation(line: 820, column: 27, scope: !1144)
!1151 = !DILocation(line: 820, column: 7, scope: !1144)
!1152 = !DILocation(line: 821, column: 8, scope: !1153)
!1153 = distinct !DILexicalBlock(scope: !1145, file: !3, line: 821, column: 8)
!1154 = !DILocation(line: 821, column: 12, scope: !1153)
!1155 = !DILocation(line: 821, column: 23, scope: !1153)
!1156 = !DILocation(line: 821, column: 8, scope: !1145)
!1157 = !DILocation(line: 822, column: 23, scope: !1153)
!1158 = !DILocation(line: 822, column: 27, scope: !1153)
!1159 = !DILocation(line: 822, column: 7, scope: !1153)
!1160 = !DILocation(line: 823, column: 19, scope: !1145)
!1161 = !DILocation(line: 823, column: 3, scope: !1145)
!1162 = !DILocation(line: 824, column: 3, scope: !1145)
!1163 = !DILocation(line: 825, column: 6, scope: !1138)
!1164 = !DILocation(line: 829, column: 5, scope: !499)
!1165 = !DILocation(line: 830, column: 5, scope: !499)
!1166 = !DILocation(line: 831, column: 5, scope: !499)
!1167 = !DILocation(line: 832, column: 5, scope: !499)
!1168 = distinct !DISubprogram(name: "parse_args", scope: !3, file: !3, line: 837, type: !1169, scopeLine: 838, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1169 = !DISubroutineType(types: !1170)
!1170 = !{null, !26, !502}
!1171 = !DILocalVariable(name: "argc", arg: 1, scope: !1168, file: !3, line: 837, type: !26)
!1172 = !DILocation(line: 837, column: 17, scope: !1168)
!1173 = !DILocalVariable(name: "argv", arg: 2, scope: !1168, file: !3, line: 837, type: !502)
!1174 = !DILocation(line: 837, column: 30, scope: !1168)
!1175 = !DILocalVariable(name: "argn", scope: !1168, file: !3, line: 839, type: !26)
!1176 = !DILocation(line: 839, column: 9, scope: !1168)
!1177 = !DILocation(line: 841, column: 11, scope: !1168)
!1178 = !DILocation(line: 842, column: 10, scope: !1168)
!1179 = !DILocation(line: 843, column: 9, scope: !1168)
!1180 = !DILocation(line: 844, column: 14, scope: !1168)
!1181 = !DILocation(line: 848, column: 15, scope: !1168)
!1182 = !DILocation(line: 850, column: 12, scope: !1168)
!1183 = !DILocation(line: 851, column: 24, scope: !1168)
!1184 = !DILocation(line: 851, column: 22, scope: !1168)
!1185 = !DILocation(line: 855, column: 14, scope: !1168)
!1186 = !DILocation(line: 860, column: 22, scope: !1168)
!1187 = !DILocation(line: 865, column: 17, scope: !1168)
!1188 = !DILocation(line: 870, column: 15, scope: !1168)
!1189 = !DILocation(line: 872, column: 17, scope: !1168)
!1190 = !DILocation(line: 873, column: 24, scope: !1168)
!1191 = !DILocation(line: 874, column: 19, scope: !1168)
!1192 = !DILocation(line: 875, column: 18, scope: !1168)
!1193 = !DILocation(line: 876, column: 14, scope: !1168)
!1194 = !DILocation(line: 877, column: 13, scope: !1168)
!1195 = !DILocation(line: 878, column: 13, scope: !1168)
!1196 = !DILocation(line: 879, column: 10, scope: !1168)
!1197 = !DILocation(line: 880, column: 13, scope: !1168)
!1198 = !DILocation(line: 881, column: 9, scope: !1168)
!1199 = !DILocation(line: 882, column: 13, scope: !1168)
!1200 = !DILocation(line: 883, column: 10, scope: !1168)
!1201 = !DILocation(line: 884, column: 5, scope: !1168)
!1202 = !DILocation(line: 884, column: 13, scope: !1168)
!1203 = !DILocation(line: 884, column: 20, scope: !1168)
!1204 = !DILocation(line: 884, column: 18, scope: !1168)
!1205 = !DILocation(line: 884, column: 25, scope: !1168)
!1206 = !DILocation(line: 884, column: 28, scope: !1168)
!1207 = !DILocation(line: 884, column: 33, scope: !1168)
!1208 = !DILocation(line: 884, column: 42, scope: !1168)
!1209 = !DILocation(line: 0, scope: !1168)
!1210 = !DILocation(line: 886, column: 15, scope: !1211)
!1211 = distinct !DILexicalBlock(scope: !1212, file: !3, line: 886, column: 7)
!1212 = distinct !DILexicalBlock(scope: !1168, file: !3, line: 885, column: 2)
!1213 = !DILocation(line: 886, column: 20, scope: !1211)
!1214 = !DILocation(line: 886, column: 7, scope: !1211)
!1215 = !DILocation(line: 886, column: 34, scope: !1211)
!1216 = !DILocation(line: 886, column: 7, scope: !1212)
!1217 = !DILocation(line: 888, column: 13, scope: !1218)
!1218 = distinct !DILexicalBlock(scope: !1211, file: !3, line: 887, column: 6)
!1219 = !DILocation(line: 889, column: 6, scope: !1218)
!1220 = !DILocation(line: 891, column: 20, scope: !1221)
!1221 = distinct !DILexicalBlock(scope: !1211, file: !3, line: 891, column: 12)
!1222 = !DILocation(line: 891, column: 25, scope: !1221)
!1223 = !DILocation(line: 891, column: 12, scope: !1221)
!1224 = !DILocation(line: 891, column: 39, scope: !1221)
!1225 = !DILocation(line: 891, column: 44, scope: !1221)
!1226 = !DILocation(line: 891, column: 47, scope: !1221)
!1227 = !DILocation(line: 891, column: 52, scope: !1221)
!1228 = !DILocation(line: 891, column: 58, scope: !1221)
!1229 = !DILocation(line: 891, column: 56, scope: !1221)
!1230 = !DILocation(line: 891, column: 12, scope: !1211)
!1231 = !DILocation(line: 893, column: 6, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !1221, file: !3, line: 892, column: 6)
!1233 = !DILocation(line: 894, column: 19, scope: !1232)
!1234 = !DILocation(line: 894, column: 24, scope: !1232)
!1235 = !DILocation(line: 894, column: 6, scope: !1232)
!1236 = !DILocation(line: 895, column: 6, scope: !1232)
!1237 = !DILocation(line: 896, column: 20, scope: !1238)
!1238 = distinct !DILexicalBlock(scope: !1221, file: !3, line: 896, column: 12)
!1239 = !DILocation(line: 896, column: 25, scope: !1238)
!1240 = !DILocation(line: 896, column: 12, scope: !1238)
!1241 = !DILocation(line: 896, column: 39, scope: !1238)
!1242 = !DILocation(line: 896, column: 44, scope: !1238)
!1243 = !DILocation(line: 896, column: 47, scope: !1238)
!1244 = !DILocation(line: 896, column: 52, scope: !1238)
!1245 = !DILocation(line: 896, column: 58, scope: !1238)
!1246 = !DILocation(line: 896, column: 56, scope: !1238)
!1247 = !DILocation(line: 896, column: 12, scope: !1221)
!1248 = !DILocation(line: 898, column: 6, scope: !1249)
!1249 = distinct !DILexicalBlock(scope: !1238, file: !3, line: 897, column: 6)
!1250 = !DILocation(line: 899, column: 36, scope: !1249)
!1251 = !DILocation(line: 899, column: 41, scope: !1249)
!1252 = !DILocation(line: 899, column: 30, scope: !1249)
!1253 = !DILocation(line: 899, column: 13, scope: !1249)
!1254 = !DILocation(line: 899, column: 11, scope: !1249)
!1255 = !DILocation(line: 900, column: 6, scope: !1249)
!1256 = !DILocation(line: 901, column: 20, scope: !1257)
!1257 = distinct !DILexicalBlock(scope: !1238, file: !3, line: 901, column: 12)
!1258 = !DILocation(line: 901, column: 25, scope: !1257)
!1259 = !DILocation(line: 901, column: 12, scope: !1257)
!1260 = !DILocation(line: 901, column: 39, scope: !1257)
!1261 = !DILocation(line: 901, column: 44, scope: !1257)
!1262 = !DILocation(line: 901, column: 47, scope: !1257)
!1263 = !DILocation(line: 901, column: 52, scope: !1257)
!1264 = !DILocation(line: 901, column: 58, scope: !1257)
!1265 = !DILocation(line: 901, column: 56, scope: !1257)
!1266 = !DILocation(line: 901, column: 12, scope: !1238)
!1267 = !DILocation(line: 903, column: 6, scope: !1268)
!1268 = distinct !DILexicalBlock(scope: !1257, file: !3, line: 902, column: 6)
!1269 = !DILocation(line: 904, column: 12, scope: !1268)
!1270 = !DILocation(line: 904, column: 17, scope: !1268)
!1271 = !DILocation(line: 904, column: 10, scope: !1268)
!1272 = !DILocation(line: 905, column: 6, scope: !1268)
!1273 = !DILocation(line: 906, column: 20, scope: !1274)
!1274 = distinct !DILexicalBlock(scope: !1257, file: !3, line: 906, column: 12)
!1275 = !DILocation(line: 906, column: 25, scope: !1274)
!1276 = !DILocation(line: 906, column: 12, scope: !1274)
!1277 = !DILocation(line: 906, column: 39, scope: !1274)
!1278 = !DILocation(line: 906, column: 12, scope: !1257)
!1279 = !DILocation(line: 908, column: 16, scope: !1280)
!1280 = distinct !DILexicalBlock(scope: !1274, file: !3, line: 907, column: 6)
!1281 = !DILocation(line: 909, column: 23, scope: !1280)
!1282 = !DILocation(line: 910, column: 6, scope: !1280)
!1283 = !DILocation(line: 911, column: 20, scope: !1284)
!1284 = distinct !DILexicalBlock(scope: !1274, file: !3, line: 911, column: 12)
!1285 = !DILocation(line: 911, column: 25, scope: !1284)
!1286 = !DILocation(line: 911, column: 12, scope: !1284)
!1287 = !DILocation(line: 911, column: 41, scope: !1284)
!1288 = !DILocation(line: 911, column: 12, scope: !1274)
!1289 = !DILocation(line: 913, column: 16, scope: !1290)
!1290 = distinct !DILexicalBlock(scope: !1284, file: !3, line: 912, column: 6)
!1291 = !DILocation(line: 914, column: 23, scope: !1290)
!1292 = !DILocation(line: 915, column: 6, scope: !1290)
!1293 = !DILocation(line: 916, column: 20, scope: !1294)
!1294 = distinct !DILexicalBlock(scope: !1284, file: !3, line: 916, column: 12)
!1295 = !DILocation(line: 916, column: 25, scope: !1294)
!1296 = !DILocation(line: 916, column: 12, scope: !1294)
!1297 = !DILocation(line: 916, column: 40, scope: !1294)
!1298 = !DILocation(line: 916, column: 45, scope: !1294)
!1299 = !DILocation(line: 916, column: 48, scope: !1294)
!1300 = !DILocation(line: 916, column: 53, scope: !1294)
!1301 = !DILocation(line: 916, column: 59, scope: !1294)
!1302 = !DILocation(line: 916, column: 57, scope: !1294)
!1303 = !DILocation(line: 916, column: 12, scope: !1284)
!1304 = !DILocation(line: 918, column: 6, scope: !1305)
!1305 = distinct !DILexicalBlock(scope: !1294, file: !3, line: 917, column: 6)
!1306 = !DILocation(line: 919, column: 17, scope: !1305)
!1307 = !DILocation(line: 919, column: 22, scope: !1305)
!1308 = !DILocation(line: 919, column: 15, scope: !1305)
!1309 = !DILocation(line: 920, column: 6, scope: !1305)
!1310 = !DILocation(line: 921, column: 20, scope: !1311)
!1311 = distinct !DILexicalBlock(scope: !1294, file: !3, line: 921, column: 12)
!1312 = !DILocation(line: 921, column: 25, scope: !1311)
!1313 = !DILocation(line: 921, column: 12, scope: !1311)
!1314 = !DILocation(line: 921, column: 39, scope: !1311)
!1315 = !DILocation(line: 921, column: 12, scope: !1294)
!1316 = !DILocation(line: 922, column: 23, scope: !1311)
!1317 = !DILocation(line: 922, column: 6, scope: !1311)
!1318 = !DILocation(line: 923, column: 20, scope: !1319)
!1319 = distinct !DILexicalBlock(scope: !1311, file: !3, line: 923, column: 12)
!1320 = !DILocation(line: 923, column: 25, scope: !1319)
!1321 = !DILocation(line: 923, column: 12, scope: !1319)
!1322 = !DILocation(line: 923, column: 41, scope: !1319)
!1323 = !DILocation(line: 923, column: 12, scope: !1311)
!1324 = !DILocation(line: 924, column: 23, scope: !1319)
!1325 = !DILocation(line: 924, column: 6, scope: !1319)
!1326 = !DILocation(line: 925, column: 20, scope: !1327)
!1327 = distinct !DILexicalBlock(scope: !1319, file: !3, line: 925, column: 12)
!1328 = !DILocation(line: 925, column: 25, scope: !1327)
!1329 = !DILocation(line: 925, column: 12, scope: !1327)
!1330 = !DILocation(line: 925, column: 39, scope: !1327)
!1331 = !DILocation(line: 925, column: 44, scope: !1327)
!1332 = !DILocation(line: 925, column: 47, scope: !1327)
!1333 = !DILocation(line: 925, column: 52, scope: !1327)
!1334 = !DILocation(line: 925, column: 58, scope: !1327)
!1335 = !DILocation(line: 925, column: 56, scope: !1327)
!1336 = !DILocation(line: 925, column: 12, scope: !1319)
!1337 = !DILocation(line: 927, column: 6, scope: !1338)
!1338 = distinct !DILexicalBlock(scope: !1327, file: !3, line: 926, column: 6)
!1339 = !DILocation(line: 928, column: 13, scope: !1338)
!1340 = !DILocation(line: 928, column: 18, scope: !1338)
!1341 = !DILocation(line: 928, column: 11, scope: !1338)
!1342 = !DILocation(line: 929, column: 6, scope: !1338)
!1343 = !DILocation(line: 930, column: 20, scope: !1344)
!1344 = distinct !DILexicalBlock(scope: !1327, file: !3, line: 930, column: 12)
!1345 = !DILocation(line: 930, column: 25, scope: !1344)
!1346 = !DILocation(line: 930, column: 12, scope: !1344)
!1347 = !DILocation(line: 930, column: 39, scope: !1344)
!1348 = !DILocation(line: 930, column: 44, scope: !1344)
!1349 = !DILocation(line: 930, column: 47, scope: !1344)
!1350 = !DILocation(line: 930, column: 52, scope: !1344)
!1351 = !DILocation(line: 930, column: 58, scope: !1344)
!1352 = !DILocation(line: 930, column: 56, scope: !1344)
!1353 = !DILocation(line: 930, column: 12, scope: !1327)
!1354 = !DILocation(line: 932, column: 6, scope: !1355)
!1355 = distinct !DILexicalBlock(scope: !1344, file: !3, line: 931, column: 6)
!1356 = !DILocation(line: 933, column: 20, scope: !1355)
!1357 = !DILocation(line: 933, column: 25, scope: !1355)
!1358 = !DILocation(line: 933, column: 18, scope: !1355)
!1359 = !DILocation(line: 934, column: 6, scope: !1355)
!1360 = !DILocation(line: 935, column: 20, scope: !1361)
!1361 = distinct !DILexicalBlock(scope: !1344, file: !3, line: 935, column: 12)
!1362 = !DILocation(line: 935, column: 25, scope: !1361)
!1363 = !DILocation(line: 935, column: 12, scope: !1361)
!1364 = !DILocation(line: 935, column: 39, scope: !1361)
!1365 = !DILocation(line: 935, column: 44, scope: !1361)
!1366 = !DILocation(line: 935, column: 47, scope: !1361)
!1367 = !DILocation(line: 935, column: 52, scope: !1361)
!1368 = !DILocation(line: 935, column: 58, scope: !1361)
!1369 = !DILocation(line: 935, column: 56, scope: !1361)
!1370 = !DILocation(line: 935, column: 12, scope: !1344)
!1371 = !DILocation(line: 937, column: 6, scope: !1372)
!1372 = distinct !DILexicalBlock(scope: !1361, file: !3, line: 936, column: 6)
!1373 = !DILocation(line: 938, column: 21, scope: !1372)
!1374 = !DILocation(line: 938, column: 26, scope: !1372)
!1375 = !DILocation(line: 938, column: 19, scope: !1372)
!1376 = !DILocation(line: 939, column: 6, scope: !1372)
!1377 = !DILocation(line: 940, column: 20, scope: !1378)
!1378 = distinct !DILexicalBlock(scope: !1361, file: !3, line: 940, column: 12)
!1379 = !DILocation(line: 940, column: 25, scope: !1378)
!1380 = !DILocation(line: 940, column: 12, scope: !1378)
!1381 = !DILocation(line: 940, column: 39, scope: !1378)
!1382 = !DILocation(line: 940, column: 44, scope: !1378)
!1383 = !DILocation(line: 940, column: 47, scope: !1378)
!1384 = !DILocation(line: 940, column: 52, scope: !1378)
!1385 = !DILocation(line: 940, column: 58, scope: !1378)
!1386 = !DILocation(line: 940, column: 56, scope: !1378)
!1387 = !DILocation(line: 940, column: 12, scope: !1361)
!1388 = !DILocation(line: 942, column: 6, scope: !1389)
!1389 = distinct !DILexicalBlock(scope: !1378, file: !3, line: 941, column: 6)
!1390 = !DILocation(line: 943, column: 17, scope: !1389)
!1391 = !DILocation(line: 943, column: 22, scope: !1389)
!1392 = !DILocation(line: 943, column: 15, scope: !1389)
!1393 = !DILocation(line: 944, column: 6, scope: !1389)
!1394 = !DILocation(line: 945, column: 20, scope: !1395)
!1395 = distinct !DILexicalBlock(scope: !1378, file: !3, line: 945, column: 12)
!1396 = !DILocation(line: 945, column: 25, scope: !1395)
!1397 = !DILocation(line: 945, column: 12, scope: !1395)
!1398 = !DILocation(line: 945, column: 39, scope: !1395)
!1399 = !DILocation(line: 945, column: 44, scope: !1395)
!1400 = !DILocation(line: 945, column: 47, scope: !1395)
!1401 = !DILocation(line: 945, column: 52, scope: !1395)
!1402 = !DILocation(line: 945, column: 58, scope: !1395)
!1403 = !DILocation(line: 945, column: 56, scope: !1395)
!1404 = !DILocation(line: 945, column: 12, scope: !1378)
!1405 = !DILocation(line: 947, column: 6, scope: !1406)
!1406 = distinct !DILexicalBlock(scope: !1395, file: !3, line: 946, column: 6)
!1407 = !DILocation(line: 948, column: 16, scope: !1406)
!1408 = !DILocation(line: 948, column: 21, scope: !1406)
!1409 = !DILocation(line: 948, column: 14, scope: !1406)
!1410 = !DILocation(line: 949, column: 6, scope: !1406)
!1411 = !DILocation(line: 950, column: 20, scope: !1412)
!1412 = distinct !DILexicalBlock(scope: !1395, file: !3, line: 950, column: 12)
!1413 = !DILocation(line: 950, column: 25, scope: !1412)
!1414 = !DILocation(line: 950, column: 12, scope: !1412)
!1415 = !DILocation(line: 950, column: 39, scope: !1412)
!1416 = !DILocation(line: 950, column: 12, scope: !1395)
!1417 = !DILocation(line: 951, column: 15, scope: !1412)
!1418 = !DILocation(line: 951, column: 6, scope: !1412)
!1419 = !DILocation(line: 952, column: 20, scope: !1420)
!1420 = distinct !DILexicalBlock(scope: !1412, file: !3, line: 952, column: 12)
!1421 = !DILocation(line: 952, column: 25, scope: !1420)
!1422 = !DILocation(line: 952, column: 12, scope: !1420)
!1423 = !DILocation(line: 952, column: 41, scope: !1420)
!1424 = !DILocation(line: 952, column: 12, scope: !1412)
!1425 = !DILocation(line: 953, column: 15, scope: !1420)
!1426 = !DILocation(line: 953, column: 6, scope: !1420)
!1427 = !DILocation(line: 954, column: 20, scope: !1428)
!1428 = distinct !DILexicalBlock(scope: !1420, file: !3, line: 954, column: 12)
!1429 = !DILocation(line: 954, column: 25, scope: !1428)
!1430 = !DILocation(line: 954, column: 12, scope: !1428)
!1431 = !DILocation(line: 954, column: 39, scope: !1428)
!1432 = !DILocation(line: 954, column: 12, scope: !1420)
!1433 = !DILocation(line: 955, column: 23, scope: !1428)
!1434 = !DILocation(line: 955, column: 6, scope: !1428)
!1435 = !DILocation(line: 956, column: 20, scope: !1436)
!1436 = distinct !DILexicalBlock(scope: !1428, file: !3, line: 956, column: 12)
!1437 = !DILocation(line: 956, column: 25, scope: !1436)
!1438 = !DILocation(line: 956, column: 12, scope: !1436)
!1439 = !DILocation(line: 956, column: 41, scope: !1436)
!1440 = !DILocation(line: 956, column: 12, scope: !1428)
!1441 = !DILocation(line: 957, column: 23, scope: !1436)
!1442 = !DILocation(line: 957, column: 6, scope: !1436)
!1443 = !DILocation(line: 958, column: 20, scope: !1444)
!1444 = distinct !DILexicalBlock(scope: !1436, file: !3, line: 958, column: 12)
!1445 = !DILocation(line: 958, column: 25, scope: !1444)
!1446 = !DILocation(line: 958, column: 12, scope: !1444)
!1447 = !DILocation(line: 958, column: 39, scope: !1444)
!1448 = !DILocation(line: 958, column: 44, scope: !1444)
!1449 = !DILocation(line: 958, column: 47, scope: !1444)
!1450 = !DILocation(line: 958, column: 52, scope: !1444)
!1451 = !DILocation(line: 958, column: 58, scope: !1444)
!1452 = !DILocation(line: 958, column: 56, scope: !1444)
!1453 = !DILocation(line: 958, column: 12, scope: !1436)
!1454 = !DILocation(line: 960, column: 6, scope: !1455)
!1455 = distinct !DILexicalBlock(scope: !1444, file: !3, line: 959, column: 6)
!1456 = !DILocation(line: 961, column: 16, scope: !1455)
!1457 = !DILocation(line: 961, column: 21, scope: !1455)
!1458 = !DILocation(line: 961, column: 14, scope: !1455)
!1459 = !DILocation(line: 962, column: 6, scope: !1455)
!1460 = !DILocation(line: 963, column: 20, scope: !1461)
!1461 = distinct !DILexicalBlock(scope: !1444, file: !3, line: 963, column: 12)
!1462 = !DILocation(line: 963, column: 25, scope: !1461)
!1463 = !DILocation(line: 963, column: 12, scope: !1461)
!1464 = !DILocation(line: 963, column: 39, scope: !1461)
!1465 = !DILocation(line: 963, column: 44, scope: !1461)
!1466 = !DILocation(line: 963, column: 47, scope: !1461)
!1467 = !DILocation(line: 963, column: 52, scope: !1461)
!1468 = !DILocation(line: 963, column: 58, scope: !1461)
!1469 = !DILocation(line: 963, column: 56, scope: !1461)
!1470 = !DILocation(line: 963, column: 12, scope: !1444)
!1471 = !DILocation(line: 965, column: 6, scope: !1472)
!1472 = distinct !DILexicalBlock(scope: !1461, file: !3, line: 964, column: 6)
!1473 = !DILocation(line: 966, column: 16, scope: !1472)
!1474 = !DILocation(line: 966, column: 21, scope: !1472)
!1475 = !DILocation(line: 966, column: 14, scope: !1472)
!1476 = !DILocation(line: 967, column: 6, scope: !1472)
!1477 = !DILocation(line: 968, column: 20, scope: !1478)
!1478 = distinct !DILexicalBlock(scope: !1461, file: !3, line: 968, column: 12)
!1479 = !DILocation(line: 968, column: 25, scope: !1478)
!1480 = !DILocation(line: 968, column: 12, scope: !1478)
!1481 = !DILocation(line: 968, column: 39, scope: !1478)
!1482 = !DILocation(line: 968, column: 44, scope: !1478)
!1483 = !DILocation(line: 968, column: 47, scope: !1478)
!1484 = !DILocation(line: 968, column: 52, scope: !1478)
!1485 = !DILocation(line: 968, column: 58, scope: !1478)
!1486 = !DILocation(line: 968, column: 56, scope: !1478)
!1487 = !DILocation(line: 968, column: 12, scope: !1461)
!1488 = !DILocation(line: 970, column: 6, scope: !1489)
!1489 = distinct !DILexicalBlock(scope: !1478, file: !3, line: 969, column: 6)
!1490 = !DILocation(line: 971, column: 12, scope: !1489)
!1491 = !DILocation(line: 971, column: 17, scope: !1489)
!1492 = !DILocation(line: 971, column: 10, scope: !1489)
!1493 = !DILocation(line: 972, column: 6, scope: !1489)
!1494 = !DILocation(line: 973, column: 20, scope: !1495)
!1495 = distinct !DILexicalBlock(scope: !1478, file: !3, line: 973, column: 12)
!1496 = !DILocation(line: 973, column: 25, scope: !1495)
!1497 = !DILocation(line: 973, column: 12, scope: !1495)
!1498 = !DILocation(line: 973, column: 39, scope: !1495)
!1499 = !DILocation(line: 973, column: 44, scope: !1495)
!1500 = !DILocation(line: 973, column: 47, scope: !1495)
!1501 = !DILocation(line: 973, column: 52, scope: !1495)
!1502 = !DILocation(line: 973, column: 58, scope: !1495)
!1503 = !DILocation(line: 973, column: 56, scope: !1495)
!1504 = !DILocation(line: 973, column: 12, scope: !1478)
!1505 = !DILocation(line: 975, column: 6, scope: !1506)
!1506 = distinct !DILexicalBlock(scope: !1495, file: !3, line: 974, column: 6)
!1507 = !DILocation(line: 976, column: 22, scope: !1506)
!1508 = !DILocation(line: 976, column: 27, scope: !1506)
!1509 = !DILocation(line: 976, column: 16, scope: !1506)
!1510 = !DILocation(line: 976, column: 14, scope: !1506)
!1511 = !DILocation(line: 977, column: 6, scope: !1506)
!1512 = !DILocation(line: 978, column: 20, scope: !1513)
!1513 = distinct !DILexicalBlock(scope: !1495, file: !3, line: 978, column: 12)
!1514 = !DILocation(line: 978, column: 25, scope: !1513)
!1515 = !DILocation(line: 978, column: 12, scope: !1513)
!1516 = !DILocation(line: 978, column: 39, scope: !1513)
!1517 = !DILocation(line: 978, column: 12, scope: !1495)
!1518 = !DILocation(line: 979, column: 12, scope: !1513)
!1519 = !DILocation(line: 979, column: 6, scope: !1513)
!1520 = !DILocation(line: 981, column: 6, scope: !1513)
!1521 = !DILocation(line: 982, column: 2, scope: !1212)
!1522 = distinct !{!1522, !1201, !1523}
!1523 = !DILocation(line: 983, column: 2, scope: !1168)
!1524 = !DILocation(line: 984, column: 10, scope: !1525)
!1525 = distinct !DILexicalBlock(scope: !1168, file: !3, line: 984, column: 10)
!1526 = !DILocation(line: 984, column: 18, scope: !1525)
!1527 = !DILocation(line: 984, column: 15, scope: !1525)
!1528 = !DILocation(line: 984, column: 10, scope: !1168)
!1529 = !DILocation(line: 985, column: 2, scope: !1525)
!1530 = !DILocation(line: 986, column: 5, scope: !1168)
!1531 = distinct !DISubprogram(name: "lookup_hostname", scope: !3, file: !3, line: 1227, type: !1532, scopeLine: 1228, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1532 = !DISubroutineType(types: !1533)
!1533 = !{null, !109, !264, !1534, !109, !264, !1534}
!1534 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64)
!1535 = !DILocalVariable(name: "sa4P", arg: 1, scope: !1531, file: !3, line: 1227, type: !109)
!1536 = !DILocation(line: 1227, column: 34, scope: !1531)
!1537 = !DILocalVariable(name: "sa4_len", arg: 2, scope: !1531, file: !3, line: 1227, type: !264)
!1538 = !DILocation(line: 1227, column: 47, scope: !1531)
!1539 = !DILocalVariable(name: "gotv4P", arg: 3, scope: !1531, file: !3, line: 1227, type: !1534)
!1540 = !DILocation(line: 1227, column: 61, scope: !1531)
!1541 = !DILocalVariable(name: "sa6P", arg: 4, scope: !1531, file: !3, line: 1227, type: !109)
!1542 = !DILocation(line: 1227, column: 85, scope: !1531)
!1543 = !DILocalVariable(name: "sa6_len", arg: 5, scope: !1531, file: !3, line: 1227, type: !264)
!1544 = !DILocation(line: 1227, column: 98, scope: !1531)
!1545 = !DILocalVariable(name: "gotv6P", arg: 6, scope: !1531, file: !3, line: 1227, type: !1534)
!1546 = !DILocation(line: 1227, column: 112, scope: !1531)
!1547 = !DILocalVariable(name: "hints", scope: !1531, file: !3, line: 1231, type: !397)
!1548 = !DILocation(line: 1231, column: 21, scope: !1531)
!1549 = !DILocalVariable(name: "portstr", scope: !1531, file: !3, line: 1232, type: !1550)
!1550 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 80, elements: !373)
!1551 = !DILocation(line: 1232, column: 10, scope: !1531)
!1552 = !DILocalVariable(name: "gaierr", scope: !1531, file: !3, line: 1233, type: !26)
!1553 = !DILocation(line: 1233, column: 9, scope: !1531)
!1554 = !DILocalVariable(name: "ai", scope: !1531, file: !3, line: 1234, type: !396)
!1555 = !DILocation(line: 1234, column: 22, scope: !1531)
!1556 = !DILocalVariable(name: "ai2", scope: !1531, file: !3, line: 1235, type: !396)
!1557 = !DILocation(line: 1235, column: 22, scope: !1531)
!1558 = !DILocalVariable(name: "aiv6", scope: !1531, file: !3, line: 1236, type: !396)
!1559 = !DILocation(line: 1236, column: 22, scope: !1531)
!1560 = !DILocalVariable(name: "aiv4", scope: !1531, file: !3, line: 1237, type: !396)
!1561 = !DILocation(line: 1237, column: 22, scope: !1531)
!1562 = !DILocation(line: 1239, column: 12, scope: !1531)
!1563 = !DILocation(line: 1240, column: 11, scope: !1531)
!1564 = !DILocation(line: 1240, column: 21, scope: !1531)
!1565 = !DILocation(line: 1241, column: 11, scope: !1531)
!1566 = !DILocation(line: 1241, column: 20, scope: !1531)
!1567 = !DILocation(line: 1242, column: 11, scope: !1531)
!1568 = !DILocation(line: 1242, column: 23, scope: !1531)
!1569 = !DILocation(line: 1243, column: 12, scope: !1531)
!1570 = !DILocation(line: 1244, column: 33, scope: !1571)
!1571 = distinct !DILexicalBlock(scope: !1531, file: !3, line: 1244, column: 10)
!1572 = !DILocation(line: 1244, column: 43, scope: !1571)
!1573 = !DILocation(line: 1244, column: 20, scope: !1571)
!1574 = !DILocation(line: 1244, column: 18, scope: !1571)
!1575 = !DILocation(line: 1244, column: 67, scope: !1571)
!1576 = !DILocation(line: 1244, column: 10, scope: !1531)
!1577 = !DILocation(line: 1248, column: 6, scope: !1578)
!1578 = distinct !DILexicalBlock(scope: !1571, file: !3, line: 1245, column: 2)
!1579 = !DILocation(line: 1248, column: 30, scope: !1578)
!1580 = !DILocation(line: 1248, column: 16, scope: !1578)
!1581 = !DILocation(line: 1246, column: 2, scope: !1578)
!1582 = !DILocation(line: 1250, column: 6, scope: !1578)
!1583 = !DILocation(line: 1251, column: 6, scope: !1578)
!1584 = !DILocation(line: 1251, column: 13, scope: !1578)
!1585 = !DILocation(line: 1251, column: 37, scope: !1578)
!1586 = !DILocation(line: 1251, column: 23, scope: !1578)
!1587 = !DILocation(line: 1249, column: 9, scope: !1578)
!1588 = !DILocation(line: 1252, column: 2, scope: !1578)
!1589 = !DILocation(line: 1256, column: 10, scope: !1531)
!1590 = !DILocation(line: 1257, column: 10, scope: !1531)
!1591 = !DILocation(line: 1258, column: 17, scope: !1592)
!1592 = distinct !DILexicalBlock(scope: !1531, file: !3, line: 1258, column: 5)
!1593 = !DILocation(line: 1258, column: 15, scope: !1592)
!1594 = !DILocation(line: 1258, column: 11, scope: !1592)
!1595 = !DILocation(line: 1258, column: 21, scope: !1596)
!1596 = distinct !DILexicalBlock(scope: !1592, file: !3, line: 1258, column: 5)
!1597 = !DILocation(line: 1258, column: 25, scope: !1596)
!1598 = !DILocation(line: 1258, column: 5, scope: !1592)
!1599 = !DILocation(line: 1260, column: 11, scope: !1600)
!1600 = distinct !DILexicalBlock(scope: !1596, file: !3, line: 1259, column: 2)
!1601 = !DILocation(line: 1260, column: 16, scope: !1600)
!1602 = !DILocation(line: 1260, column: 2, scope: !1600)
!1603 = !DILocation(line: 1263, column: 11, scope: !1604)
!1604 = distinct !DILexicalBlock(scope: !1605, file: !3, line: 1263, column: 11)
!1605 = distinct !DILexicalBlock(scope: !1600, file: !3, line: 1261, column: 6)
!1606 = !DILocation(line: 1263, column: 16, scope: !1604)
!1607 = !DILocation(line: 1263, column: 11, scope: !1605)
!1608 = !DILocation(line: 1264, column: 10, scope: !1604)
!1609 = !DILocation(line: 1264, column: 8, scope: !1604)
!1610 = !DILocation(line: 1264, column: 3, scope: !1604)
!1611 = !DILocation(line: 1265, column: 6, scope: !1605)
!1612 = !DILocation(line: 1267, column: 11, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !1605, file: !3, line: 1267, column: 11)
!1614 = !DILocation(line: 1267, column: 16, scope: !1613)
!1615 = !DILocation(line: 1267, column: 11, scope: !1605)
!1616 = !DILocation(line: 1268, column: 10, scope: !1613)
!1617 = !DILocation(line: 1268, column: 8, scope: !1613)
!1618 = !DILocation(line: 1268, column: 3, scope: !1613)
!1619 = !DILocation(line: 1269, column: 6, scope: !1605)
!1620 = !DILocation(line: 1271, column: 2, scope: !1600)
!1621 = !DILocation(line: 1258, column: 56, scope: !1596)
!1622 = !DILocation(line: 1258, column: 61, scope: !1596)
!1623 = !DILocation(line: 1258, column: 54, scope: !1596)
!1624 = !DILocation(line: 1258, column: 5, scope: !1596)
!1625 = distinct !{!1625, !1598, !1626}
!1626 = !DILocation(line: 1271, column: 2, scope: !1592)
!1627 = !DILocation(line: 1273, column: 10, scope: !1628)
!1628 = distinct !DILexicalBlock(scope: !1531, file: !3, line: 1273, column: 10)
!1629 = !DILocation(line: 1273, column: 15, scope: !1628)
!1630 = !DILocation(line: 1273, column: 10, scope: !1531)
!1631 = !DILocation(line: 1274, column: 3, scope: !1628)
!1632 = !DILocation(line: 1274, column: 10, scope: !1628)
!1633 = !DILocation(line: 1274, column: 2, scope: !1628)
!1634 = !DILocation(line: 1277, column: 7, scope: !1635)
!1635 = distinct !DILexicalBlock(scope: !1636, file: !3, line: 1277, column: 7)
!1636 = distinct !DILexicalBlock(scope: !1628, file: !3, line: 1276, column: 2)
!1637 = !DILocation(line: 1277, column: 17, scope: !1635)
!1638 = !DILocation(line: 1277, column: 23, scope: !1635)
!1639 = !DILocation(line: 1277, column: 15, scope: !1635)
!1640 = !DILocation(line: 1277, column: 7, scope: !1636)
!1641 = !DILocation(line: 1281, column: 3, scope: !1642)
!1642 = distinct !DILexicalBlock(scope: !1635, file: !3, line: 1278, column: 6)
!1643 = !DILocation(line: 1281, column: 29, scope: !1642)
!1644 = !DILocation(line: 1282, column: 19, scope: !1642)
!1645 = !DILocation(line: 1282, column: 25, scope: !1642)
!1646 = !DILocation(line: 1282, column: 3, scope: !1642)
!1647 = !DILocation(line: 1279, column: 6, scope: !1642)
!1648 = !DILocation(line: 1283, column: 6, scope: !1642)
!1649 = !DILocation(line: 1285, column: 9, scope: !1636)
!1650 = !DILocation(line: 1286, column: 9, scope: !1636)
!1651 = !DILocation(line: 1287, column: 3, scope: !1636)
!1652 = !DILocation(line: 1287, column: 10, scope: !1636)
!1653 = !DILocation(line: 1290, column: 10, scope: !1654)
!1654 = distinct !DILexicalBlock(scope: !1531, file: !3, line: 1290, column: 10)
!1655 = !DILocation(line: 1290, column: 15, scope: !1654)
!1656 = !DILocation(line: 1290, column: 10, scope: !1531)
!1657 = !DILocation(line: 1291, column: 3, scope: !1654)
!1658 = !DILocation(line: 1291, column: 10, scope: !1654)
!1659 = !DILocation(line: 1291, column: 2, scope: !1654)
!1660 = !DILocation(line: 1294, column: 7, scope: !1661)
!1661 = distinct !DILexicalBlock(scope: !1662, file: !3, line: 1294, column: 7)
!1662 = distinct !DILexicalBlock(scope: !1654, file: !3, line: 1293, column: 2)
!1663 = !DILocation(line: 1294, column: 17, scope: !1661)
!1664 = !DILocation(line: 1294, column: 23, scope: !1661)
!1665 = !DILocation(line: 1294, column: 15, scope: !1661)
!1666 = !DILocation(line: 1294, column: 7, scope: !1662)
!1667 = !DILocation(line: 1298, column: 3, scope: !1668)
!1668 = distinct !DILexicalBlock(scope: !1661, file: !3, line: 1295, column: 6)
!1669 = !DILocation(line: 1298, column: 29, scope: !1668)
!1670 = !DILocation(line: 1299, column: 19, scope: !1668)
!1671 = !DILocation(line: 1299, column: 25, scope: !1668)
!1672 = !DILocation(line: 1299, column: 3, scope: !1668)
!1673 = !DILocation(line: 1296, column: 6, scope: !1668)
!1674 = !DILocation(line: 1300, column: 6, scope: !1668)
!1675 = !DILocation(line: 1302, column: 9, scope: !1662)
!1676 = !DILocation(line: 1303, column: 9, scope: !1662)
!1677 = !DILocation(line: 1304, column: 3, scope: !1662)
!1678 = !DILocation(line: 1304, column: 10, scope: !1662)
!1679 = !DILocation(line: 1307, column: 19, scope: !1531)
!1680 = !DILocation(line: 1307, column: 5, scope: !1531)
!1681 = !DILocation(line: 1357, column: 5, scope: !1531)
!1682 = distinct !DISubprogram(name: "read_throttlefile", scope: !3, file: !3, line: 1361, type: !1683, scopeLine: 1362, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1683 = !DISubroutineType(types: !1684)
!1684 = !{null, !6}
!1685 = !DILocalVariable(name: "tf", arg: 1, scope: !1682, file: !3, line: 1361, type: !6)
!1686 = !DILocation(line: 1361, column: 26, scope: !1682)
!1687 = !DILocalVariable(name: "fp", scope: !1682, file: !3, line: 1363, type: !50)
!1688 = !DILocation(line: 1363, column: 11, scope: !1682)
!1689 = !DILocalVariable(name: "buf", scope: !1682, file: !3, line: 1364, type: !1690)
!1690 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 40000, elements: !1691)
!1691 = !{!1692}
!1692 = !DISubrange(count: 5000)
!1693 = !DILocation(line: 1364, column: 10, scope: !1682)
!1694 = !DILocalVariable(name: "cp", scope: !1682, file: !3, line: 1365, type: !6)
!1695 = !DILocation(line: 1365, column: 11, scope: !1682)
!1696 = !DILocalVariable(name: "len", scope: !1682, file: !3, line: 1366, type: !26)
!1697 = !DILocation(line: 1366, column: 9, scope: !1682)
!1698 = !DILocalVariable(name: "pattern", scope: !1682, file: !3, line: 1367, type: !1690)
!1699 = !DILocation(line: 1367, column: 10, scope: !1682)
!1700 = !DILocalVariable(name: "max_limit", scope: !1682, file: !3, line: 1368, type: !14)
!1701 = !DILocation(line: 1368, column: 10, scope: !1682)
!1702 = !DILocalVariable(name: "min_limit", scope: !1682, file: !3, line: 1368, type: !14)
!1703 = !DILocation(line: 1368, column: 21, scope: !1682)
!1704 = !DILocalVariable(name: "tv", scope: !1682, file: !3, line: 1369, type: !212)
!1705 = !DILocation(line: 1369, column: 20, scope: !1682)
!1706 = !DILocation(line: 1371, column: 17, scope: !1682)
!1707 = !DILocation(line: 1371, column: 10, scope: !1682)
!1708 = !DILocation(line: 1371, column: 8, scope: !1682)
!1709 = !DILocation(line: 1372, column: 10, scope: !1710)
!1710 = distinct !DILexicalBlock(scope: !1682, file: !3, line: 1372, column: 10)
!1711 = !DILocation(line: 1372, column: 13, scope: !1710)
!1712 = !DILocation(line: 1372, column: 10, scope: !1682)
!1713 = !DILocation(line: 1374, column: 34, scope: !1714)
!1714 = distinct !DILexicalBlock(scope: !1710, file: !3, line: 1373, column: 2)
!1715 = !DILocation(line: 1374, column: 2, scope: !1714)
!1716 = !DILocation(line: 1375, column: 10, scope: !1714)
!1717 = !DILocation(line: 1375, column: 2, scope: !1714)
!1718 = !DILocation(line: 1376, column: 2, scope: !1714)
!1719 = !DILocation(line: 1379, column: 12, scope: !1682)
!1720 = !DILocation(line: 1381, column: 5, scope: !1682)
!1721 = !DILocation(line: 1381, column: 20, scope: !1682)
!1722 = !DILocation(line: 1381, column: 38, scope: !1682)
!1723 = !DILocation(line: 1381, column: 13, scope: !1682)
!1724 = !DILocation(line: 1381, column: 43, scope: !1682)
!1725 = !DILocation(line: 1384, column: 15, scope: !1726)
!1726 = distinct !DILexicalBlock(scope: !1682, file: !3, line: 1382, column: 2)
!1727 = !DILocation(line: 1384, column: 7, scope: !1726)
!1728 = !DILocation(line: 1384, column: 5, scope: !1726)
!1729 = !DILocation(line: 1385, column: 7, scope: !1730)
!1730 = distinct !DILexicalBlock(scope: !1726, file: !3, line: 1385, column: 7)
!1731 = !DILocation(line: 1385, column: 10, scope: !1730)
!1732 = !DILocation(line: 1385, column: 7, scope: !1726)
!1733 = !DILocation(line: 1386, column: 7, scope: !1730)
!1734 = !DILocation(line: 1386, column: 10, scope: !1730)
!1735 = !DILocation(line: 1386, column: 6, scope: !1730)
!1736 = !DILocation(line: 1389, column: 16, scope: !1726)
!1737 = !DILocation(line: 1389, column: 8, scope: !1726)
!1738 = !DILocation(line: 1389, column: 6, scope: !1726)
!1739 = !DILocation(line: 1390, column: 2, scope: !1726)
!1740 = !DILocation(line: 1390, column: 10, scope: !1726)
!1741 = !DILocation(line: 1390, column: 14, scope: !1726)
!1742 = !DILocation(line: 1390, column: 18, scope: !1726)
!1743 = !DILocation(line: 1391, column: 9, scope: !1726)
!1744 = !DILocation(line: 1391, column: 12, scope: !1726)
!1745 = !DILocation(line: 1391, column: 5, scope: !1726)
!1746 = !DILocation(line: 1391, column: 16, scope: !1726)
!1747 = !DILocation(line: 1391, column: 23, scope: !1726)
!1748 = !DILocation(line: 1391, column: 30, scope: !1726)
!1749 = !DILocation(line: 1391, column: 33, scope: !1726)
!1750 = !DILocation(line: 1391, column: 26, scope: !1726)
!1751 = !DILocation(line: 1391, column: 37, scope: !1726)
!1752 = !DILocation(line: 1391, column: 45, scope: !1726)
!1753 = !DILocation(line: 1392, column: 9, scope: !1726)
!1754 = !DILocation(line: 1392, column: 12, scope: !1726)
!1755 = !DILocation(line: 1392, column: 5, scope: !1726)
!1756 = !DILocation(line: 1392, column: 16, scope: !1726)
!1757 = !DILocation(line: 1392, column: 24, scope: !1726)
!1758 = !DILocation(line: 1392, column: 31, scope: !1726)
!1759 = !DILocation(line: 1392, column: 34, scope: !1726)
!1760 = !DILocation(line: 1392, column: 27, scope: !1726)
!1761 = !DILocation(line: 1392, column: 38, scope: !1726)
!1762 = !DILocation(line: 0, scope: !1726)
!1763 = !DILocation(line: 1393, column: 10, scope: !1726)
!1764 = !DILocation(line: 1393, column: 6, scope: !1726)
!1765 = !DILocation(line: 1393, column: 17, scope: !1726)
!1766 = distinct !{!1766, !1739, !1767}
!1767 = !DILocation(line: 1393, column: 19, scope: !1726)
!1768 = !DILocation(line: 1396, column: 7, scope: !1769)
!1769 = distinct !DILexicalBlock(scope: !1726, file: !3, line: 1396, column: 7)
!1770 = !DILocation(line: 1396, column: 11, scope: !1769)
!1771 = !DILocation(line: 1396, column: 7, scope: !1726)
!1772 = !DILocation(line: 1397, column: 6, scope: !1769)
!1773 = distinct !{!1773, !1720, !1774}
!1774 = !DILocation(line: 1452, column: 2, scope: !1682)
!1775 = !DILocation(line: 1400, column: 15, scope: !1776)
!1776 = distinct !DILexicalBlock(scope: !1726, file: !3, line: 1400, column: 7)
!1777 = !DILocation(line: 1400, column: 44, scope: !1776)
!1778 = !DILocation(line: 1400, column: 7, scope: !1776)
!1779 = !DILocation(line: 1400, column: 78, scope: !1776)
!1780 = !DILocation(line: 1400, column: 7, scope: !1726)
!1781 = !DILocation(line: 1401, column: 7, scope: !1782)
!1782 = distinct !DILexicalBlock(scope: !1776, file: !3, line: 1401, column: 6)
!1783 = !DILocation(line: 1402, column: 20, scope: !1784)
!1784 = distinct !DILexicalBlock(scope: !1776, file: !3, line: 1402, column: 12)
!1785 = !DILocation(line: 1402, column: 45, scope: !1784)
!1786 = !DILocation(line: 1402, column: 12, scope: !1784)
!1787 = !DILocation(line: 1402, column: 67, scope: !1784)
!1788 = !DILocation(line: 1402, column: 12, scope: !1776)
!1789 = !DILocation(line: 1403, column: 16, scope: !1784)
!1790 = !DILocation(line: 1403, column: 6, scope: !1784)
!1791 = !DILocation(line: 1407, column: 39, scope: !1792)
!1792 = distinct !DILexicalBlock(scope: !1784, file: !3, line: 1405, column: 6)
!1793 = !DILocation(line: 1407, column: 43, scope: !1792)
!1794 = !DILocation(line: 1406, column: 6, scope: !1792)
!1795 = !DILocation(line: 1408, column: 22, scope: !1792)
!1796 = !DILocation(line: 1410, column: 3, scope: !1792)
!1797 = !DILocation(line: 1410, column: 10, scope: !1792)
!1798 = !DILocation(line: 1410, column: 14, scope: !1792)
!1799 = !DILocation(line: 1408, column: 13, scope: !1792)
!1800 = !DILocation(line: 1411, column: 6, scope: !1792)
!1801 = !DILocation(line: 1415, column: 7, scope: !1802)
!1802 = distinct !DILexicalBlock(scope: !1726, file: !3, line: 1415, column: 7)
!1803 = !DILocation(line: 1415, column: 18, scope: !1802)
!1804 = !DILocation(line: 1415, column: 7, scope: !1726)
!1805 = !DILocation(line: 1416, column: 13, scope: !1802)
!1806 = !DILocation(line: 1416, column: 6, scope: !1802)
!1807 = !DILocation(line: 1417, column: 2, scope: !1726)
!1808 = !DILocation(line: 1417, column: 25, scope: !1726)
!1809 = !DILocation(line: 1417, column: 17, scope: !1726)
!1810 = !DILocation(line: 1417, column: 15, scope: !1726)
!1811 = !DILocation(line: 1417, column: 43, scope: !1726)
!1812 = !DILocation(line: 1418, column: 13, scope: !1726)
!1813 = distinct !{!1813, !1807, !1812}
!1814 = !DILocation(line: 1421, column: 7, scope: !1815)
!1815 = distinct !DILexicalBlock(scope: !1726, file: !3, line: 1421, column: 7)
!1816 = !DILocation(line: 1421, column: 23, scope: !1815)
!1817 = !DILocation(line: 1421, column: 20, scope: !1815)
!1818 = !DILocation(line: 1421, column: 7, scope: !1726)
!1819 = !DILocation(line: 1423, column: 11, scope: !1820)
!1820 = distinct !DILexicalBlock(scope: !1821, file: !3, line: 1423, column: 11)
!1821 = distinct !DILexicalBlock(scope: !1815, file: !3, line: 1422, column: 6)
!1822 = !DILocation(line: 1423, column: 24, scope: !1820)
!1823 = !DILocation(line: 1423, column: 11, scope: !1821)
!1824 = !DILocation(line: 1425, column: 16, scope: !1825)
!1825 = distinct !DILexicalBlock(scope: !1820, file: !3, line: 1424, column: 3)
!1826 = !DILocation(line: 1426, column: 15, scope: !1825)
!1827 = !DILocation(line: 1426, column: 13, scope: !1825)
!1828 = !DILocation(line: 1427, column: 3, scope: !1825)
!1829 = !DILocation(line: 1430, column: 16, scope: !1830)
!1830 = distinct !DILexicalBlock(scope: !1820, file: !3, line: 1429, column: 3)
!1831 = !DILocation(line: 1431, column: 15, scope: !1830)
!1832 = !DILocation(line: 1431, column: 13, scope: !1830)
!1833 = !DILocation(line: 1433, column: 11, scope: !1834)
!1834 = distinct !DILexicalBlock(scope: !1821, file: !3, line: 1433, column: 11)
!1835 = !DILocation(line: 1433, column: 21, scope: !1834)
!1836 = !DILocation(line: 1433, column: 11, scope: !1821)
!1837 = !DILocation(line: 1435, column: 3, scope: !1838)
!1838 = distinct !DILexicalBlock(scope: !1834, file: !3, line: 1434, column: 3)
!1839 = !DILocation(line: 1437, column: 7, scope: !1838)
!1840 = !DILocation(line: 1438, column: 7, scope: !1838)
!1841 = !DILocation(line: 1436, column: 10, scope: !1838)
!1842 = !DILocation(line: 1439, column: 3, scope: !1838)
!1843 = !DILocation(line: 1441, column: 6, scope: !1821)
!1844 = !DILocation(line: 1444, column: 46, scope: !1726)
!1845 = !DILocation(line: 1444, column: 36, scope: !1726)
!1846 = !DILocation(line: 1444, column: 2, scope: !1726)
!1847 = !DILocation(line: 1444, column: 12, scope: !1726)
!1848 = !DILocation(line: 1444, column: 26, scope: !1726)
!1849 = !DILocation(line: 1444, column: 34, scope: !1726)
!1850 = !DILocation(line: 1445, column: 38, scope: !1726)
!1851 = !DILocation(line: 1445, column: 2, scope: !1726)
!1852 = !DILocation(line: 1445, column: 12, scope: !1726)
!1853 = !DILocation(line: 1445, column: 26, scope: !1726)
!1854 = !DILocation(line: 1445, column: 36, scope: !1726)
!1855 = !DILocation(line: 1446, column: 38, scope: !1726)
!1856 = !DILocation(line: 1446, column: 2, scope: !1726)
!1857 = !DILocation(line: 1446, column: 12, scope: !1726)
!1858 = !DILocation(line: 1446, column: 26, scope: !1726)
!1859 = !DILocation(line: 1446, column: 36, scope: !1726)
!1860 = !DILocation(line: 1447, column: 2, scope: !1726)
!1861 = !DILocation(line: 1447, column: 12, scope: !1726)
!1862 = !DILocation(line: 1447, column: 26, scope: !1726)
!1863 = !DILocation(line: 1447, column: 31, scope: !1726)
!1864 = !DILocation(line: 1448, column: 2, scope: !1726)
!1865 = !DILocation(line: 1448, column: 12, scope: !1726)
!1866 = !DILocation(line: 1448, column: 26, scope: !1726)
!1867 = !DILocation(line: 1448, column: 42, scope: !1726)
!1868 = !DILocation(line: 1449, column: 2, scope: !1726)
!1869 = !DILocation(line: 1449, column: 12, scope: !1726)
!1870 = !DILocation(line: 1449, column: 26, scope: !1726)
!1871 = !DILocation(line: 1449, column: 38, scope: !1726)
!1872 = !DILocation(line: 1451, column: 2, scope: !1726)
!1873 = !DILocation(line: 1453, column: 20, scope: !1682)
!1874 = !DILocation(line: 1453, column: 12, scope: !1682)
!1875 = !DILocation(line: 1454, column: 5, scope: !1682)
!1876 = distinct !DISubprogram(name: "handle_term", scope: !3, file: !3, line: 176, type: !107, scopeLine: 177, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1877 = !DILocalVariable(name: "sig", arg: 1, scope: !1876, file: !3, line: 176, type: !26)
!1878 = !DILocation(line: 176, column: 18, scope: !1876)
!1879 = !DILocation(line: 180, column: 5, scope: !1876)
!1880 = !DILocation(line: 181, column: 53, scope: !1876)
!1881 = !DILocation(line: 181, column: 5, scope: !1876)
!1882 = !DILocation(line: 182, column: 5, scope: !1876)
!1883 = !DILocation(line: 183, column: 5, scope: !1876)
!1884 = distinct !DISubprogram(name: "handle_chld", scope: !3, file: !3, line: 189, type: !107, scopeLine: 190, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1885 = !DILocalVariable(name: "sig", arg: 1, scope: !1884, file: !3, line: 189, type: !26)
!1886 = !DILocation(line: 189, column: 18, scope: !1884)
!1887 = !DILocalVariable(name: "oerrno", scope: !1884, file: !3, line: 191, type: !1888)
!1888 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !26)
!1889 = !DILocation(line: 191, column: 15, scope: !1884)
!1890 = !DILocation(line: 191, column: 24, scope: !1884)
!1891 = !DILocalVariable(name: "pid", scope: !1884, file: !3, line: 192, type: !392)
!1892 = !DILocation(line: 192, column: 11, scope: !1884)
!1893 = !DILocalVariable(name: "status", scope: !1884, file: !3, line: 193, type: !26)
!1894 = !DILocation(line: 193, column: 9, scope: !1884)
!1895 = !DILocation(line: 201, column: 5, scope: !1884)
!1896 = !DILocation(line: 204, column: 8, scope: !1897)
!1897 = distinct !DILexicalBlock(scope: !1898, file: !3, line: 202, column: 2)
!1898 = distinct !DILexicalBlock(scope: !1899, file: !3, line: 201, column: 5)
!1899 = distinct !DILexicalBlock(scope: !1884, file: !3, line: 201, column: 5)
!1900 = !DILocation(line: 204, column: 6, scope: !1897)
!1901 = !DILocation(line: 208, column: 13, scope: !1902)
!1902 = distinct !DILexicalBlock(scope: !1897, file: !3, line: 208, column: 7)
!1903 = !DILocation(line: 208, column: 17, scope: !1902)
!1904 = !DILocation(line: 208, column: 7, scope: !1897)
!1905 = !DILocation(line: 209, column: 6, scope: !1902)
!1906 = !DILocation(line: 210, column: 13, scope: !1907)
!1907 = distinct !DILexicalBlock(scope: !1897, file: !3, line: 210, column: 7)
!1908 = !DILocation(line: 210, column: 17, scope: !1907)
!1909 = !DILocation(line: 210, column: 7, scope: !1897)
!1910 = !DILocation(line: 212, column: 11, scope: !1911)
!1911 = distinct !DILexicalBlock(scope: !1912, file: !3, line: 212, column: 11)
!1912 = distinct !DILexicalBlock(scope: !1907, file: !3, line: 211, column: 6)
!1913 = !DILocation(line: 212, column: 17, scope: !1911)
!1914 = !DILocation(line: 212, column: 26, scope: !1911)
!1915 = !DILocation(line: 212, column: 29, scope: !1911)
!1916 = !DILocation(line: 212, column: 35, scope: !1911)
!1917 = !DILocation(line: 212, column: 11, scope: !1912)
!1918 = !DILocation(line: 213, column: 3, scope: !1911)
!1919 = distinct !{!1919, !1920, !1921}
!1920 = !DILocation(line: 201, column: 5, scope: !1899)
!1921 = !DILocation(line: 233, column: 2, scope: !1899)
!1922 = !DILocation(line: 217, column: 11, scope: !1923)
!1923 = distinct !DILexicalBlock(scope: !1912, file: !3, line: 217, column: 11)
!1924 = !DILocation(line: 217, column: 17, scope: !1923)
!1925 = !DILocation(line: 217, column: 11, scope: !1912)
!1926 = !DILocation(line: 218, column: 3, scope: !1923)
!1927 = !DILocation(line: 219, column: 6, scope: !1912)
!1928 = !DILocation(line: 227, column: 7, scope: !1929)
!1929 = distinct !DILexicalBlock(scope: !1897, file: !3, line: 227, column: 7)
!1930 = !DILocation(line: 227, column: 10, scope: !1929)
!1931 = !DILocation(line: 227, column: 7, scope: !1897)
!1932 = !DILocation(line: 229, column: 8, scope: !1933)
!1933 = distinct !DILexicalBlock(scope: !1929, file: !3, line: 228, column: 6)
!1934 = !DILocation(line: 229, column: 12, scope: !1933)
!1935 = !DILocation(line: 229, column: 6, scope: !1933)
!1936 = !DILocation(line: 230, column: 11, scope: !1937)
!1937 = distinct !DILexicalBlock(scope: !1933, file: !3, line: 230, column: 11)
!1938 = !DILocation(line: 230, column: 15, scope: !1937)
!1939 = !DILocation(line: 230, column: 25, scope: !1937)
!1940 = !DILocation(line: 230, column: 11, scope: !1933)
!1941 = !DILocation(line: 231, column: 3, scope: !1937)
!1942 = !DILocation(line: 231, column: 7, scope: !1937)
!1943 = !DILocation(line: 231, column: 17, scope: !1937)
!1944 = !DILocation(line: 232, column: 6, scope: !1933)
!1945 = !DILocation(line: 201, column: 5, scope: !1898)
!1946 = !DILocation(line: 236, column: 13, scope: !1884)
!1947 = !DILocation(line: 236, column: 5, scope: !1884)
!1948 = !DILocation(line: 236, column: 11, scope: !1884)
!1949 = !DILocation(line: 237, column: 5, scope: !1884)
!1950 = distinct !DISubprogram(name: "handle_hup", scope: !3, file: !3, line: 242, type: !107, scopeLine: 243, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1951 = !DILocalVariable(name: "sig", arg: 1, scope: !1950, file: !3, line: 242, type: !26)
!1952 = !DILocation(line: 242, column: 17, scope: !1950)
!1953 = !DILocalVariable(name: "oerrno", scope: !1950, file: !3, line: 244, type: !1888)
!1954 = !DILocation(line: 244, column: 15, scope: !1950)
!1955 = !DILocation(line: 244, column: 24, scope: !1950)
!1956 = !DILocation(line: 252, column: 13, scope: !1950)
!1957 = !DILocation(line: 255, column: 13, scope: !1950)
!1958 = !DILocation(line: 255, column: 5, scope: !1950)
!1959 = !DILocation(line: 255, column: 11, scope: !1950)
!1960 = !DILocation(line: 256, column: 5, scope: !1950)
!1961 = distinct !DISubprogram(name: "handle_usr1", scope: !3, file: !3, line: 261, type: !107, scopeLine: 262, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1962 = !DILocalVariable(name: "sig", arg: 1, scope: !1961, file: !3, line: 261, type: !26)
!1963 = !DILocation(line: 261, column: 18, scope: !1961)
!1964 = !DILocation(line: 265, column: 10, scope: !1965)
!1965 = distinct !DILexicalBlock(scope: !1961, file: !3, line: 265, column: 10)
!1966 = !DILocation(line: 265, column: 23, scope: !1965)
!1967 = !DILocation(line: 265, column: 10, scope: !1961)
!1968 = !DILocation(line: 271, column: 2, scope: !1969)
!1969 = distinct !DILexicalBlock(scope: !1965, file: !3, line: 266, column: 2)
!1970 = !DILocation(line: 272, column: 2, scope: !1969)
!1971 = !DILocation(line: 273, column: 2, scope: !1969)
!1972 = !DILocation(line: 274, column: 2, scope: !1969)
!1973 = !DILocation(line: 278, column: 14, scope: !1961)
!1974 = !DILocation(line: 281, column: 5, scope: !1961)
!1975 = distinct !DISubprogram(name: "handle_usr2", scope: !3, file: !3, line: 286, type: !107, scopeLine: 287, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1976 = !DILocalVariable(name: "sig", arg: 1, scope: !1975, file: !3, line: 286, type: !26)
!1977 = !DILocation(line: 286, column: 18, scope: !1975)
!1978 = !DILocalVariable(name: "oerrno", scope: !1975, file: !3, line: 288, type: !1888)
!1979 = !DILocation(line: 288, column: 15, scope: !1975)
!1980 = !DILocation(line: 288, column: 24, scope: !1975)
!1981 = !DILocation(line: 295, column: 5, scope: !1975)
!1982 = !DILocation(line: 298, column: 13, scope: !1975)
!1983 = !DILocation(line: 298, column: 5, scope: !1975)
!1984 = !DILocation(line: 298, column: 11, scope: !1975)
!1985 = !DILocation(line: 299, column: 5, scope: !1975)
!1986 = distinct !DISubprogram(name: "handle_alrm", scope: !3, file: !3, line: 304, type: !107, scopeLine: 305, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!1987 = !DILocalVariable(name: "sig", arg: 1, scope: !1986, file: !3, line: 304, type: !26)
!1988 = !DILocation(line: 304, column: 18, scope: !1986)
!1989 = !DILocalVariable(name: "oerrno", scope: !1986, file: !3, line: 306, type: !1888)
!1990 = !DILocation(line: 306, column: 15, scope: !1986)
!1991 = !DILocation(line: 306, column: 24, scope: !1986)
!1992 = !DILocation(line: 309, column: 12, scope: !1993)
!1993 = distinct !DILexicalBlock(scope: !1986, file: !3, line: 309, column: 10)
!1994 = !DILocation(line: 309, column: 10, scope: !1986)
!1995 = !DILocation(line: 312, column: 9, scope: !1996)
!1996 = distinct !DILexicalBlock(scope: !1993, file: !3, line: 310, column: 2)
!1997 = !DILocation(line: 314, column: 2, scope: !1996)
!1998 = !DILocation(line: 316, column: 19, scope: !1986)
!1999 = !DILocation(line: 323, column: 12, scope: !1986)
!2000 = !DILocation(line: 326, column: 13, scope: !1986)
!2001 = !DILocation(line: 326, column: 5, scope: !1986)
!2002 = !DILocation(line: 326, column: 11, scope: !1986)
!2003 = !DILocation(line: 327, column: 5, scope: !1986)
!2004 = distinct !DISubprogram(name: "occasional", scope: !3, file: !3, line: 2121, type: !227, scopeLine: 2122, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2005 = !DILocalVariable(name: "client_data", arg: 1, scope: !2004, file: !3, line: 2121, type: !229)
!2006 = !DILocation(line: 2121, column: 24, scope: !2004)
!2007 = !DILocalVariable(name: "nowP", arg: 2, scope: !2004, file: !3, line: 2121, type: !211)
!2008 = !DILocation(line: 2121, column: 53, scope: !2004)
!2009 = !DILocation(line: 2123, column: 18, scope: !2004)
!2010 = !DILocation(line: 2123, column: 5, scope: !2004)
!2011 = !DILocation(line: 2124, column: 5, scope: !2004)
!2012 = !DILocation(line: 2125, column: 19, scope: !2004)
!2013 = !DILocation(line: 2126, column: 5, scope: !2004)
!2014 = distinct !DISubprogram(name: "idle", scope: !3, file: !3, line: 2059, type: !227, scopeLine: 2060, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2015 = !DILocalVariable(name: "client_data", arg: 1, scope: !2014, file: !3, line: 2059, type: !229)
!2016 = !DILocation(line: 2059, column: 18, scope: !2014)
!2017 = !DILocalVariable(name: "nowP", arg: 2, scope: !2014, file: !3, line: 2059, type: !211)
!2018 = !DILocation(line: 2059, column: 47, scope: !2014)
!2019 = !DILocalVariable(name: "cnum", scope: !2014, file: !3, line: 2061, type: !26)
!2020 = !DILocation(line: 2061, column: 9, scope: !2014)
!2021 = !DILocalVariable(name: "c", scope: !2014, file: !3, line: 2062, type: !248)
!2022 = !DILocation(line: 2062, column: 17, scope: !2014)
!2023 = !DILocation(line: 2064, column: 16, scope: !2024)
!2024 = distinct !DILexicalBlock(scope: !2014, file: !3, line: 2064, column: 5)
!2025 = !DILocation(line: 2064, column: 11, scope: !2024)
!2026 = !DILocation(line: 2064, column: 21, scope: !2027)
!2027 = distinct !DILexicalBlock(scope: !2024, file: !3, line: 2064, column: 5)
!2028 = !DILocation(line: 2064, column: 28, scope: !2027)
!2029 = !DILocation(line: 2064, column: 26, scope: !2027)
!2030 = !DILocation(line: 2064, column: 5, scope: !2024)
!2031 = !DILocation(line: 2066, column: 7, scope: !2032)
!2032 = distinct !DILexicalBlock(scope: !2027, file: !3, line: 2065, column: 2)
!2033 = !DILocation(line: 2066, column: 16, scope: !2032)
!2034 = !DILocation(line: 2066, column: 4, scope: !2032)
!2035 = !DILocation(line: 2067, column: 11, scope: !2032)
!2036 = !DILocation(line: 2067, column: 14, scope: !2032)
!2037 = !DILocation(line: 2067, column: 2, scope: !2032)
!2038 = !DILocation(line: 2070, column: 11, scope: !2039)
!2039 = distinct !DILexicalBlock(scope: !2040, file: !3, line: 2070, column: 11)
!2040 = distinct !DILexicalBlock(scope: !2032, file: !3, line: 2068, column: 6)
!2041 = !DILocation(line: 2070, column: 17, scope: !2039)
!2042 = !DILocation(line: 2070, column: 26, scope: !2039)
!2043 = !DILocation(line: 2070, column: 29, scope: !2039)
!2044 = !DILocation(line: 2070, column: 24, scope: !2039)
!2045 = !DILocation(line: 2070, column: 39, scope: !2039)
!2046 = !DILocation(line: 2070, column: 11, scope: !2040)
!2047 = !DILocation(line: 2074, column: 20, scope: !2048)
!2048 = distinct !DILexicalBlock(scope: !2039, file: !3, line: 2071, column: 3)
!2049 = !DILocation(line: 2074, column: 23, scope: !2048)
!2050 = !DILocation(line: 2074, column: 27, scope: !2048)
!2051 = !DILocation(line: 2074, column: 7, scope: !2048)
!2052 = !DILocation(line: 2072, column: 3, scope: !2048)
!2053 = !DILocation(line: 2076, column: 7, scope: !2048)
!2054 = !DILocation(line: 2076, column: 10, scope: !2048)
!2055 = !DILocation(line: 2076, column: 19, scope: !2048)
!2056 = !DILocation(line: 2076, column: 42, scope: !2048)
!2057 = !DILocation(line: 2075, column: 3, scope: !2048)
!2058 = !DILocation(line: 2077, column: 22, scope: !2048)
!2059 = !DILocation(line: 2077, column: 25, scope: !2048)
!2060 = !DILocation(line: 2077, column: 3, scope: !2048)
!2061 = !DILocation(line: 2078, column: 3, scope: !2048)
!2062 = !DILocation(line: 2079, column: 6, scope: !2040)
!2063 = !DILocation(line: 2082, column: 11, scope: !2064)
!2064 = distinct !DILexicalBlock(scope: !2040, file: !3, line: 2082, column: 11)
!2065 = !DILocation(line: 2082, column: 17, scope: !2064)
!2066 = !DILocation(line: 2082, column: 26, scope: !2064)
!2067 = !DILocation(line: 2082, column: 29, scope: !2064)
!2068 = !DILocation(line: 2082, column: 24, scope: !2064)
!2069 = !DILocation(line: 2082, column: 39, scope: !2064)
!2070 = !DILocation(line: 2082, column: 11, scope: !2040)
!2071 = !DILocation(line: 2086, column: 20, scope: !2072)
!2072 = distinct !DILexicalBlock(scope: !2064, file: !3, line: 2083, column: 3)
!2073 = !DILocation(line: 2086, column: 23, scope: !2072)
!2074 = !DILocation(line: 2086, column: 27, scope: !2072)
!2075 = !DILocation(line: 2086, column: 7, scope: !2072)
!2076 = !DILocation(line: 2084, column: 3, scope: !2072)
!2077 = !DILocation(line: 2087, column: 21, scope: !2072)
!2078 = !DILocation(line: 2087, column: 24, scope: !2072)
!2079 = !DILocation(line: 2087, column: 3, scope: !2072)
!2080 = !DILocation(line: 2088, column: 3, scope: !2072)
!2081 = !DILocation(line: 2089, column: 6, scope: !2040)
!2082 = !DILocation(line: 2091, column: 2, scope: !2032)
!2083 = !DILocation(line: 2064, column: 42, scope: !2027)
!2084 = !DILocation(line: 2064, column: 5, scope: !2027)
!2085 = distinct !{!2085, !2030, !2086}
!2086 = !DILocation(line: 2091, column: 2, scope: !2024)
!2087 = !DILocation(line: 2092, column: 5, scope: !2014)
!2088 = distinct !DISubprogram(name: "update_throttles", scope: !3, file: !3, line: 1924, type: !227, scopeLine: 1925, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2089 = !DILocalVariable(name: "client_data", arg: 1, scope: !2088, file: !3, line: 1924, type: !229)
!2090 = !DILocation(line: 1924, column: 30, scope: !2088)
!2091 = !DILocalVariable(name: "nowP", arg: 2, scope: !2088, file: !3, line: 1924, type: !211)
!2092 = !DILocation(line: 1924, column: 59, scope: !2088)
!2093 = !DILocalVariable(name: "tnum", scope: !2088, file: !3, line: 1926, type: !26)
!2094 = !DILocation(line: 1926, column: 9, scope: !2088)
!2095 = !DILocalVariable(name: "tind", scope: !2088, file: !3, line: 1926, type: !26)
!2096 = !DILocation(line: 1926, column: 15, scope: !2088)
!2097 = !DILocalVariable(name: "cnum", scope: !2088, file: !3, line: 1927, type: !26)
!2098 = !DILocation(line: 1927, column: 9, scope: !2088)
!2099 = !DILocalVariable(name: "c", scope: !2088, file: !3, line: 1928, type: !248)
!2100 = !DILocation(line: 1928, column: 17, scope: !2088)
!2101 = !DILocalVariable(name: "l", scope: !2088, file: !3, line: 1929, type: !14)
!2102 = !DILocation(line: 1929, column: 10, scope: !2088)
!2103 = !DILocation(line: 1934, column: 16, scope: !2104)
!2104 = distinct !DILexicalBlock(scope: !2088, file: !3, line: 1934, column: 5)
!2105 = !DILocation(line: 1934, column: 11, scope: !2104)
!2106 = !DILocation(line: 1934, column: 21, scope: !2107)
!2107 = distinct !DILexicalBlock(scope: !2104, file: !3, line: 1934, column: 5)
!2108 = !DILocation(line: 1934, column: 28, scope: !2107)
!2109 = !DILocation(line: 1934, column: 26, scope: !2107)
!2110 = !DILocation(line: 1934, column: 5, scope: !2104)
!2111 = !DILocation(line: 1936, column: 31, scope: !2112)
!2112 = distinct !DILexicalBlock(scope: !2107, file: !3, line: 1935, column: 2)
!2113 = !DILocation(line: 1936, column: 41, scope: !2112)
!2114 = !DILocation(line: 1936, column: 47, scope: !2112)
!2115 = !DILocation(line: 1936, column: 29, scope: !2112)
!2116 = !DILocation(line: 1936, column: 54, scope: !2112)
!2117 = !DILocation(line: 1936, column: 64, scope: !2112)
!2118 = !DILocation(line: 1936, column: 70, scope: !2112)
!2119 = !DILocation(line: 1936, column: 86, scope: !2112)
!2120 = !DILocation(line: 1936, column: 52, scope: !2112)
!2121 = !DILocation(line: 1936, column: 104, scope: !2112)
!2122 = !DILocation(line: 1936, column: 2, scope: !2112)
!2123 = !DILocation(line: 1936, column: 12, scope: !2112)
!2124 = !DILocation(line: 1936, column: 18, scope: !2112)
!2125 = !DILocation(line: 1936, column: 23, scope: !2112)
!2126 = !DILocation(line: 1937, column: 2, scope: !2112)
!2127 = !DILocation(line: 1937, column: 12, scope: !2112)
!2128 = !DILocation(line: 1937, column: 18, scope: !2112)
!2129 = !DILocation(line: 1937, column: 34, scope: !2112)
!2130 = !DILocation(line: 1939, column: 7, scope: !2131)
!2131 = distinct !DILexicalBlock(scope: !2112, file: !3, line: 1939, column: 7)
!2132 = !DILocation(line: 1939, column: 17, scope: !2131)
!2133 = !DILocation(line: 1939, column: 23, scope: !2131)
!2134 = !DILocation(line: 1939, column: 30, scope: !2131)
!2135 = !DILocation(line: 1939, column: 40, scope: !2131)
!2136 = !DILocation(line: 1939, column: 46, scope: !2131)
!2137 = !DILocation(line: 1939, column: 28, scope: !2131)
!2138 = !DILocation(line: 1939, column: 56, scope: !2131)
!2139 = !DILocation(line: 1939, column: 59, scope: !2131)
!2140 = !DILocation(line: 1939, column: 69, scope: !2131)
!2141 = !DILocation(line: 1939, column: 75, scope: !2131)
!2142 = !DILocation(line: 1939, column: 87, scope: !2131)
!2143 = !DILocation(line: 1939, column: 7, scope: !2112)
!2144 = !DILocation(line: 1941, column: 11, scope: !2145)
!2145 = distinct !DILexicalBlock(scope: !2146, file: !3, line: 1941, column: 11)
!2146 = distinct !DILexicalBlock(scope: !2131, file: !3, line: 1940, column: 6)
!2147 = !DILocation(line: 1941, column: 21, scope: !2145)
!2148 = !DILocation(line: 1941, column: 27, scope: !2145)
!2149 = !DILocation(line: 1941, column: 34, scope: !2145)
!2150 = !DILocation(line: 1941, column: 44, scope: !2145)
!2151 = !DILocation(line: 1941, column: 50, scope: !2145)
!2152 = !DILocation(line: 1941, column: 60, scope: !2145)
!2153 = !DILocation(line: 1941, column: 32, scope: !2145)
!2154 = !DILocation(line: 1941, column: 11, scope: !2146)
!2155 = !DILocation(line: 1942, column: 96, scope: !2145)
!2156 = !DILocation(line: 1942, column: 102, scope: !2145)
!2157 = !DILocation(line: 1942, column: 112, scope: !2145)
!2158 = !DILocation(line: 1942, column: 118, scope: !2145)
!2159 = !DILocation(line: 1942, column: 127, scope: !2145)
!2160 = !DILocation(line: 1942, column: 137, scope: !2145)
!2161 = !DILocation(line: 1942, column: 143, scope: !2145)
!2162 = !DILocation(line: 1942, column: 149, scope: !2145)
!2163 = !DILocation(line: 1942, column: 159, scope: !2145)
!2164 = !DILocation(line: 1942, column: 165, scope: !2145)
!2165 = !DILocation(line: 1942, column: 176, scope: !2145)
!2166 = !DILocation(line: 1942, column: 186, scope: !2145)
!2167 = !DILocation(line: 1942, column: 192, scope: !2145)
!2168 = !DILocation(line: 1942, column: 3, scope: !2145)
!2169 = !DILocation(line: 1944, column: 86, scope: !2145)
!2170 = !DILocation(line: 1944, column: 92, scope: !2145)
!2171 = !DILocation(line: 1944, column: 102, scope: !2145)
!2172 = !DILocation(line: 1944, column: 108, scope: !2145)
!2173 = !DILocation(line: 1944, column: 117, scope: !2145)
!2174 = !DILocation(line: 1944, column: 127, scope: !2145)
!2175 = !DILocation(line: 1944, column: 133, scope: !2145)
!2176 = !DILocation(line: 1944, column: 139, scope: !2145)
!2177 = !DILocation(line: 1944, column: 149, scope: !2145)
!2178 = !DILocation(line: 1944, column: 155, scope: !2145)
!2179 = !DILocation(line: 1944, column: 166, scope: !2145)
!2180 = !DILocation(line: 1944, column: 176, scope: !2145)
!2181 = !DILocation(line: 1944, column: 182, scope: !2145)
!2182 = !DILocation(line: 1944, column: 3, scope: !2145)
!2183 = !DILocation(line: 1945, column: 6, scope: !2146)
!2184 = !DILocation(line: 1946, column: 7, scope: !2185)
!2185 = distinct !DILexicalBlock(scope: !2112, file: !3, line: 1946, column: 7)
!2186 = !DILocation(line: 1946, column: 17, scope: !2185)
!2187 = !DILocation(line: 1946, column: 23, scope: !2185)
!2188 = !DILocation(line: 1946, column: 30, scope: !2185)
!2189 = !DILocation(line: 1946, column: 40, scope: !2185)
!2190 = !DILocation(line: 1946, column: 46, scope: !2185)
!2191 = !DILocation(line: 1946, column: 28, scope: !2185)
!2192 = !DILocation(line: 1946, column: 56, scope: !2185)
!2193 = !DILocation(line: 1946, column: 59, scope: !2185)
!2194 = !DILocation(line: 1946, column: 69, scope: !2185)
!2195 = !DILocation(line: 1946, column: 75, scope: !2185)
!2196 = !DILocation(line: 1946, column: 87, scope: !2185)
!2197 = !DILocation(line: 1946, column: 7, scope: !2112)
!2198 = !DILocation(line: 1948, column: 94, scope: !2199)
!2199 = distinct !DILexicalBlock(scope: !2185, file: !3, line: 1947, column: 6)
!2200 = !DILocation(line: 1948, column: 100, scope: !2199)
!2201 = !DILocation(line: 1948, column: 110, scope: !2199)
!2202 = !DILocation(line: 1948, column: 116, scope: !2199)
!2203 = !DILocation(line: 1948, column: 125, scope: !2199)
!2204 = !DILocation(line: 1948, column: 135, scope: !2199)
!2205 = !DILocation(line: 1948, column: 141, scope: !2199)
!2206 = !DILocation(line: 1948, column: 147, scope: !2199)
!2207 = !DILocation(line: 1948, column: 157, scope: !2199)
!2208 = !DILocation(line: 1948, column: 163, scope: !2199)
!2209 = !DILocation(line: 1948, column: 174, scope: !2199)
!2210 = !DILocation(line: 1948, column: 184, scope: !2199)
!2211 = !DILocation(line: 1948, column: 190, scope: !2199)
!2212 = !DILocation(line: 1948, column: 6, scope: !2199)
!2213 = !DILocation(line: 1949, column: 6, scope: !2199)
!2214 = !DILocation(line: 1950, column: 2, scope: !2112)
!2215 = !DILocation(line: 1934, column: 42, scope: !2107)
!2216 = !DILocation(line: 1934, column: 5, scope: !2107)
!2217 = distinct !{!2217, !2110, !2218}
!2218 = !DILocation(line: 1950, column: 2, scope: !2104)
!2219 = !DILocation(line: 1955, column: 16, scope: !2220)
!2220 = distinct !DILexicalBlock(scope: !2088, file: !3, line: 1955, column: 5)
!2221 = !DILocation(line: 1955, column: 11, scope: !2220)
!2222 = !DILocation(line: 1955, column: 21, scope: !2223)
!2223 = distinct !DILexicalBlock(scope: !2220, file: !3, line: 1955, column: 5)
!2224 = !DILocation(line: 1955, column: 28, scope: !2223)
!2225 = !DILocation(line: 1955, column: 26, scope: !2223)
!2226 = !DILocation(line: 1955, column: 5, scope: !2220)
!2227 = !DILocation(line: 1957, column: 7, scope: !2228)
!2228 = distinct !DILexicalBlock(scope: !2223, file: !3, line: 1956, column: 2)
!2229 = !DILocation(line: 1957, column: 16, scope: !2228)
!2230 = !DILocation(line: 1957, column: 4, scope: !2228)
!2231 = !DILocation(line: 1958, column: 7, scope: !2232)
!2232 = distinct !DILexicalBlock(scope: !2228, file: !3, line: 1958, column: 7)
!2233 = !DILocation(line: 1958, column: 10, scope: !2232)
!2234 = !DILocation(line: 1958, column: 21, scope: !2232)
!2235 = !DILocation(line: 1958, column: 37, scope: !2232)
!2236 = !DILocation(line: 1958, column: 40, scope: !2232)
!2237 = !DILocation(line: 1958, column: 43, scope: !2232)
!2238 = !DILocation(line: 1958, column: 54, scope: !2232)
!2239 = !DILocation(line: 1958, column: 7, scope: !2228)
!2240 = !DILocation(line: 1960, column: 6, scope: !2241)
!2241 = distinct !DILexicalBlock(scope: !2232, file: !3, line: 1959, column: 6)
!2242 = !DILocation(line: 1960, column: 9, scope: !2241)
!2243 = !DILocation(line: 1960, column: 19, scope: !2241)
!2244 = !DILocation(line: 1961, column: 17, scope: !2245)
!2245 = distinct !DILexicalBlock(scope: !2241, file: !3, line: 1961, column: 6)
!2246 = !DILocation(line: 1961, column: 12, scope: !2245)
!2247 = !DILocation(line: 1961, column: 22, scope: !2248)
!2248 = distinct !DILexicalBlock(scope: !2245, file: !3, line: 1961, column: 6)
!2249 = !DILocation(line: 1961, column: 29, scope: !2248)
!2250 = !DILocation(line: 1961, column: 32, scope: !2248)
!2251 = !DILocation(line: 1961, column: 27, scope: !2248)
!2252 = !DILocation(line: 1961, column: 6, scope: !2245)
!2253 = !DILocation(line: 1963, column: 10, scope: !2254)
!2254 = distinct !DILexicalBlock(scope: !2248, file: !3, line: 1962, column: 3)
!2255 = !DILocation(line: 1963, column: 13, scope: !2254)
!2256 = !DILocation(line: 1963, column: 19, scope: !2254)
!2257 = !DILocation(line: 1963, column: 8, scope: !2254)
!2258 = !DILocation(line: 1964, column: 7, scope: !2254)
!2259 = !DILocation(line: 1964, column: 17, scope: !2254)
!2260 = !DILocation(line: 1964, column: 23, scope: !2254)
!2261 = !DILocation(line: 1964, column: 35, scope: !2254)
!2262 = !DILocation(line: 1964, column: 45, scope: !2254)
!2263 = !DILocation(line: 1964, column: 51, scope: !2254)
!2264 = !DILocation(line: 1964, column: 33, scope: !2254)
!2265 = !DILocation(line: 1964, column: 5, scope: !2254)
!2266 = !DILocation(line: 1965, column: 8, scope: !2267)
!2267 = distinct !DILexicalBlock(scope: !2254, file: !3, line: 1965, column: 8)
!2268 = !DILocation(line: 1965, column: 11, scope: !2267)
!2269 = !DILocation(line: 1965, column: 21, scope: !2267)
!2270 = !DILocation(line: 1965, column: 8, scope: !2254)
!2271 = !DILocation(line: 1966, column: 22, scope: !2267)
!2272 = !DILocation(line: 1966, column: 7, scope: !2267)
!2273 = !DILocation(line: 1966, column: 10, scope: !2267)
!2274 = !DILocation(line: 1966, column: 20, scope: !2267)
!2275 = !DILocation(line: 1968, column: 22, scope: !2267)
!2276 = !DILocation(line: 1968, column: 7, scope: !2267)
!2277 = !DILocation(line: 1968, column: 10, scope: !2267)
!2278 = !DILocation(line: 1968, column: 20, scope: !2267)
!2279 = !DILocation(line: 1969, column: 3, scope: !2254)
!2280 = !DILocation(line: 1961, column: 42, scope: !2248)
!2281 = !DILocation(line: 1961, column: 6, scope: !2248)
!2282 = distinct !{!2282, !2252, !2283}
!2283 = !DILocation(line: 1969, column: 3, scope: !2245)
!2284 = !DILocation(line: 1970, column: 6, scope: !2241)
!2285 = !DILocation(line: 1971, column: 2, scope: !2228)
!2286 = !DILocation(line: 1955, column: 42, scope: !2223)
!2287 = !DILocation(line: 1955, column: 5, scope: !2223)
!2288 = distinct !{!2288, !2226, !2289}
!2289 = !DILocation(line: 1971, column: 2, scope: !2220)
!2290 = !DILocation(line: 1972, column: 5, scope: !2088)
!2291 = distinct !DISubprogram(name: "show_stats", scope: !3, file: !3, line: 2131, type: !227, scopeLine: 2132, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2292 = !DILocalVariable(name: "client_data", arg: 1, scope: !2291, file: !3, line: 2131, type: !229)
!2293 = !DILocation(line: 2131, column: 24, scope: !2291)
!2294 = !DILocalVariable(name: "nowP", arg: 2, scope: !2291, file: !3, line: 2131, type: !211)
!2295 = !DILocation(line: 2131, column: 53, scope: !2291)
!2296 = !DILocation(line: 2133, column: 15, scope: !2291)
!2297 = !DILocation(line: 2133, column: 5, scope: !2291)
!2298 = !DILocation(line: 2134, column: 5, scope: !2291)
!2299 = distinct !DISubprogram(name: "re_open_logfile", scope: !3, file: !3, line: 331, type: !2300, scopeLine: 332, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2300 = !DISubroutineType(types: !2301)
!2301 = !{null}
!2302 = !DILocalVariable(name: "logfp", scope: !2299, file: !3, line: 333, type: !50)
!2303 = !DILocation(line: 333, column: 11, scope: !2299)
!2304 = !DILocation(line: 335, column: 10, scope: !2305)
!2305 = distinct !DILexicalBlock(scope: !2299, file: !3, line: 335, column: 10)
!2306 = !DILocation(line: 335, column: 17, scope: !2305)
!2307 = !DILocation(line: 335, column: 20, scope: !2305)
!2308 = !DILocation(line: 335, column: 23, scope: !2305)
!2309 = !DILocation(line: 335, column: 10, scope: !2299)
!2310 = !DILocation(line: 336, column: 2, scope: !2305)
!2311 = !DILocation(line: 339, column: 10, scope: !2312)
!2312 = distinct !DILexicalBlock(scope: !2299, file: !3, line: 339, column: 10)
!2313 = !DILocation(line: 339, column: 18, scope: !2312)
!2314 = !DILocation(line: 339, column: 31, scope: !2312)
!2315 = !DILocation(line: 339, column: 42, scope: !2312)
!2316 = !DILocation(line: 339, column: 34, scope: !2312)
!2317 = !DILocation(line: 339, column: 57, scope: !2312)
!2318 = !DILocation(line: 339, column: 10, scope: !2299)
!2319 = !DILocation(line: 341, column: 2, scope: !2320)
!2320 = distinct !DILexicalBlock(scope: !2312, file: !3, line: 340, column: 2)
!2321 = !DILocation(line: 342, column: 17, scope: !2320)
!2322 = !DILocation(line: 342, column: 10, scope: !2320)
!2323 = !DILocation(line: 342, column: 8, scope: !2320)
!2324 = !DILocation(line: 343, column: 7, scope: !2325)
!2325 = distinct !DILexicalBlock(scope: !2320, file: !3, line: 343, column: 7)
!2326 = !DILocation(line: 343, column: 13, scope: !2325)
!2327 = !DILocation(line: 343, column: 7, scope: !2320)
!2328 = !DILocation(line: 345, column: 49, scope: !2329)
!2329 = distinct !DILexicalBlock(scope: !2325, file: !3, line: 344, column: 6)
!2330 = !DILocation(line: 345, column: 6, scope: !2329)
!2331 = !DILocation(line: 346, column: 6, scope: !2329)
!2332 = !DILocation(line: 348, column: 24, scope: !2320)
!2333 = !DILocation(line: 348, column: 16, scope: !2320)
!2334 = !DILocation(line: 348, column: 9, scope: !2320)
!2335 = !DILocation(line: 349, column: 19, scope: !2320)
!2336 = !DILocation(line: 349, column: 23, scope: !2320)
!2337 = !DILocation(line: 349, column: 2, scope: !2320)
!2338 = !DILocation(line: 350, column: 2, scope: !2320)
!2339 = !DILocation(line: 351, column: 5, scope: !2299)
!2340 = distinct !DISubprogram(name: "handle_newconnect", scope: !3, file: !3, line: 1496, type: !2341, scopeLine: 1497, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2341 = !DISubroutineType(types: !2342)
!2342 = !{!26, !211, !26}
!2343 = !DILocalVariable(name: "tvP", arg: 1, scope: !2340, file: !3, line: 1496, type: !211)
!2344 = !DILocation(line: 1496, column: 36, scope: !2340)
!2345 = !DILocalVariable(name: "listen_fd", arg: 2, scope: !2340, file: !3, line: 1496, type: !26)
!2346 = !DILocation(line: 1496, column: 45, scope: !2340)
!2347 = !DILocalVariable(name: "c", scope: !2340, file: !3, line: 1498, type: !248)
!2348 = !DILocation(line: 1498, column: 17, scope: !2340)
!2349 = !DILocalVariable(name: "client_data", scope: !2340, file: !3, line: 1499, type: !229)
!2350 = !DILocation(line: 1499, column: 16, scope: !2340)
!2351 = !DILocation(line: 1505, column: 5, scope: !2340)
!2352 = !DILocation(line: 1508, column: 7, scope: !2353)
!2353 = distinct !DILexicalBlock(scope: !2354, file: !3, line: 1508, column: 7)
!2354 = distinct !DILexicalBlock(scope: !2355, file: !3, line: 1506, column: 2)
!2355 = distinct !DILexicalBlock(scope: !2356, file: !3, line: 1505, column: 5)
!2356 = distinct !DILexicalBlock(scope: !2340, file: !3, line: 1505, column: 5)
!2357 = !DILocation(line: 1508, column: 23, scope: !2353)
!2358 = !DILocation(line: 1508, column: 20, scope: !2353)
!2359 = !DILocation(line: 1508, column: 7, scope: !2354)
!2360 = !DILocation(line: 1514, column: 6, scope: !2361)
!2361 = distinct !DILexicalBlock(scope: !2353, file: !3, line: 1509, column: 6)
!2362 = !DILocation(line: 1515, column: 15, scope: !2361)
!2363 = !DILocation(line: 1515, column: 6, scope: !2361)
!2364 = !DILocation(line: 1516, column: 6, scope: !2361)
!2365 = !DILocation(line: 1519, column: 7, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !2354, file: !3, line: 1519, column: 7)
!2367 = !DILocation(line: 1519, column: 26, scope: !2366)
!2368 = !DILocation(line: 1519, column: 32, scope: !2366)
!2369 = !DILocation(line: 1519, column: 35, scope: !2366)
!2370 = !DILocation(line: 1519, column: 44, scope: !2366)
!2371 = !DILocation(line: 1519, column: 64, scope: !2366)
!2372 = !DILocation(line: 1519, column: 75, scope: !2366)
!2373 = !DILocation(line: 1519, column: 7, scope: !2354)
!2374 = !DILocation(line: 1521, column: 6, scope: !2375)
!2375 = distinct !DILexicalBlock(scope: !2366, file: !3, line: 1520, column: 6)
!2376 = !DILocation(line: 1522, column: 6, scope: !2375)
!2377 = !DILocation(line: 1524, column: 7, scope: !2354)
!2378 = !DILocation(line: 1524, column: 16, scope: !2354)
!2379 = !DILocation(line: 1524, column: 4, scope: !2354)
!2380 = !DILocation(line: 1526, column: 7, scope: !2381)
!2381 = distinct !DILexicalBlock(scope: !2354, file: !3, line: 1526, column: 7)
!2382 = !DILocation(line: 1526, column: 10, scope: !2381)
!2383 = !DILocation(line: 1526, column: 13, scope: !2381)
!2384 = !DILocation(line: 1526, column: 7, scope: !2354)
!2385 = !DILocation(line: 1528, column: 14, scope: !2386)
!2386 = distinct !DILexicalBlock(scope: !2381, file: !3, line: 1527, column: 6)
!2387 = !DILocation(line: 1528, column: 6, scope: !2386)
!2388 = !DILocation(line: 1528, column: 9, scope: !2386)
!2389 = !DILocation(line: 1528, column: 12, scope: !2386)
!2390 = !DILocation(line: 1529, column: 11, scope: !2391)
!2391 = distinct !DILexicalBlock(scope: !2386, file: !3, line: 1529, column: 11)
!2392 = !DILocation(line: 1529, column: 14, scope: !2391)
!2393 = !DILocation(line: 1529, column: 17, scope: !2391)
!2394 = !DILocation(line: 1529, column: 11, scope: !2386)
!2395 = !DILocation(line: 1531, column: 3, scope: !2396)
!2396 = distinct !DILexicalBlock(scope: !2391, file: !3, line: 1530, column: 3)
!2397 = !DILocation(line: 1532, column: 3, scope: !2396)
!2398 = !DILocation(line: 1534, column: 6, scope: !2386)
!2399 = !DILocation(line: 1534, column: 9, scope: !2386)
!2400 = !DILocation(line: 1534, column: 13, scope: !2386)
!2401 = !DILocation(line: 1534, column: 25, scope: !2386)
!2402 = !DILocation(line: 1535, column: 6, scope: !2386)
!2403 = !DILocation(line: 1536, column: 6, scope: !2386)
!2404 = !DILocation(line: 1539, column: 27, scope: !2354)
!2405 = !DILocation(line: 1539, column: 31, scope: !2354)
!2406 = !DILocation(line: 1539, column: 42, scope: !2354)
!2407 = !DILocation(line: 1539, column: 45, scope: !2354)
!2408 = !DILocation(line: 1539, column: 11, scope: !2354)
!2409 = !DILocation(line: 1539, column: 2, scope: !2354)
!2410 = !DILocation(line: 1545, column: 15, scope: !2411)
!2411 = distinct !DILexicalBlock(scope: !2354, file: !3, line: 1540, column: 6)
!2412 = !DILocation(line: 1545, column: 6, scope: !2411)
!2413 = !DILocation(line: 1546, column: 6, scope: !2411)
!2414 = !DILocation(line: 1550, column: 6, scope: !2411)
!2415 = !DILocation(line: 1552, column: 2, scope: !2354)
!2416 = !DILocation(line: 1552, column: 5, scope: !2354)
!2417 = !DILocation(line: 1552, column: 16, scope: !2354)
!2418 = !DILocation(line: 1554, column: 23, scope: !2354)
!2419 = !DILocation(line: 1554, column: 26, scope: !2354)
!2420 = !DILocation(line: 1554, column: 21, scope: !2354)
!2421 = !DILocation(line: 1555, column: 2, scope: !2354)
!2422 = !DILocation(line: 1555, column: 5, scope: !2354)
!2423 = !DILocation(line: 1555, column: 23, scope: !2354)
!2424 = !DILocation(line: 1556, column: 2, scope: !2354)
!2425 = !DILocation(line: 1557, column: 18, scope: !2354)
!2426 = !DILocation(line: 1557, column: 14, scope: !2354)
!2427 = !DILocation(line: 1557, column: 16, scope: !2354)
!2428 = !DILocation(line: 1558, column: 17, scope: !2354)
!2429 = !DILocation(line: 1558, column: 22, scope: !2354)
!2430 = !DILocation(line: 1558, column: 2, scope: !2354)
!2431 = !DILocation(line: 1558, column: 5, scope: !2354)
!2432 = !DILocation(line: 1558, column: 15, scope: !2354)
!2433 = !DILocation(line: 1559, column: 2, scope: !2354)
!2434 = !DILocation(line: 1559, column: 5, scope: !2354)
!2435 = !DILocation(line: 1559, column: 18, scope: !2354)
!2436 = !DILocation(line: 1560, column: 2, scope: !2354)
!2437 = !DILocation(line: 1560, column: 5, scope: !2354)
!2438 = !DILocation(line: 1560, column: 18, scope: !2354)
!2439 = !DILocation(line: 1561, column: 2, scope: !2354)
!2440 = !DILocation(line: 1561, column: 5, scope: !2354)
!2441 = !DILocation(line: 1561, column: 21, scope: !2354)
!2442 = !DILocation(line: 1562, column: 2, scope: !2354)
!2443 = !DILocation(line: 1562, column: 5, scope: !2354)
!2444 = !DILocation(line: 1562, column: 14, scope: !2354)
!2445 = !DILocation(line: 1565, column: 20, scope: !2354)
!2446 = !DILocation(line: 1565, column: 23, scope: !2354)
!2447 = !DILocation(line: 1565, column: 27, scope: !2354)
!2448 = !DILocation(line: 1565, column: 2, scope: !2354)
!2449 = !DILocation(line: 1567, column: 18, scope: !2354)
!2450 = !DILocation(line: 1567, column: 21, scope: !2354)
!2451 = !DILocation(line: 1567, column: 25, scope: !2354)
!2452 = !DILocation(line: 1567, column: 34, scope: !2354)
!2453 = !DILocation(line: 1567, column: 2, scope: !2354)
!2454 = !DILocation(line: 1569, column: 2, scope: !2354)
!2455 = !DILocation(line: 1570, column: 7, scope: !2456)
!2456 = distinct !DILexicalBlock(scope: !2354, file: !3, line: 1570, column: 7)
!2457 = !DILocation(line: 1570, column: 22, scope: !2456)
!2458 = !DILocation(line: 1570, column: 20, scope: !2456)
!2459 = !DILocation(line: 1570, column: 7, scope: !2354)
!2460 = !DILocation(line: 1571, column: 27, scope: !2456)
!2461 = !DILocation(line: 1571, column: 25, scope: !2456)
!2462 = !DILocation(line: 1571, column: 6, scope: !2456)
!2463 = !DILocation(line: 1505, column: 5, scope: !2355)
!2464 = distinct !{!2464, !2465, !2466}
!2465 = !DILocation(line: 1505, column: 5, scope: !2356)
!2466 = !DILocation(line: 1572, column: 2, scope: !2356)
!2467 = !DILocation(line: 1573, column: 5, scope: !2340)
!2468 = distinct !DISubprogram(name: "clear_connection", scope: !3, file: !3, line: 1987, type: !2469, scopeLine: 1988, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2469 = !DISubroutineType(types: !2470)
!2470 = !{null, !248, !211}
!2471 = !DILocalVariable(name: "c", arg: 1, scope: !2468, file: !3, line: 1987, type: !248)
!2472 = !DILocation(line: 1987, column: 31, scope: !2468)
!2473 = !DILocalVariable(name: "tvP", arg: 2, scope: !2468, file: !3, line: 1987, type: !211)
!2474 = !DILocation(line: 1987, column: 50, scope: !2468)
!2475 = !DILocalVariable(name: "client_data", scope: !2468, file: !3, line: 1989, type: !229)
!2476 = !DILocation(line: 1989, column: 16, scope: !2468)
!2477 = !DILocation(line: 1991, column: 10, scope: !2478)
!2478 = distinct !DILexicalBlock(scope: !2468, file: !3, line: 1991, column: 10)
!2479 = !DILocation(line: 1991, column: 13, scope: !2478)
!2480 = !DILocation(line: 1991, column: 26, scope: !2478)
!2481 = !DILocation(line: 1991, column: 10, scope: !2468)
!2482 = !DILocation(line: 1993, column: 14, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !2478, file: !3, line: 1992, column: 2)
!2484 = !DILocation(line: 1993, column: 17, scope: !2483)
!2485 = !DILocation(line: 1993, column: 2, scope: !2483)
!2486 = !DILocation(line: 1994, column: 2, scope: !2483)
!2487 = !DILocation(line: 1994, column: 5, scope: !2483)
!2488 = !DILocation(line: 1994, column: 18, scope: !2483)
!2489 = !DILocation(line: 1995, column: 2, scope: !2483)
!2490 = !DILocation(line: 2008, column: 10, scope: !2491)
!2491 = distinct !DILexicalBlock(scope: !2468, file: !3, line: 2008, column: 10)
!2492 = !DILocation(line: 2008, column: 13, scope: !2491)
!2493 = !DILocation(line: 2008, column: 24, scope: !2491)
!2494 = !DILocation(line: 2008, column: 10, scope: !2468)
!2495 = !DILocation(line: 2011, column: 14, scope: !2496)
!2496 = distinct !DILexicalBlock(scope: !2491, file: !3, line: 2009, column: 2)
!2497 = !DILocation(line: 2011, column: 17, scope: !2496)
!2498 = !DILocation(line: 2011, column: 2, scope: !2496)
!2499 = !DILocation(line: 2012, column: 2, scope: !2496)
!2500 = !DILocation(line: 2012, column: 5, scope: !2496)
!2501 = !DILocation(line: 2012, column: 18, scope: !2496)
!2502 = !DILocation(line: 2013, column: 2, scope: !2496)
!2503 = !DILocation(line: 2013, column: 5, scope: !2496)
!2504 = !DILocation(line: 2013, column: 9, scope: !2496)
!2505 = !DILocation(line: 2013, column: 23, scope: !2496)
!2506 = !DILocation(line: 2014, column: 2, scope: !2496)
!2507 = !DILocation(line: 2015, column: 10, scope: !2508)
!2508 = distinct !DILexicalBlock(scope: !2468, file: !3, line: 2015, column: 10)
!2509 = !DILocation(line: 2015, column: 13, scope: !2508)
!2510 = !DILocation(line: 2015, column: 17, scope: !2508)
!2511 = !DILocation(line: 2015, column: 10, scope: !2468)
!2512 = !DILocation(line: 2017, column: 7, scope: !2513)
!2513 = distinct !DILexicalBlock(scope: !2514, file: !3, line: 2017, column: 7)
!2514 = distinct !DILexicalBlock(scope: !2508, file: !3, line: 2016, column: 2)
!2515 = !DILocation(line: 2017, column: 10, scope: !2513)
!2516 = !DILocation(line: 2017, column: 21, scope: !2513)
!2517 = !DILocation(line: 2017, column: 7, scope: !2514)
!2518 = !DILocation(line: 2018, column: 22, scope: !2513)
!2519 = !DILocation(line: 2018, column: 25, scope: !2513)
!2520 = !DILocation(line: 2018, column: 29, scope: !2513)
!2521 = !DILocation(line: 2018, column: 6, scope: !2513)
!2522 = !DILocation(line: 2019, column: 2, scope: !2514)
!2523 = !DILocation(line: 2019, column: 5, scope: !2514)
!2524 = !DILocation(line: 2019, column: 16, scope: !2514)
!2525 = !DILocation(line: 2020, column: 12, scope: !2514)
!2526 = !DILocation(line: 2020, column: 15, scope: !2514)
!2527 = !DILocation(line: 2020, column: 19, scope: !2514)
!2528 = !DILocation(line: 2020, column: 2, scope: !2514)
!2529 = !DILocation(line: 2021, column: 18, scope: !2514)
!2530 = !DILocation(line: 2021, column: 21, scope: !2514)
!2531 = !DILocation(line: 2021, column: 25, scope: !2514)
!2532 = !DILocation(line: 2021, column: 34, scope: !2514)
!2533 = !DILocation(line: 2021, column: 2, scope: !2514)
!2534 = !DILocation(line: 2022, column: 18, scope: !2514)
!2535 = !DILocation(line: 2022, column: 14, scope: !2514)
!2536 = !DILocation(line: 2022, column: 16, scope: !2514)
!2537 = !DILocation(line: 2023, column: 7, scope: !2538)
!2538 = distinct !DILexicalBlock(scope: !2514, file: !3, line: 2023, column: 7)
!2539 = !DILocation(line: 2023, column: 10, scope: !2538)
!2540 = !DILocation(line: 2023, column: 23, scope: !2538)
!2541 = !DILocation(line: 2023, column: 7, scope: !2514)
!2542 = !DILocation(line: 2024, column: 6, scope: !2538)
!2543 = !DILocation(line: 2026, column: 6, scope: !2514)
!2544 = !DILocation(line: 2025, column: 20, scope: !2514)
!2545 = !DILocation(line: 2025, column: 2, scope: !2514)
!2546 = !DILocation(line: 2025, column: 5, scope: !2514)
!2547 = !DILocation(line: 2025, column: 18, scope: !2514)
!2548 = !DILocation(line: 2027, column: 7, scope: !2549)
!2549 = distinct !DILexicalBlock(scope: !2514, file: !3, line: 2027, column: 7)
!2550 = !DILocation(line: 2027, column: 10, scope: !2549)
!2551 = !DILocation(line: 2027, column: 23, scope: !2549)
!2552 = !DILocation(line: 2027, column: 7, scope: !2514)
!2553 = !DILocation(line: 2029, column: 6, scope: !2554)
!2554 = distinct !DILexicalBlock(scope: !2549, file: !3, line: 2028, column: 6)
!2555 = !DILocation(line: 2030, column: 6, scope: !2554)
!2556 = !DILocation(line: 2032, column: 2, scope: !2514)
!2557 = !DILocation(line: 2034, column: 27, scope: !2508)
!2558 = !DILocation(line: 2034, column: 30, scope: !2508)
!2559 = !DILocation(line: 2034, column: 2, scope: !2508)
!2560 = !DILocation(line: 2035, column: 5, scope: !2468)
!2561 = distinct !DISubprogram(name: "handle_read", scope: !3, file: !3, line: 1577, type: !2469, scopeLine: 1578, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2562 = !DILocalVariable(name: "c", arg: 1, scope: !2561, file: !3, line: 1577, type: !248)
!2563 = !DILocation(line: 1577, column: 26, scope: !2561)
!2564 = !DILocalVariable(name: "tvP", arg: 2, scope: !2561, file: !3, line: 1577, type: !211)
!2565 = !DILocation(line: 1577, column: 45, scope: !2561)
!2566 = !DILocalVariable(name: "sz", scope: !2561, file: !3, line: 1579, type: !26)
!2567 = !DILocation(line: 1579, column: 9, scope: !2561)
!2568 = !DILocalVariable(name: "client_data", scope: !2561, file: !3, line: 1580, type: !229)
!2569 = !DILocation(line: 1580, column: 16, scope: !2561)
!2570 = !DILocalVariable(name: "hc", scope: !2561, file: !3, line: 1581, type: !255)
!2571 = !DILocation(line: 1581, column: 17, scope: !2561)
!2572 = !DILocation(line: 1581, column: 22, scope: !2561)
!2573 = !DILocation(line: 1581, column: 25, scope: !2561)
!2574 = !DILocation(line: 1584, column: 10, scope: !2575)
!2575 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1584, column: 10)
!2576 = !DILocation(line: 1584, column: 14, scope: !2575)
!2577 = !DILocation(line: 1584, column: 26, scope: !2575)
!2578 = !DILocation(line: 1584, column: 30, scope: !2575)
!2579 = !DILocation(line: 1584, column: 23, scope: !2575)
!2580 = !DILocation(line: 1584, column: 10, scope: !2561)
!2581 = !DILocation(line: 1586, column: 7, scope: !2582)
!2582 = distinct !DILexicalBlock(scope: !2583, file: !3, line: 1586, column: 7)
!2583 = distinct !DILexicalBlock(scope: !2575, file: !3, line: 1585, column: 2)
!2584 = !DILocation(line: 1586, column: 11, scope: !2582)
!2585 = !DILocation(line: 1586, column: 21, scope: !2582)
!2586 = !DILocation(line: 1586, column: 7, scope: !2583)
!2587 = !DILocation(line: 1588, column: 22, scope: !2588)
!2588 = distinct !DILexicalBlock(scope: !2582, file: !3, line: 1587, column: 6)
!2589 = !DILocation(line: 1588, column: 31, scope: !2588)
!2590 = !DILocation(line: 1588, column: 54, scope: !2588)
!2591 = !DILocation(line: 1588, column: 6, scope: !2588)
!2592 = !DILocation(line: 1589, column: 25, scope: !2588)
!2593 = !DILocation(line: 1589, column: 28, scope: !2588)
!2594 = !DILocation(line: 1589, column: 6, scope: !2588)
!2595 = !DILocation(line: 1590, column: 6, scope: !2588)
!2596 = !DILocation(line: 1593, column: 7, scope: !2583)
!2597 = !DILocation(line: 1593, column: 11, scope: !2583)
!2598 = !DILocation(line: 1593, column: 22, scope: !2583)
!2599 = !DILocation(line: 1593, column: 26, scope: !2583)
!2600 = !DILocation(line: 1593, column: 37, scope: !2583)
!2601 = !DILocation(line: 1593, column: 41, scope: !2583)
!2602 = !DILocation(line: 1593, column: 51, scope: !2583)
!2603 = !DILocation(line: 1592, column: 2, scope: !2583)
!2604 = !DILocation(line: 1594, column: 2, scope: !2583)
!2605 = !DILocation(line: 1598, column: 2, scope: !2561)
!2606 = !DILocation(line: 1598, column: 6, scope: !2561)
!2607 = !DILocation(line: 1598, column: 17, scope: !2561)
!2608 = !DILocation(line: 1598, column: 21, scope: !2561)
!2609 = !DILocation(line: 1598, column: 30, scope: !2561)
!2610 = !DILocation(line: 1598, column: 34, scope: !2561)
!2611 = !DILocation(line: 1599, column: 2, scope: !2561)
!2612 = !DILocation(line: 1599, column: 6, scope: !2561)
!2613 = !DILocation(line: 1599, column: 18, scope: !2561)
!2614 = !DILocation(line: 1599, column: 22, scope: !2561)
!2615 = !DILocation(line: 1599, column: 16, scope: !2561)
!2616 = !DILocation(line: 1597, column: 10, scope: !2561)
!2617 = !DILocation(line: 1597, column: 8, scope: !2561)
!2618 = !DILocation(line: 1600, column: 10, scope: !2619)
!2619 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1600, column: 10)
!2620 = !DILocation(line: 1600, column: 13, scope: !2619)
!2621 = !DILocation(line: 1600, column: 10, scope: !2561)
!2622 = !DILocation(line: 1602, column: 18, scope: !2623)
!2623 = distinct !DILexicalBlock(scope: !2619, file: !3, line: 1601, column: 2)
!2624 = !DILocation(line: 1602, column: 27, scope: !2623)
!2625 = !DILocation(line: 1602, column: 50, scope: !2623)
!2626 = !DILocation(line: 1602, column: 2, scope: !2623)
!2627 = !DILocation(line: 1603, column: 21, scope: !2623)
!2628 = !DILocation(line: 1603, column: 24, scope: !2623)
!2629 = !DILocation(line: 1603, column: 2, scope: !2623)
!2630 = !DILocation(line: 1604, column: 2, scope: !2623)
!2631 = !DILocation(line: 1606, column: 10, scope: !2632)
!2632 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1606, column: 10)
!2633 = !DILocation(line: 1606, column: 13, scope: !2632)
!2634 = !DILocation(line: 1606, column: 10, scope: !2561)
!2635 = !DILocation(line: 1613, column: 7, scope: !2636)
!2636 = distinct !DILexicalBlock(scope: !2637, file: !3, line: 1613, column: 7)
!2637 = distinct !DILexicalBlock(scope: !2632, file: !3, line: 1607, column: 2)
!2638 = !DILocation(line: 1613, column: 13, scope: !2636)
!2639 = !DILocation(line: 1613, column: 22, scope: !2636)
!2640 = !DILocation(line: 1613, column: 25, scope: !2636)
!2641 = !DILocation(line: 1613, column: 31, scope: !2636)
!2642 = !DILocation(line: 1613, column: 41, scope: !2636)
!2643 = !DILocation(line: 1613, column: 44, scope: !2636)
!2644 = !DILocation(line: 1613, column: 50, scope: !2636)
!2645 = !DILocation(line: 1613, column: 7, scope: !2637)
!2646 = !DILocation(line: 1614, column: 6, scope: !2636)
!2647 = !DILocation(line: 1616, column: 6, scope: !2637)
!2648 = !DILocation(line: 1616, column: 15, scope: !2637)
!2649 = !DILocation(line: 1616, column: 38, scope: !2637)
!2650 = !DILocation(line: 1615, column: 2, scope: !2637)
!2651 = !DILocation(line: 1617, column: 21, scope: !2637)
!2652 = !DILocation(line: 1617, column: 24, scope: !2637)
!2653 = !DILocation(line: 1617, column: 2, scope: !2637)
!2654 = !DILocation(line: 1618, column: 2, scope: !2637)
!2655 = !DILocation(line: 1620, column: 21, scope: !2561)
!2656 = !DILocation(line: 1620, column: 5, scope: !2561)
!2657 = !DILocation(line: 1620, column: 9, scope: !2561)
!2658 = !DILocation(line: 1620, column: 18, scope: !2561)
!2659 = !DILocation(line: 1621, column: 20, scope: !2561)
!2660 = !DILocation(line: 1621, column: 25, scope: !2561)
!2661 = !DILocation(line: 1621, column: 5, scope: !2561)
!2662 = !DILocation(line: 1621, column: 8, scope: !2561)
!2663 = !DILocation(line: 1621, column: 18, scope: !2561)
!2664 = !DILocation(line: 1624, column: 33, scope: !2561)
!2665 = !DILocation(line: 1624, column: 14, scope: !2561)
!2666 = !DILocation(line: 1624, column: 5, scope: !2561)
!2667 = !DILocation(line: 1627, column: 2, scope: !2668)
!2668 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1625, column: 2)
!2669 = !DILocation(line: 1629, column: 18, scope: !2668)
!2670 = !DILocation(line: 1629, column: 27, scope: !2668)
!2671 = !DILocation(line: 1629, column: 50, scope: !2668)
!2672 = !DILocation(line: 1629, column: 2, scope: !2668)
!2673 = !DILocation(line: 1630, column: 21, scope: !2668)
!2674 = !DILocation(line: 1630, column: 24, scope: !2668)
!2675 = !DILocation(line: 1630, column: 2, scope: !2668)
!2676 = !DILocation(line: 1631, column: 2, scope: !2668)
!2677 = !DILocation(line: 1635, column: 31, scope: !2678)
!2678 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1635, column: 10)
!2679 = !DILocation(line: 1635, column: 10, scope: !2678)
!2680 = !DILocation(line: 1635, column: 36, scope: !2678)
!2681 = !DILocation(line: 1635, column: 10, scope: !2561)
!2682 = !DILocation(line: 1637, column: 21, scope: !2683)
!2683 = distinct !DILexicalBlock(scope: !2678, file: !3, line: 1636, column: 2)
!2684 = !DILocation(line: 1637, column: 24, scope: !2683)
!2685 = !DILocation(line: 1637, column: 2, scope: !2683)
!2686 = !DILocation(line: 1638, column: 2, scope: !2683)
!2687 = !DILocation(line: 1642, column: 29, scope: !2688)
!2688 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1642, column: 10)
!2689 = !DILocation(line: 1642, column: 12, scope: !2688)
!2690 = !DILocation(line: 1642, column: 10, scope: !2561)
!2691 = !DILocation(line: 1645, column: 6, scope: !2692)
!2692 = distinct !DILexicalBlock(scope: !2688, file: !3, line: 1643, column: 2)
!2693 = !DILocation(line: 1645, column: 15, scope: !2692)
!2694 = !DILocation(line: 1645, column: 38, scope: !2692)
!2695 = !DILocation(line: 1645, column: 56, scope: !2692)
!2696 = !DILocation(line: 1645, column: 60, scope: !2692)
!2697 = !DILocation(line: 1644, column: 2, scope: !2692)
!2698 = !DILocation(line: 1646, column: 21, scope: !2692)
!2699 = !DILocation(line: 1646, column: 24, scope: !2692)
!2700 = !DILocation(line: 1646, column: 2, scope: !2692)
!2701 = !DILocation(line: 1647, column: 2, scope: !2692)
!2702 = !DILocation(line: 1651, column: 31, scope: !2703)
!2703 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1651, column: 10)
!2704 = !DILocation(line: 1651, column: 35, scope: !2703)
!2705 = !DILocation(line: 1651, column: 10, scope: !2703)
!2706 = !DILocation(line: 1651, column: 41, scope: !2703)
!2707 = !DILocation(line: 1651, column: 10, scope: !2561)
!2708 = !DILocation(line: 1654, column: 21, scope: !2709)
!2709 = distinct !DILexicalBlock(scope: !2703, file: !3, line: 1652, column: 2)
!2710 = !DILocation(line: 1654, column: 24, scope: !2709)
!2711 = !DILocation(line: 1654, column: 2, scope: !2709)
!2712 = !DILocation(line: 1655, column: 2, scope: !2709)
!2713 = !DILocation(line: 1659, column: 10, scope: !2714)
!2714 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1659, column: 10)
!2715 = !DILocation(line: 1659, column: 14, scope: !2714)
!2716 = !DILocation(line: 1659, column: 10, scope: !2561)
!2717 = !DILocation(line: 1661, column: 23, scope: !2718)
!2718 = distinct !DILexicalBlock(scope: !2714, file: !3, line: 1660, column: 2)
!2719 = !DILocation(line: 1661, column: 27, scope: !2718)
!2720 = !DILocation(line: 1661, column: 2, scope: !2718)
!2721 = !DILocation(line: 1661, column: 5, scope: !2718)
!2722 = !DILocation(line: 1661, column: 21, scope: !2718)
!2723 = !DILocation(line: 1662, column: 22, scope: !2718)
!2724 = !DILocation(line: 1662, column: 26, scope: !2718)
!2725 = !DILocation(line: 1662, column: 42, scope: !2718)
!2726 = !DILocation(line: 1662, column: 2, scope: !2718)
!2727 = !DILocation(line: 1662, column: 5, scope: !2718)
!2728 = !DILocation(line: 1662, column: 20, scope: !2718)
!2729 = !DILocation(line: 1663, column: 2, scope: !2718)
!2730 = !DILocation(line: 1664, column: 15, scope: !2731)
!2731 = distinct !DILexicalBlock(scope: !2714, file: !3, line: 1664, column: 15)
!2732 = !DILocation(line: 1664, column: 19, scope: !2731)
!2733 = !DILocation(line: 1664, column: 33, scope: !2731)
!2734 = !DILocation(line: 1664, column: 15, scope: !2714)
!2735 = !DILocation(line: 1665, column: 2, scope: !2731)
!2736 = !DILocation(line: 1665, column: 5, scope: !2731)
!2737 = !DILocation(line: 1665, column: 20, scope: !2731)
!2738 = !DILocation(line: 1667, column: 22, scope: !2731)
!2739 = !DILocation(line: 1667, column: 26, scope: !2731)
!2740 = !DILocation(line: 1667, column: 2, scope: !2731)
!2741 = !DILocation(line: 1667, column: 5, scope: !2731)
!2742 = !DILocation(line: 1667, column: 20, scope: !2731)
!2743 = !DILocation(line: 1670, column: 10, scope: !2744)
!2744 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1670, column: 10)
!2745 = !DILocation(line: 1670, column: 14, scope: !2744)
!2746 = !DILocation(line: 1670, column: 27, scope: !2744)
!2747 = !DILocation(line: 1670, column: 10, scope: !2561)
!2748 = !DILocalVariable(name: "tind", scope: !2749, file: !3, line: 1673, type: !26)
!2749 = distinct !DILexicalBlock(scope: !2744, file: !3, line: 1671, column: 2)
!2750 = !DILocation(line: 1673, column: 6, scope: !2749)
!2751 = !DILocation(line: 1674, column: 13, scope: !2752)
!2752 = distinct !DILexicalBlock(scope: !2749, file: !3, line: 1674, column: 2)
!2753 = !DILocation(line: 1674, column: 8, scope: !2752)
!2754 = !DILocation(line: 1674, column: 18, scope: !2755)
!2755 = distinct !DILexicalBlock(scope: !2752, file: !3, line: 1674, column: 2)
!2756 = !DILocation(line: 1674, column: 25, scope: !2755)
!2757 = !DILocation(line: 1674, column: 28, scope: !2755)
!2758 = !DILocation(line: 1674, column: 23, scope: !2755)
!2759 = !DILocation(line: 1674, column: 2, scope: !2752)
!2760 = !DILocation(line: 1675, column: 51, scope: !2755)
!2761 = !DILocation(line: 1675, column: 55, scope: !2755)
!2762 = !DILocation(line: 1675, column: 6, scope: !2755)
!2763 = !DILocation(line: 1675, column: 16, scope: !2755)
!2764 = !DILocation(line: 1675, column: 19, scope: !2755)
!2765 = !DILocation(line: 1675, column: 25, scope: !2755)
!2766 = !DILocation(line: 1675, column: 32, scope: !2755)
!2767 = !DILocation(line: 1675, column: 48, scope: !2755)
!2768 = !DILocation(line: 1674, column: 38, scope: !2755)
!2769 = !DILocation(line: 1674, column: 2, scope: !2755)
!2770 = distinct !{!2770, !2759, !2771}
!2771 = !DILocation(line: 1675, column: 55, scope: !2752)
!2772 = !DILocation(line: 1676, column: 23, scope: !2749)
!2773 = !DILocation(line: 1676, column: 27, scope: !2749)
!2774 = !DILocation(line: 1676, column: 2, scope: !2749)
!2775 = !DILocation(line: 1676, column: 5, scope: !2749)
!2776 = !DILocation(line: 1676, column: 21, scope: !2749)
!2777 = !DILocation(line: 1677, column: 21, scope: !2749)
!2778 = !DILocation(line: 1677, column: 24, scope: !2749)
!2779 = !DILocation(line: 1677, column: 2, scope: !2749)
!2780 = !DILocation(line: 1678, column: 2, scope: !2749)
!2781 = !DILocation(line: 1680, column: 10, scope: !2782)
!2782 = distinct !DILexicalBlock(scope: !2561, file: !3, line: 1680, column: 10)
!2783 = !DILocation(line: 1680, column: 13, scope: !2782)
!2784 = !DILocation(line: 1680, column: 32, scope: !2782)
!2785 = !DILocation(line: 1680, column: 35, scope: !2782)
!2786 = !DILocation(line: 1680, column: 29, scope: !2782)
!2787 = !DILocation(line: 1680, column: 10, scope: !2561)
!2788 = !DILocation(line: 1683, column: 21, scope: !2789)
!2789 = distinct !DILexicalBlock(scope: !2782, file: !3, line: 1681, column: 2)
!2790 = !DILocation(line: 1683, column: 24, scope: !2789)
!2791 = !DILocation(line: 1683, column: 2, scope: !2789)
!2792 = !DILocation(line: 1684, column: 2, scope: !2789)
!2793 = !DILocation(line: 1688, column: 5, scope: !2561)
!2794 = !DILocation(line: 1688, column: 8, scope: !2561)
!2795 = !DILocation(line: 1688, column: 19, scope: !2561)
!2796 = !DILocation(line: 1689, column: 21, scope: !2561)
!2797 = !DILocation(line: 1689, column: 26, scope: !2561)
!2798 = !DILocation(line: 1689, column: 5, scope: !2561)
!2799 = !DILocation(line: 1689, column: 8, scope: !2561)
!2800 = !DILocation(line: 1689, column: 19, scope: !2561)
!2801 = !DILocation(line: 1690, column: 5, scope: !2561)
!2802 = !DILocation(line: 1690, column: 8, scope: !2561)
!2803 = !DILocation(line: 1690, column: 25, scope: !2561)
!2804 = !DILocation(line: 1691, column: 21, scope: !2561)
!2805 = !DILocation(line: 1691, column: 17, scope: !2561)
!2806 = !DILocation(line: 1691, column: 19, scope: !2561)
!2807 = !DILocation(line: 1693, column: 21, scope: !2561)
!2808 = !DILocation(line: 1693, column: 25, scope: !2561)
!2809 = !DILocation(line: 1693, column: 5, scope: !2561)
!2810 = !DILocation(line: 1694, column: 21, scope: !2561)
!2811 = !DILocation(line: 1694, column: 25, scope: !2561)
!2812 = !DILocation(line: 1694, column: 34, scope: !2561)
!2813 = !DILocation(line: 1694, column: 5, scope: !2561)
!2814 = !DILocation(line: 1695, column: 5, scope: !2561)
!2815 = distinct !DISubprogram(name: "handle_send", scope: !3, file: !3, line: 1699, type: !2469, scopeLine: 1700, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!2816 = !DILocalVariable(name: "c", arg: 1, scope: !2815, file: !3, line: 1699, type: !248)
!2817 = !DILocation(line: 1699, column: 26, scope: !2815)
!2818 = !DILocalVariable(name: "tvP", arg: 2, scope: !2815, file: !3, line: 1699, type: !211)
!2819 = !DILocation(line: 1699, column: 45, scope: !2815)
!2820 = !DILocalVariable(name: "max_bytes", scope: !2815, file: !3, line: 1701, type: !264)
!2821 = !DILocation(line: 1701, column: 12, scope: !2815)
!2822 = !DILocalVariable(name: "sz", scope: !2815, file: !3, line: 1702, type: !26)
!2823 = !DILocation(line: 1702, column: 9, scope: !2815)
!2824 = !DILocalVariable(name: "coast", scope: !2815, file: !3, line: 1702, type: !26)
!2825 = !DILocation(line: 1702, column: 13, scope: !2815)
!2826 = !DILocalVariable(name: "client_data", scope: !2815, file: !3, line: 1703, type: !229)
!2827 = !DILocation(line: 1703, column: 16, scope: !2815)
!2828 = !DILocalVariable(name: "elapsed", scope: !2815, file: !3, line: 1704, type: !244)
!2829 = !DILocation(line: 1704, column: 12, scope: !2815)
!2830 = !DILocalVariable(name: "hc", scope: !2815, file: !3, line: 1705, type: !255)
!2831 = !DILocation(line: 1705, column: 17, scope: !2815)
!2832 = !DILocation(line: 1705, column: 22, scope: !2815)
!2833 = !DILocation(line: 1705, column: 25, scope: !2815)
!2834 = !DILocalVariable(name: "tind", scope: !2815, file: !3, line: 1706, type: !26)
!2835 = !DILocation(line: 1706, column: 9, scope: !2815)
!2836 = !DILocation(line: 1708, column: 10, scope: !2837)
!2837 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1708, column: 10)
!2838 = !DILocation(line: 1708, column: 13, scope: !2837)
!2839 = !DILocation(line: 1708, column: 23, scope: !2837)
!2840 = !DILocation(line: 1708, column: 10, scope: !2815)
!2841 = !DILocation(line: 1709, column: 12, scope: !2837)
!2842 = !DILocation(line: 1709, column: 2, scope: !2837)
!2843 = !DILocation(line: 1711, column: 14, scope: !2837)
!2844 = !DILocation(line: 1711, column: 17, scope: !2837)
!2845 = !DILocation(line: 1711, column: 27, scope: !2837)
!2846 = !DILocation(line: 1711, column: 12, scope: !2837)
!2847 = !DILocation(line: 1714, column: 10, scope: !2848)
!2848 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1714, column: 10)
!2849 = !DILocation(line: 1714, column: 14, scope: !2848)
!2850 = !DILocation(line: 1714, column: 26, scope: !2848)
!2851 = !DILocation(line: 1714, column: 10, scope: !2815)
!2852 = !DILocation(line: 1718, column: 6, scope: !2853)
!2853 = distinct !DILexicalBlock(scope: !2848, file: !3, line: 1715, column: 2)
!2854 = !DILocation(line: 1718, column: 10, scope: !2853)
!2855 = !DILocation(line: 1718, column: 21, scope: !2853)
!2856 = !DILocation(line: 1718, column: 25, scope: !2853)
!2857 = !DILocation(line: 1718, column: 38, scope: !2853)
!2858 = !DILocation(line: 1718, column: 41, scope: !2853)
!2859 = !DILocation(line: 1719, column: 6, scope: !2853)
!2860 = !DILocation(line: 1717, column: 7, scope: !2853)
!2861 = !DILocation(line: 1717, column: 5, scope: !2853)
!2862 = !DILocation(line: 1720, column: 2, scope: !2853)
!2863 = !DILocalVariable(name: "iv", scope: !2864, file: !3, line: 1726, type: !2865)
!2864 = distinct !DILexicalBlock(scope: !2848, file: !3, line: 1722, column: 2)
!2865 = !DICompositeType(tag: DW_TAG_array_type, baseType: !2866, size: 256, elements: !367)
!2866 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "iovec", file: !2867, line: 31, size: 128, elements: !2868)
!2867 = !DIFile(filename: "/usr/include/sys/_types/_iovec_t.h", directory: "")
!2868 = !{!2869, !2870}
!2869 = !DIDerivedType(tag: DW_TAG_member, name: "iov_base", scope: !2866, file: !2867, line: 32, baseType: !70, size: 64)
!2870 = !DIDerivedType(tag: DW_TAG_member, name: "iov_len", scope: !2866, file: !2867, line: 33, baseType: !264, size: 64, offset: 64)
!2871 = !DILocation(line: 1726, column: 15, scope: !2864)
!2872 = !DILocation(line: 1728, column: 19, scope: !2864)
!2873 = !DILocation(line: 1728, column: 23, scope: !2864)
!2874 = !DILocation(line: 1728, column: 2, scope: !2864)
!2875 = !DILocation(line: 1728, column: 8, scope: !2864)
!2876 = !DILocation(line: 1728, column: 17, scope: !2864)
!2877 = !DILocation(line: 1729, column: 18, scope: !2864)
!2878 = !DILocation(line: 1729, column: 22, scope: !2864)
!2879 = !DILocation(line: 1729, column: 2, scope: !2864)
!2880 = !DILocation(line: 1729, column: 8, scope: !2864)
!2881 = !DILocation(line: 1729, column: 16, scope: !2864)
!2882 = !DILocation(line: 1730, column: 21, scope: !2864)
!2883 = !DILocation(line: 1730, column: 25, scope: !2864)
!2884 = !DILocation(line: 1730, column: 38, scope: !2864)
!2885 = !DILocation(line: 1730, column: 41, scope: !2864)
!2886 = !DILocation(line: 1730, column: 2, scope: !2864)
!2887 = !DILocation(line: 1730, column: 8, scope: !2864)
!2888 = !DILocation(line: 1730, column: 17, scope: !2864)
!2889 = !DILocation(line: 1731, column: 18, scope: !2864)
!2890 = !DILocation(line: 1731, column: 2, scope: !2864)
!2891 = !DILocation(line: 1731, column: 8, scope: !2864)
!2892 = !DILocation(line: 1731, column: 16, scope: !2864)
!2893 = !DILocation(line: 1732, column: 15, scope: !2864)
!2894 = !DILocation(line: 1732, column: 19, scope: !2864)
!2895 = !DILocation(line: 1732, column: 28, scope: !2864)
!2896 = !DILocation(line: 1732, column: 7, scope: !2864)
!2897 = !DILocation(line: 1732, column: 5, scope: !2864)
!2898 = !DILocation(line: 1735, column: 10, scope: !2899)
!2899 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1735, column: 10)
!2900 = !DILocation(line: 1735, column: 13, scope: !2899)
!2901 = !DILocation(line: 1735, column: 17, scope: !2899)
!2902 = !DILocation(line: 1735, column: 20, scope: !2899)
!2903 = !DILocation(line: 1735, column: 26, scope: !2899)
!2904 = !DILocation(line: 1735, column: 10, scope: !2815)
!2905 = !DILocation(line: 1736, column: 2, scope: !2899)
!2906 = !DILocation(line: 1738, column: 10, scope: !2907)
!2907 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1738, column: 10)
!2908 = !DILocation(line: 1738, column: 13, scope: !2907)
!2909 = !DILocation(line: 1738, column: 18, scope: !2907)
!2910 = !DILocation(line: 1739, column: 5, scope: !2907)
!2911 = !DILocation(line: 1739, column: 8, scope: !2907)
!2912 = !DILocation(line: 1739, column: 12, scope: !2907)
!2913 = !DILocation(line: 1739, column: 17, scope: !2907)
!2914 = !DILocation(line: 1739, column: 23, scope: !2907)
!2915 = !DILocation(line: 1739, column: 38, scope: !2907)
!2916 = !DILocation(line: 1739, column: 41, scope: !2907)
!2917 = !DILocation(line: 1739, column: 47, scope: !2907)
!2918 = !DILocation(line: 1738, column: 10, scope: !2815)
!2919 = !DILocation(line: 1751, column: 2, scope: !2920)
!2920 = distinct !DILexicalBlock(scope: !2907, file: !3, line: 1740, column: 2)
!2921 = !DILocation(line: 1751, column: 5, scope: !2920)
!2922 = !DILocation(line: 1751, column: 22, scope: !2920)
!2923 = !DILocation(line: 1752, column: 2, scope: !2920)
!2924 = !DILocation(line: 1752, column: 5, scope: !2920)
!2925 = !DILocation(line: 1752, column: 16, scope: !2920)
!2926 = !DILocation(line: 1753, column: 18, scope: !2920)
!2927 = !DILocation(line: 1753, column: 22, scope: !2920)
!2928 = !DILocation(line: 1753, column: 2, scope: !2920)
!2929 = !DILocation(line: 1754, column: 18, scope: !2920)
!2930 = !DILocation(line: 1754, column: 14, scope: !2920)
!2931 = !DILocation(line: 1754, column: 16, scope: !2920)
!2932 = !DILocation(line: 1755, column: 7, scope: !2933)
!2933 = distinct !DILexicalBlock(scope: !2920, file: !3, line: 1755, column: 7)
!2934 = !DILocation(line: 1755, column: 10, scope: !2933)
!2935 = !DILocation(line: 1755, column: 23, scope: !2933)
!2936 = !DILocation(line: 1755, column: 7, scope: !2920)
!2937 = !DILocation(line: 1756, column: 6, scope: !2933)
!2938 = !DILocation(line: 1758, column: 6, scope: !2920)
!2939 = !DILocation(line: 1758, column: 43, scope: !2920)
!2940 = !DILocation(line: 1758, column: 46, scope: !2920)
!2941 = !DILocation(line: 1757, column: 20, scope: !2920)
!2942 = !DILocation(line: 1757, column: 2, scope: !2920)
!2943 = !DILocation(line: 1757, column: 5, scope: !2920)
!2944 = !DILocation(line: 1757, column: 18, scope: !2920)
!2945 = !DILocation(line: 1759, column: 7, scope: !2946)
!2946 = distinct !DILexicalBlock(scope: !2920, file: !3, line: 1759, column: 7)
!2947 = !DILocation(line: 1759, column: 10, scope: !2946)
!2948 = !DILocation(line: 1759, column: 23, scope: !2946)
!2949 = !DILocation(line: 1759, column: 7, scope: !2920)
!2950 = !DILocation(line: 1761, column: 6, scope: !2951)
!2951 = distinct !DILexicalBlock(scope: !2946, file: !3, line: 1760, column: 6)
!2952 = !DILocation(line: 1762, column: 6, scope: !2951)
!2953 = !DILocation(line: 1764, column: 2, scope: !2920)
!2954 = !DILocation(line: 1767, column: 10, scope: !2955)
!2955 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1767, column: 10)
!2956 = !DILocation(line: 1767, column: 13, scope: !2955)
!2957 = !DILocation(line: 1767, column: 10, scope: !2815)
!2958 = !DILocation(line: 1780, column: 7, scope: !2959)
!2959 = distinct !DILexicalBlock(scope: !2960, file: !3, line: 1780, column: 7)
!2960 = distinct !DILexicalBlock(scope: !2955, file: !3, line: 1768, column: 2)
!2961 = !DILocation(line: 1780, column: 13, scope: !2959)
!2962 = !DILocation(line: 1780, column: 22, scope: !2959)
!2963 = !DILocation(line: 1780, column: 25, scope: !2959)
!2964 = !DILocation(line: 1780, column: 31, scope: !2959)
!2965 = !DILocation(line: 1780, column: 41, scope: !2959)
!2966 = !DILocation(line: 1780, column: 44, scope: !2959)
!2967 = !DILocation(line: 1780, column: 50, scope: !2959)
!2968 = !DILocation(line: 1780, column: 7, scope: !2960)
!2969 = !DILocation(line: 1781, column: 51, scope: !2959)
!2970 = !DILocation(line: 1781, column: 55, scope: !2959)
!2971 = !DILocation(line: 1781, column: 6, scope: !2959)
!2972 = !DILocation(line: 1782, column: 20, scope: !2960)
!2973 = !DILocation(line: 1782, column: 23, scope: !2960)
!2974 = !DILocation(line: 1782, column: 2, scope: !2960)
!2975 = !DILocation(line: 1783, column: 2, scope: !2960)
!2976 = !DILocation(line: 1787, column: 20, scope: !2815)
!2977 = !DILocation(line: 1787, column: 25, scope: !2815)
!2978 = !DILocation(line: 1787, column: 5, scope: !2815)
!2979 = !DILocation(line: 1787, column: 8, scope: !2815)
!2980 = !DILocation(line: 1787, column: 18, scope: !2815)
!2981 = !DILocation(line: 1789, column: 10, scope: !2982)
!2982 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1789, column: 10)
!2983 = !DILocation(line: 1789, column: 14, scope: !2982)
!2984 = !DILocation(line: 1789, column: 26, scope: !2982)
!2985 = !DILocation(line: 1789, column: 10, scope: !2815)
!2986 = !DILocation(line: 1792, column: 7, scope: !2987)
!2987 = distinct !DILexicalBlock(scope: !2988, file: !3, line: 1792, column: 7)
!2988 = distinct !DILexicalBlock(scope: !2982, file: !3, line: 1790, column: 2)
!2989 = !DILocation(line: 1792, column: 12, scope: !2987)
!2990 = !DILocation(line: 1792, column: 16, scope: !2987)
!2991 = !DILocation(line: 1792, column: 10, scope: !2987)
!2992 = !DILocation(line: 1792, column: 7, scope: !2988)
!2993 = !DILocalVariable(name: "newlen", scope: !2994, file: !3, line: 1795, type: !26)
!2994 = distinct !DILexicalBlock(scope: !2987, file: !3, line: 1793, column: 6)
!2995 = !DILocation(line: 1795, column: 10, scope: !2994)
!2996 = !DILocation(line: 1795, column: 19, scope: !2994)
!2997 = !DILocation(line: 1795, column: 23, scope: !2994)
!2998 = !DILocation(line: 1795, column: 37, scope: !2994)
!2999 = !DILocation(line: 1795, column: 35, scope: !2994)
!3000 = !DILocation(line: 1796, column: 13, scope: !2994)
!3001 = !DILocation(line: 1797, column: 24, scope: !2994)
!3002 = !DILocation(line: 1797, column: 6, scope: !2994)
!3003 = !DILocation(line: 1797, column: 10, scope: !2994)
!3004 = !DILocation(line: 1797, column: 22, scope: !2994)
!3005 = !DILocation(line: 1798, column: 9, scope: !2994)
!3006 = !DILocation(line: 1799, column: 6, scope: !2994)
!3007 = !DILocation(line: 1803, column: 12, scope: !3008)
!3008 = distinct !DILexicalBlock(scope: !2987, file: !3, line: 1801, column: 6)
!3009 = !DILocation(line: 1803, column: 16, scope: !3008)
!3010 = !DILocation(line: 1803, column: 9, scope: !3008)
!3011 = !DILocation(line: 1804, column: 6, scope: !3008)
!3012 = !DILocation(line: 1804, column: 10, scope: !3008)
!3013 = !DILocation(line: 1804, column: 22, scope: !3008)
!3014 = !DILocation(line: 1806, column: 2, scope: !2988)
!3015 = !DILocation(line: 1808, column: 27, scope: !2815)
!3016 = !DILocation(line: 1808, column: 5, scope: !2815)
!3017 = !DILocation(line: 1808, column: 8, scope: !2815)
!3018 = !DILocation(line: 1808, column: 24, scope: !2815)
!3019 = !DILocation(line: 1809, column: 26, scope: !2815)
!3020 = !DILocation(line: 1809, column: 5, scope: !2815)
!3021 = !DILocation(line: 1809, column: 8, scope: !2815)
!3022 = !DILocation(line: 1809, column: 12, scope: !2815)
!3023 = !DILocation(line: 1809, column: 23, scope: !2815)
!3024 = !DILocation(line: 1810, column: 16, scope: !3025)
!3025 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1810, column: 5)
!3026 = !DILocation(line: 1810, column: 11, scope: !3025)
!3027 = !DILocation(line: 1810, column: 21, scope: !3028)
!3028 = distinct !DILexicalBlock(scope: !3025, file: !3, line: 1810, column: 5)
!3029 = !DILocation(line: 1810, column: 28, scope: !3028)
!3030 = !DILocation(line: 1810, column: 31, scope: !3028)
!3031 = !DILocation(line: 1810, column: 26, scope: !3028)
!3032 = !DILocation(line: 1810, column: 5, scope: !3025)
!3033 = !DILocation(line: 1811, column: 47, scope: !3028)
!3034 = !DILocation(line: 1811, column: 2, scope: !3028)
!3035 = !DILocation(line: 1811, column: 12, scope: !3028)
!3036 = !DILocation(line: 1811, column: 15, scope: !3028)
!3037 = !DILocation(line: 1811, column: 21, scope: !3028)
!3038 = !DILocation(line: 1811, column: 28, scope: !3028)
!3039 = !DILocation(line: 1811, column: 44, scope: !3028)
!3040 = !DILocation(line: 1810, column: 41, scope: !3028)
!3041 = !DILocation(line: 1810, column: 5, scope: !3028)
!3042 = distinct !{!3042, !3032, !3043}
!3043 = !DILocation(line: 1811, column: 47, scope: !3025)
!3044 = !DILocation(line: 1814, column: 10, scope: !3045)
!3045 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1814, column: 10)
!3046 = !DILocation(line: 1814, column: 13, scope: !3045)
!3047 = !DILocation(line: 1814, column: 32, scope: !3045)
!3048 = !DILocation(line: 1814, column: 35, scope: !3045)
!3049 = !DILocation(line: 1814, column: 29, scope: !3045)
!3050 = !DILocation(line: 1814, column: 10, scope: !2815)
!3051 = !DILocation(line: 1817, column: 21, scope: !3052)
!3052 = distinct !DILexicalBlock(scope: !3045, file: !3, line: 1815, column: 2)
!3053 = !DILocation(line: 1817, column: 24, scope: !3052)
!3054 = !DILocation(line: 1817, column: 2, scope: !3052)
!3055 = !DILocation(line: 1818, column: 2, scope: !3052)
!3056 = !DILocation(line: 1822, column: 10, scope: !3057)
!3057 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1822, column: 10)
!3058 = !DILocation(line: 1822, column: 13, scope: !3057)
!3059 = !DILocation(line: 1822, column: 30, scope: !3057)
!3060 = !DILocation(line: 1822, column: 10, scope: !2815)
!3061 = !DILocation(line: 1823, column: 2, scope: !3057)
!3062 = !DILocation(line: 1823, column: 5, scope: !3057)
!3063 = !DILocation(line: 1823, column: 22, scope: !3057)
!3064 = !DILocation(line: 1826, column: 10, scope: !3065)
!3065 = distinct !DILexicalBlock(scope: !2815, file: !3, line: 1826, column: 10)
!3066 = !DILocation(line: 1826, column: 13, scope: !3065)
!3067 = !DILocation(line: 1826, column: 23, scope: !3065)
!3068 = !DILocation(line: 1826, column: 10, scope: !2815)
!3069 = !DILocation(line: 1828, column: 12, scope: !3070)
!3070 = distinct !DILexicalBlock(scope: !3065, file: !3, line: 1827, column: 2)
!3071 = !DILocation(line: 1828, column: 17, scope: !3070)
!3072 = !DILocation(line: 1828, column: 26, scope: !3070)
!3073 = !DILocation(line: 1828, column: 29, scope: !3070)
!3074 = !DILocation(line: 1828, column: 24, scope: !3070)
!3075 = !DILocation(line: 1828, column: 10, scope: !3070)
!3076 = !DILocation(line: 1829, column: 7, scope: !3077)
!3077 = distinct !DILexicalBlock(scope: !3070, file: !3, line: 1829, column: 7)
!3078 = !DILocation(line: 1829, column: 15, scope: !3077)
!3079 = !DILocation(line: 1829, column: 7, scope: !3070)
!3080 = !DILocation(line: 1830, column: 14, scope: !3077)
!3081 = !DILocation(line: 1830, column: 6, scope: !3077)
!3082 = !DILocation(line: 1831, column: 7, scope: !3083)
!3083 = distinct !DILexicalBlock(scope: !3070, file: !3, line: 1831, column: 7)
!3084 = !DILocation(line: 1831, column: 10, scope: !3083)
!3085 = !DILocation(line: 1831, column: 14, scope: !3083)
!3086 = !DILocation(line: 1831, column: 27, scope: !3083)
!3087 = !DILocation(line: 1831, column: 25, scope: !3083)
!3088 = !DILocation(line: 1831, column: 37, scope: !3083)
!3089 = !DILocation(line: 1831, column: 40, scope: !3083)
!3090 = !DILocation(line: 1831, column: 35, scope: !3083)
!3091 = !DILocation(line: 1831, column: 7, scope: !3070)
!3092 = !DILocation(line: 1833, column: 6, scope: !3093)
!3093 = distinct !DILexicalBlock(scope: !3083, file: !3, line: 1832, column: 6)
!3094 = !DILocation(line: 1833, column: 9, scope: !3093)
!3095 = !DILocation(line: 1833, column: 20, scope: !3093)
!3096 = !DILocation(line: 1834, column: 22, scope: !3093)
!3097 = !DILocation(line: 1834, column: 26, scope: !3093)
!3098 = !DILocation(line: 1834, column: 6, scope: !3093)
!3099 = !DILocation(line: 1838, column: 14, scope: !3093)
!3100 = !DILocation(line: 1838, column: 17, scope: !3093)
!3101 = !DILocation(line: 1838, column: 21, scope: !3093)
!3102 = !DILocation(line: 1838, column: 34, scope: !3093)
!3103 = !DILocation(line: 1838, column: 37, scope: !3093)
!3104 = !DILocation(line: 1838, column: 32, scope: !3093)
!3105 = !DILocation(line: 1838, column: 49, scope: !3093)
!3106 = !DILocation(line: 1838, column: 47, scope: !3093)
!3107 = !DILocation(line: 1838, column: 12, scope: !3093)
!3108 = !DILocation(line: 1839, column: 22, scope: !3093)
!3109 = !DILocation(line: 1839, column: 18, scope: !3093)
!3110 = !DILocation(line: 1839, column: 20, scope: !3093)
!3111 = !DILocation(line: 1840, column: 11, scope: !3112)
!3112 = distinct !DILexicalBlock(scope: !3093, file: !3, line: 1840, column: 11)
!3113 = !DILocation(line: 1840, column: 14, scope: !3112)
!3114 = !DILocation(line: 1840, column: 27, scope: !3112)
!3115 = !DILocation(line: 1840, column: 11, scope: !3093)
!3116 = !DILocation(line: 1841, column: 3, scope: !3112)
!3117 = !DILocation(line: 1843, column: 3, scope: !3093)
!3118 = !DILocation(line: 1844, column: 3, scope: !3093)
!3119 = !DILocation(line: 1844, column: 9, scope: !3093)
!3120 = !DILocation(line: 1844, column: 17, scope: !3093)
!3121 = !DILocation(line: 1844, column: 23, scope: !3093)
!3122 = !DILocation(line: 1842, column: 24, scope: !3093)
!3123 = !DILocation(line: 1842, column: 6, scope: !3093)
!3124 = !DILocation(line: 1842, column: 9, scope: !3093)
!3125 = !DILocation(line: 1842, column: 22, scope: !3093)
!3126 = !DILocation(line: 1845, column: 11, scope: !3127)
!3127 = distinct !DILexicalBlock(scope: !3093, file: !3, line: 1845, column: 11)
!3128 = !DILocation(line: 1845, column: 14, scope: !3127)
!3129 = !DILocation(line: 1845, column: 27, scope: !3127)
!3130 = !DILocation(line: 1845, column: 11, scope: !3093)
!3131 = !DILocation(line: 1847, column: 3, scope: !3132)
!3132 = distinct !DILexicalBlock(scope: !3127, file: !3, line: 1846, column: 3)
!3133 = !DILocation(line: 1848, column: 3, scope: !3132)
!3134 = !DILocation(line: 1850, column: 6, scope: !3093)
!3135 = !DILocation(line: 1851, column: 2, scope: !3070)
!3136 = !DILocation(line: 1853, column: 5, scope: !2815)
!3137 = distinct !DISubprogram(name: "handle_linger", scope: !3, file: !3, line: 1857, type: !2469, scopeLine: 1858, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3138 = !DILocalVariable(name: "c", arg: 1, scope: !3137, file: !3, line: 1857, type: !248)
!3139 = !DILocation(line: 1857, column: 28, scope: !3137)
!3140 = !DILocalVariable(name: "tvP", arg: 2, scope: !3137, file: !3, line: 1857, type: !211)
!3141 = !DILocation(line: 1857, column: 47, scope: !3137)
!3142 = !DILocalVariable(name: "buf", scope: !3137, file: !3, line: 1859, type: !3143)
!3143 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 32768, elements: !3144)
!3144 = !{!3145}
!3145 = !DISubrange(count: 4096)
!3146 = !DILocation(line: 1859, column: 10, scope: !3137)
!3147 = !DILocalVariable(name: "r", scope: !3137, file: !3, line: 1860, type: !26)
!3148 = !DILocation(line: 1860, column: 9, scope: !3137)
!3149 = !DILocation(line: 1865, column: 15, scope: !3137)
!3150 = !DILocation(line: 1865, column: 18, scope: !3137)
!3151 = !DILocation(line: 1865, column: 22, scope: !3137)
!3152 = !DILocation(line: 1865, column: 31, scope: !3137)
!3153 = !DILocation(line: 1865, column: 9, scope: !3137)
!3154 = !DILocation(line: 1865, column: 7, scope: !3137)
!3155 = !DILocation(line: 1866, column: 10, scope: !3156)
!3156 = distinct !DILexicalBlock(scope: !3137, file: !3, line: 1866, column: 10)
!3157 = !DILocation(line: 1866, column: 12, scope: !3156)
!3158 = !DILocation(line: 1866, column: 16, scope: !3156)
!3159 = !DILocation(line: 1866, column: 21, scope: !3156)
!3160 = !DILocation(line: 1866, column: 27, scope: !3156)
!3161 = !DILocation(line: 1866, column: 36, scope: !3156)
!3162 = !DILocation(line: 1866, column: 39, scope: !3156)
!3163 = !DILocation(line: 1866, column: 45, scope: !3156)
!3164 = !DILocation(line: 1866, column: 10, scope: !3137)
!3165 = !DILocation(line: 1867, column: 2, scope: !3156)
!3166 = !DILocation(line: 1868, column: 10, scope: !3167)
!3167 = distinct !DILexicalBlock(scope: !3137, file: !3, line: 1868, column: 10)
!3168 = !DILocation(line: 1868, column: 12, scope: !3167)
!3169 = !DILocation(line: 1868, column: 10, scope: !3137)
!3170 = !DILocation(line: 1869, column: 27, scope: !3167)
!3171 = !DILocation(line: 1869, column: 30, scope: !3167)
!3172 = !DILocation(line: 1869, column: 2, scope: !3167)
!3173 = !DILocation(line: 1870, column: 5, scope: !3137)
!3174 = distinct !DISubprogram(name: "shut_down", scope: !3, file: !3, line: 1458, type: !2300, scopeLine: 1459, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3175 = !DILocalVariable(name: "cnum", scope: !3174, file: !3, line: 1460, type: !26)
!3176 = !DILocation(line: 1460, column: 9, scope: !3174)
!3177 = !DILocalVariable(name: "tv", scope: !3174, file: !3, line: 1461, type: !212)
!3178 = !DILocation(line: 1461, column: 20, scope: !3174)
!3179 = !DILocation(line: 1463, column: 12, scope: !3174)
!3180 = !DILocation(line: 1464, column: 5, scope: !3174)
!3181 = !DILocation(line: 1465, column: 16, scope: !3182)
!3182 = distinct !DILexicalBlock(scope: !3174, file: !3, line: 1465, column: 5)
!3183 = !DILocation(line: 1465, column: 11, scope: !3182)
!3184 = !DILocation(line: 1465, column: 21, scope: !3185)
!3185 = distinct !DILexicalBlock(scope: !3182, file: !3, line: 1465, column: 5)
!3186 = !DILocation(line: 1465, column: 28, scope: !3185)
!3187 = !DILocation(line: 1465, column: 26, scope: !3185)
!3188 = !DILocation(line: 1465, column: 5, scope: !3182)
!3189 = !DILocation(line: 1467, column: 7, scope: !3190)
!3190 = distinct !DILexicalBlock(scope: !3191, file: !3, line: 1467, column: 7)
!3191 = distinct !DILexicalBlock(scope: !3185, file: !3, line: 1466, column: 2)
!3192 = !DILocation(line: 1467, column: 16, scope: !3190)
!3193 = !DILocation(line: 1467, column: 22, scope: !3190)
!3194 = !DILocation(line: 1467, column: 33, scope: !3190)
!3195 = !DILocation(line: 1467, column: 7, scope: !3191)
!3196 = !DILocation(line: 1468, column: 24, scope: !3190)
!3197 = !DILocation(line: 1468, column: 33, scope: !3190)
!3198 = !DILocation(line: 1468, column: 39, scope: !3190)
!3199 = !DILocation(line: 1468, column: 6, scope: !3190)
!3200 = !DILocation(line: 1469, column: 7, scope: !3201)
!3201 = distinct !DILexicalBlock(scope: !3191, file: !3, line: 1469, column: 7)
!3202 = !DILocation(line: 1469, column: 16, scope: !3201)
!3203 = !DILocation(line: 1469, column: 22, scope: !3201)
!3204 = !DILocation(line: 1469, column: 25, scope: !3201)
!3205 = !DILocation(line: 1469, column: 7, scope: !3191)
!3206 = !DILocation(line: 1471, column: 26, scope: !3207)
!3207 = distinct !DILexicalBlock(scope: !3201, file: !3, line: 1470, column: 6)
!3208 = !DILocation(line: 1471, column: 35, scope: !3207)
!3209 = !DILocation(line: 1471, column: 41, scope: !3207)
!3210 = !DILocation(line: 1471, column: 6, scope: !3207)
!3211 = !DILocation(line: 1472, column: 20, scope: !3207)
!3212 = !DILocation(line: 1472, column: 29, scope: !3207)
!3213 = !DILocation(line: 1472, column: 35, scope: !3207)
!3214 = !DILocation(line: 1472, column: 12, scope: !3207)
!3215 = !DILocation(line: 1472, column: 6, scope: !3207)
!3216 = !DILocation(line: 1473, column: 6, scope: !3207)
!3217 = !DILocation(line: 1474, column: 6, scope: !3207)
!3218 = !DILocation(line: 1474, column: 15, scope: !3207)
!3219 = !DILocation(line: 1474, column: 21, scope: !3207)
!3220 = !DILocation(line: 1474, column: 24, scope: !3207)
!3221 = !DILocation(line: 1475, column: 6, scope: !3207)
!3222 = !DILocation(line: 1476, column: 2, scope: !3191)
!3223 = !DILocation(line: 1465, column: 42, scope: !3185)
!3224 = !DILocation(line: 1465, column: 5, scope: !3185)
!3225 = distinct !{!3225, !3188, !3226}
!3226 = !DILocation(line: 1476, column: 2, scope: !3182)
!3227 = !DILocation(line: 1477, column: 10, scope: !3228)
!3228 = distinct !DILexicalBlock(scope: !3174, file: !3, line: 1477, column: 10)
!3229 = !DILocation(line: 1477, column: 13, scope: !3228)
!3230 = !DILocation(line: 1477, column: 10, scope: !3174)
!3231 = !DILocalVariable(name: "ths", scope: !3232, file: !3, line: 1479, type: !187)
!3232 = distinct !DILexicalBlock(scope: !3228, file: !3, line: 1478, column: 2)
!3233 = !DILocation(line: 1479, column: 16, scope: !3232)
!3234 = !DILocation(line: 1479, column: 22, scope: !3232)
!3235 = !DILocation(line: 1480, column: 5, scope: !3232)
!3236 = !DILocation(line: 1481, column: 7, scope: !3237)
!3237 = distinct !DILexicalBlock(scope: !3232, file: !3, line: 1481, column: 7)
!3238 = !DILocation(line: 1481, column: 12, scope: !3237)
!3239 = !DILocation(line: 1481, column: 23, scope: !3237)
!3240 = !DILocation(line: 1481, column: 7, scope: !3232)
!3241 = !DILocation(line: 1482, column: 22, scope: !3237)
!3242 = !DILocation(line: 1482, column: 27, scope: !3237)
!3243 = !DILocation(line: 1482, column: 6, scope: !3237)
!3244 = !DILocation(line: 1483, column: 7, scope: !3245)
!3245 = distinct !DILexicalBlock(scope: !3232, file: !3, line: 1483, column: 7)
!3246 = !DILocation(line: 1483, column: 12, scope: !3245)
!3247 = !DILocation(line: 1483, column: 23, scope: !3245)
!3248 = !DILocation(line: 1483, column: 7, scope: !3232)
!3249 = !DILocation(line: 1484, column: 22, scope: !3245)
!3250 = !DILocation(line: 1484, column: 27, scope: !3245)
!3251 = !DILocation(line: 1484, column: 6, scope: !3245)
!3252 = !DILocation(line: 1485, column: 19, scope: !3232)
!3253 = !DILocation(line: 1485, column: 2, scope: !3232)
!3254 = !DILocation(line: 1486, column: 2, scope: !3232)
!3255 = !DILocation(line: 1487, column: 5, scope: !3174)
!3256 = !DILocation(line: 1488, column: 5, scope: !3174)
!3257 = !DILocation(line: 1489, column: 19, scope: !3174)
!3258 = !DILocation(line: 1489, column: 11, scope: !3174)
!3259 = !DILocation(line: 1489, column: 5, scope: !3174)
!3260 = !DILocation(line: 1490, column: 10, scope: !3261)
!3261 = distinct !DILexicalBlock(scope: !3174, file: !3, line: 1490, column: 10)
!3262 = !DILocation(line: 1490, column: 20, scope: !3261)
!3263 = !DILocation(line: 1490, column: 10, scope: !3174)
!3264 = !DILocation(line: 1491, column: 16, scope: !3261)
!3265 = !DILocation(line: 1491, column: 8, scope: !3261)
!3266 = !DILocation(line: 1491, column: 2, scope: !3261)
!3267 = !DILocation(line: 1492, column: 5, scope: !3174)
!3268 = distinct !DISubprogram(name: "logstats", scope: !3, file: !3, line: 2140, type: !3269, scopeLine: 2141, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3269 = !DISubroutineType(types: !3270)
!3270 = !{null, !211}
!3271 = !DILocalVariable(name: "nowP", arg: 1, scope: !3268, file: !3, line: 2140, type: !211)
!3272 = !DILocation(line: 2140, column: 27, scope: !3268)
!3273 = !DILocalVariable(name: "tv", scope: !3268, file: !3, line: 2142, type: !212)
!3274 = !DILocation(line: 2142, column: 20, scope: !3268)
!3275 = !DILocalVariable(name: "now", scope: !3268, file: !3, line: 2143, type: !244)
!3276 = !DILocation(line: 2143, column: 12, scope: !3268)
!3277 = !DILocalVariable(name: "up_secs", scope: !3268, file: !3, line: 2144, type: !14)
!3278 = !DILocation(line: 2144, column: 10, scope: !3268)
!3279 = !DILocalVariable(name: "stats_secs", scope: !3268, file: !3, line: 2144, type: !14)
!3280 = !DILocation(line: 2144, column: 19, scope: !3268)
!3281 = !DILocation(line: 2146, column: 10, scope: !3282)
!3282 = distinct !DILexicalBlock(scope: !3268, file: !3, line: 2146, column: 10)
!3283 = !DILocation(line: 2146, column: 15, scope: !3282)
!3284 = !DILocation(line: 2146, column: 10, scope: !3268)
!3285 = !DILocation(line: 2148, column: 9, scope: !3286)
!3286 = distinct !DILexicalBlock(scope: !3282, file: !3, line: 2147, column: 2)
!3287 = !DILocation(line: 2149, column: 7, scope: !3286)
!3288 = !DILocation(line: 2150, column: 2, scope: !3286)
!3289 = !DILocation(line: 2151, column: 11, scope: !3268)
!3290 = !DILocation(line: 2151, column: 17, scope: !3268)
!3291 = !DILocation(line: 2151, column: 9, scope: !3268)
!3292 = !DILocation(line: 2152, column: 15, scope: !3268)
!3293 = !DILocation(line: 2152, column: 21, scope: !3268)
!3294 = !DILocation(line: 2152, column: 19, scope: !3268)
!3295 = !DILocation(line: 2152, column: 13, scope: !3268)
!3296 = !DILocation(line: 2153, column: 18, scope: !3268)
!3297 = !DILocation(line: 2153, column: 24, scope: !3268)
!3298 = !DILocation(line: 2153, column: 22, scope: !3268)
!3299 = !DILocation(line: 2153, column: 16, scope: !3268)
!3300 = !DILocation(line: 2154, column: 10, scope: !3301)
!3301 = distinct !DILexicalBlock(scope: !3268, file: !3, line: 2154, column: 10)
!3302 = !DILocation(line: 2154, column: 21, scope: !3301)
!3303 = !DILocation(line: 2154, column: 10, scope: !3268)
!3304 = !DILocation(line: 2155, column: 13, scope: !3301)
!3305 = !DILocation(line: 2155, column: 2, scope: !3301)
!3306 = !DILocation(line: 2156, column: 18, scope: !3268)
!3307 = !DILocation(line: 2156, column: 16, scope: !3268)
!3308 = !DILocation(line: 2158, column: 44, scope: !3268)
!3309 = !DILocation(line: 2158, column: 53, scope: !3268)
!3310 = !DILocation(line: 2157, column: 5, scope: !3268)
!3311 = !DILocation(line: 2160, column: 22, scope: !3268)
!3312 = !DILocation(line: 2160, column: 5, scope: !3268)
!3313 = !DILocation(line: 2161, column: 21, scope: !3268)
!3314 = !DILocation(line: 2161, column: 5, scope: !3268)
!3315 = !DILocation(line: 2162, column: 19, scope: !3268)
!3316 = !DILocation(line: 2162, column: 5, scope: !3268)
!3317 = !DILocation(line: 2163, column: 23, scope: !3268)
!3318 = !DILocation(line: 2163, column: 5, scope: !3268)
!3319 = !DILocation(line: 2164, column: 19, scope: !3268)
!3320 = !DILocation(line: 2164, column: 5, scope: !3268)
!3321 = !DILocation(line: 2165, column: 5, scope: !3268)
!3322 = distinct !DISubprogram(name: "thttpd_logstats", scope: !3, file: !3, line: 2170, type: !3323, scopeLine: 2171, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3323 = !DISubroutineType(types: !3324)
!3324 = !{null, !14}
!3325 = !DILocalVariable(name: "secs", arg: 1, scope: !3322, file: !3, line: 2170, type: !14)
!3326 = !DILocation(line: 2170, column: 23, scope: !3322)
!3327 = !DILocation(line: 2172, column: 10, scope: !3328)
!3328 = distinct !DILexicalBlock(scope: !3322, file: !3, line: 2172, column: 10)
!3329 = !DILocation(line: 2172, column: 15, scope: !3328)
!3330 = !DILocation(line: 2172, column: 10, scope: !3322)
!3331 = !DILocation(line: 2175, column: 6, scope: !3328)
!3332 = !DILocation(line: 2175, column: 33, scope: !3328)
!3333 = !DILocation(line: 2175, column: 25, scope: !3328)
!3334 = !DILocation(line: 2175, column: 53, scope: !3328)
!3335 = !DILocation(line: 2175, column: 51, scope: !3328)
!3336 = !DILocation(line: 2176, column: 6, scope: !3328)
!3337 = !DILocation(line: 2176, column: 38, scope: !3328)
!3338 = !DILocation(line: 2177, column: 14, scope: !3328)
!3339 = !DILocation(line: 2177, column: 6, scope: !3328)
!3340 = !DILocation(line: 2177, column: 28, scope: !3328)
!3341 = !DILocation(line: 2177, column: 26, scope: !3328)
!3342 = !DILocation(line: 2177, column: 34, scope: !3328)
!3343 = !DILocation(line: 2173, column: 2, scope: !3328)
!3344 = !DILocation(line: 2178, column: 23, scope: !3322)
!3345 = !DILocation(line: 2179, column: 17, scope: !3322)
!3346 = !DILocation(line: 2180, column: 24, scope: !3322)
!3347 = !DILocation(line: 2181, column: 5, scope: !3322)
!3348 = distinct !DISubprogram(name: "read_config", scope: !3, file: !3, line: 1000, type: !1683, scopeLine: 1001, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3349 = !DILocalVariable(name: "filename", arg: 1, scope: !3348, file: !3, line: 1000, type: !6)
!3350 = !DILocation(line: 1000, column: 20, scope: !3348)
!3351 = !DILocalVariable(name: "fp", scope: !3348, file: !3, line: 1002, type: !50)
!3352 = !DILocation(line: 1002, column: 11, scope: !3348)
!3353 = !DILocalVariable(name: "line", scope: !3348, file: !3, line: 1003, type: !3354)
!3354 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 80000, elements: !3355)
!3355 = !{!3356}
!3356 = !DISubrange(count: 10000)
!3357 = !DILocation(line: 1003, column: 10, scope: !3348)
!3358 = !DILocalVariable(name: "cp", scope: !3348, file: !3, line: 1004, type: !6)
!3359 = !DILocation(line: 1004, column: 11, scope: !3348)
!3360 = !DILocalVariable(name: "cp2", scope: !3348, file: !3, line: 1005, type: !6)
!3361 = !DILocation(line: 1005, column: 11, scope: !3348)
!3362 = !DILocalVariable(name: "name", scope: !3348, file: !3, line: 1006, type: !6)
!3363 = !DILocation(line: 1006, column: 11, scope: !3348)
!3364 = !DILocalVariable(name: "value", scope: !3348, file: !3, line: 1007, type: !6)
!3365 = !DILocation(line: 1007, column: 11, scope: !3348)
!3366 = !DILocation(line: 1009, column: 17, scope: !3348)
!3367 = !DILocation(line: 1009, column: 10, scope: !3348)
!3368 = !DILocation(line: 1009, column: 8, scope: !3348)
!3369 = !DILocation(line: 1010, column: 10, scope: !3370)
!3370 = distinct !DILexicalBlock(scope: !3348, file: !3, line: 1010, column: 10)
!3371 = !DILocation(line: 1010, column: 13, scope: !3370)
!3372 = !DILocation(line: 1010, column: 10, scope: !3348)
!3373 = !DILocation(line: 1012, column: 10, scope: !3374)
!3374 = distinct !DILexicalBlock(scope: !3370, file: !3, line: 1011, column: 2)
!3375 = !DILocation(line: 1012, column: 2, scope: !3374)
!3376 = !DILocation(line: 1013, column: 2, scope: !3374)
!3377 = !DILocation(line: 1016, column: 5, scope: !3348)
!3378 = !DILocation(line: 1016, column: 20, scope: !3348)
!3379 = !DILocation(line: 1016, column: 40, scope: !3348)
!3380 = !DILocation(line: 1016, column: 13, scope: !3348)
!3381 = !DILocation(line: 1016, column: 45, scope: !3348)
!3382 = !DILocation(line: 1019, column: 22, scope: !3383)
!3383 = distinct !DILexicalBlock(scope: !3384, file: !3, line: 1019, column: 7)
!3384 = distinct !DILexicalBlock(scope: !3348, file: !3, line: 1017, column: 2)
!3385 = !DILocation(line: 1019, column: 14, scope: !3383)
!3386 = !DILocation(line: 1019, column: 12, scope: !3383)
!3387 = !DILocation(line: 1019, column: 36, scope: !3383)
!3388 = !DILocation(line: 1019, column: 7, scope: !3384)
!3389 = !DILocation(line: 1020, column: 7, scope: !3383)
!3390 = !DILocation(line: 1020, column: 10, scope: !3383)
!3391 = !DILocation(line: 1020, column: 6, scope: !3383)
!3392 = !DILocation(line: 1023, column: 7, scope: !3384)
!3393 = !DILocation(line: 1023, column: 5, scope: !3384)
!3394 = !DILocation(line: 1024, column: 16, scope: !3384)
!3395 = !DILocation(line: 1024, column: 8, scope: !3384)
!3396 = !DILocation(line: 1024, column: 5, scope: !3384)
!3397 = !DILocation(line: 1027, column: 2, scope: !3384)
!3398 = !DILocation(line: 1027, column: 11, scope: !3384)
!3399 = !DILocation(line: 1027, column: 10, scope: !3384)
!3400 = !DILocation(line: 1027, column: 14, scope: !3384)
!3401 = !DILocation(line: 1030, column: 12, scope: !3402)
!3402 = distinct !DILexicalBlock(scope: !3384, file: !3, line: 1028, column: 6)
!3403 = !DILocation(line: 1030, column: 26, scope: !3402)
!3404 = !DILocation(line: 1030, column: 17, scope: !3402)
!3405 = !DILocation(line: 1030, column: 15, scope: !3402)
!3406 = !DILocation(line: 1030, column: 10, scope: !3402)
!3407 = !DILocation(line: 1032, column: 6, scope: !3402)
!3408 = !DILocation(line: 1032, column: 15, scope: !3402)
!3409 = !DILocation(line: 1032, column: 14, scope: !3402)
!3410 = !DILocation(line: 1032, column: 19, scope: !3402)
!3411 = !DILocation(line: 1032, column: 26, scope: !3402)
!3412 = !DILocation(line: 1032, column: 30, scope: !3402)
!3413 = !DILocation(line: 1032, column: 29, scope: !3402)
!3414 = !DILocation(line: 1032, column: 34, scope: !3402)
!3415 = !DILocation(line: 1032, column: 42, scope: !3402)
!3416 = !DILocation(line: 1032, column: 46, scope: !3402)
!3417 = !DILocation(line: 1032, column: 45, scope: !3402)
!3418 = !DILocation(line: 1032, column: 50, scope: !3402)
!3419 = !DILocation(line: 1032, column: 58, scope: !3402)
!3420 = !DILocation(line: 1032, column: 62, scope: !3402)
!3421 = !DILocation(line: 1032, column: 61, scope: !3402)
!3422 = !DILocation(line: 1032, column: 66, scope: !3402)
!3423 = !DILocation(line: 1033, column: 7, scope: !3402)
!3424 = !DILocation(line: 1033, column: 10, scope: !3402)
!3425 = distinct !{!3425, !3407, !3426}
!3426 = !DILocation(line: 1033, column: 12, scope: !3402)
!3427 = !DILocation(line: 1035, column: 13, scope: !3402)
!3428 = !DILocation(line: 1035, column: 11, scope: !3402)
!3429 = !DILocation(line: 1036, column: 22, scope: !3402)
!3430 = !DILocation(line: 1036, column: 14, scope: !3402)
!3431 = !DILocation(line: 1036, column: 12, scope: !3402)
!3432 = !DILocation(line: 1037, column: 11, scope: !3433)
!3433 = distinct !DILexicalBlock(scope: !3402, file: !3, line: 1037, column: 11)
!3434 = !DILocation(line: 1037, column: 17, scope: !3433)
!3435 = !DILocation(line: 1037, column: 11, scope: !3402)
!3436 = !DILocation(line: 1038, column: 9, scope: !3433)
!3437 = !DILocation(line: 1038, column: 12, scope: !3433)
!3438 = !DILocation(line: 1038, column: 3, scope: !3433)
!3439 = !DILocation(line: 1040, column: 23, scope: !3440)
!3440 = distinct !DILexicalBlock(scope: !3402, file: !3, line: 1040, column: 11)
!3441 = !DILocation(line: 1040, column: 11, scope: !3440)
!3442 = !DILocation(line: 1040, column: 39, scope: !3440)
!3443 = !DILocation(line: 1040, column: 11, scope: !3402)
!3444 = !DILocation(line: 1042, column: 22, scope: !3445)
!3445 = distinct !DILexicalBlock(scope: !3440, file: !3, line: 1041, column: 3)
!3446 = !DILocation(line: 1042, column: 28, scope: !3445)
!3447 = !DILocation(line: 1042, column: 3, scope: !3445)
!3448 = !DILocation(line: 1043, column: 9, scope: !3445)
!3449 = !DILocation(line: 1044, column: 3, scope: !3445)
!3450 = !DILocation(line: 1045, column: 28, scope: !3451)
!3451 = distinct !DILexicalBlock(scope: !3440, file: !3, line: 1045, column: 16)
!3452 = !DILocation(line: 1045, column: 16, scope: !3451)
!3453 = !DILocation(line: 1045, column: 43, scope: !3451)
!3454 = !DILocation(line: 1045, column: 16, scope: !3440)
!3455 = !DILocation(line: 1047, column: 19, scope: !3456)
!3456 = distinct !DILexicalBlock(scope: !3451, file: !3, line: 1046, column: 3)
!3457 = !DILocation(line: 1047, column: 25, scope: !3456)
!3458 = !DILocation(line: 1047, column: 3, scope: !3456)
!3459 = !DILocation(line: 1048, column: 33, scope: !3456)
!3460 = !DILocation(line: 1048, column: 27, scope: !3456)
!3461 = !DILocation(line: 1048, column: 10, scope: !3456)
!3462 = !DILocation(line: 1048, column: 8, scope: !3456)
!3463 = !DILocation(line: 1049, column: 3, scope: !3456)
!3464 = !DILocation(line: 1050, column: 28, scope: !3465)
!3465 = distinct !DILexicalBlock(scope: !3451, file: !3, line: 1050, column: 16)
!3466 = !DILocation(line: 1050, column: 16, scope: !3465)
!3467 = !DILocation(line: 1050, column: 42, scope: !3465)
!3468 = !DILocation(line: 1050, column: 16, scope: !3451)
!3469 = !DILocation(line: 1052, column: 19, scope: !3470)
!3470 = distinct !DILexicalBlock(scope: !3465, file: !3, line: 1051, column: 3)
!3471 = !DILocation(line: 1052, column: 25, scope: !3470)
!3472 = !DILocation(line: 1052, column: 3, scope: !3470)
!3473 = !DILocation(line: 1053, column: 19, scope: !3470)
!3474 = !DILocation(line: 1053, column: 9, scope: !3470)
!3475 = !DILocation(line: 1053, column: 7, scope: !3470)
!3476 = !DILocation(line: 1054, column: 3, scope: !3470)
!3477 = !DILocation(line: 1055, column: 28, scope: !3478)
!3478 = distinct !DILexicalBlock(scope: !3465, file: !3, line: 1055, column: 16)
!3479 = !DILocation(line: 1055, column: 16, scope: !3478)
!3480 = !DILocation(line: 1055, column: 45, scope: !3478)
!3481 = !DILocation(line: 1055, column: 16, scope: !3465)
!3482 = !DILocation(line: 1057, column: 22, scope: !3483)
!3483 = distinct !DILexicalBlock(scope: !3478, file: !3, line: 1056, column: 3)
!3484 = !DILocation(line: 1057, column: 28, scope: !3483)
!3485 = !DILocation(line: 1057, column: 3, scope: !3483)
!3486 = !DILocation(line: 1058, column: 13, scope: !3483)
!3487 = !DILocation(line: 1059, column: 20, scope: !3483)
!3488 = !DILocation(line: 1060, column: 3, scope: !3483)
!3489 = !DILocation(line: 1061, column: 28, scope: !3490)
!3490 = distinct !DILexicalBlock(scope: !3478, file: !3, line: 1061, column: 16)
!3491 = !DILocation(line: 1061, column: 16, scope: !3490)
!3492 = !DILocation(line: 1061, column: 47, scope: !3490)
!3493 = !DILocation(line: 1061, column: 16, scope: !3478)
!3494 = !DILocation(line: 1063, column: 22, scope: !3495)
!3495 = distinct !DILexicalBlock(scope: !3490, file: !3, line: 1062, column: 3)
!3496 = !DILocation(line: 1063, column: 28, scope: !3495)
!3497 = !DILocation(line: 1063, column: 3, scope: !3495)
!3498 = !DILocation(line: 1064, column: 13, scope: !3495)
!3499 = !DILocation(line: 1065, column: 20, scope: !3495)
!3500 = !DILocation(line: 1066, column: 3, scope: !3495)
!3501 = !DILocation(line: 1067, column: 28, scope: !3502)
!3502 = distinct !DILexicalBlock(scope: !3490, file: !3, line: 1067, column: 16)
!3503 = !DILocation(line: 1067, column: 16, scope: !3502)
!3504 = !DILocation(line: 1067, column: 47, scope: !3502)
!3505 = !DILocation(line: 1067, column: 16, scope: !3490)
!3506 = !DILocation(line: 1069, column: 19, scope: !3507)
!3507 = distinct !DILexicalBlock(scope: !3502, file: !3, line: 1068, column: 3)
!3508 = !DILocation(line: 1069, column: 25, scope: !3507)
!3509 = !DILocation(line: 1069, column: 3, scope: !3507)
!3510 = !DILocation(line: 1070, column: 24, scope: !3507)
!3511 = !DILocation(line: 1070, column: 14, scope: !3507)
!3512 = !DILocation(line: 1070, column: 12, scope: !3507)
!3513 = !DILocation(line: 1071, column: 3, scope: !3507)
!3514 = !DILocation(line: 1072, column: 28, scope: !3515)
!3515 = distinct !DILexicalBlock(scope: !3502, file: !3, line: 1072, column: 16)
!3516 = !DILocation(line: 1072, column: 16, scope: !3515)
!3517 = !DILocation(line: 1072, column: 53, scope: !3515)
!3518 = !DILocation(line: 1072, column: 16, scope: !3502)
!3519 = !DILocation(line: 1074, column: 22, scope: !3520)
!3520 = distinct !DILexicalBlock(scope: !3515, file: !3, line: 1073, column: 3)
!3521 = !DILocation(line: 1074, column: 28, scope: !3520)
!3522 = !DILocation(line: 1074, column: 3, scope: !3520)
!3523 = !DILocation(line: 1075, column: 20, scope: !3520)
!3524 = !DILocation(line: 1076, column: 3, scope: !3520)
!3525 = !DILocation(line: 1077, column: 28, scope: !3526)
!3526 = distinct !DILexicalBlock(scope: !3515, file: !3, line: 1077, column: 16)
!3527 = !DILocation(line: 1077, column: 16, scope: !3526)
!3528 = !DILocation(line: 1077, column: 51, scope: !3526)
!3529 = !DILocation(line: 1077, column: 16, scope: !3515)
!3530 = !DILocation(line: 1079, column: 22, scope: !3531)
!3531 = distinct !DILexicalBlock(scope: !3526, file: !3, line: 1078, column: 3)
!3532 = !DILocation(line: 1079, column: 28, scope: !3531)
!3533 = !DILocation(line: 1079, column: 3, scope: !3531)
!3534 = !DILocation(line: 1080, column: 20, scope: !3531)
!3535 = !DILocation(line: 1081, column: 3, scope: !3531)
!3536 = !DILocation(line: 1082, column: 28, scope: !3537)
!3537 = distinct !DILexicalBlock(scope: !3526, file: !3, line: 1082, column: 16)
!3538 = !DILocation(line: 1082, column: 16, scope: !3537)
!3539 = !DILocation(line: 1082, column: 43, scope: !3537)
!3540 = !DILocation(line: 1082, column: 16, scope: !3526)
!3541 = !DILocation(line: 1084, column: 19, scope: !3542)
!3542 = distinct !DILexicalBlock(scope: !3537, file: !3, line: 1083, column: 3)
!3543 = !DILocation(line: 1084, column: 25, scope: !3542)
!3544 = !DILocation(line: 1084, column: 3, scope: !3542)
!3545 = !DILocation(line: 1085, column: 20, scope: !3542)
!3546 = !DILocation(line: 1085, column: 10, scope: !3542)
!3547 = !DILocation(line: 1085, column: 8, scope: !3542)
!3548 = !DILocation(line: 1086, column: 3, scope: !3542)
!3549 = !DILocation(line: 1087, column: 28, scope: !3550)
!3550 = distinct !DILexicalBlock(scope: !3537, file: !3, line: 1087, column: 16)
!3551 = !DILocation(line: 1087, column: 16, scope: !3550)
!3552 = !DILocation(line: 1087, column: 45, scope: !3550)
!3553 = !DILocation(line: 1087, column: 16, scope: !3537)
!3554 = !DILocation(line: 1089, column: 19, scope: !3555)
!3555 = distinct !DILexicalBlock(scope: !3550, file: !3, line: 1088, column: 3)
!3556 = !DILocation(line: 1089, column: 25, scope: !3555)
!3557 = !DILocation(line: 1089, column: 3, scope: !3555)
!3558 = !DILocation(line: 1090, column: 27, scope: !3555)
!3559 = !DILocation(line: 1090, column: 17, scope: !3555)
!3560 = !DILocation(line: 1090, column: 15, scope: !3555)
!3561 = !DILocation(line: 1091, column: 3, scope: !3555)
!3562 = !DILocation(line: 1092, column: 28, scope: !3563)
!3563 = distinct !DILexicalBlock(scope: !3550, file: !3, line: 1092, column: 16)
!3564 = !DILocation(line: 1092, column: 16, scope: !3563)
!3565 = !DILocation(line: 1092, column: 47, scope: !3563)
!3566 = !DILocation(line: 1092, column: 16, scope: !3550)
!3567 = !DILocation(line: 1094, column: 19, scope: !3568)
!3568 = distinct !DILexicalBlock(scope: !3563, file: !3, line: 1093, column: 3)
!3569 = !DILocation(line: 1094, column: 25, scope: !3568)
!3570 = !DILocation(line: 1094, column: 3, scope: !3568)
!3571 = !DILocation(line: 1095, column: 21, scope: !3568)
!3572 = !DILocation(line: 1095, column: 15, scope: !3568)
!3573 = !DILocation(line: 1095, column: 13, scope: !3568)
!3574 = !DILocation(line: 1096, column: 3, scope: !3568)
!3575 = !DILocation(line: 1097, column: 28, scope: !3576)
!3576 = distinct !DILexicalBlock(scope: !3563, file: !3, line: 1097, column: 16)
!3577 = !DILocation(line: 1097, column: 16, scope: !3576)
!3578 = !DILocation(line: 1097, column: 45, scope: !3576)
!3579 = !DILocation(line: 1097, column: 16, scope: !3563)
!3580 = !DILocation(line: 1099, column: 19, scope: !3581)
!3581 = distinct !DILexicalBlock(scope: !3576, file: !3, line: 1098, column: 3)
!3582 = !DILocation(line: 1099, column: 25, scope: !3581)
!3583 = !DILocation(line: 1099, column: 3, scope: !3581)
!3584 = !DILocation(line: 1100, column: 27, scope: !3581)
!3585 = !DILocation(line: 1100, column: 17, scope: !3581)
!3586 = !DILocation(line: 1100, column: 15, scope: !3581)
!3587 = !DILocation(line: 1101, column: 3, scope: !3581)
!3588 = !DILocation(line: 1102, column: 28, scope: !3589)
!3589 = distinct !DILexicalBlock(scope: !3576, file: !3, line: 1102, column: 16)
!3590 = !DILocation(line: 1102, column: 16, scope: !3589)
!3591 = !DILocation(line: 1102, column: 54, scope: !3589)
!3592 = !DILocation(line: 1102, column: 59, scope: !3589)
!3593 = !DILocation(line: 1103, column: 28, scope: !3589)
!3594 = !DILocation(line: 1103, column: 16, scope: !3589)
!3595 = !DILocation(line: 1103, column: 55, scope: !3589)
!3596 = !DILocation(line: 1102, column: 16, scope: !3576)
!3597 = !DILocation(line: 1105, column: 22, scope: !3598)
!3598 = distinct !DILexicalBlock(scope: !3589, file: !3, line: 1104, column: 3)
!3599 = !DILocation(line: 1105, column: 28, scope: !3598)
!3600 = !DILocation(line: 1105, column: 3, scope: !3598)
!3601 = !DILocation(line: 1106, column: 22, scope: !3598)
!3602 = !DILocation(line: 1107, column: 3, scope: !3598)
!3603 = !DILocation(line: 1108, column: 28, scope: !3604)
!3604 = distinct !DILexicalBlock(scope: !3589, file: !3, line: 1108, column: 16)
!3605 = !DILocation(line: 1108, column: 16, scope: !3604)
!3606 = !DILocation(line: 1108, column: 47, scope: !3604)
!3607 = !DILocation(line: 1108, column: 16, scope: !3589)
!3608 = !DILocation(line: 1110, column: 19, scope: !3609)
!3609 = distinct !DILexicalBlock(scope: !3604, file: !3, line: 1109, column: 3)
!3610 = !DILocation(line: 1110, column: 25, scope: !3609)
!3611 = !DILocation(line: 1110, column: 3, scope: !3609)
!3612 = !DILocation(line: 1111, column: 29, scope: !3609)
!3613 = !DILocation(line: 1111, column: 19, scope: !3609)
!3614 = !DILocation(line: 1111, column: 17, scope: !3609)
!3615 = !DILocation(line: 1112, column: 3, scope: !3609)
!3616 = !DILocation(line: 1113, column: 28, scope: !3617)
!3617 = distinct !DILexicalBlock(scope: !3604, file: !3, line: 1113, column: 16)
!3618 = !DILocation(line: 1113, column: 16, scope: !3617)
!3619 = !DILocation(line: 1113, column: 48, scope: !3617)
!3620 = !DILocation(line: 1113, column: 16, scope: !3604)
!3621 = !DILocation(line: 1115, column: 19, scope: !3622)
!3622 = distinct !DILexicalBlock(scope: !3617, file: !3, line: 1114, column: 3)
!3623 = !DILocation(line: 1115, column: 25, scope: !3622)
!3624 = !DILocation(line: 1115, column: 3, scope: !3622)
!3625 = !DILocation(line: 1116, column: 28, scope: !3622)
!3626 = !DILocation(line: 1116, column: 18, scope: !3622)
!3627 = !DILocation(line: 1116, column: 16, scope: !3622)
!3628 = !DILocation(line: 1117, column: 3, scope: !3622)
!3629 = !DILocation(line: 1118, column: 28, scope: !3630)
!3630 = distinct !DILexicalBlock(scope: !3617, file: !3, line: 1118, column: 16)
!3631 = !DILocation(line: 1118, column: 16, scope: !3630)
!3632 = !DILocation(line: 1118, column: 43, scope: !3630)
!3633 = !DILocation(line: 1118, column: 16, scope: !3617)
!3634 = !DILocation(line: 1120, column: 19, scope: !3635)
!3635 = distinct !DILexicalBlock(scope: !3630, file: !3, line: 1119, column: 3)
!3636 = !DILocation(line: 1120, column: 25, scope: !3635)
!3637 = !DILocation(line: 1120, column: 3, scope: !3635)
!3638 = !DILocation(line: 1121, column: 24, scope: !3635)
!3639 = !DILocation(line: 1121, column: 14, scope: !3635)
!3640 = !DILocation(line: 1121, column: 12, scope: !3635)
!3641 = !DILocation(line: 1122, column: 3, scope: !3635)
!3642 = !DILocation(line: 1123, column: 28, scope: !3643)
!3643 = distinct !DILexicalBlock(scope: !3630, file: !3, line: 1123, column: 16)
!3644 = !DILocation(line: 1123, column: 16, scope: !3643)
!3645 = !DILocation(line: 1123, column: 46, scope: !3643)
!3646 = !DILocation(line: 1123, column: 16, scope: !3630)
!3647 = !DILocation(line: 1125, column: 19, scope: !3648)
!3648 = distinct !DILexicalBlock(scope: !3643, file: !3, line: 1124, column: 3)
!3649 = !DILocation(line: 1125, column: 25, scope: !3648)
!3650 = !DILocation(line: 1125, column: 3, scope: !3648)
!3651 = !DILocation(line: 1126, column: 23, scope: !3648)
!3652 = !DILocation(line: 1126, column: 13, scope: !3648)
!3653 = !DILocation(line: 1126, column: 11, scope: !3648)
!3654 = !DILocation(line: 1127, column: 3, scope: !3648)
!3655 = !DILocation(line: 1128, column: 28, scope: !3656)
!3656 = distinct !DILexicalBlock(scope: !3643, file: !3, line: 1128, column: 16)
!3657 = !DILocation(line: 1128, column: 16, scope: !3656)
!3658 = !DILocation(line: 1128, column: 44, scope: !3656)
!3659 = !DILocation(line: 1128, column: 16, scope: !3643)
!3660 = !DILocation(line: 1130, column: 22, scope: !3661)
!3661 = distinct !DILexicalBlock(scope: !3656, file: !3, line: 1129, column: 3)
!3662 = !DILocation(line: 1130, column: 28, scope: !3661)
!3663 = !DILocation(line: 1130, column: 3, scope: !3661)
!3664 = !DILocation(line: 1131, column: 12, scope: !3661)
!3665 = !DILocation(line: 1132, column: 3, scope: !3661)
!3666 = !DILocation(line: 1133, column: 28, scope: !3667)
!3667 = distinct !DILexicalBlock(scope: !3656, file: !3, line: 1133, column: 16)
!3668 = !DILocation(line: 1133, column: 16, scope: !3667)
!3669 = !DILocation(line: 1133, column: 46, scope: !3667)
!3670 = !DILocation(line: 1133, column: 16, scope: !3656)
!3671 = !DILocation(line: 1135, column: 22, scope: !3672)
!3672 = distinct !DILexicalBlock(scope: !3667, file: !3, line: 1134, column: 3)
!3673 = !DILocation(line: 1135, column: 28, scope: !3672)
!3674 = !DILocation(line: 1135, column: 3, scope: !3672)
!3675 = !DILocation(line: 1136, column: 12, scope: !3672)
!3676 = !DILocation(line: 1137, column: 3, scope: !3672)
!3677 = !DILocation(line: 1138, column: 28, scope: !3678)
!3678 = distinct !DILexicalBlock(scope: !3667, file: !3, line: 1138, column: 16)
!3679 = !DILocation(line: 1138, column: 16, scope: !3678)
!3680 = !DILocation(line: 1138, column: 51, scope: !3678)
!3681 = !DILocation(line: 1138, column: 16, scope: !3667)
!3682 = !DILocation(line: 1140, column: 22, scope: !3683)
!3683 = distinct !DILexicalBlock(scope: !3678, file: !3, line: 1139, column: 3)
!3684 = !DILocation(line: 1140, column: 28, scope: !3683)
!3685 = !DILocation(line: 1140, column: 3, scope: !3683)
!3686 = !DILocation(line: 1141, column: 20, scope: !3683)
!3687 = !DILocation(line: 1142, column: 3, scope: !3683)
!3688 = !DILocation(line: 1143, column: 28, scope: !3689)
!3689 = distinct !DILexicalBlock(scope: !3678, file: !3, line: 1143, column: 16)
!3690 = !DILocation(line: 1143, column: 16, scope: !3689)
!3691 = !DILocation(line: 1143, column: 53, scope: !3689)
!3692 = !DILocation(line: 1143, column: 16, scope: !3678)
!3693 = !DILocation(line: 1145, column: 22, scope: !3694)
!3694 = distinct !DILexicalBlock(scope: !3689, file: !3, line: 1144, column: 3)
!3695 = !DILocation(line: 1145, column: 28, scope: !3694)
!3696 = !DILocation(line: 1145, column: 3, scope: !3694)
!3697 = !DILocation(line: 1146, column: 20, scope: !3694)
!3698 = !DILocation(line: 1147, column: 3, scope: !3694)
!3699 = !DILocation(line: 1148, column: 28, scope: !3700)
!3700 = distinct !DILexicalBlock(scope: !3689, file: !3, line: 1148, column: 16)
!3701 = !DILocation(line: 1148, column: 16, scope: !3700)
!3702 = !DILocation(line: 1148, column: 46, scope: !3700)
!3703 = !DILocation(line: 1148, column: 16, scope: !3689)
!3704 = !DILocation(line: 1150, column: 19, scope: !3705)
!3705 = distinct !DILexicalBlock(scope: !3700, file: !3, line: 1149, column: 3)
!3706 = !DILocation(line: 1150, column: 25, scope: !3705)
!3707 = !DILocation(line: 1150, column: 3, scope: !3705)
!3708 = !DILocation(line: 1151, column: 23, scope: !3705)
!3709 = !DILocation(line: 1151, column: 13, scope: !3705)
!3710 = !DILocation(line: 1151, column: 11, scope: !3705)
!3711 = !DILocation(line: 1152, column: 3, scope: !3705)
!3712 = !DILocation(line: 1153, column: 28, scope: !3713)
!3713 = distinct !DILexicalBlock(scope: !3700, file: !3, line: 1153, column: 16)
!3714 = !DILocation(line: 1153, column: 16, scope: !3713)
!3715 = !DILocation(line: 1153, column: 46, scope: !3713)
!3716 = !DILocation(line: 1153, column: 16, scope: !3700)
!3717 = !DILocation(line: 1155, column: 19, scope: !3718)
!3718 = distinct !DILexicalBlock(scope: !3713, file: !3, line: 1154, column: 3)
!3719 = !DILocation(line: 1155, column: 25, scope: !3718)
!3720 = !DILocation(line: 1155, column: 3, scope: !3718)
!3721 = !DILocation(line: 1156, column: 23, scope: !3718)
!3722 = !DILocation(line: 1156, column: 13, scope: !3718)
!3723 = !DILocation(line: 1156, column: 11, scope: !3718)
!3724 = !DILocation(line: 1157, column: 3, scope: !3718)
!3725 = !DILocation(line: 1158, column: 28, scope: !3726)
!3726 = distinct !DILexicalBlock(scope: !3713, file: !3, line: 1158, column: 16)
!3727 = !DILocation(line: 1158, column: 16, scope: !3726)
!3728 = !DILocation(line: 1158, column: 42, scope: !3726)
!3729 = !DILocation(line: 1158, column: 16, scope: !3713)
!3730 = !DILocation(line: 1160, column: 19, scope: !3731)
!3731 = distinct !DILexicalBlock(scope: !3726, file: !3, line: 1159, column: 3)
!3732 = !DILocation(line: 1160, column: 25, scope: !3731)
!3733 = !DILocation(line: 1160, column: 3, scope: !3731)
!3734 = !DILocation(line: 1161, column: 19, scope: !3731)
!3735 = !DILocation(line: 1161, column: 9, scope: !3731)
!3736 = !DILocation(line: 1161, column: 7, scope: !3731)
!3737 = !DILocation(line: 1162, column: 3, scope: !3731)
!3738 = !DILocation(line: 1163, column: 28, scope: !3739)
!3739 = distinct !DILexicalBlock(scope: !3726, file: !3, line: 1163, column: 16)
!3740 = !DILocation(line: 1163, column: 16, scope: !3739)
!3741 = !DILocation(line: 1163, column: 46, scope: !3739)
!3742 = !DILocation(line: 1163, column: 16, scope: !3726)
!3743 = !DILocation(line: 1165, column: 19, scope: !3744)
!3744 = distinct !DILexicalBlock(scope: !3739, file: !3, line: 1164, column: 3)
!3745 = !DILocation(line: 1165, column: 25, scope: !3744)
!3746 = !DILocation(line: 1165, column: 3, scope: !3744)
!3747 = !DILocation(line: 1166, column: 19, scope: !3744)
!3748 = !DILocation(line: 1166, column: 13, scope: !3744)
!3749 = !DILocation(line: 1166, column: 11, scope: !3744)
!3750 = !DILocation(line: 1167, column: 3, scope: !3744)
!3751 = !DILocation(line: 1171, column: 7, scope: !3752)
!3752 = distinct !DILexicalBlock(scope: !3739, file: !3, line: 1169, column: 3)
!3753 = !DILocation(line: 1171, column: 51, scope: !3752)
!3754 = !DILocation(line: 1171, column: 58, scope: !3752)
!3755 = !DILocation(line: 1170, column: 10, scope: !3752)
!3756 = !DILocation(line: 1172, column: 3, scope: !3752)
!3757 = !DILocation(line: 1176, column: 11, scope: !3402)
!3758 = !DILocation(line: 1176, column: 9, scope: !3402)
!3759 = !DILocation(line: 1177, column: 20, scope: !3402)
!3760 = !DILocation(line: 1177, column: 12, scope: !3402)
!3761 = !DILocation(line: 1177, column: 9, scope: !3402)
!3762 = distinct !{!3762, !3397, !3763}
!3763 = !DILocation(line: 1178, column: 6, scope: !3384)
!3764 = distinct !{!3764, !3377, !3765}
!3765 = !DILocation(line: 1179, column: 2, scope: !3348)
!3766 = !DILocation(line: 1181, column: 20, scope: !3348)
!3767 = !DILocation(line: 1181, column: 12, scope: !3348)
!3768 = !DILocation(line: 1182, column: 5, scope: !3348)
!3769 = distinct !DISubprogram(name: "usage", scope: !3, file: !3, line: 990, type: !2300, scopeLine: 991, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3770 = !DILocation(line: 992, column: 21, scope: !3769)
!3771 = !DILocation(line: 994, column: 2, scope: !3769)
!3772 = !DILocation(line: 992, column: 12, scope: !3769)
!3773 = !DILocation(line: 995, column: 5, scope: !3769)
!3774 = distinct !DISubprogram(name: "no_value_required", scope: !3, file: !3, line: 1198, type: !3775, scopeLine: 1199, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3775 = !DISubroutineType(types: !3776)
!3776 = !{null, !6, !6}
!3777 = !DILocalVariable(name: "name", arg: 1, scope: !3774, file: !3, line: 1198, type: !6)
!3778 = !DILocation(line: 1198, column: 26, scope: !3774)
!3779 = !DILocalVariable(name: "value", arg: 2, scope: !3774, file: !3, line: 1198, type: !6)
!3780 = !DILocation(line: 1198, column: 38, scope: !3774)
!3781 = !DILocation(line: 1200, column: 10, scope: !3782)
!3782 = distinct !DILexicalBlock(scope: !3774, file: !3, line: 1200, column: 10)
!3783 = !DILocation(line: 1200, column: 16, scope: !3782)
!3784 = !DILocation(line: 1200, column: 10, scope: !3774)
!3785 = !DILocation(line: 1203, column: 6, scope: !3786)
!3786 = distinct !DILexicalBlock(scope: !3782, file: !3, line: 1201, column: 2)
!3787 = !DILocation(line: 1204, column: 6, scope: !3786)
!3788 = !DILocation(line: 1204, column: 13, scope: !3786)
!3789 = !DILocation(line: 1202, column: 9, scope: !3786)
!3790 = !DILocation(line: 1205, column: 2, scope: !3786)
!3791 = !DILocation(line: 1207, column: 5, scope: !3774)
!3792 = distinct !DISubprogram(name: "value_required", scope: !3, file: !3, line: 1186, type: !3775, scopeLine: 1187, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3793 = !DILocalVariable(name: "name", arg: 1, scope: !3792, file: !3, line: 1186, type: !6)
!3794 = !DILocation(line: 1186, column: 23, scope: !3792)
!3795 = !DILocalVariable(name: "value", arg: 2, scope: !3792, file: !3, line: 1186, type: !6)
!3796 = !DILocation(line: 1186, column: 35, scope: !3792)
!3797 = !DILocation(line: 1188, column: 10, scope: !3798)
!3798 = distinct !DILexicalBlock(scope: !3792, file: !3, line: 1188, column: 10)
!3799 = !DILocation(line: 1188, column: 16, scope: !3798)
!3800 = !DILocation(line: 1188, column: 10, scope: !3792)
!3801 = !DILocation(line: 1191, column: 6, scope: !3802)
!3802 = distinct !DILexicalBlock(scope: !3798, file: !3, line: 1189, column: 2)
!3803 = !DILocation(line: 1191, column: 52, scope: !3802)
!3804 = !DILocation(line: 1191, column: 59, scope: !3802)
!3805 = !DILocation(line: 1190, column: 9, scope: !3802)
!3806 = !DILocation(line: 1192, column: 2, scope: !3802)
!3807 = !DILocation(line: 1194, column: 5, scope: !3792)
!3808 = distinct !DISubprogram(name: "e_strdup", scope: !3, file: !3, line: 1211, type: !3809, scopeLine: 1212, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3809 = !DISubroutineType(types: !3810)
!3810 = !{!6, !6}
!3811 = !DILocalVariable(name: "oldstr", arg: 1, scope: !3808, file: !3, line: 1211, type: !6)
!3812 = !DILocation(line: 1211, column: 17, scope: !3808)
!3813 = !DILocalVariable(name: "newstr", scope: !3808, file: !3, line: 1213, type: !6)
!3814 = !DILocation(line: 1213, column: 11, scope: !3808)
!3815 = !DILocation(line: 1215, column: 22, scope: !3808)
!3816 = !DILocation(line: 1215, column: 14, scope: !3808)
!3817 = !DILocation(line: 1215, column: 12, scope: !3808)
!3818 = !DILocation(line: 1216, column: 10, scope: !3819)
!3819 = distinct !DILexicalBlock(scope: !3808, file: !3, line: 1216, column: 10)
!3820 = !DILocation(line: 1216, column: 17, scope: !3819)
!3821 = !DILocation(line: 1216, column: 10, scope: !3808)
!3822 = !DILocation(line: 1218, column: 2, scope: !3823)
!3823 = distinct !DILexicalBlock(scope: !3819, file: !3, line: 1217, column: 2)
!3824 = !DILocation(line: 1219, column: 18, scope: !3823)
!3825 = !DILocation(line: 1219, column: 66, scope: !3823)
!3826 = !DILocation(line: 1219, column: 9, scope: !3823)
!3827 = !DILocation(line: 1220, column: 2, scope: !3823)
!3828 = !DILocation(line: 1222, column: 12, scope: !3808)
!3829 = !DILocation(line: 1222, column: 5, scope: !3808)
!3830 = distinct !DISubprogram(name: "finish_connection", scope: !3, file: !3, line: 1976, type: !2469, scopeLine: 1977, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3831 = !DILocalVariable(name: "c", arg: 1, scope: !3830, file: !3, line: 1976, type: !248)
!3832 = !DILocation(line: 1976, column: 32, scope: !3830)
!3833 = !DILocalVariable(name: "tvP", arg: 2, scope: !3830, file: !3, line: 1976, type: !211)
!3834 = !DILocation(line: 1976, column: 51, scope: !3830)
!3835 = !DILocation(line: 1979, column: 27, scope: !3830)
!3836 = !DILocation(line: 1979, column: 30, scope: !3830)
!3837 = !DILocation(line: 1979, column: 5, scope: !3830)
!3838 = !DILocation(line: 1982, column: 23, scope: !3830)
!3839 = !DILocation(line: 1982, column: 26, scope: !3830)
!3840 = !DILocation(line: 1982, column: 5, scope: !3830)
!3841 = !DILocation(line: 1983, column: 5, scope: !3830)
!3842 = distinct !DISubprogram(name: "check_throttles", scope: !3, file: !3, line: 1874, type: !3843, scopeLine: 1875, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3843 = !DISubroutineType(types: !3844)
!3844 = !{!26, !248}
!3845 = !DILocalVariable(name: "c", arg: 1, scope: !3842, file: !3, line: 1874, type: !248)
!3846 = !DILocation(line: 1874, column: 30, scope: !3842)
!3847 = !DILocalVariable(name: "tnum", scope: !3842, file: !3, line: 1876, type: !26)
!3848 = !DILocation(line: 1876, column: 9, scope: !3842)
!3849 = !DILocalVariable(name: "l", scope: !3842, file: !3, line: 1877, type: !14)
!3850 = !DILocation(line: 1877, column: 10, scope: !3842)
!3851 = !DILocation(line: 1879, column: 5, scope: !3842)
!3852 = !DILocation(line: 1879, column: 8, scope: !3842)
!3853 = !DILocation(line: 1879, column: 17, scope: !3842)
!3854 = !DILocation(line: 1880, column: 20, scope: !3842)
!3855 = !DILocation(line: 1880, column: 23, scope: !3842)
!3856 = !DILocation(line: 1880, column: 33, scope: !3842)
!3857 = !DILocation(line: 1880, column: 5, scope: !3842)
!3858 = !DILocation(line: 1880, column: 8, scope: !3842)
!3859 = !DILocation(line: 1880, column: 18, scope: !3842)
!3860 = !DILocation(line: 1881, column: 16, scope: !3861)
!3861 = distinct !DILexicalBlock(scope: !3842, file: !3, line: 1881, column: 5)
!3862 = !DILocation(line: 1881, column: 11, scope: !3861)
!3863 = !DILocation(line: 1881, column: 21, scope: !3864)
!3864 = distinct !DILexicalBlock(scope: !3861, file: !3, line: 1881, column: 5)
!3865 = !DILocation(line: 1881, column: 28, scope: !3864)
!3866 = !DILocation(line: 1881, column: 26, scope: !3864)
!3867 = !DILocation(line: 1881, column: 41, scope: !3864)
!3868 = !DILocation(line: 1881, column: 44, scope: !3864)
!3869 = !DILocation(line: 1881, column: 47, scope: !3864)
!3870 = !DILocation(line: 1881, column: 56, scope: !3864)
!3871 = !DILocation(line: 0, scope: !3864)
!3872 = !DILocation(line: 1881, column: 5, scope: !3861)
!3873 = !DILocation(line: 1883, column: 14, scope: !3874)
!3874 = distinct !DILexicalBlock(scope: !3864, file: !3, line: 1883, column: 7)
!3875 = !DILocation(line: 1883, column: 24, scope: !3874)
!3876 = !DILocation(line: 1883, column: 30, scope: !3874)
!3877 = !DILocation(line: 1883, column: 39, scope: !3874)
!3878 = !DILocation(line: 1883, column: 42, scope: !3874)
!3879 = !DILocation(line: 1883, column: 46, scope: !3874)
!3880 = !DILocation(line: 1883, column: 7, scope: !3874)
!3881 = !DILocation(line: 1883, column: 7, scope: !3864)
!3882 = !DILocation(line: 1886, column: 11, scope: !3883)
!3883 = distinct !DILexicalBlock(scope: !3884, file: !3, line: 1886, column: 11)
!3884 = distinct !DILexicalBlock(scope: !3874, file: !3, line: 1884, column: 6)
!3885 = !DILocation(line: 1886, column: 21, scope: !3883)
!3886 = !DILocation(line: 1886, column: 27, scope: !3883)
!3887 = !DILocation(line: 1886, column: 34, scope: !3883)
!3888 = !DILocation(line: 1886, column: 44, scope: !3883)
!3889 = !DILocation(line: 1886, column: 50, scope: !3883)
!3890 = !DILocation(line: 1886, column: 60, scope: !3883)
!3891 = !DILocation(line: 1886, column: 32, scope: !3883)
!3892 = !DILocation(line: 1886, column: 11, scope: !3884)
!3893 = !DILocation(line: 1887, column: 3, scope: !3883)
!3894 = !DILocation(line: 1889, column: 11, scope: !3895)
!3895 = distinct !DILexicalBlock(scope: !3884, file: !3, line: 1889, column: 11)
!3896 = !DILocation(line: 1889, column: 21, scope: !3895)
!3897 = !DILocation(line: 1889, column: 27, scope: !3895)
!3898 = !DILocation(line: 1889, column: 34, scope: !3895)
!3899 = !DILocation(line: 1889, column: 44, scope: !3895)
!3900 = !DILocation(line: 1889, column: 50, scope: !3895)
!3901 = !DILocation(line: 1889, column: 32, scope: !3895)
!3902 = !DILocation(line: 1889, column: 11, scope: !3884)
!3903 = !DILocation(line: 1890, column: 3, scope: !3895)
!3904 = !DILocation(line: 1891, column: 11, scope: !3905)
!3905 = distinct !DILexicalBlock(scope: !3884, file: !3, line: 1891, column: 11)
!3906 = !DILocation(line: 1891, column: 21, scope: !3905)
!3907 = !DILocation(line: 1891, column: 27, scope: !3905)
!3908 = !DILocation(line: 1891, column: 39, scope: !3905)
!3909 = !DILocation(line: 1891, column: 11, scope: !3884)
!3910 = !DILocation(line: 1893, column: 3, scope: !3911)
!3911 = distinct !DILexicalBlock(scope: !3905, file: !3, line: 1892, column: 3)
!3912 = !DILocation(line: 1894, column: 3, scope: !3911)
!3913 = !DILocation(line: 1894, column: 13, scope: !3911)
!3914 = !DILocation(line: 1894, column: 19, scope: !3911)
!3915 = !DILocation(line: 1894, column: 31, scope: !3911)
!3916 = !DILocation(line: 1895, column: 3, scope: !3911)
!3917 = !DILocation(line: 1896, column: 32, scope: !3884)
!3918 = !DILocation(line: 1896, column: 6, scope: !3884)
!3919 = !DILocation(line: 1896, column: 9, scope: !3884)
!3920 = !DILocation(line: 1896, column: 15, scope: !3884)
!3921 = !DILocation(line: 1896, column: 18, scope: !3884)
!3922 = !DILocation(line: 1896, column: 26, scope: !3884)
!3923 = !DILocation(line: 1896, column: 30, scope: !3884)
!3924 = !DILocation(line: 1897, column: 8, scope: !3884)
!3925 = !DILocation(line: 1897, column: 18, scope: !3884)
!3926 = !DILocation(line: 1897, column: 24, scope: !3884)
!3927 = !DILocation(line: 1897, column: 6, scope: !3884)
!3928 = !DILocation(line: 1898, column: 10, scope: !3884)
!3929 = !DILocation(line: 1898, column: 20, scope: !3884)
!3930 = !DILocation(line: 1898, column: 26, scope: !3884)
!3931 = !DILocation(line: 1898, column: 38, scope: !3884)
!3932 = !DILocation(line: 1898, column: 48, scope: !3884)
!3933 = !DILocation(line: 1898, column: 54, scope: !3884)
!3934 = !DILocation(line: 1898, column: 36, scope: !3884)
!3935 = !DILocation(line: 1898, column: 8, scope: !3884)
!3936 = !DILocation(line: 1899, column: 11, scope: !3937)
!3937 = distinct !DILexicalBlock(scope: !3884, file: !3, line: 1899, column: 11)
!3938 = !DILocation(line: 1899, column: 14, scope: !3937)
!3939 = !DILocation(line: 1899, column: 24, scope: !3937)
!3940 = !DILocation(line: 1899, column: 11, scope: !3884)
!3941 = !DILocation(line: 1900, column: 18, scope: !3937)
!3942 = !DILocation(line: 1900, column: 3, scope: !3937)
!3943 = !DILocation(line: 1900, column: 6, scope: !3937)
!3944 = !DILocation(line: 1900, column: 16, scope: !3937)
!3945 = !DILocation(line: 1902, column: 18, scope: !3937)
!3946 = !DILocation(line: 1902, column: 3, scope: !3937)
!3947 = !DILocation(line: 1902, column: 6, scope: !3937)
!3948 = !DILocation(line: 1902, column: 16, scope: !3937)
!3949 = !DILocation(line: 1903, column: 10, scope: !3884)
!3950 = !DILocation(line: 1903, column: 20, scope: !3884)
!3951 = !DILocation(line: 1903, column: 26, scope: !3884)
!3952 = !DILocation(line: 1903, column: 8, scope: !3884)
!3953 = !DILocation(line: 1904, column: 11, scope: !3954)
!3954 = distinct !DILexicalBlock(scope: !3884, file: !3, line: 1904, column: 11)
!3955 = !DILocation(line: 1904, column: 14, scope: !3954)
!3956 = !DILocation(line: 1904, column: 24, scope: !3954)
!3957 = !DILocation(line: 1904, column: 11, scope: !3884)
!3958 = !DILocation(line: 1905, column: 18, scope: !3954)
!3959 = !DILocation(line: 1905, column: 3, scope: !3954)
!3960 = !DILocation(line: 1905, column: 6, scope: !3954)
!3961 = !DILocation(line: 1905, column: 16, scope: !3954)
!3962 = !DILocation(line: 1907, column: 18, scope: !3954)
!3963 = !DILocation(line: 1907, column: 3, scope: !3954)
!3964 = !DILocation(line: 1907, column: 6, scope: !3954)
!3965 = !DILocation(line: 1907, column: 16, scope: !3954)
!3966 = !DILocation(line: 1908, column: 6, scope: !3884)
!3967 = !DILocation(line: 1883, column: 59, scope: !3874)
!3968 = !DILocation(line: 1882, column: 4, scope: !3864)
!3969 = !DILocation(line: 1881, column: 5, scope: !3864)
!3970 = distinct !{!3970, !3872, !3971}
!3971 = !DILocation(line: 1908, column: 6, scope: !3861)
!3972 = !DILocation(line: 1909, column: 5, scope: !3842)
!3973 = !DILocation(line: 1910, column: 5, scope: !3842)
!3974 = distinct !DISubprogram(name: "wakeup_connection", scope: !3, file: !3, line: 2096, type: !227, scopeLine: 2097, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!3975 = !DILocalVariable(name: "client_data", arg: 1, scope: !3974, file: !3, line: 2096, type: !229)
!3976 = !DILocation(line: 2096, column: 31, scope: !3974)
!3977 = !DILocalVariable(name: "nowP", arg: 2, scope: !3974, file: !3, line: 2096, type: !211)
!3978 = !DILocation(line: 2096, column: 60, scope: !3974)
!3979 = !DILocalVariable(name: "c", scope: !3974, file: !3, line: 2098, type: !248)
!3980 = !DILocation(line: 2098, column: 17, scope: !3974)
!3981 = !DILocation(line: 2100, column: 35, scope: !3974)
!3982 = !DILocation(line: 2100, column: 9, scope: !3974)
!3983 = !DILocation(line: 2100, column: 7, scope: !3974)
!3984 = !DILocation(line: 2101, column: 5, scope: !3974)
!3985 = !DILocation(line: 2101, column: 8, scope: !3974)
!3986 = !DILocation(line: 2101, column: 21, scope: !3974)
!3987 = !DILocation(line: 2102, column: 10, scope: !3988)
!3988 = distinct !DILexicalBlock(scope: !3974, file: !3, line: 2102, column: 10)
!3989 = !DILocation(line: 2102, column: 13, scope: !3988)
!3990 = !DILocation(line: 2102, column: 24, scope: !3988)
!3991 = !DILocation(line: 2102, column: 10, scope: !3974)
!3992 = !DILocation(line: 2104, column: 2, scope: !3993)
!3993 = distinct !DILexicalBlock(scope: !3988, file: !3, line: 2103, column: 2)
!3994 = !DILocation(line: 2104, column: 5, scope: !3993)
!3995 = !DILocation(line: 2104, column: 16, scope: !3993)
!3996 = !DILocation(line: 2105, column: 18, scope: !3993)
!3997 = !DILocation(line: 2105, column: 21, scope: !3993)
!3998 = !DILocation(line: 2105, column: 25, scope: !3993)
!3999 = !DILocation(line: 2105, column: 34, scope: !3993)
!4000 = !DILocation(line: 2105, column: 2, scope: !3993)
!4001 = !DILocation(line: 2106, column: 2, scope: !3993)
!4002 = !DILocation(line: 2107, column: 5, scope: !3974)
!4003 = distinct !DISubprogram(name: "really_clear_connection", scope: !3, file: !3, line: 2039, type: !2469, scopeLine: 2040, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!4004 = !DILocalVariable(name: "c", arg: 1, scope: !4003, file: !3, line: 2039, type: !248)
!4005 = !DILocation(line: 2039, column: 38, scope: !4003)
!4006 = !DILocalVariable(name: "tvP", arg: 2, scope: !4003, file: !3, line: 2039, type: !211)
!4007 = !DILocation(line: 2039, column: 57, scope: !4003)
!4008 = !DILocation(line: 2041, column: 20, scope: !4003)
!4009 = !DILocation(line: 2041, column: 23, scope: !4003)
!4010 = !DILocation(line: 2041, column: 27, scope: !4003)
!4011 = !DILocation(line: 2041, column: 17, scope: !4003)
!4012 = !DILocation(line: 2042, column: 10, scope: !4013)
!4013 = distinct !DILexicalBlock(scope: !4003, file: !3, line: 2042, column: 10)
!4014 = !DILocation(line: 2042, column: 13, scope: !4013)
!4015 = !DILocation(line: 2042, column: 24, scope: !4013)
!4016 = !DILocation(line: 2042, column: 10, scope: !4003)
!4017 = !DILocation(line: 2043, column: 18, scope: !4013)
!4018 = !DILocation(line: 2043, column: 21, scope: !4013)
!4019 = !DILocation(line: 2043, column: 25, scope: !4013)
!4020 = !DILocation(line: 2043, column: 2, scope: !4013)
!4021 = !DILocation(line: 2044, column: 23, scope: !4003)
!4022 = !DILocation(line: 2044, column: 26, scope: !4003)
!4023 = !DILocation(line: 2044, column: 30, scope: !4003)
!4024 = !DILocation(line: 2044, column: 5, scope: !4003)
!4025 = !DILocation(line: 2045, column: 22, scope: !4003)
!4026 = !DILocation(line: 2045, column: 25, scope: !4003)
!4027 = !DILocation(line: 2045, column: 5, scope: !4003)
!4028 = !DILocation(line: 2046, column: 10, scope: !4029)
!4029 = distinct !DILexicalBlock(scope: !4003, file: !3, line: 2046, column: 10)
!4030 = !DILocation(line: 2046, column: 13, scope: !4029)
!4031 = !DILocation(line: 2046, column: 26, scope: !4029)
!4032 = !DILocation(line: 2046, column: 10, scope: !4003)
!4033 = !DILocation(line: 2048, column: 14, scope: !4034)
!4034 = distinct !DILexicalBlock(scope: !4029, file: !3, line: 2047, column: 2)
!4035 = !DILocation(line: 2048, column: 17, scope: !4034)
!4036 = !DILocation(line: 2048, column: 2, scope: !4034)
!4037 = !DILocation(line: 2049, column: 2, scope: !4034)
!4038 = !DILocation(line: 2049, column: 5, scope: !4034)
!4039 = !DILocation(line: 2049, column: 18, scope: !4034)
!4040 = !DILocation(line: 2050, column: 2, scope: !4034)
!4041 = !DILocation(line: 2051, column: 5, scope: !4003)
!4042 = !DILocation(line: 2051, column: 8, scope: !4003)
!4043 = !DILocation(line: 2051, column: 19, scope: !4003)
!4044 = !DILocation(line: 2052, column: 28, scope: !4003)
!4045 = !DILocation(line: 2052, column: 5, scope: !4003)
!4046 = !DILocation(line: 2052, column: 8, scope: !4003)
!4047 = !DILocation(line: 2052, column: 26, scope: !4003)
!4048 = !DILocation(line: 2053, column: 26, scope: !4003)
!4049 = !DILocation(line: 2053, column: 30, scope: !4003)
!4050 = !DILocation(line: 2053, column: 28, scope: !4003)
!4051 = !DILocation(line: 2053, column: 24, scope: !4003)
!4052 = !DILocation(line: 2054, column: 5, scope: !4003)
!4053 = !DILocation(line: 2055, column: 5, scope: !4003)
!4054 = distinct !DISubprogram(name: "clear_throttles", scope: !3, file: !3, line: 1914, type: !2469, scopeLine: 1915, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!4055 = !DILocalVariable(name: "c", arg: 1, scope: !4054, file: !3, line: 1914, type: !248)
!4056 = !DILocation(line: 1914, column: 30, scope: !4054)
!4057 = !DILocalVariable(name: "tvP", arg: 2, scope: !4054, file: !3, line: 1914, type: !211)
!4058 = !DILocation(line: 1914, column: 49, scope: !4054)
!4059 = !DILocalVariable(name: "tind", scope: !4054, file: !3, line: 1916, type: !26)
!4060 = !DILocation(line: 1916, column: 9, scope: !4054)
!4061 = !DILocation(line: 1918, column: 16, scope: !4062)
!4062 = distinct !DILexicalBlock(scope: !4054, file: !3, line: 1918, column: 5)
!4063 = !DILocation(line: 1918, column: 11, scope: !4062)
!4064 = !DILocation(line: 1918, column: 21, scope: !4065)
!4065 = distinct !DILexicalBlock(scope: !4062, file: !3, line: 1918, column: 5)
!4066 = !DILocation(line: 1918, column: 28, scope: !4065)
!4067 = !DILocation(line: 1918, column: 31, scope: !4065)
!4068 = !DILocation(line: 1918, column: 26, scope: !4065)
!4069 = !DILocation(line: 1918, column: 5, scope: !4062)
!4070 = !DILocation(line: 1919, column: 4, scope: !4065)
!4071 = !DILocation(line: 1919, column: 14, scope: !4065)
!4072 = !DILocation(line: 1919, column: 17, scope: !4065)
!4073 = !DILocation(line: 1919, column: 23, scope: !4065)
!4074 = !DILocation(line: 1919, column: 30, scope: !4065)
!4075 = !DILocation(line: 1919, column: 2, scope: !4065)
!4076 = !DILocation(line: 1918, column: 41, scope: !4065)
!4077 = !DILocation(line: 1918, column: 5, scope: !4065)
!4078 = distinct !{!4078, !4069, !4079}
!4079 = !DILocation(line: 1919, column: 30, scope: !4062)
!4080 = !DILocation(line: 1920, column: 5, scope: !4054)
!4081 = distinct !DISubprogram(name: "linger_clear_connection", scope: !3, file: !3, line: 2110, type: !227, scopeLine: 2111, flags: DIFlagPrototyped, spFlags: DISPFlagLocalToUnit | DISPFlagDefinition, unit: !2, retainedNodes: !4)
!4082 = !DILocalVariable(name: "client_data", arg: 1, scope: !4081, file: !3, line: 2110, type: !229)
!4083 = !DILocation(line: 2110, column: 37, scope: !4081)
!4084 = !DILocalVariable(name: "nowP", arg: 2, scope: !4081, file: !3, line: 2110, type: !211)
!4085 = !DILocation(line: 2110, column: 66, scope: !4081)
!4086 = !DILocalVariable(name: "c", scope: !4081, file: !3, line: 2112, type: !248)
!4087 = !DILocation(line: 2112, column: 17, scope: !4081)
!4088 = !DILocation(line: 2114, column: 35, scope: !4081)
!4089 = !DILocation(line: 2114, column: 9, scope: !4081)
!4090 = !DILocation(line: 2114, column: 7, scope: !4081)
!4091 = !DILocation(line: 2115, column: 5, scope: !4081)
!4092 = !DILocation(line: 2115, column: 8, scope: !4081)
!4093 = !DILocation(line: 2115, column: 21, scope: !4081)
!4094 = !DILocation(line: 2116, column: 30, scope: !4081)
!4095 = !DILocation(line: 2116, column: 33, scope: !4081)
!4096 = !DILocation(line: 2116, column: 5, scope: !4081)
!4097 = !DILocation(line: 2117, column: 5, scope: !4081)
