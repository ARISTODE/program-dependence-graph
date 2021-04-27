; ModuleID = 'example.bc'
source_filename = "example.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@greeter.sample = internal global i32 1, align 4, !dbg !0
@.str = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c", welcome!\0A\00", align 1
@key = common dso_local global i8* null, align 8, !dbg !14
@i = internal global i32 0, align 4, !dbg !18
@ciphertext = common dso_local global i8* null, align 8, !dbg !16
@.str.2 = private unnamed_addr constant [10 x i8] c"green\00", section "llvm.metadata"
@.str.3 = private unnamed_addr constant [10 x i8] c"example.c\00", section "llvm.metadata"
@.str.4 = private unnamed_addr constant [13 x i8] c"orange\00", section "llvm.metadata"
@.str.5 = private unnamed_addr constant [17 x i8] c"Enter username: \00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c"%19s\00", align 1
@.str.7 = private unnamed_addr constant [18 x i8] c"Enter plaintext: \00", align 1
@.str.8 = private unnamed_addr constant [7 x i8] c"%1023s\00", align 1
@.str.9 = private unnamed_addr constant [14 x i8] c"Cipher text: \00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"%x \00", align 1
@.str.11 = private unnamed_addr constant [22 x i8] c"encryption length: %d\00", align 1
@.str.12 = private unnamed_addr constant [7 x i8] c"blue\00", section "llvm.metadata"
@llvm.global.annotations = appending global [2 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (i32 (i8*, i32)* @encrypt to i8*), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i32 23 }, { i8*, i8*, i8*, i32 } { i8* bitcast (i8** @key to i8*), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i32 5 }], section "llvm.metadata"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @greeter(i8* %0, i32* %1) #0 !dbg !2 {
  %3 = alloca i8*, align 8
  %4 = alloca i32*, align 8
  %5 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !25, metadata !DIExpression()), !dbg !26
  store i32* %1, i32** %4, align 8
  call void @llvm.dbg.declare(metadata i32** %4, metadata !27, metadata !DIExpression()), !dbg !28
  call void @llvm.dbg.declare(metadata i8** %5, metadata !29, metadata !DIExpression()), !dbg !30
  %6 = load i8*, i8** %3, align 8, !dbg !31
  store i8* %6, i8** %5, align 8, !dbg !30
  %7 = load i8*, i8** %5, align 8, !dbg !32
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i8* %7), !dbg !33
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i64 0, i64 0)), !dbg !34
  %10 = load i32*, i32** %4, align 8, !dbg !35
  store i32 15, i32* %10, align 4, !dbg !36
  ret void, !dbg !37
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @initkey(i32 %0) #0 !dbg !38 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !41, metadata !DIExpression()), !dbg !42
  %3 = load i32, i32* %2, align 4, !dbg !43
  %4 = sext i32 %3 to i64, !dbg !43
  %5 = call noalias i8* @malloc(i64 %4) #6, !dbg !44
  store i8* %5, i8** @key, align 8, !dbg !45
  store i32 0, i32* @i, align 4, !dbg !46
  br label %6, !dbg !48

6:                                                ; preds = %15, %1
  %7 = load i32, i32* @i, align 4, !dbg !49
  %8 = load i32, i32* %2, align 4, !dbg !51
  %9 = icmp ult i32 %7, %8, !dbg !52
  br i1 %9, label %10, label %18, !dbg !53

10:                                               ; preds = %6
  %11 = load i8*, i8** @key, align 8, !dbg !54
  %12 = load i32, i32* @i, align 4, !dbg !55
  %13 = zext i32 %12 to i64, !dbg !54
  %14 = getelementptr inbounds i8, i8* %11, i64 %13, !dbg !54
  store i8 1, i8* %14, align 1, !dbg !56
  br label %15, !dbg !54

15:                                               ; preds = %10
  %16 = load i32, i32* @i, align 4, !dbg !57
  %17 = add i32 %16, 1, !dbg !57
  store i32 %17, i32* @i, align 4, !dbg !57
  br label %6, !dbg !58, !llvm.loop !59

18:                                               ; preds = %6
  ret void, !dbg !61
}

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #3

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @encrypt(i8* %0, i32 %1) #0 !dbg !62 {
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  call void @llvm.dbg.declare(metadata i8** %3, metadata !65, metadata !DIExpression()), !dbg !66
  store i32 %1, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !67, metadata !DIExpression()), !dbg !68
  %5 = load i32, i32* %4, align 4, !dbg !69
  %6 = sext i32 %5 to i64, !dbg !69
  %7 = call noalias i8* @malloc(i64 %6) #6, !dbg !70
  store i8* %7, i8** @ciphertext, align 8, !dbg !71
  store i32 0, i32* @i, align 4, !dbg !72
  br label %8, !dbg !74

8:                                                ; preds = %31, %2
  %9 = load i32, i32* @i, align 4, !dbg !75
  %10 = load i32, i32* %4, align 4, !dbg !77
  %11 = icmp ult i32 %9, %10, !dbg !78
  br i1 %11, label %12, label %34, !dbg !79

12:                                               ; preds = %8
  %13 = load i8*, i8** %3, align 8, !dbg !80
  %14 = load i32, i32* @i, align 4, !dbg !81
  %15 = zext i32 %14 to i64, !dbg !80
  %16 = getelementptr inbounds i8, i8* %13, i64 %15, !dbg !80
  %17 = load i8, i8* %16, align 1, !dbg !80
  %18 = sext i8 %17 to i32, !dbg !80
  %19 = load i8*, i8** @key, align 8, !dbg !82
  %20 = load i32, i32* @i, align 4, !dbg !83
  %21 = zext i32 %20 to i64, !dbg !82
  %22 = getelementptr inbounds i8, i8* %19, i64 %21, !dbg !82
  %23 = load i8, i8* %22, align 1, !dbg !82
  %24 = sext i8 %23 to i32, !dbg !82
  %25 = xor i32 %18, %24, !dbg !84
  %26 = trunc i32 %25 to i8, !dbg !80
  %27 = load i8*, i8** @ciphertext, align 8, !dbg !85
  %28 = load i32, i32* @i, align 4, !dbg !86
  %29 = zext i32 %28 to i64, !dbg !85
  %30 = getelementptr inbounds i8, i8* %27, i64 %29, !dbg !85
  store i8 %26, i8* %30, align 1, !dbg !87
  br label %31, !dbg !85

31:                                               ; preds = %12
  %32 = load i32, i32* @i, align 4, !dbg !88
  %33 = add i32 %32, 1, !dbg !88
  store i32 %33, i32* @i, align 4, !dbg !88
  br label %8, !dbg !89, !llvm.loop !90

34:                                               ; preds = %8
  %35 = load i32, i32* %4, align 4, !dbg !92
  ret i32 %35, !dbg !93
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !94 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca [20 x i8], align 16
  %4 = alloca [1024 x i8], align 16
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !97, metadata !DIExpression()), !dbg !98
  store i32 10, i32* %2, align 4, !dbg !98
  call void @llvm.dbg.declare(metadata [20 x i8]* %3, metadata !99, metadata !DIExpression()), !dbg !103
  %6 = bitcast [20 x i8]* %3 to i8*, !dbg !104
  call void @llvm.var.annotation(i8* %6, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i32 32), !dbg !104
  call void @llvm.dbg.declare(metadata [1024 x i8]* %4, metadata !105, metadata !DIExpression()), !dbg !109
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.5, i64 0, i64 0)), !dbg !110
  %8 = getelementptr inbounds [20 x i8], [20 x i8]* %3, i64 0, i64 0, !dbg !111
  %9 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i64 0, i64 0), i8* %8), !dbg !112
  %10 = getelementptr inbounds [20 x i8], [20 x i8]* %3, i64 0, i64 0, !dbg !113
  call void @greeter(i8* %10, i32* %2), !dbg !114
  %11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.7, i64 0, i64 0)), !dbg !115
  %12 = getelementptr inbounds [1024 x i8], [1024 x i8]* %4, i64 0, i64 0, !dbg !116
  %13 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.8, i64 0, i64 0), i8* %12), !dbg !117
  %14 = getelementptr inbounds [1024 x i8], [1024 x i8]* %4, i64 0, i64 0, !dbg !118
  %15 = call i64 @strlen(i8* %14) #7, !dbg !119
  %16 = trunc i64 %15 to i32, !dbg !119
  call void @initkey(i32 %16), !dbg !120
  call void @llvm.dbg.declare(metadata i32* %5, metadata !121, metadata !DIExpression()), !dbg !122
  %17 = getelementptr inbounds [1024 x i8], [1024 x i8]* %4, i64 0, i64 0, !dbg !123
  %18 = getelementptr inbounds [1024 x i8], [1024 x i8]* %4, i64 0, i64 0, !dbg !124
  %19 = call i64 @strlen(i8* %18) #7, !dbg !125
  %20 = trunc i64 %19 to i32, !dbg !125
  %21 = call i32 @encrypt(i8* %17, i32 %20), !dbg !126
  store i32 %21, i32* %5, align 4, !dbg !122
  %22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i64 0, i64 0)), !dbg !127
  store i32 0, i32* @i, align 4, !dbg !128
  br label %23, !dbg !130

23:                                               ; preds = %37, %0
  %24 = load i32, i32* @i, align 4, !dbg !131
  %25 = zext i32 %24 to i64, !dbg !131
  %26 = getelementptr inbounds [1024 x i8], [1024 x i8]* %4, i64 0, i64 0, !dbg !133
  %27 = call i64 @strlen(i8* %26) #7, !dbg !134
  %28 = icmp ult i64 %25, %27, !dbg !135
  br i1 %28, label %29, label %40, !dbg !136

29:                                               ; preds = %23
  %30 = load i8*, i8** @ciphertext, align 8, !dbg !137
  %31 = load i32, i32* @i, align 4, !dbg !138
  %32 = zext i32 %31 to i64, !dbg !137
  %33 = getelementptr inbounds i8, i8* %30, i64 %32, !dbg !137
  %34 = load i8, i8* %33, align 1, !dbg !137
  %35 = sext i8 %34 to i32, !dbg !137
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i64 0, i64 0), i32 %35), !dbg !139
  br label %37, !dbg !139

37:                                               ; preds = %29
  %38 = load i32, i32* @i, align 4, !dbg !140
  %39 = add i32 %38, 1, !dbg !140
  store i32 %39, i32* @i, align 4, !dbg !140
  br label %23, !dbg !141, !llvm.loop !142

40:                                               ; preds = %23
  %41 = load i32, i32* %5, align 4, !dbg !144
  %42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.11, i64 0, i64 0), i32 %41), !dbg !145
  ret i32 0, !dbg !146
}

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #4

declare dso_local i32 @__isoc99_scanf(i8*, ...) #2

; Function Attrs: nounwind readonly
declare dso_local i64 @strlen(i8*) #5

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind willreturn }
attributes #5 = { nounwind readonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!10}
!llvm.module.flags = !{!21, !22, !23}
!llvm.ident = !{!24}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "sample", scope: !2, file: !3, line: 11, type: !9, isLocal: true, isDefinition: true)
!2 = distinct !DISubprogram(name: "greeter", scope: !3, file: !3, line: 9, type: !4, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !10, retainedNodes: !11)
!3 = !DIFile(filename: "example.c", directory: "/home/rbrotzman/pdg/program-dependence-graph/Edge_Specification")
!4 = !DISubroutineType(types: !5)
!5 = !{null, !6, !8}
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!7 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.1 (https://github.com/gaps-closure/llvm-project 4954dd8b02af91d5e8d4815824208b6004f667a8)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !11, retainedTypes: !12, globals: !13, splitDebugInlining: false, nameTableKind: None)
!11 = !{}
!12 = !{!6}
!13 = !{!0, !14, !16, !18}
!14 = !DIGlobalVariableExpression(var: !15, expr: !DIExpression())
!15 = distinct !DIGlobalVariable(name: "key", scope: !10, file: !3, line: 5, type: !6, isLocal: false, isDefinition: true)
!16 = !DIGlobalVariableExpression(var: !17, expr: !DIExpression())
!17 = distinct !DIGlobalVariable(name: "ciphertext", scope: !10, file: !3, line: 6, type: !6, isLocal: false, isDefinition: true)
!18 = !DIGlobalVariableExpression(var: !19, expr: !DIExpression())
!19 = distinct !DIGlobalVariable(name: "i", scope: !10, file: !3, line: 7, type: !20, isLocal: true, isDefinition: true)
!20 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!21 = !{i32 7, !"Dwarf Version", i32 4}
!22 = !{i32 2, !"Debug Info Version", i32 3}
!23 = !{i32 1, !"wchar_size", i32 4}
!24 = !{!"clang version 10.0.1 (https://github.com/gaps-closure/llvm-project 4954dd8b02af91d5e8d4815824208b6004f667a8)"}
!25 = !DILocalVariable(name: "str", arg: 1, scope: !2, file: !3, line: 9, type: !6)
!26 = !DILocation(line: 9, column: 21, scope: !2)
!27 = !DILocalVariable(name: "s", arg: 2, scope: !2, file: !3, line: 9, type: !8)
!28 = !DILocation(line: 9, column: 31, scope: !2)
!29 = !DILocalVariable(name: "p", scope: !2, file: !3, line: 10, type: !6)
!30 = !DILocation(line: 10, column: 11, scope: !2)
!31 = !DILocation(line: 10, column: 15, scope: !2)
!32 = !DILocation(line: 12, column: 20, scope: !2)
!33 = !DILocation(line: 12, column: 5, scope: !2)
!34 = !DILocation(line: 13, column: 5, scope: !2)
!35 = !DILocation(line: 14, column: 6, scope: !2)
!36 = !DILocation(line: 14, column: 8, scope: !2)
!37 = !DILocation(line: 15, column: 1, scope: !2)
!38 = distinct !DISubprogram(name: "initkey", scope: !3, file: !3, line: 17, type: !39, scopeLine: 17, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !10, retainedNodes: !11)
!39 = !DISubroutineType(types: !40)
!40 = !{null, !9}
!41 = !DILocalVariable(name: "sz", arg: 1, scope: !38, file: !3, line: 17, type: !9)
!42 = !DILocation(line: 17, column: 19, scope: !38)
!43 = !DILocation(line: 18, column: 26, scope: !38)
!44 = !DILocation(line: 18, column: 18, scope: !38)
!45 = !DILocation(line: 18, column: 6, scope: !38)
!46 = !DILocation(line: 20, column: 8, scope: !47)
!47 = distinct !DILexicalBlock(scope: !38, file: !3, line: 20, column: 2)
!48 = !DILocation(line: 20, column: 7, scope: !47)
!49 = !DILocation(line: 20, column: 12, scope: !50)
!50 = distinct !DILexicalBlock(scope: !47, file: !3, line: 20, column: 2)
!51 = !DILocation(line: 20, column: 14, scope: !50)
!52 = !DILocation(line: 20, column: 13, scope: !50)
!53 = !DILocation(line: 20, column: 2, scope: !47)
!54 = !DILocation(line: 20, column: 23, scope: !50)
!55 = !DILocation(line: 20, column: 27, scope: !50)
!56 = !DILocation(line: 20, column: 29, scope: !50)
!57 = !DILocation(line: 20, column: 19, scope: !50)
!58 = !DILocation(line: 20, column: 2, scope: !50)
!59 = distinct !{!59, !53, !60}
!60 = !DILocation(line: 20, column: 31, scope: !47)
!61 = !DILocation(line: 21, column: 1, scope: !38)
!62 = distinct !DISubprogram(name: "encrypt", scope: !3, file: !3, line: 23, type: !63, scopeLine: 23, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !10, retainedNodes: !11)
!63 = !DISubroutineType(types: !64)
!64 = !{!9, !6, !9}
!65 = !DILocalVariable(name: "plaintext", arg: 1, scope: !62, file: !3, line: 23, type: !6)
!66 = !DILocation(line: 23, column: 59, scope: !62)
!67 = !DILocalVariable(name: "sz", arg: 2, scope: !62, file: !3, line: 23, type: !9)
!68 = !DILocation(line: 23, column: 74, scope: !62)
!69 = !DILocation(line: 24, column: 33, scope: !62)
!70 = !DILocation(line: 24, column: 25, scope: !62)
!71 = !DILocation(line: 24, column: 13, scope: !62)
!72 = !DILocation(line: 25, column: 8, scope: !73)
!73 = distinct !DILexicalBlock(scope: !62, file: !3, line: 25, column: 2)
!74 = !DILocation(line: 25, column: 7, scope: !73)
!75 = !DILocation(line: 25, column: 12, scope: !76)
!76 = distinct !DILexicalBlock(scope: !73, file: !3, line: 25, column: 2)
!77 = !DILocation(line: 25, column: 14, scope: !76)
!78 = !DILocation(line: 25, column: 13, scope: !76)
!79 = !DILocation(line: 25, column: 2, scope: !73)
!80 = !DILocation(line: 26, column: 17, scope: !76)
!81 = !DILocation(line: 26, column: 27, scope: !76)
!82 = !DILocation(line: 26, column: 32, scope: !76)
!83 = !DILocation(line: 26, column: 36, scope: !76)
!84 = !DILocation(line: 26, column: 30, scope: !76)
!85 = !DILocation(line: 26, column: 3, scope: !76)
!86 = !DILocation(line: 26, column: 14, scope: !76)
!87 = !DILocation(line: 26, column: 16, scope: !76)
!88 = !DILocation(line: 25, column: 19, scope: !76)
!89 = !DILocation(line: 25, column: 2, scope: !76)
!90 = distinct !{!90, !79, !91}
!91 = !DILocation(line: 26, column: 37, scope: !73)
!92 = !DILocation(line: 27, column: 12, scope: !62)
!93 = !DILocation(line: 27, column: 5, scope: !62)
!94 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 30, type: !95, scopeLine: 30, spFlags: DISPFlagDefinition, unit: !10, retainedNodes: !11)
!95 = !DISubroutineType(types: !96)
!96 = !{!9}
!97 = !DILocalVariable(name: "age", scope: !94, file: !3, line: 31, type: !9)
!98 = !DILocation(line: 31, column: 9, scope: !94)
!99 = !DILocalVariable(name: "username", scope: !94, file: !3, line: 32, type: !100)
!100 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 160, elements: !101)
!101 = !{!102}
!102 = !DISubrange(count: 20)
!103 = !DILocation(line: 32, column: 48, scope: !94)
!104 = !DILocation(line: 32, column: 2, scope: !94)
!105 = !DILocalVariable(name: "text", scope: !94, file: !3, line: 33, type: !106)
!106 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 8192, elements: !107)
!107 = !{!108}
!108 = !DISubrange(count: 1024)
!109 = !DILocation(line: 33, column: 10, scope: !94)
!110 = !DILocation(line: 34, column: 2, scope: !94)
!111 = !DILocation(line: 35, column: 15, scope: !94)
!112 = !DILocation(line: 35, column: 2, scope: !94)
!113 = !DILocation(line: 36, column: 10, scope: !94)
!114 = !DILocation(line: 36, column: 2, scope: !94)
!115 = !DILocation(line: 37, column: 2, scope: !94)
!116 = !DILocation(line: 38, column: 17, scope: !94)
!117 = !DILocation(line: 38, column: 2, scope: !94)
!118 = !DILocation(line: 40, column: 17, scope: !94)
!119 = !DILocation(line: 40, column: 10, scope: !94)
!120 = !DILocation(line: 40, column: 2, scope: !94)
!121 = !DILocalVariable(name: "sz", scope: !94, file: !3, line: 41, type: !9)
!122 = !DILocation(line: 41, column: 6, scope: !94)
!123 = !DILocation(line: 41, column: 19, scope: !94)
!124 = !DILocation(line: 41, column: 32, scope: !94)
!125 = !DILocation(line: 41, column: 25, scope: !94)
!126 = !DILocation(line: 41, column: 11, scope: !94)
!127 = !DILocation(line: 42, column: 2, scope: !94)
!128 = !DILocation(line: 43, column: 8, scope: !129)
!129 = distinct !DILexicalBlock(scope: !94, file: !3, line: 43, column: 2)
!130 = !DILocation(line: 43, column: 7, scope: !129)
!131 = !DILocation(line: 43, column: 12, scope: !132)
!132 = distinct !DILexicalBlock(scope: !129, file: !3, line: 43, column: 2)
!133 = !DILocation(line: 43, column: 21, scope: !132)
!134 = !DILocation(line: 43, column: 14, scope: !132)
!135 = !DILocation(line: 43, column: 13, scope: !132)
!136 = !DILocation(line: 43, column: 2, scope: !129)
!137 = !DILocation(line: 44, column: 16, scope: !132)
!138 = !DILocation(line: 44, column: 27, scope: !132)
!139 = !DILocation(line: 44, column: 3, scope: !132)
!140 = !DILocation(line: 43, column: 29, scope: !132)
!141 = !DILocation(line: 43, column: 2, scope: !132)
!142 = distinct !{!142, !136, !143}
!143 = !DILocation(line: 44, column: 29, scope: !129)
!144 = !DILocation(line: 45, column: 37, scope: !94)
!145 = !DILocation(line: 45, column: 5, scope: !94)
!146 = !DILocation(line: 46, column: 5, scope: !94)
