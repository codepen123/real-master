<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>漢字学習システム - ランダム完全版</title>
    <style>
        body {
            font-family: 'Helvetica Neue', Arial, 'Hiragino Kaku Gothic ProN', 'Hiragino Sans', Meiryo, sans-serif;
            background-color: #f7f9fa;
            color: #333;
            margin: 0;
            padding: 20px;
        }
        .container {
            max-width: 650px;
            margin: 0 auto;
        }
        h1 {
            text-align: center;
            font-size: 24px;
            color: #2c3e50;
            margin-bottom: 20px;
            border-bottom: 2px solid #bdc3c7;
            padding-bottom: 10px;
        }
        .info-bar {
            background-color: #e8f4f8;
            border-left: 4px solid #2980b9;
            padding: 10px;
            margin-bottom: 20px;
            font-size: 14px;
            border-radius: 0 4px 4px 0;
        }
        .card {
            background: #fff;
            border-radius: 8px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.08);
            padding: 15px 20px;
            margin-bottom: 12px;
            display: flex;
            flex-direction: column;
        }
        .question-block {
            display: flex;
            justify-content: space-between;
            align-items: flex-start;
            gap: 15px;
        }
        .question {
            font-size: 17px;
            font-weight: bold;
            line-height: 1.6;
            flex-grow: 1;
        }
        .meta-tag {
            color: #7f8c8d;
            font-size: 12px;
            font-weight: normal;
            display: block;
            margin-bottom: 4px;
        }
        .katakana {
            color: #d35400;
            text-decoration: underline;
            font-size: 18px;
        }
        .kanji-target {
            color: #2980b9;
            text-decoration: underline;
            font-size: 18px;
        }
        .btn-show {
            background-color: #7f8c8d;
            color: #fff;
            border: none;
            padding: 6px 12px;
            font-size: 13px;
            border-radius: 4px;
            cursor: pointer;
            transition: background 0.2s;
            white-space: nowrap;
        }
        .btn-show:hover {
            background-color: #34495e;
        }
        .answer-box {
            margin-top: 10px;
            font-size: 18px;
            font-weight: bold;
            color: #e74c3c;
            border-top: 1px dashed #efefef;
            padding-top: 8px;
            display: none;
        }
        .answer-box.show {
            display: block;
        }
    </style>
</head>
<body>

<div class="container">
    <h1>漢字マスター（第17回〜第24回 ランダム版）</h1>
    <div class="info-bar">
        💡 ページを再読み込み（リロード）するたびに、すべての問題が自動でシャッフルされます。
    </div>

    <div id="quiz-content"></div>
</div>

<script>
// 全データ配列（不具合箇所を修正済み）
const quizData = [
    // ==========================================
    // 書き問題セクション
    // ==========================================
    { group: "第17回 【書き】", q: "出場を<span class='katakana'>ジタイ</span>する。", a: "辞退" },
    { group: "第17回 【書き】", q: "今期かぎりで会長を<span class='katakana'>ジニン</span>する。", a: "辞任" },
    { group: "第17回 【書き】", q: "<span class='katakana'>ジセイ</span>の句を残す。", a: "辞世" },
    { group: "第17回 【書き】", q: "提出期限が<span class='katakana'>セッパク</span>する。", a: "切迫" },
    { group: "第17回 【書き】", q: "船の<span class='katakana'>テンプク</span>を防ぐ。", a: "転覆" },
    { group: "第17回 【書き】", q: "<span class='katakana'>フクメン</span>で批評活動をする。", a: "覆面" },
    { group: "第17回 【書き】", q: "日ごろから<span class='katakana'>ヨウジョウ</span>する。", a: "養生" },
    { group: "第17回 【書き】", q: "卵には<span class='katakana'>ジヨウ</span>がある。", a: "滋養" },
    { group: "第17回 【書き】", q: "自己の<span class='katakana'>シュウヨウ</span>に努める。", a: "修養" },
    { group: "第17回 【書き】", q: "<span class='katakana'>キョウヨウ</span>を身につける。", a: "教養" },
    { group: "第17回 【書き】", q: "音楽の<span class='katakana'>ソヨウ</span>がある。", a: "素養" },
    { group: "第17回 【書き】", q: "オリンピックを<span class='katakana'>カイサイ</span>する。", a: "開催" },
    { group: "第17回 【書き】", q: "競技会を<span class='katakana'>シュサイ</span>する。", a: "主催" },
    { group: "第17回 【書き】", q: "<span class='katakana'>サイミン</span>療法で治す。", a: "催眠" },
    { group: "第17回 【書き】", q: "子どもの<span class='katakana'>ヘンショク</span>を直す。", a: "偏食" },
    { group: "第17回 【書き】", q: "頑固で<span class='katakana'>ヘンシュウ</span>な人。", a: "偏執" },
    { group: "第17回 【書き】", q: "いわれなき<span class='katakana'>ヘンケン</span>の打破。", a: "偏見" },
    { group: "第17回 【書き】", q: "学歴<span class='katakana'>ヘンチョウ</span>の社会。", a: "偏重" },
    { group: "第17回 【書き】", q: "<span class='katakana'>ヘンコウ</span>した政治を批判する。", a: "偏向" },
    { group: "第17回 【書き】", q: "富の<span class='katakana'>ヘンサイ</span>を防ぐ。", a: "偏在" },

    { group: "第18・19回 【書き】", q: "戦術的な<span class='katakana'>シキサイ</span>を帯びる。", a: "色彩" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>タサイ</span>な顔ぶれ。", a: "多彩" },
    { group: "第18・19回 【書き】", q: "異彩を放つ<span class='katakana'>イサイ</span>な新人。", a: "異才" },
    { group: "第18・19回 【書き】", q: "プレーに<span class='katakana'>セイサイ</span>を欠く。", a: "精彩" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>フキュウ</span>の名作。", a: "不朽" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ロウキュウ</span>化した家屋。", a: "老朽" },
    { group: "第18・19回 【書き】", q: "湿気で<span class='katakana'>フキュウ</span>した材木。", a: "腐朽" },
    { group: "第18・19回 【書き】", q: "欠員の<span class='katakana'>ホジュウ</span>がつかない。", a: "補充" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ジュウジツ</span>した内容。", a: "充実" },
    { group: "第18・19回 【書き】", q: "ガスが<span class='katakana'>ジュウマン</span>する。", a: "充満" },
    { group: "第18・19回 【書き】", q: "心の<span class='katakana'>ジュウソク</span>を求める。", a: "充足" },
    { group: "第18・19回 【書き】", q: "残金は会費に<span class='katakana'>ジュウトウ</span>する。", a: "充当" },
    { group: "第18・19回 【書き】", q: "堤防の<span class='katakana'>ホキョウ</span>工事。", a: "補強" },
    { group: "第18・19回 【書き】", q: "説明を<span class='katakana'>ホソク</span>する。", a: "補足" },
    { group: "第18・19回 【書き】", q: "会長を<span class='katakana'>ホサ</span>する。", a: "補佐" },
    { group: "第18・19回 【書き】", q: "欠点を<span class='katakana'>ホカン</span>する。", a: "補完" },
    { group: "第18・19回 【書き】", q: "芸能界で<span class='katakana'>カツヤク</span>する。", a: "活躍" },
    { group: "第18・19回 【書き】", q: "論理に<span class='katakana'>ヒヤク</span>がある。", a: "飛躍" },
    { group: "第18・19回 【書き】", q: "一躍<span class='katakana'>イチヤク</span>有名になる。", a: "一躍" },
    { group: "第18・19回 【書き】", q: "黒幕が<span class='katakana'>アンヤク</span>する。", a: "暗躍" },
    { group: "第18・19回 【書き】", q: "若手選手が<span class='katakana'>ヤクシン</span>を遂げる。", a: "躍進" },
    { group: "第18・19回 【書き】", q: "全身を使って<span class='katakana'>チョウヤク</span>する。", a: "跳躍" },
    { group: "第18・19回 【書き】", q: "巨匠の面目<span class='katakana'>ヤクジョ</span>たる傑作。", a: "躍如" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ヤッキ</span>になって働く。", a: "躍起" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ヤクドウ</span>する若いちから。", a: "躍動" },
    { group: "第18・19回 【書き】", q: "音の大きさと<span class='katakana'>シンプク</span>の関係。", a: "振幅" },
    { group: "第18・19回 【書き】", q: "産業の<span class='katakana'>シンコウ</span>を図る。", a: "振興" },
    { group: "第18・19回 【書き】", q: "最近景気が<span class='katakana'>フシン</span>だ。", a: "不振" },
    { group: "第18・19回 【書き】", q: "よく跳ね返り、<span class='katakana'>ダンリョク</span>のあるボール。", a: "弾力" },
    { group: "第18・19回 【書き】", q: "世の<span class='katakana'>シダン</span>を受ける。", a: "指弾" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ダンアツ</span>に屈しない気迫を示す。", a: "弾圧" },
    { group: "第18・19回 【書き】", q: "政府を<span class='katakana'>ダンガイ</span>する。", a: "弾劾" },
    { group: "第18・19回 【書き】", q: "規則には<span class='katakana'>ハイハン</span>しない。", a: "違反" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ハイニン</span>罪で訴える。", a: "背任" },
    { group: "第18・19回 【書き】", q: "許しがたい<span class='katakana'>ハイシン</span>行為。", a: "背信" },
    { group: "第18・19回 【書き】", q: "敵の<span class='katakana'>ハイゴ</span>を衝く。", a: "背後" },
    { group: "第18・19回 【書き】", q: "経済的な<span class='katakana'>ハイケイ</span>を調べる。", a: "背景" },
    { group: "第18・19回 【書き】", q: "謹んで<span class='katakana'>アイトウ</span>の気持ちを表す。", a: "哀悼" },
    { group: "第18・19回 【書き】", q: "亡くなった人を<span class='katakana'>ツイトウ</span>する。", a: "追悼" },
    { group: "第18・19回 【書き】", q: "どんな<span class='katakana'>ジョショク</span>にも負けない。", a: "侮辱" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ケイブ</span>をもって相手をみる。", a: "軽侮" },
    { group: "第18・19回 【書き】", q: "悪に<span class='katakana'>コリ</span>て、二度とすまいという気になる。", a: "懲" },
    { group: "第18・19回 【書き】", q: "被告人を<span class='katakana'>チョウエキ</span>刑に処す。", a: "懲役" },
    { group: "第18・19回 【書き】", q: "違反者に<span class='katakana'>チョウバツ</span>を与える。", a: "懲罰" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>チョウカイ</span>処分にする。", a: "懲戒" },
    { group: "第18・19回 【書き】", q: "勧善<span class='katakana'>チョウアク</span>の演劇。", a: "懲悪" },
    { group: "第18・19回 【書き】", q: "敵を<span class='katakana'>シュウゲキ</span>する。", a: "襲撃" },
    { group: "第18・19回 【書き】", q: "家元を<span class='katakana'>セシュウ</span>する。", a: "世襲" },
    { group: "第18・19回 【書き】", q: "前例を<span class='katakana'>トウシュウ</span>する。", a: "踏襲" },
    { group: "第18・19回 【書き】", q: "児童を<span class='katakana'>インソツ</span>して行く。", a: "引率" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ソッセン</span>垂範して行う。", a: "率先" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>トウソツ</span>のとれたチーム。", a: "統率" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ケイソツ</span>な行動は慎め。", a: "軽率" },
    { group: "第18・19回 【書き】", q: "<span class='katakana'>ソッチョク</span>に見解を述べる。", a: "率直" },

    { group: "第20〜22回 【書き】", q: "彼の考えに<span class='katakana'>センノウ</span>される。", a: "洗脳" },
    { group: "第20〜22回 【書き】", q: "旅行で命の<span class='katakana'>センタク</span>をする。", a: "洗濯" },
    { group: "第20〜22回 【書き】", q: "猛特訓の<span class='katakana'>センレイ</span>を受けた。", a: "洗礼" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>センレン</span>された技術。", a: "洗練" },
    { group: "第20〜22回 【書き】", q: "総力を<span class='katakana'>ケッシュウ</span>する。", a: "結集" },
    { group: "第20〜22回 【書き】", q: "努力が<span class='katakana'>ケツジツ</span>する。", a: "結実" },
    { group: "第20〜22回 【書き】", q: "そうなるのが必然の<span class='katakana'>キケツ</span>だ。", a: "帰結" },
    { group: "第20〜22回 【書き】", q: "ようやく議論が<span class='katakana'>シュウケツ</span>した。", a: "終結" },
    { group: "第20〜22回 【書き】", q: "長い裁判が<span class='katakana'>ケッシン</span>した。", a: "結審" },
    { group: "第20〜22回 【書き】", q: "強い口調で<span class='katakana'>ホンイ</span>を促す。", a: "翻意" },
    { group: "第20〜22回 【書き】", q: "海外小説を<span class='katakana'>ホンヤク</span>する。", a: "翻訳" },
    { group: "第20〜22回 【書き】", q: "人生の<span class='katakana'>キュウキョク</span>の目的。", a: "究極" },
    { group: "第20〜22回 【書き】", q: "生活に<span class='katakana'>コンキュウ</span>する。", a: "困窮" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>キュウツツ</span>な空気に耐える。", a: "窮屈" },
    { group: "第20〜22回 【書き】", q: "チームの<span class='katakana'>キュウチ</span>を救う活躍。", a: "窮地" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>キュウハク</span>した財政。", a: "窮迫" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>キュウヨ</span>の一策を案じる。", a: "窮余" },
    { group: "第20〜22回 【書き】", q: "建物を<span class='katakana'>ジョウト</span>する。", a: "譲渡" },
    { group: "第20〜22回 【書き】", q: "権限の一部を<span class='katakana'>イジョウ</span>する。", a: "委譲" },
    { group: "第20〜22回 【書き】", q: "相手の主張に<span class='katakana'>ジョウホ</span>する。", a: "譲歩" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ケンジョウ</span>の美徳。", a: "謙譲" },
    { group: "第20〜22回 【書き】", q: "小説家の夢を<span class='katakana'>ダンネン</span>する。", a: "断念" },
    { group: "第20〜22回 【書き】", q: "国交を<span class='katakana'>ダンゼツ</span>する。", a: "断绝" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ダンペン</span>的な記憶。", a: "断片" },
    { group: "第20〜22回 【書き】", q: "洪水で道路が<span class='katakana'>スンダン</span>される。", a: "寸断" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ユダン</span>大敵を心がけよ。", a: "油断" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>カンダン</span>なく雨が降る。", a: "間断" },
    { group: "第20〜22回 【書き】", q: "かすかな音が<span class='katakana'>フダン</span>に続く。", a: "不断" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ダンマツマ</span>の叫びを聞く。", a: "断末魔" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ダンチョウ</span>の思い。", a: "断腸" },
    { group: "第20〜22回 【書き】", q: "きっとやる、と<span class='katakana'>ダンゲン</span>する。", a: "断言" },
    { group: "第20〜22回 【書き】", q: "かなりの<span class='katakana'>ケツダン</span>を要する。", a: "決断" },
    { group: "第20〜22回 【書き】", q: "機をみて<span class='katakana'>ダンコウ</span>する（熟慮断行）。", a: "断行" },
    { group: "第20〜22回 【書き】", q: "犯人のゆくえを<span class='katakana'>タンサク</span>する。", a: "探索" },
    { group: "第20〜22回 【書き】", q: "幸福を<span class='katakana'>タンキュウ</span>する。", a: "探求" },
    { group: "第20〜22回 【書き】", q: "自分の非を認めて<span class='katakana'>アヤマル</span>。", a: "謝る" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>カンシャ</span>の気持ちを表す。", a: "感謝" },
    { group: "第20〜22回 【書き】", q: "お心遣いに<span class='katakana'>シンシャ</span>します。", a: "深謝" },
    { group: "第20〜22回 【書き】", q: "面会<span class='katakana'>シャゼツ</span>の重傷。", a: "謝絶" },
    { group: "第20〜22回 【書き】", q: "身体の新陳<span class='katakana'>タイシャ</span>を図る。", a: "代謝" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>クツジョク</span>を受ける。", a: "屈辱" },
    { group: "第20〜22回 【書き】", q: "公衆の面前で受けた<span class='katakana'>チジョク</span>。", a: "恥辱" },
    { group: "第20〜22回 【書き】", q: "次の試合で<span class='katakana'>セツジョク</span>する。", a: "雪辱" },
    { group: "第20〜22回 【書き】", q: "足どりを追って<span class='katakana'>ソウサ</span>する。", a: "捜査" },
    { group: "第20〜22回 【書き】", q: "遭難者を<span class='katakana'>ソウサク</span>する。", a: "捜索" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>タイマン</span>な態度を改める。", a: "怠慢" },
    { group: "第20〜22回 【書き】", q: "単調な作業に<span class='katakana'>ケンタイ</span>をおぼえる。", a: "倦怠" },
    { group: "第20〜22回 【書き】", q: "老舗ののれんが<span class='katakana'>スタレル</span>。", a: "廃れる" },
    { group: "第20〜22回 【書き】", q: "優遇措置を<span class='katakana'>ハイシ</span>する。", a: "廃止" },
    { group: "第20〜22回 【書き】", q: "人心が<span class='katakana'>コウハイ</span>する。", a: "荒廃" },
    { group: "第20〜22回 【書き】", q: "核兵器の<span class='katakana'>ハイゼツ</span>。", a: "廃絶" },
    { group: "第20〜22回 【書き】", q: "道義が<span class='katakana'>タイハイ</span>する。", a: "退廃" },
    { group: "第20〜22回 【書き】", q: "反抗期の年ごろになる（ハンコウ）。", a: "反抗" },
    { group: "第20〜22回 【書き】", q: "見苦しい内部<span class='katakana'>コウソウ</span>だ。", a: "抗争" },
    { group: "第20〜22回 【書き】", q: "他社に<span class='katakana'>タイコウ</span>した商品。", a: "対抗" },
    { group: "第20〜22回 【書き】", q: "審判に<span class='katakana'>コウギ</span>する。", a: "抗議" },
    { group: "第20〜22回 【書き】", q: "両チーム<span class='katakana'>キッコウ</span>した試合。", a: "拮抗" },
    { group: "第20〜22回 【書き】", q: "病気になり<span class='katakana'>コウタイ</span>ができる。", a: "抗体" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>コウセイ</span>物質の投与。", a: "抗生" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ムボウ</span>な計画。", a: "無謀" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>インボウ</span>を企てる。", a: "陰謀" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>シンボウ</span>遠慮をめぐらす。", a: "深謀" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ケンボウ</span>術数に長けた人物。", a: "権謀" },
    { group: "第20〜22回 【書き】", q: "戦国時代きっての<span class='katakana'>サクボウ</span>家。", a: "策謀" },
    { group: "第20〜22回 【書き】", q: "安全な場所へ<span class='katakana'>ユウドウ</span>する。", a: "誘導" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ユウカイ</span>事件の捜査。", a: "誘拐" },
    { group: "第20〜22回 【書き】", q: "結果を引きおこす（ウナガす）。", a: "促す" },
    { group: "第20〜22回 【書き】", q: "事件の<span class='katakana'>ユウイン</span>を探る。", a: "誘因" },
    { group: "第20〜22回 【書き】", q: "寝不足がミスを<span class='katakana'>ユウハツ</span>した。", a: "誘発" },
    { group: "第20〜22回 【書き】", q: "相手を<span class='katakana'>コウゲキ</span>する。", a: "攻撃" },
    { group: "第20〜22回 【書き】", q: "後半戦から<span class='katakana'>コウセイ</span>に転じた。", a: "攻勢" },
    { group: "第20〜22回 【書き】", q: "敵の<span class='katakana'>シンコウ</span>をくいとめる。", a: "侵攻" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>セイコウ</span>法で勝った。", a: "正攻" },
    { group: "第20〜22回 【書き】", q: "経済学を<span class='katakana'>センコウ</span>する。", a: "専攻" },
    { group: "第20〜22回 【書き】", q: "家屋に<span class='katakana'>シンニュウ</span>する。", a: "侵入" },
    { group: "第20〜22回 【書き】", q: "プライバシーの<span class='katakana'>シンガイ</span>。", a: "侵害" },
    { group: "第20〜22回 【書き】", q: "敵の<span class='katakana'>シンリャク</span>を跳ね返す。", a: "侵略" },
    { group: "第20〜22回 【書き】", q: "病原菌に<span class='katakana'>シンショク</span>される。", a: "侵食" },
    { group: "第20〜22回 【書き】", q: "国境を<span class='katakana'>シンパン</span>する。", a: "侵犯" },
    { group: "第20〜22回 【書き】", q: "急患を<span class='katakana'>タンカ</span>で運ぶ。", a: "担架" },
    { group: "第20〜22回 【書き】", q: "料金は各自が<span class='katakana'>フタン</span>する。", a: "負担" },
    { group: "第20〜22回 【書き】", q: "文筆<span class='katakana'>カギョウ</span>に精を出す。", a: "稼業" },
    { group: "第20〜22回 【書き】", q: "最新設備がフル<span class='katakana'>カドウ</span>する。", a: "稼働" },
    { group: "第20〜22回 【書き】", q: "写真を著書に<span class='katakana'>ソウニュウ</span>する。", a: "挿入" },
    { group: "第20〜22回 【書き】", q: "エピソードを交えて語る（ソウワ）。", a: "挿話" },
    { group: "第20〜22回 【書き】", q: "起伏に富んだ<span class='katakana'>チケイ</span>。", a: "地形" },
    { group: "第20〜22回 【書き】", q: "その場に<span class='katakana'>ヘイフク</span>して謝る。", a: "平伏" },
    { group: "第20〜22回 【書き】", q: "小説の<span class='katakana'>フクセン</span>を張る。", a: "伏線" },
    { group: "第20〜22回 【書き】", q: "無条件で<span class='katakana'>コウフク</span>する。", a: "降伏" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>シフク</span>して機会を待つ。", a: "雌伏" },
    { group: "第20〜22回 【書き】", q: "街から暴力を<span class='katakana'>ツイホウ</span>する。", a: "追放" },
    { group: "第20〜22回 【書き】", q: "光を<span class='katakana'>ホウシャ</span>する。", a: "放射" },
    { group: "第20〜22回 【書き】", q: "しばらく<span class='katakana'>ホウシン</span>状態になる。", a: "放心" },
    { group: "第20〜22回 【書き】", q: "重責から<span class='katakana'>カイホウ</span>された。", a: "開放" },
    { group: "第20〜22回 【書き】", q: "他人の営業を<span class='katakana'>ボウガイ</span>する。", a: "妨害" },
    { group: "第20〜22回 【書き】", q: "事件の発生を<span class='katakana'>ヨボウ</span>する。", a: "予防" },
    { group: "第20〜22回 【書き】", q: "一命を<span class='katakana'>トリトメル</span>。", a: "取り留める" },
    { group: "第20〜22回 【書き】", q: "野党の提出した<span class='katakana'>ホウアン</span>。", a: "法案" },
    { group: "第20〜22回 【書き】", q: "記念碑を<span class='katakana'>コンリュウ</span>する。", a: "建立" },
    { group: "第20〜22回 【書き】", q: "私財を<span class='katakana'>ナゲウツ</span>。", a: "投げうつ" },
    { group: "第20〜22回 【書き】", q: "資本を<span class='katakana'>トウ</span>じる。", a: "投じる" },
    { group: "第20〜22回 【書き】", q: "一票を<span class='katakana'>トウ</span>じる。", a: "投じる" },
    { group: "第20〜22回 【書き】", q: "強豪チームに<span class='katakana'>イド</span>む。", a: "挑む" },
    { group: "第20〜22回 【書き】", q: "相手を<span class='katakana'>チョウハツ</span>する。", a: "挑発" },
    { group: "第20〜22回 【書き】", q: "挑戦を<span class='katakana'>ウ</span>けて立つ。", a: "受けて立つ" },
    { group: "第20〜22回 【書き】", q: "新記録に<span class='katakana'>チョウセン</span>する。", a: "挑戦" },
    { group: "第20〜22回 【書き】", q: "意見を<span class='katakana'>ノ</span>べる。", a: "述べる" },
    { group: "第20〜22回 【書き】", q: "感想を<span class='katakana'>チンジュツ</span>する。", a: "陳述" },
    { group: "第20〜22回 【書き】", q: "自分の意見を<span class='katakana'>シュショウ</span>する。", a: "主唱" },
    { group: "第20〜22回 【書き】", q: "異議を<span class='katakana'>トナ</span>える。", a: "唱える" },
    { group: "第20〜22回 【書き】", q: "混声<span class='katakana'>ガッショウ</span>団。", a: "合唱" },
    { group: "第20〜22回 【書き】", q: "基本理念を<span class='katakana'>テイショウ</span>する。", a: "提唱" },
    { group: "第20〜22回 【書き】", q: "スローガンを<span class='katakana'>コウショウ</span>する。", a: "高唱" },
    { group: "第20〜22回 【書き】", q: "反対を<span class='katakana'>サケ</span>ぶ。", a: "叫ぶ" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ゼッキョウ</span>の歓声が上がる。", a: "絶叫" },
    { group: "第20〜22回 【書き】", q: "大声で<span class='katakana'>キョウカン</span>する。", a: "叫喚" },
    { group: "第20〜22回 【書き】", q: "真実を<span class='katakana'>ウタガ</span>う。", a: "疑う" },
    { group: "第20〜22回 【書き】", q: "<span class='katakana'>ギモン</span>
