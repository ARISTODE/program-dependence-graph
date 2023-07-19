; ModuleID = 'test_ind_call.c'
source_filename = "test_ind_call.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Person = type { i32, [10 x i8] }

@.str = private unnamed_addr constant [16 x i8] c"age of p is %d\0A\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"Student\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @f(%struct.Person* %0) #0 !dbg !18 {
  %2 = alloca %struct.Person*, align 8
  store %struct.Person* %0, %struct.Person** %2, align 8
  call void @llvm.dbg.declare(metadata %struct.Person** %2, metadata !21, metadata !DIExpression()), !dbg !22
  %3 = load %struct.Person*, %struct.Person** %2, align 8, !dbg !23
  %4 = getelementptr inbounds %struct.Person, %struct.Person* %3, i32 0, i32 0, !dbg !24
  %5 = load i32, i32* %4, align 4, !dbg !24
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 %5), !dbg !25
  ret void, !dbg !26
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !27 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.Person*, align 8
  %3 = alloca void (%struct.Person*)*, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata %struct.Person** %2, metadata !30, metadata !DIExpression()), !dbg !31
  %4 = call noalias i8* @malloc(i64 16) #4, !dbg !32
  %5 = bitcast i8* %4 to %struct.Person*, !dbg !33
  store %struct.Person* %5, %struct.Person** %2, align 8, !dbg !31
  %6 = load %struct.Person*, %struct.Person** %2, align 8, !dbg !34
  %7 = getelementptr inbounds %struct.Person, %struct.Person* %6, i32 0, i32 0, !dbg !35
  store i32 5, i32* %7, align 4, !dbg !36
  %8 = load %struct.Person*, %struct.Person** %2, align 8, !dbg !37
  %9 = getelementptr inbounds %struct.Person, %struct.Person* %8, i32 0, i32 1, !dbg !38
  %10 = getelementptr inbounds [10 x i8], [10 x i8]* %9, i64 0, i64 0, !dbg !37
  %11 = call i8* @strcpy(i8* %10, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #4, !dbg !39
  call void @llvm.dbg.declare(metadata void (%struct.Person*)** %3, metadata !40, metadata !DIExpression()), !dbg !42
  store void (%struct.Person*)* @f, void (%struct.Person*)** %3, align 8, !dbg !42
  %12 = load void (%struct.Person*)*, void (%struct.Person*)** %3, align 8, !dbg !43
  %13 = load %struct.Person*, %struct.Person** %2, align 8, !dbg !44
  call void %12(%struct.Person* %13), !dbg !43
  %14 = load %struct.Person*, %struct.Person** %2, align 8, !dbg !45
  %15 = bitcast %struct.Person* %14 to i8*, !dbg !45
  call void @free(i8* %15) #4, !dbg !46
  ret i32 0, !dbg !47
}

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare dso_local i8* @strcpy(i8*, i8*) #3

; Function Attrs: nounwind
declare dso_local void @free(i8*) #3

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!14, !15, !16}
!llvm.ident = !{!17}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "Ubuntu clang version 10.0.1-++20211003085942+ef32c611aa21-1~exp1~20211003090334.2", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, retainedTypes: !3, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "test_ind_call.c", directory: "/home/yzh89/Documents/pdg/test")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64)
!5 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "Person", file: !1, line: 5, size: 128, elements: !6)
!6 = !{!7, !9}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !5, file: !1, line: 6, baseType: !8, size: 32)
!8 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!9 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !5, file: !1, line: 7, baseType: !10, size: 80, offset: 32)
!10 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 80, elements: !12)
!11 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!12 = !{!13}
!13 = !DISubrange(count: 10)
!14 = !{i32 7, !"Dwarf Version", i32 4}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{i32 1, !"wchar_size", i32 4}
!17 = !{!"Ubuntu clang version 10.0.1-++20211003085942+ef32c611aa21-1~exp1~20211003090334.2"}
!18 = distinct !DISubprogram(name: "f", scope: !1, file: !1, line: 10, type: !19, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!19 = !DISubroutineType(types: !20)
!20 = !{null, !4}
!21 = !DILocalVariable(name: "p", arg: 1, scope: !18, file: !1, line: 10, type: !4)
!22 = !DILocation(line: 10, column: 23, scope: !18)
!23 = !DILocation(line: 12, column: 32, scope: !18)
!24 = !DILocation(line: 12, column: 35, scope: !18)
!25 = !DILocation(line: 12, column: 5, scope: !18)
!26 = !DILocation(line: 13, column: 1, scope: !18)
!27 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 15, type: !28, scopeLine: 15, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!28 = !DISubroutineType(types: !29)
!29 = !{!8}
!30 = !DILocalVariable(name: "p", scope: !27, file: !1, line: 16, type: !4)
!31 = !DILocation(line: 16, column: 20, scope: !27)
!32 = !DILocation(line: 16, column: 40, scope: !27)
!33 = !DILocation(line: 16, column: 24, scope: !27)
!34 = !DILocation(line: 17, column: 5, scope: !27)
!35 = !DILocation(line: 17, column: 8, scope: !27)
!36 = !DILocation(line: 17, column: 12, scope: !27)
!37 = !DILocation(line: 18, column: 12, scope: !27)
!38 = !DILocation(line: 18, column: 15, scope: !27)
!39 = !DILocation(line: 18, column: 5, scope: !27)
!40 = !DILocalVariable(name: "fun_ptr", scope: !27, file: !1, line: 19, type: !41)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64)
!42 = !DILocation(line: 19, column: 12, scope: !27)
!43 = !DILocation(line: 20, column: 5, scope: !27)
!44 = !DILocation(line: 20, column: 13, scope: !27)
!45 = !DILocation(line: 21, column: 10, scope: !27)
!46 = !DILocation(line: 21, column: 5, scope: !27)
!47 = !DILocation(line: 22, column: 5, scope: !27)
