@global.var.b = common global i1 0, align 4
declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = load i1, i1* @global.var.b
	%2 = add i1 0, 1
	%3 = zext i1 %2 to i32
	%4 = icmp eq i32 %3, 0
	store i1 %4, i1* @global.var.b
	%5 = load i1, i1* @global.var.b
	%6 = load i1, i1* @global.var.b
	%7 = zext i1 %6 to i32
	%8 = icmp eq i32 %7, 0
	%9 = zext i1 %8 to i32
	%10 = icmp eq i32 %9, 0
	%11 = zext i1 %10 to i32
	%12 = icmp eq i32 %11, 0
	%13 = zext i1 %12 to i32
	%14 = icmp eq i32 %13, 0
	%15 = zext i1 %14 to i32
	%16 = icmp eq i32 %15, 0
	%17 = zext i1 %16 to i32
	%18 = icmp eq i32 %17, 0
	%19 = zext i1 %18 to i32
	%20 = icmp eq i32 %19, 0
	%compare.1 = icmp eq i1 %20, 1
	br i1 %compare.1, label %compare.if.1, label %compare.else.1
	compare.if.1:
		%21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.1, i32 0, i32 0))
		br label %compare.end.1
	compare.else.1:
		%22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.2, i32 0, i32 0))
		br label %compare.end.1
	compare.end.1:
	%23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.3, i32 0, i32 0))
	%24 = fadd double 0.000000e+00, 4.2000000000000000e+02
	%25 = fsub double -0.000000e+00, %24
	%26 = fsub double -0.000000e+00, %25
	%27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.4, i32 0, i32 0), double %26)
	%28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.5, i32 0, i32 0))
	%29 = add i32 0, 420
	%30 = sub nsw i32 0, %29
	%31 = sub nsw i32 0, %30
	%32 = sub nsw i32 0, %31
	%33 = sub nsw i32 0, %32
	%34 = sub nsw i32 0, %33
	%35 = add i32 0, 421
	%36 = sub nsw i32 0, %35
	%37 = icmp sgt i32 %34, %36
	%38 = zext i1 %37 to i32
	%39 = icmp eq i32 %38, 0
	%compare.2 = icmp eq i1 %39, 1
	br i1 %compare.2, label %compare.if.2, label %compare.else.2
	compare.if.2:
		%40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.6, i32 0, i32 0))
		br label %compare.end.2
	compare.else.2:
		%41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.7, i32 0, i32 0))
		br label %compare.end.2
	compare.end.2:
	%42 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.8, i32 0, i32 0))
	%43 = add i1 0, 0
	%44 = call i1 @function.declaration.b.falseB.()
	%45 = zext i1 %43 to i32
	%46 = zext i1 %44 to i32
	%47 = icmp eq i32 %46, %45
	%48 = zext i1 %47 to i32
	%49 = icmp eq i32 %48, 0
	%compare.3 = icmp eq i1 %49, 1
	br i1 %compare.3, label %compare.if.3, label %compare.else.3
	compare.if.3:
		%50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.9, i32 0, i32 0))
		br label %compare.end.3
	compare.else.3:
		%51 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.10, i32 0, i32 0))
		br label %compare.end.3
	compare.end.3:
	%52 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.11, i32 0, i32 0))
	%53 = add i32 0, 1
	%54 = add i32 0, 1
	%55 = sub i32 %53, %54
	%56 = add i32 0, 0
	%57 = add i32 %55, %56
	%58 = sub nsw i32 0, %57
	%59 = sub nsw i32 0, %58
	%60 = add i32 %59, 1
	%61 = load i8**, i8*** %argv_aux, align 8
	%62 = getelementptr inbounds i8*, i8** %61, i32 %60
	%63 = load i8*, i8** %62, align 8
	%64 = call i32 @atoi(i8* %63)
	%65 = sub nsw i32 0, %64
	%66 = sub nsw i32 0, %65
	%67 = sub nsw i32 0, %66
	%68 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.12, i32 0, i32 0), i32 %67)
	%69 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.13, i32 0, i32 0))
	ret void
}
define i1 @function.declaration.b.falseB.() {
	%1 = add i1 0, 1
	%2 = zext i1 %1 to i32
	%3 = icmp eq i32 %2, 0
	ret i1 %3
	ret i1 1
}

@.global.strlit.1 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.2 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.4 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.6 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.7 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.9 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.10 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.11 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.12 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.13 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
