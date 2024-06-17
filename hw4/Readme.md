# 多執行緒提款與存款程式

## 目標

這個專案旨在展示多執行緒環境下如何處理競態條件，並通過兩個版本的程式展示使用 mutex 與不使用 mutex 的差異。

## 程式說明

我們創建了兩個版本的多執行緒提款與存款程式：

1. `race_condition.c`：這個版本不使用 mutex，因而會產生競態條件。
2. `no_race_condition.c`：這個版本使用 mutex，來防止競態條件的發生。

### 需求

a. 使用者應紀錄自己原本帳戶有多少錢，每次存提多少錢，還剩下多少錢。
b. 每次存提款請求給銀行之後，銀行應傳回還剩下多少錢。
c. 使用者應檢核『存款＋-存提款數量＝剩下金額』是否正確，如果有錯立刻報錯。

## 執行結果

### 無 mutex 的版本

```bash
$ gcc -o race_condition race_condition.c -lpthread
$ ./race_condition
Account balance: 23456
Error: Expected account balance is 1000, but got 23456
