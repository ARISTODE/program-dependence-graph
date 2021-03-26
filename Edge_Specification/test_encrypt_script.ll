; ModuleID = 'test_encrypt_script.c'
source_filename = "test_encrypt_script.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

@.str = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c", welcome!\0A\00", align 1
@key = common global i8* null, align 8, !dbg !0
@i = common global i32 0, align 4, !dbg !11
@ciphertext = common global i8* null, align 8, !dbg !9
@.str.2 = private unnamed_addr constant [10 x i8] c"sensitive\00", section "llvm.metadata"
@.str.3 = private unnamed_addr constant [22 x i8] c"test_encrypt_script.c\00", section "llvm.metadata"
@.str.4 = private unnamed_addr constant [17 x i8] c"Enter username: \00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"%19s\00", align 1
@.str.6 = private unnamed_addr constant [18 x i8] c"Enter plaintext: \00", align 1
@.str.7 = private unnamed_addr constant [7 x i8] c"%1023s\00", align 1
@.str.8 = private unnamed_addr constant [14 x i8] c"Cipher text: \00", align 1
@.str.9 = private unnamed_addr constant [4 x i8] c"%x \00", align 1
@.str.10 = private unnamed_addr constant [22 x i8] c"encryption length: %d\00", align 1
@llvm.global.annotations = appending global [1 x { i8*, i8*, i8*, i32 }] [{ i8*, i8*, i8*, i32 } { i8* bitcast (i8** @key to i8*), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.3, i32 0, i32 0), i32 5 }], section "llvm.metadata"

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @greeter(i8* %str, i32* %s) #0 !dbg !19 {
entry:
  %str.addr = alloca i8*, align 8
  %s.addr = alloca i32*, align 8
  %p = alloca i8*, align 8
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !24, metadata !DIExpression()), !dbg !25
  store i32* %s, i32** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %s.addr, metadata !26, metadata !DIExpression()), !dbg !27
  call void @llvm.dbg.declare(metadata i8** %p, metadata !28, metadata !DIExpression()), !dbg !29
  %0 = load i8*, i8** %str.addr, align 8, !dbg !30
  store i8* %0, i8** %p, align 8, !dbg !29
  %1 = load i8*, i8** %p, align 8, !dbg !31
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i8* %1), !dbg !32
  %call1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i64 0, i64 0)), !dbg !33
  %2 = load i32*, i32** %s.addr, align 8, !dbg !34
  store i32 15, i32* %2, align 4, !dbg !35
  ret void, !dbg !36
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @initkey(i32 %sz) #0 !dbg !37 {
entry:
  %sz.addr = alloca i32, align 4
  store i32 %sz, i32* %sz.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sz.addr, metadata !40, metadata !DIExpression()), !dbg !41
  %0 = load i32, i32* %sz.addr, align 4, !dbg !42
  %conv = sext i32 %0 to i64, !dbg !42
  %call = call i8* @malloc(i64 %conv) #5, !dbg !43
  store i8* %call, i8** @key, align 8, !dbg !44
  store i32 0, i32* @i, align 4, !dbg !45
  br label %for.cond, !dbg !47

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, i32* @i, align 4, !dbg !48
  %2 = load i32, i32* %sz.addr, align 4, !dbg !50
  %cmp = icmp ult i32 %1, %2, !dbg !51
  br i1 %cmp, label %for.body, label %for.end, !dbg !52

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** @key, align 8, !dbg !53
  %4 = load i32, i32* @i, align 4, !dbg !54
  %idxprom = zext i32 %4 to i64, !dbg !53
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %idxprom, !dbg !53
  store i8 1, i8* %arrayidx, align 1, !dbg !55
  br label %for.inc, !dbg !53

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* @i, align 4, !dbg !56
  %inc = add i32 %5, 1, !dbg !56
  store i32 %inc, i32* @i, align 4, !dbg !56
  br label %for.cond, !dbg !57, !llvm.loop !58

for.end:                                          ; preds = %for.cond
  ret void, !dbg !60
}

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @encrypt(i8* %plaintext, i32 %sz) #0 !dbg !61 {
entry:
  %plaintext.addr = alloca i8*, align 8
  %sz.addr = alloca i32, align 4
  store i8* %plaintext, i8** %plaintext.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %plaintext.addr, metadata !64, metadata !DIExpression()), !dbg !65
  store i32 %sz, i32* %sz.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sz.addr, metadata !66, metadata !DIExpression()), !dbg !67
  %0 = load i32, i32* %sz.addr, align 4, !dbg !68
  %conv = sext i32 %0 to i64, !dbg !68
  %call = call i8* @malloc(i64 %conv) #5, !dbg !69
  store i8* %call, i8** @ciphertext, align 8, !dbg !70
  store i32 0, i32* @i, align 4, !dbg !71
  br label %for.cond, !dbg !73

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i32, i32* @i, align 4, !dbg !74
  %2 = load i32, i32* %sz.addr, align 4, !dbg !76
  %cmp = icmp ult i32 %1, %2, !dbg !77
  br i1 %cmp, label %for.body, label %for.end, !dbg !78

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** %plaintext.addr, align 8, !dbg !79
  %4 = load i32, i32* @i, align 4, !dbg !80
  %idxprom = zext i32 %4 to i64, !dbg !79
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %idxprom, !dbg !79
  %5 = load i8, i8* %arrayidx, align 1, !dbg !79
  %conv2 = sext i8 %5 to i32, !dbg !79
  %6 = load i8*, i8** @key, align 8, !dbg !81
  %7 = load i32, i32* @i, align 4, !dbg !82
  %idxprom3 = zext i32 %7 to i64, !dbg !81
  %arrayidx4 = getelementptr inbounds i8, i8* %6, i64 %idxprom3, !dbg !81
  %8 = load i8, i8* %arrayidx4, align 1, !dbg !81
  %conv5 = sext i8 %8 to i32, !dbg !81
  %xor = xor i32 %conv2, %conv5, !dbg !83
  %conv6 = trunc i32 %xor to i8, !dbg !79
  %9 = load i8*, i8** @ciphertext, align 8, !dbg !84
  %10 = load i32, i32* @i, align 4, !dbg !85
  %idxprom7 = zext i32 %10 to i64, !dbg !84
  %arrayidx8 = getelementptr inbounds i8, i8* %9, i64 %idxprom7, !dbg !84
  store i8 %conv6, i8* %arrayidx8, align 1, !dbg !86
  br label %for.inc, !dbg !84

for.inc:                                          ; preds = %for.body
  %11 = load i32, i32* @i, align 4, !dbg !87
  %inc = add i32 %11, 1, !dbg !87
  store i32 %inc, i32* @i, align 4, !dbg !87
  br label %for.cond, !dbg !88, !llvm.loop !89

for.end:                                          ; preds = %for.cond
  %12 = load i32, i32* %sz.addr, align 4, !dbg !91
  ret i32 %12, !dbg !92
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main() #0 !dbg !93 {
entry:
  %retval = alloca i32, align 4
  %age = alloca i32, align 4
  %username = alloca [20 x i8], align 16
  %text = alloca [1024 x i8], align 16
  %sz = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %age, metadata !96, metadata !DIExpression()), !dbg !97
  store i32 10, i32* %age, align 4, !dbg !97
  call void @llvm.dbg.declare(metadata [20 x i8]* %username, metadata !98, metadata !DIExpression()), !dbg !102
  %username1 = bitcast [20 x i8]* %username to i8*, !dbg !103
  call void @llvm.var.annotation(i8* %username1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.3, i32 0, i32 0), i32 31), !dbg !103
  call void @llvm.dbg.declare(metadata [1024 x i8]* %text, metadata !104, metadata !DIExpression()), !dbg !108
  %text2 = bitcast [1024 x i8]* %text to i8*, !dbg !103
  call void @llvm.var.annotation(i8* %text2, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.3, i32 0, i32 0), i32 31), !dbg !103
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.4, i64 0, i64 0)), !dbg !109
  %arraydecay = getelementptr inbounds [20 x i8], [20 x i8]* %username, i64 0, i64 0, !dbg !110
  %call3 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i64 0, i64 0), i8* %arraydecay), !dbg !111
  %arraydecay4 = getelementptr inbounds [20 x i8], [20 x i8]* %username, i64 0, i64 0, !dbg !112
  call void @greeter(i8* %arraydecay4, i32* %age), !dbg !113
  %call5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i64 0, i64 0)), !dbg !114
  %arraydecay6 = getelementptr inbounds [1024 x i8], [1024 x i8]* %text, i64 0, i64 0, !dbg !115
  %call7 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i64 0, i64 0), i8* %arraydecay6), !dbg !116
  %arraydecay8 = getelementptr inbounds [1024 x i8], [1024 x i8]* %text, i64 0, i64 0, !dbg !117
  %call9 = call i64 @strlen(i8* %arraydecay8), !dbg !118
  %conv = trunc i64 %call9 to i32, !dbg !118
  call void @initkey(i32 %conv), !dbg !119
  call void @llvm.dbg.declare(metadata i32* %sz, metadata !120, metadata !DIExpression()), !dbg !121
  %arraydecay10 = getelementptr inbounds [1024 x i8], [1024 x i8]* %text, i64 0, i64 0, !dbg !122
  %arraydecay11 = getelementptr inbounds [1024 x i8], [1024 x i8]* %text, i64 0, i64 0, !dbg !123
  %call12 = call i64 @strlen(i8* %arraydecay11), !dbg !124
  %conv13 = trunc i64 %call12 to i32, !dbg !124
  %call14 = call i32 @encrypt(i8* %arraydecay10, i32 %conv13), !dbg !125
  store i32 %call14, i32* %sz, align 4, !dbg !121
  %call15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.8, i64 0, i64 0)), !dbg !126
  store i32 0, i32* @i, align 4, !dbg !127
  br label %for.cond, !dbg !129

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* @i, align 4, !dbg !130
  %conv16 = zext i32 %0 to i64, !dbg !130
  %arraydecay17 = getelementptr inbounds [1024 x i8], [1024 x i8]* %text, i64 0, i64 0, !dbg !132
  %call18 = call i64 @strlen(i8* %arraydecay17), !dbg !133
  %cmp = icmp ult i64 %conv16, %call18, !dbg !134
  br i1 %cmp, label %for.body, label %for.end, !dbg !135

for.body:                                         ; preds = %for.cond
  %1 = load i8*, i8** @ciphertext, align 8, !dbg !136
  %2 = load i32, i32* @i, align 4, !dbg !137
  %idxprom = zext i32 %2 to i64, !dbg !136
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 %idxprom, !dbg !136
  %3 = load i8, i8* %arrayidx, align 1, !dbg !136
  %conv20 = sext i8 %3 to i32, !dbg !136
  %call21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i64 0, i64 0), i32 %conv20), !dbg !138
  br label %for.inc, !dbg !138

for.inc:                                          ; preds = %for.body
  %4 = load i32, i32* @i, align 4, !dbg !139
  %inc = add i32 %4, 1, !dbg !139
  store i32 %inc, i32* @i, align 4, !dbg !139
  br label %for.cond, !dbg !140, !llvm.loop !141

for.end:                                          ; preds = %for.cond
  %5 = load i32, i32* %sz, align 4, !dbg !143
  %call22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.10, i64 0, i64 0), i32 %5), !dbg !144
  ret i32 0, !dbg !145
}

; Function Attrs: nounwind willreturn
declare void @llvm.var.annotation(i8*, i8*, i8*, i32) #4

declare i32 @scanf(i8*, ...) #2

declare i64 @strlen(i8*) #2

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { allocsize(0) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind willreturn }
attributes #5 = { allocsize(0) }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!14, !15, !16, !17}
!llvm.ident = !{!18}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "key", scope: !2, file: !3, line: 5, type: !6, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !5, globals: !8, nameTableKind: None)
!3 = !DIFile(filename: "test_encrypt_script.c", directory: "/Users/yongzhehuang/Library/Mobile Documents/com~apple~CloudDocs/Documents/llvm_versions/program-dependence-graph-in-llvm/test/pdg_test")
!4 = !{}
!5 = !{!6}
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!7 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!8 = !{!0, !9, !11}
!9 = !DIGlobalVariableExpression(var: !10, expr: !DIExpression())
!10 = distinct !DIGlobalVariable(name: "ciphertext", scope: !2, file: !3, line: 6, type: !6, isLocal: false, isDefinition: true)
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "i", scope: !2, file: !3, line: 7, type: !13, isLocal: false, isDefinition: true)
!13 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!14 = !{i32 7, !"Dwarf Version", i32 4}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{i32 1, !"wchar_size", i32 4}
!17 = !{i32 7, !"PIC Level", i32 2}
!18 = !{!"clang version 10.0.0 "}
!19 = distinct !DISubprogram(name: "greeter", scope: !3, file: !3, line: 9, type: !20, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!20 = !DISubroutineType(types: !21)
!21 = !{null, !6, !22}
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64)
!23 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!24 = !DILocalVariable(name: "str", arg: 1, scope: !19, file: !3, line: 9, type: !6)
!25 = !DILocation(line: 9, column: 21, scope: !19)
!26 = !DILocalVariable(name: "s", arg: 2, scope: !19, file: !3, line: 9, type: !22)
!27 = !DILocation(line: 9, column: 31, scope: !19)
!28 = !DILocalVariable(name: "p", scope: !19, file: !3, line: 10, type: !6)
!29 = !DILocation(line: 10, column: 11, scope: !19)
!30 = !DILocation(line: 10, column: 15, scope: !19)
!31 = !DILocation(line: 11, column: 20, scope: !19)
!32 = !DILocation(line: 11, column: 5, scope: !19)
!33 = !DILocation(line: 12, column: 5, scope: !19)
!34 = !DILocation(line: 13, column: 6, scope: !19)
!35 = !DILocation(line: 13, column: 8, scope: !19)
!36 = !DILocation(line: 14, column: 1, scope: !19)
!37 = distinct !DISubprogram(name: "initkey", scope: !3, file: !3, line: 16, type: !38, scopeLine: 16, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!38 = !DISubroutineType(types: !39)
!39 = !{null, !23}
!40 = !DILocalVariable(name: "sz", arg: 1, scope: !37, file: !3, line: 16, type: !23)
!41 = !DILocation(line: 16, column: 19, scope: !37)
!42 = !DILocation(line: 17, column: 26, scope: !37)
!43 = !DILocation(line: 17, column: 18, scope: !37)
!44 = !DILocation(line: 17, column: 6, scope: !37)
!45 = !DILocation(line: 19, column: 8, scope: !46)
!46 = distinct !DILexicalBlock(scope: !37, file: !3, line: 19, column: 2)
!47 = !DILocation(line: 19, column: 7, scope: !46)
!48 = !DILocation(line: 19, column: 12, scope: !49)
!49 = distinct !DILexicalBlock(scope: !46, file: !3, line: 19, column: 2)
!50 = !DILocation(line: 19, column: 14, scope: !49)
!51 = !DILocation(line: 19, column: 13, scope: !49)
!52 = !DILocation(line: 19, column: 2, scope: !46)
!53 = !DILocation(line: 19, column: 23, scope: !49)
!54 = !DILocation(line: 19, column: 27, scope: !49)
!55 = !DILocation(line: 19, column: 29, scope: !49)
!56 = !DILocation(line: 19, column: 19, scope: !49)
!57 = !DILocation(line: 19, column: 2, scope: !49)
!58 = distinct !{!58, !52, !59}
!59 = !DILocation(line: 19, column: 31, scope: !46)
!60 = !DILocation(line: 20, column: 1, scope: !37)
!61 = distinct !DISubprogram(name: "encrypt", scope: !3, file: !3, line: 22, type: !62, scopeLine: 22, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !6, !23}
!64 = !DILocalVariable(name: "plaintext", arg: 1, scope: !61, file: !3, line: 22, type: !6)
!65 = !DILocation(line: 22, column: 20, scope: !61)
!66 = !DILocalVariable(name: "sz", arg: 2, scope: !61, file: !3, line: 22, type: !23)
!67 = !DILocation(line: 22, column: 35, scope: !61)
!68 = !DILocation(line: 23, column: 33, scope: !61)
!69 = !DILocation(line: 23, column: 25, scope: !61)
!70 = !DILocation(line: 23, column: 13, scope: !61)
!71 = !DILocation(line: 24, column: 8, scope: !72)
!72 = distinct !DILexicalBlock(scope: !61, file: !3, line: 24, column: 2)
!73 = !DILocation(line: 24, column: 7, scope: !72)
!74 = !DILocation(line: 24, column: 12, scope: !75)
!75 = distinct !DILexicalBlock(scope: !72, file: !3, line: 24, column: 2)
!76 = !DILocation(line: 24, column: 14, scope: !75)
!77 = !DILocation(line: 24, column: 13, scope: !75)
!78 = !DILocation(line: 24, column: 2, scope: !72)
!79 = !DILocation(line: 25, column: 17, scope: !75)
!80 = !DILocation(line: 25, column: 27, scope: !75)
!81 = !DILocation(line: 25, column: 32, scope: !75)
!82 = !DILocation(line: 25, column: 36, scope: !75)
!83 = !DILocation(line: 25, column: 30, scope: !75)
!84 = !DILocation(line: 25, column: 3, scope: !75)
!85 = !DILocation(line: 25, column: 14, scope: !75)
!86 = !DILocation(line: 25, column: 16, scope: !75)
!87 = !DILocation(line: 24, column: 19, scope: !75)
!88 = !DILocation(line: 24, column: 2, scope: !75)
!89 = distinct !{!89, !78, !90}
!90 = !DILocation(line: 25, column: 37, scope: !72)
!91 = !DILocation(line: 26, column: 12, scope: !61)
!92 = !DILocation(line: 26, column: 5, scope: !61)
!93 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 29, type: !94, scopeLine: 29, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!94 = !DISubroutineType(types: !95)
!95 = !{!23}
!96 = !DILocalVariable(name: "age", scope: !93, file: !3, line: 30, type: !23)
!97 = !DILocation(line: 30, column: 9, scope: !93)
!98 = !DILocalVariable(name: "username", scope: !93, file: !3, line: 31, type: !99)
!99 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 160, elements: !100)
!100 = !{!101}
!101 = !DISubrange(count: 20)
!102 = !DILocation(line: 31, column: 46, scope: !93)
!103 = !DILocation(line: 31, column: 2, scope: !93)
!104 = !DILocalVariable(name: "text", scope: !93, file: !3, line: 31, type: !105)
!105 = !DICompositeType(tag: DW_TAG_array_type, baseType: !7, size: 8192, elements: !106)
!106 = !{!107}
!107 = !DISubrange(count: 1024)
!108 = !DILocation(line: 31, column: 60, scope: !93)
!109 = !DILocation(line: 32, column: 2, scope: !93)
!110 = !DILocation(line: 33, column: 15, scope: !93)
!111 = !DILocation(line: 33, column: 2, scope: !93)
!112 = !DILocation(line: 34, column: 10, scope: !93)
!113 = !DILocation(line: 34, column: 2, scope: !93)
!114 = !DILocation(line: 35, column: 2, scope: !93)
!115 = !DILocation(line: 36, column: 17, scope: !93)
!116 = !DILocation(line: 36, column: 2, scope: !93)
!117 = !DILocation(line: 38, column: 17, scope: !93)
!118 = !DILocation(line: 38, column: 10, scope: !93)
!119 = !DILocation(line: 38, column: 2, scope: !93)
!120 = !DILocalVariable(name: "sz", scope: !93, file: !3, line: 39, type: !23)
!121 = !DILocation(line: 39, column: 6, scope: !93)
!122 = !DILocation(line: 39, column: 19, scope: !93)
!123 = !DILocation(line: 39, column: 32, scope: !93)
!124 = !DILocation(line: 39, column: 25, scope: !93)
!125 = !DILocation(line: 39, column: 11, scope: !93)
!126 = !DILocation(line: 40, column: 2, scope: !93)
!127 = !DILocation(line: 41, column: 8, scope: !128)
!128 = distinct !DILexicalBlock(scope: !93, file: !3, line: 41, column: 2)
!129 = !DILocation(line: 41, column: 7, scope: !128)
!130 = !DILocation(line: 41, column: 12, scope: !131)
!131 = distinct !DILexicalBlock(scope: !128, file: !3, line: 41, column: 2)
!132 = !DILocation(line: 41, column: 21, scope: !131)
!133 = !DILocation(line: 41, column: 14, scope: !131)
!134 = !DILocation(line: 41, column: 13, scope: !131)
!135 = !DILocation(line: 41, column: 2, scope: !128)
!136 = !DILocation(line: 42, column: 16, scope: !131)
!137 = !DILocation(line: 42, column: 27, scope: !131)
!138 = !DILocation(line: 42, column: 3, scope: !131)
!139 = !DILocation(line: 41, column: 29, scope: !131)
!140 = !DILocation(line: 41, column: 2, scope: !131)
!141 = distinct !{!141, !135, !142}
!142 = !DILocation(line: 42, column: 29, scope: !128)
!143 = !DILocation(line: 43, column: 37, scope: !93)
!144 = !DILocation(line: 43, column: 5, scope: !93)
!145 = !DILocation(line: 44, column: 5, scope: !93)
