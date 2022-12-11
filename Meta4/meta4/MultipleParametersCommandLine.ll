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
	%arg1 = alloca i32, align 4
	%1 = load i32, i32* %arg1, align 4
	%2 = add i32 0, 0
	%3 = add i32 %2, 1
	%4 = load i8**, i8*** %argv_aux, align 8
	%5 = getelementptr inbounds i8*, i8** %4, i32 %3
	%6 = load i8*, i8** %5, align 8
	%7 = call i32 @atoi(i8* %6)
	store i32 %7, i32* %arg1, align 4
	%8 = load i32, i32* %arg1, align 4
	%arg2 = alloca i32, align 4
	%9 = load i32, i32* %arg2, align 4
	%10 = add i32 0, 1
	%11 = add i32 %10, 1
	%12 = load i8**, i8*** %argv_aux, align 8
	%13 = getelementptr inbounds i8*, i8** %12, i32 %11
	%14 = load i8*, i8** %13, align 8
	%15 = call i32 @atoi(i8* %14)
	store i32 %15, i32* %arg2, align 4
	%16 = load i32, i32* %arg2, align 4
	%17 = load i32, i32* %arg1, align 4
	%18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.1, i32 0, i32 0), i32 %17)
	%19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%20 = load i32, i32* %arg2, align 4
	%21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %20)
	%22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
