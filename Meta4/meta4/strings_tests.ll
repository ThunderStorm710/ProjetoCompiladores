@global.var.i = common global i32 0, align 4
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
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.global.strlit.1, i32 0, i32 0))
	%a = alloca i32, align 4
	%2 = load i32, i32* %a, align 4
	%3 = load i32, i32* %argc_aux, align 4
	%4 = sub i32 %3, 1
	store i32 %4, i32* %a, align 4
	%5 = load i32, i32* %a, align 4
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.global.strlit.2, i32 0, i32 0))
	%7 = load i32, i32* %a, align 4
	%8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %7)
	%9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	%10 = load i32, i32* %a, align 4
	%11 = add i32 0, 0
	%12 = icmp sgt i32 %10, %11
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%13 = icmp eq i1 %12, 1
	br i1 %13, label %label.then1, label %label.else1
label.then1:       ;it's if 
	br label %label.entry.while1
label.entry.while1:       ;it's while 
	%14 = load i32, i32* %a, align 4
	%15 = add i32 0, 1
	%16 = add i32 %14, %15
	%17 = load i32, i32* @global.var.i, align 4
	%18 = load i32, i32* @global.var.i, align 4
	%19 = add i32 0, 1
	%20 = add i32 %18, %19
	store i32 %20, i32* @global.var.i, align 4
	%21 = load i32, i32* @global.var.i, align 4
	%22 = icmp sgt i32 %16, %21
	%23 = icmp eq i1 %22, 1
	br i1 %23, label %label.work.while1, label %label.finished.while1
label.work.while1:       ;it's while 
	%24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.5, i32 0, i32 0))
	%25 = load i32, i32* @global.var.i, align 4
	%26 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.6, i32 0, i32 0), i32 %25)
	%27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.global.strlit.7, i32 0, i32 0))
	%28 = load i32, i32* @global.var.i, align 4
	%29 = add i32 0, 1
	%30 = sub i32 %28, %29
	%31 = add i32 %30, 1
	%32 = load i8**, i8*** %argv_aux, align 8
	%33 = getelementptr inbounds i8*, i8** %32, i32 %31
	%34 = load i8*, i8** %33, align 8
	%35 = call i32 @atoi(i8* %34)
	%36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.8, i32 0, i32 0), i32 %35)
	%37 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.9, i32 0, i32 0))
	br label %label.entry.while1
label.finished.while1:
br label %label.finished.if1
label.else1:       ;it's else 
	%38 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.global.strlit.10, i32 0, i32 0))
br label %label.finished.if1
label.finished.if1:
	%39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.11, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [7 x i8] c"\0D\5C\22\0C\09\0A\00", align 1
@.global.strlit.2 = private unnamed_addr constant [22 x i8] c"Number of arguments:\09\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [6 x i8] c"Arg (\00", align 1
@.global.strlit.6 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.7 = private unnamed_addr constant [4 x i8] c"): \00", align 1
@.global.strlit.8 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.9 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.10 = private unnamed_addr constant [16 x i8] c"No arguments :(\00", align 1
@.global.strlit.11 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
