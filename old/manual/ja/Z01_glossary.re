= 用語整理

: プロセス
    PIONEにおけるプロセスとは、基本プロセス構造（①アクション②順次処理③条件処理④反復処理）の複合から成るものを指す。
: ルール 
    適用条件と振る舞いの対。条件が満たされた場合にアクションが実行される、いわゆるIF-THENルールの事。ルール記述列から成るシステムをルールシステムと呼ぶ事にする。
: 前向き推論
    初期状態からゴール状態に至るまでの推論において、初期状態側からたどりゴール状態へと進む方式の事。プロダクションルールは前向き推論の代表例。逆に、ゴール状態から初期状態へと向かう推論を後ろ向き推論と呼ぶ。make, prologがその代表例。
: プロダクションシステム
    ルールシステムの代表的な方式の一つであり、ルールセットとワーキングメモリの対から成るシステム。ワーキングメモリ内のデータに適合するルールを発見した場合、ルールアクションを実行することでワーキングメモリを書き換える。これを繰り返し、ルールの適用が全て終了した場合をゴール状態とする。
: Lindaモデル
    分散処理方式の一つに数えられる協調モデルであり、共有メモリとして機能するタプル空間とそれに対するいくつかの操作（read, take, write等）から構成される。
: タプル空間
    タプル（記号の組）を単位としてデータを格納する空間。
: タスク分割型の分散処理
    分散処理は、何を分割することにより分散し処理を行うのかについて、タスク分割／データ分割の観点が存在する。そのどちらかもしくは両方により分散を行うが、PIONEは前者のみによる分散を実施する。有名な分散処理フレームワークであるMapReduceは両者による分散を行う方式である。
: 特性
    タスクにおける性質とタスクワーカにおける能力を表す表示の事。特性論理により性質と能力のマッチングが計算可能である。
: マルチエージェントシステム
    自律動作を行う複数のエージェントの協調動作によってシステム全体の挙動が成立するシステムの事。
