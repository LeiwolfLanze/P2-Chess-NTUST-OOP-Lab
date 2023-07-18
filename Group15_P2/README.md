# 網頁GUI使用說明
* 點擊或拖拉以移動棋子
* 可在左上欄位中輸入FEN，按下Enter鍵或Load可載入當前顯示的FEN，按下Copy可複製到剪貼簿
* 想要讓黑方先下就把FEN的w改成b
* 按下Replay可重置棋盤
* 可按undo和redo來還原、取消還原當前對局中做過的步驟（每次Load或Replay就會清空紀錄）
* 按Next song切換歌曲，當切換到最後一首歌之後音樂會停下，再按一次可重播第一首歌。
* 遊戲發生特殊事件（Checkmate、Stalemate、時間到、投降之類）時會暫時跳出對話方塊告知。
* 遊戲結束之後還是可以undo, remove和移動棋子，不會強行重置，要不要繼續玩是你的自由。
* 點擊棋盤上下的黑白旗幟可替黑或白方投降
* 兵走到最後一列的格子上時，該格會顯示四個棋子圖示（騎士、主教、車、皇后），點擊對應的圖片就能把兵升變成該棋子，按其他地方可取消。


# Command Line (Chess.exe) 使用說明

## Commands In Menu

---

| Command | Description | Short term |
| --- | --- | --- |
| `New Game` | To new a game with default settings | `ng` |
| `load <FEN>` | To new a game with given FEN code | `l <FEN>` |

### Sub-commands for New Game

---

| Command | Description | Short term |
| --- | --- | --- |
| `White` | To choose White as the player to go first | `w` |
| `Black` | To choose Black as the player to go first | `b` |

## Commands In Execution

---

| Command | Description | Short term |
| --- | --- | --- |
| `undo` | To undo the move | `Null` |
| `redo` | To redo the move | `Null` |
| `reset` | To reset a game with default settings | `Null` |
| `reload <FEN>` | To reload a game with given FEN code | `Null` |
| `getFEN` | To get the FEN code for current board | `Null` |
| `capitulate` | To capitulate | `Null` |
| `<src> <dest>` | To move a piece | `Null` |

## Commands In Promotion

---

| Command | Description | Short term |
| --- | --- | --- |
| `Rook` | To promote the pawn to a rook | `r` |
| `Knight` | To promote the pawn to a knight | `k` |
| `Bishop` | To promote the pawn to a bishop | `b` |
| `Queen` | To promote the pawn to a queen | `q` |

## Commands In Play Again Section

---

| Command | Description | Short term  |
| --- | --- | --- |
| `Restart` | To restart a game with default settings | `r` |
| `Back to Menu` | To head back to the start menu | `b` |
| `Esc` | To end the game | `e` |

## FEN Format

---

```bash
<Pieces> <Turn> <CA> <EP> <HM> <FM>
```

| Code | Description | Necessity | Default value |
| --- | --- | --- | --- |
| Pieces | R8/R7/R6/R5/R4/R3/R2/R1 | Necessary parameter |  |
| Turn  | Which color to Move ( Whose turn ) | Unnecessary parameter | `1` |
| CA | Castling availability | Unnecessary parameter | `KQkq` |
| EP | Possible en passant | Unnecessary parameter | `-` |
| HM | Halfmove clock | Unnecessary parameter | `0` |
| FM | The number of fullmove (completed turns in the game) | Unnecessary parameter | `1` |

* More details are provided on：https://leeward-alyssum-312.notion.site/OOP-Lab-Project-02-Chess-Game-d2c2a10154504035a757fb6712177bab
