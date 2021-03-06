= はじめに

== PIONEとは何か

PIONE（Process-rule for Input/Output Negotiation Environment）は、前向き推論型の
ルール方式を採用したワークフローシステムである。入力ファイルに対して定義書に記述
された処理を適用することにより、分散環境において出力ファイルを得る事が出来る。
PIONEエンジンはMITライセンスに従って配布されており、オープンソースソフトウェアと
して自由に使用及び再配布が可能である。

PIONEの開発目的は、汎用のプロセス定義方式（記述方式）を提供し、またその処理を行う
システムを提供する事にある。より具体的には、makeによるプロセス定義に対する改善と
して、下記を目的としている。

 * 記述性の優れたプロセス定義方式を提供する
 * 多入力・多出力のデータフローを処理する
 * 多様な環境における分散処理を可能とする
 * プロセス定義の再利用性を確保する

== 何が出来るのか

PIONEを利用することにより、プロセスの定義及び処理が可能である。

== 特徴

PIONEは上記の目的を達成するため、プロセス定義をルール形式により記述し、タプル空間
に接続した複数のエージェントが協調動作を行うことで処理を実現する。PIONEは次に挙げ
る特徴を備える事で、優れた記述性と効率的な処理、柔軟な運用を実現する。

=== ルールシステムである

ファイルを処理単位とするプロダクションシステム類似の独自の前向き推論型ルールシス
テムを採用しており、プロセスは全て構成原理に基づくルール形式により記述する。ルー
ルには「フロールール」と「アクションルール」の二種類が存在し、プロセスを構成する
フローとアクションを明確に区別して表現する事で定義の再利用性を高めている。またメ
モリ空間は単一ではなくドメインという単位で区切られており、処理の影響を局所に留め
る事で副作用を気にする事なく記述及び処理を行なう事が出来る。また、ルールエンジン
はルールに従い処理順序や並列可能性等を自動的に判断する。従ってフローを全て記述す
る必要がないという利点があり、記述性に優れている。

=== 処理効率に優れる

ファイルの依存関係をルールの入出力条件として記述する事で、make同様の効率的な更新
処理を実現する。即ち、処理すべき処理のみを行ない、無駄がない。

=== 多様な環境を想定した分散処理が可能である

LINDAモデルに基づき、タスク分割型の分散処理を実現する。ルールエンジンはタプル空間
をワーキングメモリとして利用し、タスクを必要な時に必要な分だけ分散して処理する。

タスクとワーカは「特性」の概念により適切なマッチングが可能である。これにより多
様な環境においてもワーカがタスク処理に成功する事を

=== マルチエージェントシステムである

マルチエージェントシステムであり、機能及び役割の分割が実現されている。

== システム構成

PIONEはマルチエージェントシステムであり、各エージェントが協調動作することにより処理を実現する。エージェントには下記のものが存在する。

: クライアント
   タプル空間の提供とプロセス処理依頼を行う※
: ブローカ
   タプル空間の状況把握とタスクワーカの割当管理を行う
: タスクワーカ
   タプル空間に存在するタスクを処理する
: 入力ジェネレータ
   初期データをタプル空間に入力する
: ロガー
   ログの管理を行う
: ルールプロバイダ
   タスクワーカに対するルールの提供を行う
: タプル空間プロバイダ
   タプル空間レシーバにタプル空間の場所を伝達する
: タプル空間レシーバ
   ブローカに対してタプル空間を提供する
: リレー
   セグメントを超える為にクライアント・ブローカ間通信を中継する
   ※将来的には、タプル空間の提供と処理依頼の役割は分割される予定

以上のエージェントをまとめ、PIONEは次のような基本構成を形成する。

: クライアント群
   プロセス処理依頼とタプル空間の提供を行う
: ブローカ群
   タスクワーカを供給し、プロセス処理を実行する
: リレーサーバ
   クライアントとブローカの通信を中継する
: ファイルサーバ
   ファイルストレージを提供する
   ※ 将来的には、タプル空間の提供と処理依頼の役割は分割される予定

クライアント群はプロセス処理依頼を実現し、ブローカ群は依頼された処理を実施する。
リレーサーバは、ネットワークセグメントが異なるクライアント群とブローカ群を接続す
る役割を果たす。必要に応じてこれらの郡を組み合わせる事により、多様な運用を可能に
する。

=== クライアント群

標準的なクライアント構成は下記のエージェントから成る。

 * クライアント
 * 入力ジェネレータ
 * ロガー
 * ルールプロバイダ
 * タプル空間プロバイダ
 * タスクワーカ

クライアント群は、タプル空間の提供や入力ジェネレータのデータ投入などにより、処理
依頼を可能とする環境を構築する。クライアント群は概ね下記のシーケンスにより処理依
頼を実現する。

 1. クライアントがタプル空間の提供を開始する。
 2. ロガーがタプル空間へ接続し、ログを監視する。
 3. 入力ジェネレータがタプル空間に接続し、入力データをタプル空間上に反映する。ストリーム処理の場合には入力追加の継続監視を行う。
 4. 定義書を翻訳し、ルールを得る。ルールプロバイダがルールをタスクワーカに配信する。
 5. タプル空間プロバイダによるタプル空間の存在通知を開始する。
 6. タスクワーカが起動される。※
 7. クライアントがルートルールの実行を開始する。

※タスクワーカはブローカ側においても起動されるが、クライアント側のみで処理を完結するスタンドアローン実行時やクライアント側のみで実行されるべきプロセスを処理する為に存在する。

==== ブローカ群

標準的なブローカ構成は下記のエージェントから成る。

 * ブローカ
 * タスクワーカ
 * タプル空間レシーバ

ブローカ側のシーケンスは下記の通りとなる。

 1. ブローカが起動される。
 2. タプル空間レシーバが起動される。
 3. タプル空間レシーバに対して存在通知が行われた場合、タスクワーカが起動されてタプル空間との接続が行われる。
 4. タプル空間に接続されたタスクワーカがタスク処理を開始する。

==== リレーサーバ

リレーサーバは下記エージェントから成る。

 * リレー
 * タプル空間プロバイダ

リレーはクライアント側からの接続により、ブローカ側に対してクライアントと同様の振る舞いを行う。

==== ファイルサーバ

ファイルサーバはファイルデータを実際に保持する機能を果たす。ファイルサーバ自身はPIONEシステムが提供するのではなく、既存の一般的なファイルサーバを利用する事になる。現在PIONEが対応するファイルサーバとしては、ローカルファイル、FTPサーバ、Dropboxが存在する。

=== 運用形態

PIONEシステムの実際の構成は、運用により基本構成を組み合わせて柔軟に変更が可能である。目的に応じて下記のような運用形態が考えられる。

: クライアント群のみによる、スタンドアローン構成
    //noindent
    例）ローカルマシン単体で処理を行う場合@<br>{}
    例）定義書の試験を行う場合
: ブローカ群・リレーサーバ構成
    //noindent
    例）計算能力を提供するサービスを行う場合@<br>{}
        クライアント群／ブローカ群／ファイルサーバ構成@<br>{}
    例）LAN内の計算機を使用した分散処理を行う場合@<br>{}
        クライアント群／ブローカ群／リレーサーバ／ファイルサーバ構成@<br>{}
    例）インターネットを経由した分散処理を行う場合
: エージェント間通信
    各エージェントは基本的にタプル空間を共有メモリとして協調動作を実現する。タプル空間はクライアントが提供するが、他エージェントがタプル空間に接続する方法は分散オブジェクト通信による。ただしプロセス間通信としてタプル空間を経ずに直接分散オブジェクト通信を行う場合（例えば、ブローカによるタスクワーカの割当管理や、リレーによる通信の中継）や、下記に示す存在通知といった例外が存在する。
: 存在通知
    クライアント群とブローカ群はタプル空間を共有する為に、ブローカ群はタプル空間の存在場所をクライアント群から伝達されなければならない。このタプル空間の存在の通知を存在通知と呼び、これをタプル空間プロバイダとタプル空間レシーバにより実現する。クライアント群に属するタプル空間プロバイダはタプル空間の存在をUDPパケットのブロードキャストにより伝達し、ブローカ群に属するタプル空間レシーバはそれを受け取りタプル空間参照に変換する。

