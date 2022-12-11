declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define i32 @function.declaration.i.a.i.(i32 %input_aux) {
	%input = alloca i32, align 4
	store i32 %input_aux, i32* %input, align 4
	%i = alloca i32, align 4
	%1 = load i32, i32* %i, align 4
	%2 = add i32 0, 0
	store i32 %2, i32* %i, align 4
	%3 = load i32, i32* %i, align 4
	br label %label.entry.while1
label.entry.while1:       ;it's while 
	%4 = load i32, i32* %i, align 4
	%5 = add i32 0, 10
	%6 = icmp slt i32 %4, %5
	%7 = icmp eq i1 %6, 1
	br i1 %7, label %label.work.while1, label %label.finished.while1
label.work.while1:       ;it's while 
	%8 = load i32, i32* %input, align 4
	%9 = load i32, i32* %input, align 4
	%10 = add i32 0, 2
	%11 = add i32 %9, %10
	store i32 %11, i32* %input, align 4
	%12 = load i32, i32* %input, align 4
	%13 = load i32, i32* %i, align 4
	%14 = load i32, i32* %i, align 4
	%15 = add i32 0, 1
	%16 = add i32 %14, %15
	store i32 %16, i32* %i, align 4
	%17 = load i32, i32* %i, align 4
	br label %label.entry.while1
label.finished.while1:
	%18 = load i32, i32* %input, align 4
	ret i32 %18
	ret i32 0
}
define i32 @function.declaration.i.b.i.(i32 %input_aux) {
	%input = alloca i32, align 4
	store i32 %input_aux, i32* %input, align 4
	%k = alloca i32, align 4
	%1 = load i32, i32* %k, align 4
	%2 = add i32 0, 0
	store i32 %2, i32* %k, align 4
	%3 = load i32, i32* %k, align 4
	br label %label.entry.while1
label.entry.while1:       ;it's while 
	%4 = load i32, i32* %k, align 4
	%5 = add i32 0, 5
	%6 = icmp slt i32 %4, %5
	%7 = icmp eq i1 %6, 1
	br i1 %7, label %label.work.while1, label %label.finished.while1
label.work.while1:       ;it's while 
	%8 = load i32, i32* %k, align 4
	%9 = add i32 0, 1
	%10 = icmp eq i32 %8, %9
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%11 = icmp eq i1 %10, 1
	br i1 %11, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%12 = load i32, i32* %input, align 4
	%13 = load i32, i32* %input, align 4
	%14 = add i32 0, 2
	%15 = sub i32 %13, %14
	store i32 %15, i32* %input, align 4
	%16 = load i32, i32* %input, align 4
br label %label.finished.if1
label.else1:       ;it's else 
	%17 = load i32, i32* %k, align 4
	%18 = add i32 0, 2
	%19 = icmp eq i32 %17, %18
	br label %label.entry.if2
label.entry.if2:       ;it's if 
	%20 = icmp eq i1 %19, 1
	br i1 %20, label %label.then2, label %label.else2
label.then2:       ;it's if 
	%21 = load i32, i32* %input, align 4
	%22 = load i32, i32* %input, align 4
	%23 = add i32 0, 3
	%24 = mul i32 %22, %23
	store i32 %24, i32* %input, align 4
	%25 = load i32, i32* %input, align 4
br label %label.finished.if2
label.else2:       ;it's else 
br label %label.finished.if2
label.finished.if2:
br label %label.finished.if1
label.finished.if1:
	%26 = load i32, i32* %k, align 4
	%27 = load i32, i32* %k, align 4
	%28 = add i32 0, 1
	%29 = add i32 %27, %28
	store i32 %29, i32* %k, align 4
	%30 = load i32, i32* %k, align 4
	br label %label.entry.while1
label.finished.while1:
	%31 = load i32, i32* %input, align 4
	ret i32 %31
	ret i32 0
}
define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%input = alloca i32, align 4
	%aux = alloca i32, align 4
	%aux1 = alloca i32, align 4
	%1 = load i32, i32* %aux, align 4
	%2 = add i32 0, 0
	store i32 %2, i32* %aux, align 4
	%3 = load i32, i32* %aux, align 4
	%4 = load i32, i32* %aux1, align 4
	%5 = add i32 0, 0
	store i32 %5, i32* %aux1, align 4
	%6 = load i32, i32* %aux1, align 4
	%7 = load i32, i32* %input, align 4
	%8 = add i32 0, 0
	%9 = add i32 %8, 1
	%10 = load i8**, i8*** %argv_aux, align 8
	%11 = getelementptr inbounds i8*, i8** %10, i32 %9
	%12 = load i8*, i8** %11, align 8
	%13 = call i32 @atoi(i8* %12)
	store i32 %13, i32* %input, align 4
	%14 = load i32, i32* %input, align 4
	%15 = load i32, i32* %input, align 4
	%16 = add i32 0, 10
	%17 = icmp slt i32 %15, %16
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%18 = icmp eq i1 %17, 1
	br i1 %18, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%19 = load i32, i32* %aux, align 4
	%20 = load i32, i32* %input, align 4
	%21 = call i32 @function.declaration.i.a.i.(i32 %20)
	store i32 %21, i32* %aux, align 4
	%22 = load i32, i32* %aux, align 4
br label %label.finished.if1
label.else1:       ;it's else 
	%23 = load i32, i32* %aux1, align 4
	%24 = load i32, i32* %input, align 4
	%25 = call i32 @function.declaration.i.b.i.(i32 %24)
	store i32 %25, i32* %aux1, align 4
	%26 = load i32, i32* %aux1, align 4
br label %label.finished.if1
label.finished.if1:
	%27 = load i32, i32* %aux, align 4
	%28 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.1, i32 0, i32 0), i32 %27)
	%29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.2, i32 0, i32 0))
	%30 = load i32, i32* %aux1, align 4
	%31 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0), i32 %30)
	%32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.4, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
