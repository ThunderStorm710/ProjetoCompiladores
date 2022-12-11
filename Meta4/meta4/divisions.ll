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
	%n1 = alloca double, align 8
	%n2 = alloca double, align 8
	%1 = load double, double* %n1, align 8
	%2 = add i32 0, 11
	%3 = sub nsw i32 0, %2
	%convertion.1 = sitofp i32 %3 to double
	store double %convertion.1, double* %n1, align 8
	%4 = load double, double* %n1, align 8
	%5 = load double, double* %n2, align 8
	%6 = add i32 0, 53
	%7 = sub nsw i32 0, %6
	%convertion.2 = sitofp i32 %7 to double
	store double %convertion.2, double* %n2, align 8
	%8 = load double, double* %n2, align 8
	%9 = load double, double* %n2, align 8
	%10 = load double, double* %n1, align 8
	%11 = fdiv double %9, %10
	%12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.1, i32 0, i32 0), double %11)
	%13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%n3 = alloca i32, align 4
	%n4 = alloca i32, align 4
	%14 = load i32, i32* %n3, align 4
	%15 = add i32 0, 11
	%16 = sub nsw i32 0, %15
	store i32 %16, i32* %n3, align 4
	%17 = load i32, i32* %n3, align 4
	%18 = load i32, i32* %n4, align 4
	%19 = add i32 0, 53
	%20 = sub nsw i32 0, %19
	store i32 %20, i32* %n4, align 4
	%21 = load i32, i32* %n4, align 4
	%22 = load i32, i32* %n4, align 4
	%23 = load i32, i32* %n3, align 4
	%24 = sdiv i32 %22, %23
	%25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %24)
	%26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	%27 = load i32, i32* %n3, align 4
	%28 = add i32 0, 11
	store i32 %28, i32* %n3, align 4
	%29 = load i32, i32* %n3, align 4
	%30 = load i32, i32* %n4, align 4
	%31 = add i32 0, 53
	%32 = sub nsw i32 0, %31
	store i32 %32, i32* %n4, align 4
	%33 = load i32, i32* %n4, align 4
	%34 = load i32, i32* %n4, align 4
	%35 = load i32, i32* %n3, align 4
	%36 = sdiv i32 %34, %35
	%37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.5, i32 0, i32 0), i32 %36)
	%38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.6, i32 0, i32 0))
	%39 = load i32, i32* %n3, align 4
	%40 = add i32 0, 2
	store i32 %40, i32* %n3, align 4
	%41 = load i32, i32* %n3, align 4
	%42 = load i32, i32* %n4, align 4
	%43 = add i32 0, 85
	%44 = sub nsw i32 0, %43
	store i32 %44, i32* %n4, align 4
	%45 = load i32, i32* %n4, align 4
	%46 = load i32, i32* %n4, align 4
	%47 = load i32, i32* %n3, align 4
	%48 = srem i32 %46, %47
	%49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.7, i32 0, i32 0), i32 %48)
	%50 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.8, i32 0, i32 0))
	%51 = load i32, i32* %n3, align 4
	%52 = add i32 0, 2
	%53 = sub nsw i32 0, %52
	store i32 %53, i32* %n3, align 4
	%54 = load i32, i32* %n3, align 4
	%55 = load i32, i32* %n4, align 4
	%56 = add i32 0, 85
	store i32 %56, i32* %n4, align 4
	%57 = load i32, i32* %n4, align 4
	%58 = load i32, i32* %n4, align 4
	%59 = load i32, i32* %n3, align 4
	%60 = srem i32 %58, %59
	%61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.9, i32 0, i32 0), i32 %60)
	%62 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.10, i32 0, i32 0))
	%63 = load i32, i32* %n3, align 4
	%64 = add i32 0, 2
	store i32 %64, i32* %n3, align 4
	%65 = load i32, i32* %n3, align 4
	%66 = load i32, i32* %n4, align 4
	%67 = add i32 0, 85
	store i32 %67, i32* %n4, align 4
	%68 = load i32, i32* %n4, align 4
	%69 = load i32, i32* %n4, align 4
	%70 = load i32, i32* %n3, align 4
	%71 = srem i32 %69, %70
	%72 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.11, i32 0, i32 0), i32 %71)
	%73 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.12, i32 0, i32 0))
	%74 = load double, double* %n2, align 8
	%75 = load double, double* %n1, align 8
	%76 = add i32 0, 0
	%convertion.3 = sitofp i32 %76 to double
	store double %convertion.3, double* %n1, align 8
	%77 = load double, double* %n1, align 8
	store double %77, double* %n2, align 8
	%78 = load double, double* %n2, align 8
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.7 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.8 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.9 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.10 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.11 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.12 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
