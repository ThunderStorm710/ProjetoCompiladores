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
	%1 = load i32, i32* %argc_aux, align 4
	%2 = sub i32 %1, 1
	%3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.1, i32 0, i32 0), i32 %2)
	%4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
