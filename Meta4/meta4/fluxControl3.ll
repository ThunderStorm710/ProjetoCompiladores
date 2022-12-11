declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
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
	%i = alloca i32, align 4
	%g = alloca i32, align 4
	%4 = load i32, i32* %i, align 4
	%5 = add i32 0, 0
	store i32 %5, i32* %i, align 4
	%6 = load i32, i32* %i, align 4
	%7 = load i32, i32* %g, align 4
	%8 = add i32 0, 0
	store i32 %8, i32* %g, align 4
	%9 = load i32, i32* %g, align 4
	%is_pair = alloca i32, align 4
	%10 = load i32, i32* %is_pair, align 4
	%11 = add i32 0, 0
	store i32 %11, i32* %is_pair, align 4
	%12 = load i32, i32* %is_pair, align 4
	br label %label.entry.while1
label.entry.while1:       ;it's while 
	%13 = load i32, i32* %k, align 4
	%14 = add i32 0, 5
	%15 = icmp slt i32 %13, %14
	%16 = icmp eq i1 %15, 1
	br i1 %16, label %label.work.while1, label %label.finished.while1
label.work.while1:       ;it's while 
	%17 = load i32, i32* %k, align 4
	%18 = add i32 0, 1
	%19 = icmp eq i32 %17, %18
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%20 = icmp eq i1 %19, 1
	br i1 %20, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%21 = load i32, i32* %input, align 4
	%22 = load i32, i32* %input, align 4
	%23 = add i32 0, 2
	%24 = sub i32 %22, %23
	store i32 %24, i32* %input, align 4
	%25 = load i32, i32* %input, align 4
	%26 = load i32, i32* %i, align 4
	%27 = add i32 0, 0
	store i32 %27, i32* %i, align 4
	%28 = load i32, i32* %i, align 4
	%29 = load i32, i32* %g, align 4
	%30 = add i32 0, 0
	store i32 %30, i32* %g, align 4
	%31 = load i32, i32* %g, align 4
	br label %label.entry.while2
label.entry.while2:       ;it's while 
	%32 = load i32, i32* %i, align 4
	%33 = add i32 0, 100
	%34 = icmp slt i32 %32, %33
	%35 = icmp eq i1 %34, 1
	br i1 %35, label %label.work.while2, label %label.finished.while2
label.work.while2:       ;it's while 
	br label %label.entry.while3
label.entry.while3:       ;it's while 
	%36 = load i32, i32* %g, align 4
	%37 = add i32 0, 50
	%38 = icmp slt i32 %36, %37
	%39 = icmp eq i1 %38, 1
	br i1 %39, label %label.work.while3, label %label.finished.while3
label.work.while3:       ;it's while 
	%40 = load i32, i32* %input, align 4
	%41 = load i32, i32* %input, align 4
	%42 = add i32 0, 2
	%43 = add i32 %41, %42
	store i32 %43, i32* %input, align 4
	%44 = load i32, i32* %input, align 4
	%45 = load i32, i32* %g, align 4
	%46 = add i32 0, 2
	%47 = srem i32 %45, %46
	%48 = add i32 0, 0
	%49 = icmp eq i32 %47, %48
	br label %label.entry.if2
label.entry.if2:       ;it's if 
	%50 = icmp eq i1 %49, 1
	br i1 %50, label %label.then2, label %label.else2
label.then2:       ;it's if 
	%51 = load i32, i32* %is_pair, align 4
	%52 = load i32, i32* %is_pair, align 4
	%53 = add i32 0, 1
	%54 = add i32 %52, %53
	store i32 %54, i32* %is_pair, align 4
	%55 = load i32, i32* %is_pair, align 4
br label %label.finished.if2
label.else2:       ;it's else 
br label %label.finished.if2
label.finished.if2:
	%56 = load i32, i32* %g, align 4
	%57 = load i32, i32* %g, align 4
	%58 = add i32 0, 1
	%59 = add i32 %57, %58
	store i32 %59, i32* %g, align 4
	%60 = load i32, i32* %g, align 4
	br label %label.entry.while3
label.finished.while3:
	%61 = load i32, i32* %g, align 4
	%62 = add i32 0, 0
	store i32 %62, i32* %g, align 4
	%63 = load i32, i32* %g, align 4
	%64 = load i32, i32* %i, align 4
	%65 = load i32, i32* %i, align 4
	%66 = add i32 0, 1
	%67 = add i32 %65, %66
	store i32 %67, i32* %i, align 4
	%68 = load i32, i32* %i, align 4
	br label %label.entry.while2
label.finished.while2:
br label %label.finished.if1
label.else1:       ;it's else 
	%69 = load i32, i32* %k, align 4
	%70 = add i32 0, 2
	%71 = icmp eq i32 %69, %70
	br label %label.entry.if3
label.entry.if3:       ;it's if 
	%72 = icmp eq i1 %71, 1
	br i1 %72, label %label.then3, label %label.else3
label.then3:       ;it's if 
	%73 = load i32, i32* %input, align 4
	%74 = load i32, i32* %input, align 4
	%75 = add i32 0, 3
	%76 = mul i32 %74, %75
	store i32 %76, i32* %input, align 4
	%77 = load i32, i32* %input, align 4
br label %label.finished.if3
label.else3:       ;it's else 
br label %label.finished.if3
label.finished.if3:
br label %label.finished.if1
label.finished.if1:
	%78 = load i32, i32* %k, align 4
	%79 = load i32, i32* %k, align 4
	%80 = add i32 0, 1
	%81 = add i32 %79, %80
	store i32 %81, i32* %k, align 4
	%82 = load i32, i32* %k, align 4
	br label %label.entry.while1
label.finished.while1:
	%83 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.global.strlit.1, i32 0, i32 0))
	%84 = load i32, i32* %is_pair, align 4
	%85 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.2, i32 0, i32 0), i32 %84)
	%86 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.3, i32 0, i32 0))
	%87 = load i32, i32* %input, align 4
	ret i32 %87
	ret i32 0
}
define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%aux1 = alloca i32, align 4
	%1 = load i32, i32* %aux1, align 4
	%2 = add i32 0, 40
	store i32 %2, i32* %aux1, align 4
	%3 = load i32, i32* %aux1, align 4
	%4 = load i32, i32* %aux1, align 4
	%5 = load i32, i32* %aux1, align 4
	%6 = call i32 @function.declaration.i.b.i.(i32 %5)
	store i32 %6, i32* %aux1, align 4
	%7 = load i32, i32* %aux1, align 4
	%8 = add i32 0, 0
	%9 = add i32 %8, 1
	%10 = load i8**, i8*** %argv_aux, align 8
	%11 = getelementptr inbounds i8*, i8** %10, i32 %9
	%12 = load i8*, i8** %11, align 8
	%13 = call i32 @atoi(i8* %12)
	%14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.4, i32 0, i32 0), i32 %13)
	%15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.5, i32 0, i32 0))
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [10 x i8] c"Is pair: \00", align 1
@.global.strlit.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.3 = private unnamed_addr constant [3 x i8] c"|\0A\00", align 1
@.global.strlit.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.5 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
