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
	%1 = fadd double 0.000000e+00, 0.0000000000000000e+00
	%2 = fsub double -0.000000e+00, %1
	%3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.1, i32 0, i32 0), double %2)
	%4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%5 = add i32 0, 0
	%6 = sub nsw i32 0, %5
	%7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %6)
	%8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	%9 = fadd double 0.000000e+00, 2.9999999999999999e-01
	%10 = fsub double -0.000000e+00, %9
	%11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.5, i32 0, i32 0), double %10)
	%12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.6, i32 0, i32 0))
	%13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.global.strlit.7, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.7 = private unnamed_addr constant [10 x i8] c"%%%%%%%%\0A\00", align 1
