= 特性

== 目的

PIONEにおける特性は、ルール及びタスクワーカに付与される属性の一種であり、タスクの性質を表す。タスクワーカは、タスクの持つ特性に従い、自身がそのタスクを処理可能かを判定する。

== 応答判断システム

ワーカのタスク取得要求に対して、タプル空間サーバはワーカがタスクを処理出来るか否かを判断する。これを応答判断と呼び、今回はこの判断を決定可能なシステムを構築する。

=== 例：応答文「!Interactive & ^X ← +Interactive」

//emlist{
!Interactive & ^X ← +Interactive
⇒ !Interactive & ^X ← +Interactive & * （空特性追加）
⇒ ^X ← *　（限定特性による必須特性充足除去）
⇒ * ← *　（可能特性除去）
//}

応答文「!Interactive & ^X ← +Interactive」（「X」の能力を持つ「Interactive」のみを実行したいワーカは、Interactiveであることを要求するタスクを処理可能か？）は、応答可能である。

=== 例：応答文「!Interactive & !Linux ← +Interactive & +Windows」

//emlist{
!Interactive & ^Linux ← +Interactive & -Windows
^Linux ← +Windows　（限定特性による必須特性充足除去）
//}

応答文「!Interactive & ^Linux ← +Interactive & +Windows」（「Linux」の能力を持つ「Interactive」のみを実行したいワーカは、InteractiveかつWindowsを要求するタスクを処理可能か？）は、応答不可である。

=== 特性に関わる概念の再構築

まずシステムの前提となる特性概念の再構築を行う。特性の提供と要求の関係による応答の有無を明確に表現する為に、応答文を用意する。応答文は応答演算子と提供式、要求式により構成される表現であり、その応答判断の結果として真偽が決定される（決定方法は後述）。応答文が真である場合にはその応答に成功すると判断され、ワーカはタスクを取得可能である。一方偽である場合には応答に失敗し、取得不可となる。

== 提供式及び要求式における特性一覧

=== 提供特性

==== 可能特性

一項の要求演算子「^」により表わされる提供特性。
項に指定された特性記号がタスク処理に対して提供が可能であることを表す。

//emlist{
^X
//}

==== 限定特性

一項の要求演算子「!」により表わされる提供特性。
項に指定された特性記号がタスク処理に対して提供可能であり、かつその特性を要求するタスクのみを処理するべきであることを表す。

//emlist{
!X
//}

=== 要求特性

==== 必須特性

一項の要求演算子「+」により表わされる要求特性。
項に指定された特性記号がタスク処理に必須であることを表しており、処理を行うワーカに対してその特性を備えている事を要求する。

//emlist{
+X
//}

==== 阻害特性

一項の要求演算子「-」により表わされる要求特性。
項に指定された特性記号がタスク処理を阻害する事を表しており、処理を行うワーカに対してその特性を備えていない事を要求する。

//emlist{
-X
//}

==== 優先特性

一項の要求演算子「?」により表わされる要求特性。
項に指定された特性記号を提供するワーカは優先特性を持つタスクを優先して処理する事を要求する。

//emlist{
?X
//}

=== 共通

==== 空特性

記号「*」により表わされる特殊な特性であり、タスク処理において特性を要求しない事（要求特性としての空特性）や能力を持たない事（提供特性としての空特性）を表す。

//emlist{
*
//}

==== 全特性

記号「＠」により表わされる特殊な特性であり、タスク処理において全ての必須特性や全ての特性の限定特性を表す。

//emlist{
@
//}

==== 記号一覧

: 特性記号
    A, B, C, ...
: 特殊特性
    *, @
: 提供演算子
    ^, !
: 要求演算子
    +, -, ?
: 応答演算子
    ←
: 結合子
    &, |
: 補助記号
    (, )

== 統語

: 応答文
    提供式 ← 要求式
: 提供式
     *, @, ^ 特性記号, ! 特性記号, 提供式 & 提供式, 提供式 | 提供式, ( 提供式 )
: 要求式
     *, @, + 特性記号, - 特性記号, ? 特性記号, 要求式 & 要求式, 要求式 | 要求式, ( 要求式 )
 
ただし結合子は、「|」が「&」の結合に優先する。例えば +A & +B | +C & +D であれば、+A & ( +B | +C ) & +D と見做される。 

== 応答判断の算出方法

応答判断は、下記に示す応答文に対する書換規則の適用により実現する。応答文を書換規則により「* → *」に書き換える事が出来る場合、応答文は真であると判断する（要求特性のないタスクは、提供特性のないワーカにより処理可能である為）。それ以外の場合、応答文は偽である。書き換えによる応答判断の具体的な手順は次の通り：

 1. 単一化規則を全て適用し、書き換え可能な箇所がなくなるまで繰り返す
 2. 上記の結果に対して除去規則を全て適用し、書き換え可能な箇所がなくなるまで繰り返す
 3. 上記により得られた特性応答文が「* → *」である場合には真、それ以外の場合には偽と判断する

=== 書換規則

提供式、要求式、または応答文は、下記の規則により書き換えが可能であるとする。
※規則における下記の記号の意味は次の通り：

→	左の記号列を右の記号列に書き換えられることを表す
X	任意の特性記号を表す
Γ	任意の提供式を表す
Δ	任意の要求式を表す

==== 単一化規則

: and単一化
    Γ & Γ → Γ @<br>{}
    Δ & Δ → Δ @<br>{}
    理由：　重複した式は消去して構わない
: 空特性によるand単一化
    * & Γ → Γ @<br>{}
    * & Δ → Δ @<br>{}
    理由：　and結合の空特性は何も主張していない
: or単一化
    Γ | Γ → Γ @<br>{}
    Δ | Δ → Δ @<br>{}
    理由：　重複した式は消去して構わない
: 空特性によるor単一化
    * | Δ → * @<br>{}
    理由：　要求式に限ればor結合の空特性は何も主張していない @<br>{}
   （注：提供式に対する規則適用「* | Γ → *」は認めない）
: and集約
    (Γ1 & Γ2) | (Γ1 & Γ3) → Γ1 & (Γ2 | Γ3) @<br>{}
    (Δ1 & Δ2) | (Δ1 & Δ3) → Δ1 & (Δ2 | Δ3) @<br>{}
    理由：　結合子＆は｜に対して分配的である
: or集約
    (Γ1 | Γ2) & (Γ1 | Γ3) → Γ1 | (Γ2 & Γ3) @<br>{}
    (Δ1 | Δ2) & (Δ1 | Δ3) → Δ1 | (Δ2 & Δ3) @<br>{}
    理由：　結合子｜は＆に対して分配的である
: 中和
    +X | -X → * @<br>{}
    理由：　必須または阻害であれば特性はあってもなくても良いので何も主張していない
: 必須特性による優先特性背景化
    +X & ?X → +X @<br>{}
    理由：　優先特性よりも必須特性の要求が勝る
: 阻害特性による優先特性背景化
    -X & ?X → -X @<br>{}
    理由：　優先特性よりも阻害特性の要求が勝る
: 優先特性による必須特性背景化
    ?X | +X → ?X @<br>{}
    理由：　優先特性の要求は必須特性よりも弱い為、or句内では弱い要求を採る
: 優先特性による阻害特性前景化
    ?X | -X → ?X @<br>{}
    理由：　優先特性の要求は必須特性よりも弱い為、or句内では弱い要求を採る
: 限定単一化
    !X & ^X → !X @<br>{}
    理由：　可能特性よりも限定特性の主張が勝る
: 可能単一化
    !X | ^X → ^X @<br>{}
    理由：　可能特性の主張は限定特性よりも弱い為、or句内では弱い主張を採る

==== 除去規則:

: 可能特性による必須特性充足除去
    ((^X | Γ1) & Γ2 ← (+X | Δ1) & Δ2) → (Γ2 ← Δ2)　ただしΓ1 及びΓ2 、Δ1、Δ2にXを含まない場合 @<br>{}
    Γ1＝@及びΔ1=@の場合、(^X & Γ ← +X & Δ) → (Γ←Δ)　ただしΓ及びΔにXを含まない場合 @<br>{}
    理由：　可能特性は必須特性の要求を満たす
: 限定特性による必須特性充足除去
    ((!X | Γ1) & Γ2 ← (+X | Δ1) & Δ2) → (Γ2 ← Δ)　ただしΓ1 及びΓ2 、Δ1、Δ2にXを含まない場合 @<br>{}
    Γ1＝@及びΔ1=@の場合、(!X & Γ ← +X & Δ) → (Γ ← Δ)　ただしΓ及びΔにXを含まない場合 @<br>{}
    理由：　限定特性は必須特性の要求を満たす
: 阻害特性充足除去
    ((*| Γ) ← (-X | Δ1)& Δ2) → (Γ ← Δ2)　ただしΓ及びΔ1、Δ2にXを含まない場合 @<br>{}
    Γ1＝@及びΔ1=@の場合、(* & Γ ← -X & Δ) → (Γ & Δ)　ただしΓおよびΔ にXを含まない場合 @<br>{}
    理由：　特性が提供されていなければ、阻害特性が満たされる
: or句内空特性除去
    (* | Γ ← *) → (* ← *) @<br>{}
    理由：　or句内の空特性は、要求が空の場合のみ除去可能
: 優先特性除去
    (Γ ← ?X & Δ) → (Γ ← Δ)　ただしΔにXを含まない場合 @<br>{}
    理由：　優先特性は特性応答判断に影響しない
: 可能特性除去
    (^X & Γ ← Δ) → (Γ←Δ)　ただしΓ及びΔにXを含まない場合 @<br>{}
    理由：　可能特性は、要求特性に影響しない限り無視出来る

==== 補助規則

: and空特性追加
    Γ → Γ & * @<br>{}
    Δ → Δ & * @<br>{}
    理由：　空特性は何も主張しない為、and結合であれば任意に追加可能
: or全特性追加
    Γ → Γ | @ @<br>{}
    Δ → Δ | @ @<br>{}
    理由：　全特性はor結合であれば任意に追加可能
: 交換律
    Γ1 & Γ2 → Γ2 & Γ1 @<br>{}
    Γ1 | Γ2 → Γ2 |  Γ1 @<br>{}
    Δ1 & Δ2 → Δ2 & Δ1 @<br>{}
    Δ1 | Δ2 → Δ2 | Δ1 @<br>{}
    理由：　特性に順序はない為、交換律に従う
: 結合律
    (Γ1 & Γ2) & Γ3 → Γ1 & (Γ2 & Γ3) @<br>{}
    Γ1 & ( Γ2 & Γ3) → ( Γ1 & Γ2) & Γ3 @<br>{}
    (Γ1 | Γ2) | Γ3 → Γ1 | (Γ2 | Γ3) @<br>{}
    Γ1 | ( Γ2 | Γ3) → ( Γ1 | Γ2) | Γ3 @<br>{}
    (Δ1 & Δ2) & Δ3 → Δ1 & (Δ2 & Δ3) @<br>{}
    Δ1 & (Δ2 & Δ3) → (Δ1 & Δ2) & Δ3 @<br>{}
    (Δ1 | Δ2) | Δ3 → Δ1 | (Δ2 | Δ3) @<br>{}
    Δ1 | (Δ2 | Δ3) → (Δ1 | Δ2) | Δ3 @<br>{}
    理由：　＆及び｜は結合的である

== 応答判断例

=== 例「^A ← +A」

//emlist{
^A ← +A
^A & * ← +A & *　（and空特性追加）
(^A | @) & * ← (+A | @) & * （or全特性追加）
* ← *　（可能特性による必須特性充足除去）
//}

以上により「* ← *」が導出された為、応答文「^A ← +A」は真である。

=== 例「^A ← -A」

//emlist{
^A ← -A
//}

「^A ← -A」に適用可能な除去規則は存在しない為（-Aを除去できるのは、阻害特性充足除去のみであるが、適用不可）、「* ← *」に書き換えることはできない。従って応答文「^A ← -A」は偽である。

=== 例「^A ← ?A」

//emlist{
^A ← ?A
^A ← ?A & *　（and空特性追加）
^A ← *　（優先特性除去）
* ← *　（可能特性除去）
//}

以上により「* ← *」が導出された為、応答文「^A ← ?A」は真である。

=== 例「!A ← ?A」

//emlist{
!A ← ?A
!A ← ?A & *　（and空特性追加）
!A ← *　（優先特性除去）
//}

「!A ← *」に適用可能な除去規則は存在しない為、「* ← *」に書き換えることはできない。従って応答文「!A ← ?A」は偽である。

=== 例「!A & !B ← +A & +B」

//emlist{
!A & !B ← +A & +B
!B ← +B　（限定特性による必須特性充足除去）
!B & * ← +B & *　（and空特性追加）
* ← *　（限定特性による必須特性充足除去）
//}

以上により「* ← *」が導出された為、応答文「!A & !B ← +A & +B」は真である。

=== 例「!A | !B ← +A & +B」

//emlist{
!A | !B ← +A & +B
(!A | !B) & * ← +A & +B　（and空特性追加）
* ← +B　（限定特性による必須特性充足除去）
//}

「* ← +B」に適用可能な除去規則は存在しない為、「* ← *」に書き換えることはできない。
従って応答文「!A | !B ← +A & +B」は偽である。

=== 例「^A | !B ← +A」

//emlist{
^A | !B ← +A
(^A | !B) & * ← +A & *　（and空特性追加）
* ← *　（限定特性による必須特性充足除去）
//}

以上により「* ← *」が導出された為、応答文「^A | !B ← +A」は真である。

=== 例「^A | ^B ← +A & +B」

//emlist{
^A | ^B → +A & +B
(^A | ^B) & * ← +A & +B　（and空特性追加）
* ← +B　（可能特性による必須特性充足除去）
//}

「* ← +B」に適用可能な除去規則は存在しない為、「* ← *」に書き換えることはできない。
従って応答文「(^A | ^B) ← +A & +B」は偽である。

=== 例「* | !A ← +A」

//emlist{
* | !A ← +A
!A | * ← +A　（交換律）
(!A | *) & * ← +A & * （and空特性追加）
* ← *　（限定特性による必須特性充足除去）
//}

以上により「* ← *」が導出された為、応答文「* | !A ← +A」は真である。

=== 例「* | !A ← -A」

//emlist{
* | !A ← -A
(* | !A) & * ← -A & * (and空特性追加)
(* | !A) & * ← (-A | @) & * (全特性追加)
* ← * (阻害特性充足除去) 
//}

以上により「* ← *」が導出された為、応答文「* | !A ← -A」は真である。

=== 例「* | !A ← ?A」

//emlist{
* | !A ← ?A
* | !A ← ?A & * (and空特性追加)
* | !A ← * (優先特性除去)
* ← * (or句内空特性除去) 
//}

以上により「* ← *」が導出された為、応答文「* | !A ← ?A」は真である。
