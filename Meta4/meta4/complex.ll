@global.var.overload = common global i32 0, align 4
declare i32 @atoi(i8*)
declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
	call void @function.declaration.v.main.s.(i32 %argc, i8** %argv)
	ret i32 0
}

define i1 @function.declaration.b.overload.b.(i1 %n_aux) {
	%n = alloca i1
	store i1 %n_aux, i1* %n
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.global.strlit.1, i32 0, i32 0))
	%2 = add i1 0, 0
	ret i1 %2
	ret i1 1
}
define double @function.declaration.d.overload.d.(double %n_aux) {
	%n = alloca double, align 8
	store double %n_aux, double* %n, align 8
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.global.strlit.2, i32 0, i32 0))
	%2 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%3 = add i32 0, 2
	%4 = sitofp i32 %3 to double
	%5 = fmul double %2, %4
	%6 = add i32 0, 2
	%7 = call i32 @function.declaration.i.main.i.(i32 %6)
	%8 = add i32 0, 5
	%9 = sdiv i32 %7, %8
	%10 = add i32 0, 6
	%11 = mul i32 %9, %10
	%12 = sitofp i32 %11 to double
	%13 = fadd double %5, %12
	%14 = add i32 0, 2
	%15 = add i32 0, 3
	%16 = mul i32 %14, %15
	%17 = sitofp i32 %16 to double
	%18 = fadd double %13, %17
	%19 = add i32 0, 3
	%20 = add i32 0, 4
	%21 = mul i32 %19, %20
	%22 = sitofp i32 %21 to double
	%23 = fadd double %18, %22
	%24 = add i32 0, 2
	%25 = add i32 0, 8
	%26 = mul i32 %24, %25
	%27 = sitofp i32 %26 to double
	%28 = fadd double %23, %27
	%29 = add i32 0, 5
	%30 = add i32 0, 9
	%31 = mul i32 %29, %30
	%32 = sitofp i32 %31 to double
	%33 = fadd double %28, %32
	%34 = add i32 0, 2
	%35 = add i32 0, 2
	%36 = call i32 @function.declaration.i.overload.i.i.(i32 %34, i32 %35)
	%37 = sitofp i32 %36 to double
	%38 = fadd double %33, %37
	ret double %38
	ret double 0.000000e+00
}
define i32 @function.declaration.i.overload.d.d.(double %b_aux, double %b1_aux) {
	%b = alloca double, align 8
	store double %b_aux, double* %b, align 8
	%b1 = alloca double, align 8
	store double %b1_aux, double* %b1, align 8
	%1 = load i32, i32* @global.var.overload, align 4
	%2 = add i32 0, 2
	%3 = load i32, i32* @global.var.overload, align 4
	%4 = add i32 %2, %3
	store i32 %4, i32* @global.var.overload, align 4
	%5 = load i32, i32* @global.var.overload, align 4
	%overload = alloca double, align 8
	%6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.global.strlit.3, i32 0, i32 0))
	%7 = add i32 0, 5
	ret i32 %7
	ret i32 0
}
define i32 @function.declaration.i.overload.i.i.(i32 %b_aux, i32 %b1_aux) {
	%b = alloca i32, align 4
	store i32 %b_aux, i32* %b, align 4
	%b1 = alloca i32, align 4
	store i32 %b1_aux, i32* %b1, align 4
	%1 = add i32 0, 5
	ret i32 %1
	ret i32 0
}
define i32 @function.declaration.i.main.i.(i32 %n_aux) {
	%n = alloca i32, align 4
	store i32 %n_aux, i32* %n, align 4
	%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.global.strlit.4, i32 0, i32 0))
	%2 = add i32 0, 5
	ret i32 %2
	ret i32 0
}
define void @function.declaration.v.main.s.(i32 %argc, i8** %argv) {
	%argc_aux = alloca i32, align 4
	%argv_aux = alloca i8**, align 8
	store i32 %argc, i32* %argc_aux, align 4
	store i8** %argv, i8*** %argv_aux, align 8
	%1 = load i32, i32* %argc_aux, align 4
	%2 = sub i32 %1, 1
	%3 = add i32 0, 0
	%4 = icmp sgt i32 %2, %3
	br label %label.entry.if1
label.entry.if1:       ;it's if 
	%5 = icmp eq i1 %4, 1
	br i1 %5, label %label.then1, label %label.else1
label.then1:       ;it's if 
	%6 = add i32 0, 0
	%7 = add i32 %6, 1
	%8 = load i8**, i8*** %argv_aux, align 8
	%9 = getelementptr inbounds i8*, i8** %8, i32 %7
	%10 = load i8*, i8** %9, align 8
	%11 = call i32 @atoi(i8* %10)
	%12 = sitofp i32 %11 to double
	%13 = call double @function.declaration.d.overload.d.(double %12)
br label %label.finished.if1
label.else1:       ;it's else 
	%14 = add i32 0, 5
	%15 = sitofp i32 %14 to double
	%16 = call double @function.declaration.d.overload.d.(double %15)
br label %label.finished.if1
label.finished.if1:
	%17 = add i1 0, 0
	%18 = zext i1 %17 to i32
	%19 = icmp eq i32 %18, 0
	%compare.1 = icmp eq i1 %19, 1
	br i1 %compare.1, label %compare.if.1, label %compare.else.1
	compare.if.1:
		%20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.5, i32 0, i32 0))
		br label %compare.end.1
	compare.else.1:
		%21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.6, i32 0, i32 0))
		br label %compare.end.1
	compare.end.1:
	%22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.7, i32 0, i32 0))
	%a = alloca i32, align 4
	%23 = load i32, i32* %a, align 4
	%24 = add i32 0, 2222222
	store i32 %24, i32* %a, align 4
	%25 = load i32, i32* %a, align 4
	%d = alloca double, align 8
	%26 = load double, double* %d, align 8
	%27 = fadd double 0.000000e+00, 2.3232332000000000e+08
	store double %27, double* %d, align 8
	%28 = load double, double* %d, align 8
	%b = alloca i32, align 4
	%29 = load i32, i32* %b, align 4
	%30 = add i32 0, 3
	store i32 %30, i32* %b, align 4
	%31 = load i32, i32* %b, align 4
	%32 = load i32, i32* %a, align 4
	%33 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.8, i32 0, i32 0), i32 %32)
	%b1 = alloca i1
	%34 = load i1, i1* %b1
	%35 = add i1 0, 1
	store i1 %35, i1* %b1
	%36 = load i1, i1* %b1
	%37 = load i32, i32* %a, align 4
	%38 = load i32, i32* %a, align 4
	%39 = add i32 %37, %38
	%40 = load i32, i32* %a, align 4
	%41 = add i32 %39, %40
	%42 = add i32 0, 8
	%43 = add i32 0, 2
	%44 = srem i32 %42, %43
	%45 = add i32 %41, %44
	%46 = load double, double* %d, align 8
	%47 = add i32 0, 3
	%48 = sitofp i32 %47 to double
	%49 = fdiv double %46, %48
	%50 = sitofp i32 %45 to double
	%51 = fadd double %50, %49
	%52 = load i32, i32* %a, align 4
	%53 = load double, double* %d, align 8
	%54 = sitofp i32 %52 to double
	%55 = fmul double %54, %53
	%56 = fadd double %51, %55
	%57 = load double, double* %d, align 8
	%58 = fadd double %56, %57
	%59 = load i32, i32* %a, align 4
	%60 = sitofp i32 %59 to double
	%61 = fsub double %58, %60
	%62 = load i32, i32* %a, align 4
	%63 = load i32, i32* %b, align 4
	%64 = mul i32 %62, %63
	%65 = load double, double* %d, align 8
	%66 = sitofp i32 %64 to double
	%67 = fdiv double %66, %65
	%68 = load i32, i32* %a, align 4
	%69 = load i32, i32* %b, align 4
	%70 = mul i32 %68, %69
	%71 = load double, double* %d, align 8
	%72 = sitofp i32 %70 to double
	%73 = fdiv double %72, %71
	%74 = fmul double %67, %73
	%75 = fadd double %61, %74
	%76 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%77 = call double @function.declaration.d.overload.d.(double %76)
	%78 = fadd double %75, %77
	%79 = load double, double* %d, align 8
	%80 = add i32 0, 1
	%81 = add i32 0, 1
	%82 = call i32 @function.declaration.i.overload.i.i.(i32 %80, i32 %81)
	%convertion.1 = sitofp i32 %82 to double
	store double %convertion.1, double* %d, align 8
	%83 = load double, double* %d, align 8
	%84 = fadd double %78, %83
	%85 = add i32 0, 5
	%86 = call i32 @function.declaration.i.main.i.(i32 %85)
	%87 = sitofp i32 %86 to double
	%88 = fadd double %84, %87
	%89 = load i32, i32* %argc_aux, align 4
	%90 = sub i32 %89, 1
	%91 = add i32 0, 1
	%92 = sub i32 %90, %91
	%93 = add i32 %92, 1
	%94 = load i8**, i8*** %argv_aux, align 8
	%95 = getelementptr inbounds i8*, i8** %94, i32 %93
	%96 = load i8*, i8** %95, align 8
	%97 = call i32 @atoi(i8* %96)
	%98 = sitofp i32 %97 to double
	%99 = fadd double %88, %98
	%100 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.9, i32 0, i32 0), double %99)
	%101 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.10, i32 0, i32 0))
	%102 = load i32, i32* %a, align 4
	%103 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.global.strlit.11, i32 0, i32 0), i32 %102)
	%104 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.global.strlit.12, i32 0, i32 0))
	%105 = load i32, i32* %a, align 4
	%106 = add i32 0, 2
	%107 = add i32 0, 2
	%108 = mul i32 %106, %107
	%109 = add i32 0, 3
	%110 = add i32 0, 5
	%111 = sdiv i32 %109, %110
	%112 = add i32 %108, %111
	%113 = add i32 0, 5
	%114 = call i32 @function.declaration.i.main.i.(i32 %113)
	%115 = add i32 %112, %114
	%116 = icmp sge i32 %105, %115
	br label %label.entry.if2
label.entry.if2:       ;it's if 
	%117 = icmp eq i1 %116, 1
	br i1 %117, label %label.then2, label %label.else2
label.then2:       ;it's if 
	%118 = load i32, i32* %a, align 4
	%119 = add i32 0, 2
	%120 = icmp sle i32 %118, %119
	br label %label.entry.if3
label.entry.if3:       ;it's if 
	%121 = icmp eq i1 %120, 1
	br i1 %121, label %label.then3, label %label.else3
label.then3:       ;it's if 
	%122 = add i32 0, 2
	%123 = load i32, i32* %a, align 4
	%124 = icmp sge i32 %122, %123
	br label %label.entry.if4
label.entry.if4:       ;it's if 
	%125 = icmp eq i1 %124, 1
	br i1 %125, label %label.then4, label %label.else4
label.then4:       ;it's if 
	%126 = add i32 0, 2
	%127 = load i32, i32* %a, align 4
	%128 = icmp sle i32 %126, %127
	br label %label.entry.if5
label.entry.if5:       ;it's if 
	%129 = icmp eq i1 %128, 1
	br i1 %129, label %label.then5, label %label.else5
label.then5:       ;it's if 
	%130 = load i32, i32* %a, align 4
	%131 = add i32 0, 2
	%132 = icmp eq i32 %130, %131
	br label %label.entry.if6
label.entry.if6:       ;it's if 
	%133 = icmp eq i1 %132, 1
	br i1 %133, label %label.then6, label %label.else6
label.then6:       ;it's if 
	%134 = add i32 0, 2
	%135 = load i32, i32* %a, align 4
	%136 = icmp eq i32 %134, %135
	br label %label.entry.if7
label.entry.if7:       ;it's if 
	%137 = icmp eq i1 %136, 1
	br i1 %137, label %label.then7, label %label.else7
label.then7:       ;it's if 
	%138 = load i32, i32* %a, align 4
	%139 = add i32 0, 2
	%140 = icmp sgt i32 %138, %139
	br label %label.entry.if8
label.entry.if8:       ;it's if 
	%141 = icmp eq i1 %140, 1
	br i1 %141, label %label.then8, label %label.else8
label.then8:       ;it's if 
	%142 = load i32, i32* %a, align 4
	%143 = add i32 0, 2
	%144 = icmp slt i32 %142, %143
	br label %label.entry.if9
label.entry.if9:       ;it's if 
	%145 = icmp eq i1 %144, 1
	br i1 %145, label %label.then9, label %label.else9
label.then9:       ;it's if 
	%146 = add i32 0, 2
	%147 = load i32, i32* %a, align 4
	%148 = icmp sgt i32 %146, %147
	br label %label.entry.if10
label.entry.if10:       ;it's if 
	%149 = icmp eq i1 %148, 1
	br i1 %149, label %label.then10, label %label.else10
label.then10:       ;it's if 
	%150 = add i32 0, 2
	%151 = load i32, i32* %a, align 4
	%152 = icmp slt i32 %150, %151
	br label %label.entry.if11
label.entry.if11:       ;it's if 
	%153 = icmp eq i1 %152, 1
	br i1 %153, label %label.then11, label %label.else11
label.then11:       ;it's if 
	%154 = load i32, i32* %a, align 4
	%155 = add i32 0, 2
	%156 = icmp ne i32 %154, %155
	br label %label.entry.if12
label.entry.if12:       ;it's if 
	%157 = icmp eq i1 %156, 1
	br i1 %157, label %label.then12, label %label.else12
label.then12:       ;it's if 
	%158 = add i32 0, 2
	%159 = load i32, i32* %a, align 4
	%160 = icmp ne i32 %158, %159
	br label %label.entry.if13
label.entry.if13:       ;it's if 
	%161 = icmp eq i1 %160, 1
	br i1 %161, label %label.then13, label %label.else13
label.then13:       ;it's if 
br label %label.finished.if13
label.else13:       ;it's else 
br label %label.finished.if13
label.finished.if13:
br label %label.finished.if12
label.else12:       ;it's else 
br label %label.finished.if12
label.finished.if12:
br label %label.finished.if11
label.else11:       ;it's else 
br label %label.finished.if11
label.finished.if11:
br label %label.finished.if10
label.else10:       ;it's else 
br label %label.finished.if10
label.finished.if10:
br label %label.finished.if9
label.else9:       ;it's else 
br label %label.finished.if9
label.finished.if9:
br label %label.finished.if8
label.else8:       ;it's else 
br label %label.finished.if8
label.finished.if8:
br label %label.finished.if7
label.else7:       ;it's else 
br label %label.finished.if7
label.finished.if7:
br label %label.finished.if6
label.else6:       ;it's else 
br label %label.finished.if6
label.finished.if6:
br label %label.finished.if5
label.else5:       ;it's else 
br label %label.finished.if5
label.finished.if5:
br label %label.finished.if4
label.else4:       ;it's else 
br label %label.finished.if4
label.finished.if4:
br label %label.finished.if3
label.else3:       ;it's else 
br label %label.finished.if3
label.finished.if3:
br label %label.finished.if2
label.else2:       ;it's else 
br label %label.finished.if2
label.finished.if2:
	%162 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.global.strlit.13, i32 0, i32 0))
	%163 = load double, double* %d, align 8
	%164 = add i32 0, 2
	%165 = sitofp i32 %164 to double
	%166 = fcmp oge double %163, %165
	br label %label.entry.if14
label.entry.if14:       ;it's if 
	%167 = icmp eq i1 %166, 1
	br i1 %167, label %label.then14, label %label.else14
label.then14:       ;it's if 
	%168 = load double, double* %d, align 8
	%169 = add i32 0, 2
	%170 = sitofp i32 %169 to double
	%171 = fcmp ole double %168, %170
	br label %label.entry.if15
label.entry.if15:       ;it's if 
	%172 = icmp eq i1 %171, 1
	br i1 %172, label %label.then15, label %label.else15
label.then15:       ;it's if 
	%173 = add i32 0, 2
	%174 = load double, double* %d, align 8
	%175 = sitofp i32 %173 to double
	%176 = fcmp oge double %175, %174
	br label %label.entry.if16
label.entry.if16:       ;it's if 
	%177 = icmp eq i1 %176, 1
	br i1 %177, label %label.then16, label %label.else16
label.then16:       ;it's if 
	%178 = add i32 0, 2
	%179 = load double, double* %d, align 8
	%180 = sitofp i32 %178 to double
	%181 = fcmp ole double %180, %179
	br label %label.entry.if17
label.entry.if17:       ;it's if 
	%182 = icmp eq i1 %181, 1
	br i1 %182, label %label.then17, label %label.else17
label.then17:       ;it's if 
	%183 = load double, double* %d, align 8
	%184 = add i32 0, 2
	%185 = sitofp i32 %184 to double
	%186 = fcmp oeq double %183, %185
	br label %label.entry.if18
label.entry.if18:       ;it's if 
	%187 = icmp eq i1 %186, 1
	br i1 %187, label %label.then18, label %label.else18
label.then18:       ;it's if 
	%188 = add i32 0, 2
	%189 = load double, double* %d, align 8
	%190 = sitofp i32 %188 to double
	%191 = fcmp oeq double %190, %189
	br label %label.entry.if19
label.entry.if19:       ;it's if 
	%192 = icmp eq i1 %191, 1
	br i1 %192, label %label.then19, label %label.else19
label.then19:       ;it's if 
	%193 = load double, double* %d, align 8
	%194 = add i32 0, 2
	%195 = sitofp i32 %194 to double
	%196 = fcmp ogt double %193, %195
	br label %label.entry.if20
label.entry.if20:       ;it's if 
	%197 = icmp eq i1 %196, 1
	br i1 %197, label %label.then20, label %label.else20
label.then20:       ;it's if 
	%198 = load double, double* %d, align 8
	%199 = add i32 0, 2
	%200 = sitofp i32 %199 to double
	%201 = fcmp olt double %198, %200
	br label %label.entry.if21
label.entry.if21:       ;it's if 
	%202 = icmp eq i1 %201, 1
	br i1 %202, label %label.then21, label %label.else21
label.then21:       ;it's if 
	%203 = add i32 0, 2
	%204 = load double, double* %d, align 8
	%205 = sitofp i32 %203 to double
	%206 = fcmp ogt double %205, %204
	br label %label.entry.if22
label.entry.if22:       ;it's if 
	%207 = icmp eq i1 %206, 1
	br i1 %207, label %label.then22, label %label.else22
label.then22:       ;it's if 
	%208 = add i32 0, 2
	%209 = load double, double* %d, align 8
	%210 = sitofp i32 %208 to double
	%211 = fcmp olt double %210, %209
	br label %label.entry.if23
label.entry.if23:       ;it's if 
	%212 = icmp eq i1 %211, 1
	br i1 %212, label %label.then23, label %label.else23
label.then23:       ;it's if 
	%213 = load double, double* %d, align 8
	%214 = add i32 0, 2
	%215 = sitofp i32 %214 to double
	%216 = fcmp une double %213, %215
	br label %label.entry.if24
label.entry.if24:       ;it's if 
	%217 = icmp eq i1 %216, 1
	br i1 %217, label %label.then24, label %label.else24
label.then24:       ;it's if 
	%218 = add i32 0, 2
	%219 = load double, double* %d, align 8
	%220 = sitofp i32 %218 to double
	%221 = fcmp une double %220, %219
	br label %label.entry.if25
label.entry.if25:       ;it's if 
	%222 = icmp eq i1 %221, 1
	br i1 %222, label %label.then25, label %label.else25
label.then25:       ;it's if 
br label %label.finished.if25
label.else25:       ;it's else 
br label %label.finished.if25
label.finished.if25:
br label %label.finished.if24
label.else24:       ;it's else 
br label %label.finished.if24
label.finished.if24:
br label %label.finished.if23
label.else23:       ;it's else 
br label %label.finished.if23
label.finished.if23:
br label %label.finished.if22
label.else22:       ;it's else 
br label %label.finished.if22
label.finished.if22:
br label %label.finished.if21
label.else21:       ;it's else 
br label %label.finished.if21
label.finished.if21:
br label %label.finished.if20
label.else20:       ;it's else 
br label %label.finished.if20
label.finished.if20:
br label %label.finished.if19
label.else19:       ;it's else 
br label %label.finished.if19
label.finished.if19:
br label %label.finished.if18
label.else18:       ;it's else 
br label %label.finished.if18
label.finished.if18:
br label %label.finished.if17
label.else17:       ;it's else 
br label %label.finished.if17
label.finished.if17:
br label %label.finished.if16
label.else16:       ;it's else 
br label %label.finished.if16
label.finished.if16:
br label %label.finished.if15
label.else15:       ;it's else 
br label %label.finished.if15
label.finished.if15:
br label %label.finished.if14
label.else14:       ;it's else 
br label %label.finished.if14
label.finished.if14:
	%223 = load double, double* %d, align 8
	%224 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%225 = fcmp oge double %223, %224
	br label %label.entry.if26
label.entry.if26:       ;it's if 
	%226 = icmp eq i1 %225, 1
	br i1 %226, label %label.then26, label %label.else26
label.then26:       ;it's if 
	%227 = load double, double* %d, align 8
	%228 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%229 = fcmp ole double %227, %228
	br label %label.entry.if27
label.entry.if27:       ;it's if 
	%230 = icmp eq i1 %229, 1
	br i1 %230, label %label.then27, label %label.else27
label.then27:       ;it's if 
	%231 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%232 = load double, double* %d, align 8
	%233 = fcmp oge double %231, %232
	br label %label.entry.if28
label.entry.if28:       ;it's if 
	%234 = icmp eq i1 %233, 1
	br i1 %234, label %label.then28, label %label.else28
label.then28:       ;it's if 
	%235 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%236 = load double, double* %d, align 8
	%237 = fcmp ole double %235, %236
	br label %label.entry.if29
label.entry.if29:       ;it's if 
	%238 = icmp eq i1 %237, 1
	br i1 %238, label %label.then29, label %label.else29
label.then29:       ;it's if 
	%239 = load double, double* %d, align 8
	%240 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%241 = fcmp oeq double %239, %240
	br label %label.entry.if30
label.entry.if30:       ;it's if 
	%242 = icmp eq i1 %241, 1
	br i1 %242, label %label.then30, label %label.else30
label.then30:       ;it's if 
	%243 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%244 = load double, double* %d, align 8
	%245 = fcmp oeq double %243, %244
	br label %label.entry.if31
label.entry.if31:       ;it's if 
	%246 = icmp eq i1 %245, 1
	br i1 %246, label %label.then31, label %label.else31
label.then31:       ;it's if 
	%247 = load double, double* %d, align 8
	%248 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%249 = fcmp ogt double %247, %248
	br label %label.entry.if32
label.entry.if32:       ;it's if 
	%250 = icmp eq i1 %249, 1
	br i1 %250, label %label.then32, label %label.else32
label.then32:       ;it's if 
	%251 = load double, double* %d, align 8
	%252 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%253 = fcmp olt double %251, %252
	br label %label.entry.if33
label.entry.if33:       ;it's if 
	%254 = icmp eq i1 %253, 1
	br i1 %254, label %label.then33, label %label.else33
label.then33:       ;it's if 
	%255 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%256 = load double, double* %d, align 8
	%257 = fcmp ogt double %255, %256
	br label %label.entry.if34
label.entry.if34:       ;it's if 
	%258 = icmp eq i1 %257, 1
	br i1 %258, label %label.then34, label %label.else34
label.then34:       ;it's if 
	%259 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%260 = load double, double* %d, align 8
	%261 = fcmp olt double %259, %260
	br label %label.entry.if35
label.entry.if35:       ;it's if 
	%262 = icmp eq i1 %261, 1
	br i1 %262, label %label.then35, label %label.else35
label.then35:       ;it's if 
	%263 = load double, double* %d, align 8
	%264 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%265 = fcmp une double %263, %264
	br label %label.entry.if36
label.entry.if36:       ;it's if 
	%266 = icmp eq i1 %265, 1
	br i1 %266, label %label.then36, label %label.else36
label.then36:       ;it's if 
	%267 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%268 = load double, double* %d, align 8
	%269 = fcmp une double %267, %268
	br label %label.entry.if37
label.entry.if37:       ;it's if 
	%270 = icmp eq i1 %269, 1
	br i1 %270, label %label.then37, label %label.else37
label.then37:       ;it's if 
br label %label.finished.if37
label.else37:       ;it's else 
br label %label.finished.if37
label.finished.if37:
br label %label.finished.if36
label.else36:       ;it's else 
br label %label.finished.if36
label.finished.if36:
br label %label.finished.if35
label.else35:       ;it's else 
br label %label.finished.if35
label.finished.if35:
br label %label.finished.if34
label.else34:       ;it's else 
br label %label.finished.if34
label.finished.if34:
br label %label.finished.if33
label.else33:       ;it's else 
br label %label.finished.if33
label.finished.if33:
br label %label.finished.if32
label.else32:       ;it's else 
br label %label.finished.if32
label.finished.if32:
br label %label.finished.if31
label.else31:       ;it's else 
br label %label.finished.if31
label.finished.if31:
br label %label.finished.if30
label.else30:       ;it's else 
br label %label.finished.if30
label.finished.if30:
br label %label.finished.if29
label.else29:       ;it's else 
br label %label.finished.if29
label.finished.if29:
br label %label.finished.if28
label.else28:       ;it's else 
br label %label.finished.if28
label.finished.if28:
br label %label.finished.if27
label.else27:       ;it's else 
br label %label.finished.if27
label.finished.if27:
br label %label.finished.if26
label.else26:       ;it's else 
br label %label.finished.if26
label.finished.if26:
	%271 = load i1, i1* %b1
	%272 = add i1 0, 1
	%273 = zext i1 %271 to i32
	%274 = zext i1 %272 to i32
	%275 = icmp eq i32 %274, %273
	br label %label.entry1
label.entry1:        ;it's an and
	%276 = icmp eq i1 %275, 1
	br i1 %276, label %label.transition1, label %label.end1
label.transition1:       ;transition of an and
	%277 = load double, double* %d, align 8
	%278 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%279 = fcmp oge double %277, %278
	%280 = icmp eq i1 %279, 1
	br label %label.end1
label.end1:      ; it's the end of an and
	%281 = phi i1 [ 0, %label.entry1 ], [ %280, %label.transition1 ]
	br label %label.entry2
label.entry2:        ;it's an and
	%282 = icmp eq i1 %281, 1
	br i1 %282, label %label.transition2, label %label.end2
label.transition2:       ;transition of an and
	%283 = add i32 0, 2
	%284 = load double, double* %d, align 8
	%285 = sitofp i32 %283 to double
	%286 = fcmp oge double %285, %284
	%287 = icmp eq i1 %286, 1
	br label %label.end2
label.end2:      ; it's the end of an and
	%288 = phi i1 [ 0, %label.entry2 ], [ %287, %label.transition2 ]
	br label %label.entry3
label.entry3:        ;it's an and
	%289 = icmp eq i1 %288, 1
	br i1 %289, label %label.transition3, label %label.end3
label.transition3:       ;transition of an and
	%290 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%291 = load double, double* %d, align 8
	%292 = fcmp ole double %290, %291
	%293 = icmp eq i1 %292, 1
	br label %label.end3
label.end3:      ; it's the end of an and
	%294 = phi i1 [ 0, %label.entry3 ], [ %293, %label.transition3 ]
	br label %label.entry4
label.entry4:        ;it's an or
	%295 = icmp eq i1 %294, 0
	br i1 %295, label %label.transition4, label %label.end4
label.transition4:       ;transition of an or
	%296 = fadd double 0.000000e+00, 2.2000000000000002e+00
	%297 = load double, double* %d, align 8
	%298 = load double, double* %d, align 8
	%299 = fadd double 0.000000e+00, 2.2999999999999998e+00
	%300 = load i32, i32* %a, align 4
	%301 = add i32 0, 2
	store i32 %301, i32* %a, align 4
	%302 = load i32, i32* %a, align 4
	%303 = sitofp i32 %302 to double
	%304 = fadd double %299, %303
	%305 = load double, double* %d, align 8
	%306 = add i32 0, 2
	%convertion.2 = sitofp i32 %306 to double
	store double %convertion.2, double* %d, align 8
	%307 = load double, double* %d, align 8
	%308 = fadd double %304, %307
	store double %308, double* %d, align 8
	%309 = load double, double* %d, align 8
	%310 = fadd double %297, %309
	%311 = fcmp oeq double %296, %310
	%312 = icmp eq i1 %311, 1
	br label %label.end4
label.end4:      ; it's the end of an or
	%313 = phi i1 [ 1, %label.entry4 ], [ %312, %label.transition4 ]
	br label %label.entry.if38
label.entry.if38:       ;it's if 
	%314 = icmp eq i1 %313, 1
	br i1 %314, label %label.then38, label %label.else38
label.then38:       ;it's if 
	%315 = add i1 0, 1
	%316 = load i1, i1* %b1
	%317 = zext i1 %315 to i32
	%318 = zext i1 %316 to i32
	%319 = icmp eq i32 %318, %317
	br label %label.entry.if39
label.entry.if39:       ;it's if 
	%320 = icmp eq i1 %319, 1
	br i1 %320, label %label.then39, label %label.else39
label.then39:       ;it's if 
	%321 = load i1, i1* %b1
	%322 = add i1 0, 1
	%323 = zext i1 %321 to i32
	%324 = zext i1 %322 to i32
	%325 = icmp ne i32 %324, %323
	br label %label.entry.if40
label.entry.if40:       ;it's if 
	%326 = icmp eq i1 %325, 1
	br i1 %326, label %label.then40, label %label.else40
label.then40:       ;it's if 
	%327 = add i1 0, 1
	%328 = load i1, i1* %b1
	%329 = zext i1 %327 to i32
	%330 = zext i1 %328 to i32
	%331 = icmp ne i32 %330, %329
	br label %label.entry.if41
label.entry.if41:       ;it's if 
	%332 = icmp eq i1 %331, 1
	br i1 %332, label %label.then41, label %label.else41
label.then41:       ;it's if 
br label %label.finished.if41
label.else41:       ;it's else 
br label %label.finished.if41
label.finished.if41:
br label %label.finished.if40
label.else40:       ;it's else 
br label %label.finished.if40
label.finished.if40:
br label %label.finished.if39
label.else39:       ;it's else 
br label %label.finished.if39
label.finished.if39:
br label %label.finished.if38
label.else38:       ;it's else 
br label %label.finished.if38
label.finished.if38:
	%333 = load i1, i1* %b1
	br label %label.entry5
label.entry5:        ;it's an and
	%334 = icmp eq i1 %333, 1
	br i1 %334, label %label.transition5, label %label.end5
label.transition5:       ;transition of an and
	%335 = add i1 0, 1
	%336 = icmp eq i1 %335, 1
	br label %label.end5
label.end5:      ; it's the end of an and
	%337 = phi i1 [ 0, %label.entry5 ], [ %336, %label.transition5 ]
	br label %label.entry6
label.entry6:        ;it's an or
	%338 = icmp eq i1 %337, 0
	br i1 %338, label %label.transition6, label %label.end6
label.transition6:       ;transition of an or
	%339 = load i1, i1* %b1
	%340 = icmp eq i1 %339, 1
	br label %label.end6
label.end6:      ; it's the end of an or
	%341 = phi i1 [ 1, %label.entry6 ], [ %340, %label.transition6 ]
	br label %label.entry7
label.entry7:        ;it's an or
	%342 = icmp eq i1 %341, 0
	br i1 %342, label %label.transition7, label %label.end7
label.transition7:       ;transition of an or
	%343 = add i1 0, 1
	br label %label.entry8
label.entry8:        ;it's an and
	%344 = icmp eq i1 %343, 1
	br i1 %344, label %label.transition8, label %label.end8
label.transition8:       ;transition of an and
	%345 = load i1, i1* %b1
	%346 = zext i1 %345 to i32
	%347 = icmp eq i32 %346, 0
	%348 = add i1 0, 0
	%349 = icmp eq i1 %348, 1
	br label %label.end8
label.end8:      ; it's the end of an and
	%350 = phi i1 [ 0, %label.entry8 ], [ %349, %label.transition8 ]
	%351 = icmp eq i1 %350, 1
	br label %label.end7
label.end7:      ; it's the end of an or
	%352 = phi i1 [ 1, %label.entry7 ], [ %351, %label.end8 ]
	br label %label.entry.if42
label.entry.if42:       ;it's if 
	%353 = icmp eq i1 %352, 1
	br i1 %353, label %label.then42, label %label.else42
label.then42:       ;it's if 
	%354 = add i1 0, 1
	br label %label.entry9
label.entry9:        ;it's an and
	%355 = icmp eq i1 %354, 1
	br i1 %355, label %label.transition9, label %label.end9
label.transition9:       ;transition of an and
	%356 = load i1, i1* %b1
	%357 = icmp eq i1 %356, 1
	br label %label.end9
label.end9:      ; it's the end of an and
	%358 = phi i1 [ 0, %label.entry9 ], [ %357, %label.transition9 ]
	br label %label.entry10
label.entry10:        ;it's an or
	%359 = icmp eq i1 %358, 0
	br i1 %359, label %label.transition10, label %label.end10
label.transition10:       ;transition of an or
	%360 = add i1 0, 1
	%361 = icmp eq i1 %360, 1
	br label %label.end10
label.end10:      ; it's the end of an or
	%362 = phi i1 [ 1, %label.entry10 ], [ %361, %label.transition10 ]
	br label %label.entry11
label.entry11:        ;it's an or
	%363 = icmp eq i1 %362, 0
	br i1 %363, label %label.transition11, label %label.end11
label.transition11:       ;transition of an or
	%364 = load i1, i1* %b1
	br label %label.entry12
label.entry12:        ;it's an and
	%365 = icmp eq i1 %364, 1
	br i1 %365, label %label.transition12, label %label.end12
label.transition12:       ;transition of an and
	%366 = add i1 0, 0
	%367 = load i1, i1* %b1
	%368 = zext i1 %367 to i32
	%369 = icmp eq i32 %368, 0
	%370 = icmp eq i1 %369, 1
	br label %label.end12
label.end12:      ; it's the end of an and
	%371 = phi i1 [ 0, %label.entry12 ], [ %370, %label.transition12 ]
	%372 = icmp eq i1 %371, 1
	br label %label.end11
label.end11:      ; it's the end of an or
	%373 = phi i1 [ 1, %label.entry11 ], [ %372, %label.end12 ]
	br label %label.entry.if43
label.entry.if43:       ;it's if 
	%374 = icmp eq i1 %373, 1
	br i1 %374, label %label.then43, label %label.else43
label.then43:       ;it's if 
br label %label.finished.if43
label.else43:       ;it's else 
br label %label.finished.if43
label.finished.if43:
br label %label.finished.if42
label.else42:       ;it's else 
br label %label.finished.if42
label.finished.if42:
	%375 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.global.strlit.14, i32 0, i32 0))
	%376 = load i32, i32* %a, align 4
	%377 = load double, double* %d, align 8
	%378 = fsub double -0.000000e+00, %377
	%379 = sitofp i32 %376 to double
	%380 = fmul double %379, %378
	%381 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.15, i32 0, i32 0), double %380)
	%382 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.16, i32 0, i32 0))
	%383 = add i1 0, 0
	%384 = load i1, i1* %b1
	%385 = zext i1 %384 to i32
	%386 = icmp eq i32 %385, 0
	%compare.2 = icmp eq i1 %386, 1
	br i1 %compare.2, label %compare.if.2, label %compare.else.2
	compare.if.2:
		%387 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.global.strlit.17, i32 0, i32 0))
		br label %compare.end.2
	compare.else.2:
		%388 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.global.strlit.18, i32 0, i32 0))
		br label %compare.end.2
	compare.end.2:
	%389 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.global.strlit.19, i32 0, i32 0))
	%d1 = alloca double, align 8
	%390 = load double, double* %d1, align 8
	%391 = load i32, i32* %argc_aux, align 4
	%392 = sub i32 %391, 1
	%393 = fadd double 0.000000e+00, 1.1000000000000001e+00
	%394 = sitofp i32 %392 to double
	%395 = fadd double %394, %393
	%396 = add i32 0, 3
	%397 = sitofp i32 %396 to double
	%398 = call double @function.declaration.d.overload.d.(double %397)
	%399 = fadd double %395, %398
	%400 = add i32 0, 3
	%401 = add i32 0, 3
	%402 = mul i32 %400, %401
	%403 = sitofp i32 %402 to double
	%404 = fadd double %399, %403
	%405 = add i32 0, 2
	%406 = sitofp i32 %405 to double
	%407 = fadd double %404, %406
	%408 = add i32 0, 2
	%409 = sitofp i32 %408 to double
	%410 = fadd double %407, %409
	%411 = add i32 0, 2
	%412 = sub nsw i32 0, %411
	%413 = sitofp i32 %412 to double
	%414 = fadd double %410, %413
	%415 = add i32 0, 3
	%416 = add i32 0, 3
	%417 = sdiv i32 %415, %416
	%418 = sitofp i32 %417 to double
	%419 = fadd double %414, %418
	store double %419, double* %d1, align 8
	%420 = load double, double* %d1, align 8
	%i = alloca i32, align 4
	%421 = load i32, i32* %i, align 4
	%422 = add i32 0, 0
	store i32 %422, i32* %i, align 4
	%423 = load i32, i32* %i, align 4
	%j = alloca i32, align 4
	%424 = load i32, i32* %j, align 4
	%425 = add i32 0, 0
	store i32 %425, i32* %j, align 4
	%426 = load i32, i32* %j, align 4
	%427 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.global.strlit.20, i32 0, i32 0))
	br label %label.entry.while1
label.entry.while1:       ;it's while 
	%428 = load i32, i32* %i, align 4
	%429 = add i32 0, 10
	%430 = icmp slt i32 %428, %429
	%431 = icmp eq i1 %430, 1
	br i1 %431, label %label.work.while1, label %label.finished.while1
label.work.while1:       ;it's while 
	br label %label.entry.while2
label.entry.while2:       ;it's while 
	%432 = add i32 0, 10
	%433 = load i32, i32* %i, align 4
	%434 = icmp sgt i32 %432, %433
	%435 = icmp eq i1 %434, 1
	br i1 %435, label %label.work.while2, label %label.finished.while2
label.work.while2:       ;it's while 
	br label %label.entry.while3
label.entry.while3:       ;it's while 
	%436 = add i32 0, 20
	%437 = load i32, i32* %j, align 4
	%438 = icmp sgt i32 %436, %437
	br label %label.entry13
label.entry13:        ;it's an and
	%439 = icmp eq i1 %438, 1
	br i1 %439, label %label.transition13, label %label.end13
label.transition13:       ;transition of an and
	%440 = load i32, i32* %i, align 4
	%441 = add i32 0, 10
	%442 = icmp slt i32 %440, %441
	%443 = icmp eq i1 %442, 1
	br label %label.end13
label.end13:      ; it's the end of an and
	%444 = phi i1 [ 0, %label.entry13 ], [ %443, %label.transition13 ]
	%445 = icmp eq i1 %444, 1
	br i1 %445, label %label.work.while3, label %label.finished.while3
label.work.while3:       ;it's while 
	%446 = load i32, i32* %i, align 4
	%447 = load i32, i32* %i, align 4
	%448 = add i32 0, 1
	%449 = add i32 %447, %448
	store i32 %449, i32* %i, align 4
	%450 = load i32, i32* %i, align 4
	%451 = load i32, i32* %j, align 4
	%452 = load i32, i32* %j, align 4
	%453 = add i32 0, 1
	%454 = add i32 %452, %453
	store i32 %454, i32* %j, align 4
	%455 = load i32, i32* %j, align 4
	%456 = load i32, i32* %i, align 4
	%457 = add i32 0, 10
	%458 = icmp eq i32 %456, %457
	br label %label.entry.if44
label.entry.if44:       ;it's if 
	%459 = icmp eq i1 %458, 1
	br i1 %459, label %label.then44, label %label.else44
label.then44:       ;it's if 
	%460 = load i32, i32* %j, align 4
	%461 = add i32 0, 9
	%462 = icmp eq i32 %460, %461
	br label %label.entry.if45
label.entry.if45:       ;it's if 
	%463 = icmp eq i1 %462, 1
	br i1 %463, label %label.then45, label %label.else45
label.then45:       ;it's if 
br label %label.finished.if45
label.else45:       ;it's else 
br label %label.finished.if45
label.finished.if45:
br label %label.finished.if44
label.else44:       ;it's else 
br label %label.finished.if44
label.finished.if44:
	br label %label.entry.while3
label.finished.while3:
	br label %label.entry.while2
label.finished.while2:
	br label %label.entry.while1
label.finished.while1:
	ret void
}

@.global.strlit.1 = private unnamed_addr constant [20 x i8] c"I have two doubles\0A\00", align 1
@.global.strlit.2 = private unnamed_addr constant [19 x i8] c"I have one double\0A\00", align 1
@.global.strlit.3 = private unnamed_addr constant [16 x i8] c"I have one int\0A\00", align 1
@.global.strlit.4 = private unnamed_addr constant [19 x i8] c"I'm the fake main\0A\00", align 1
@.global.strlit.5 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.6 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.8 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.9 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.10 = private unnamed_addr constant [5 x i8] c"\0Aa:\0A\00", align 1
@.global.strlit.11 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.global.strlit.12 = private unnamed_addr constant [11 x i8] c"Before if\0A\00", align 1
@.global.strlit.13 = private unnamed_addr constant [11 x i8] c"After ifs\0A\00", align 1
@.global.strlit.14 = private unnamed_addr constant [11 x i8] c"After ifs\0A\00", align 1
@.global.strlit.15 = private unnamed_addr constant [6 x i8] c"%.16e\00", align 1
@.global.strlit.16 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.17 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.global.strlit.18 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@.global.strlit.19 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.global.strlit.20 = private unnamed_addr constant [14 x i8] c"Before while\0A\00", align 1
