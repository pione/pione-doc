= サンプル「Fib.pione」

定義書の設計及び記述の例として、フィボナッチ数の算出を行う定義書「Fib.pione」を説明する。
フィボナッチ数は下記の条件により求められる数である。
n番目のフィボナッチ数を F@<sub>{n} で表すと、

F@<sub>{0} = 0
F@<sub>{1} = 1
F@<sub>{n+2} = F@<sub>{n} + F@<sub>{n+1}

である。

これを定義書とする場合には、まず定義書のエントリーとなるルールMainの入出力を決定する。
N番目のフィボナッチ数を求める場合、パラメータによりNを指定し（指定しない場合、10番目のフィボナッチ数を求めるものとする）、
その結果がresult.txtに書き出されるプロセスであるとする。
この設定の場合、

//emlist{
Rule Main
  param $N := 10
  output 'result.txt'
Flow
  ...
End
//}





//emlist{
Rule Main
  output 'result.txt'
  param $N := 10
Flow
  rule Fib
  rule Result
End

Rule Fib0
  output 'fib0.txt'
Action
  echo -n '0' > fib0.txt
End

Rule Fib1
  output 'fib1.txt'
Action
  echo -n '1' > fib1.txt
End

Rule FibN
  input 'fib{$P1}.txt'
  input 'fib{$P2}.txt'
  output 'fib{$N}.txt'
  param $N
  param $P1
  param $P2
Action
  expr `cat {$I[1]}` + `cat {$I[2]}` > {$O[1]}
End

Rule Fib
  output 'fib{$N}.txt'
  param $N
Flow
  case $N
  when 0
    rule Fib0
  when 1
    rule Fib1
  else
    $P1 := $N - 2
    $P2 := $N - 1
    rule Fib.params({N: $P1})
    rule Fib.params({N: $P2})
    rule Calc.params({N: $NUM, P1: $P1, P2: $P2})
  end
End

Rule Result
  input 'fib{$N}.txt'
  output 'result.txt'
  param $N
Action
  cat {$I[1]} > {$O[1]}
End
//}

