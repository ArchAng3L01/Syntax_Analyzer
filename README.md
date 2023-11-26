# Syntax_Analyzer

Syntax analyzer for input grammatic

Program → Begin Descriptions Operators End

Begin → PROGRAM Id

End → END Id

Descriptions → Descr | Descr Descriptions

Operators→ Op | Op Operators

Descr → Type VarList

Type → INTEGER | REAL

VarList → Id | Id , VarList

Op → Id = Expr

SimpleExpr → Id | Const | ( Expr ) | ITOR ( Expr ) | RTOI ( Expr )

Expr → SimpleExpr | SimpleExpr + Expr | SimpleExpr - Expr

Id → Letter | Letter Id

Const → IntNum | RealNum

IntNum → Digit | Digit IntNum

RealNum → IntNum.IntNum

Digit → 0 | 1 | . . . | 9

Letter → a | b | . . . | z | A | B | . . . | Z