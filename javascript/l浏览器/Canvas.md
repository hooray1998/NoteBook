# Canvas

Canvas是HTML5新增的组件，它就像一块幕布，可以用JavaScript在上面绘制各种图表、动画等。

没有Canvas的年代，绘图只能借助Flash插件实现，页面不得不用JavaScript和Flash进行交互。有了Canvas，我们就再也不需要Flash了，直接使用JavaScript完成绘制。

一个Canvas定义了一个指定尺寸的矩形框，在这个范围内我们可以随意绘制：

```html
<canvas id="test-canvas" width="300" height="200"></canvas>
```
由于浏览器对HTML5标准支持不一致，所以，通常在<canvas>内部添加一些说明性HTML代码，如果浏览器支持Canvas，它将忽略<canvas>内部的HTML，如果浏览器不支持Canvas，它将显示<canvas>内部的HTML：

```html
<canvas id="test-stock" width="300" height="200">
    <p>Current Price: 25.51</p>
</canvas>
```
在使用Canvas前，用canvas.getContext来测试浏览器是否支持Canvas：

```html
<!-- HTML代码 -->
<canvas id="test-canvas" width="200" heigth="100">
    <p>你的浏览器不支持Canvas</p>
</canvas>
```
```javascript
 'use strict';
var canvas = document.getElementById('test-canvas');
if (canvas.getContext) {
    console.log('你的浏览器支持Canvas!');
} else {
    console.log('你的浏览器不支持Canvas!');
}
```

你的浏览器支持Canvas!
getContext('2d')方法让我们拿到一个CanvasRenderingContext2D对象，所有的绘图操作都需要通过这个对象完成。

var ctx = canvas.getContext('2d');
如果需要绘制3D怎么办？HTML5还有一个WebGL规范，允许在Canvas中绘制3D图形：

gl = canvas.getContext("webgl");
本节我们只专注于绘制2D图形。

绘制形状
我们可以在Canvas上绘制各种形状。在绘制前，我们需要先了解一下Canvas的坐标系统：

canvas-xy

Canvas的坐标以左上角为原点，水平向右为X轴，垂直向下为Y轴，以像素为单位，所以每个点都是非负整数。

CanvasRenderingContext2D对象有若干方法来绘制图形：

```javascript
'use strict';

var
    canvas = document.getElementById('test-shape-canvas'),
    ctx = canvas.getContext('2d');
ctx.clearRect(0, 0, 200, 200); // 擦除(0,0)位置大小为200x200的矩形，擦除的意思是把该区域变为透明
ctx.fillStyle = '#dddddd'; // 设置颜色
ctx.fillRect(10, 10, 130, 130); // 把(10,10)位置大小为130x130的矩形涂色
// 利用Path绘制复杂路径:
var path=new Path2D();
path.arc(75, 75, 50, 0, Math.PI*2, true);
path.moveTo(110,75);
path.arc(75, 75, 35, 0, Math.PI, false);
path.moveTo(65, 65);
path.arc(60, 65, 5, 0, Math.PI*2, true);
path.moveTo(95, 65);
path.arc(90, 65, 5, 0, Math.PI*2, true);
ctx.strokeStyle = '#0000ff';
ctx.stroke(path);
```

 Run
(no output)
绘制文本
绘制文本就是在指定的位置输出文本，可以设置文本的字体、样式、阴影等，与CSS完全一致：

```javascript
'use strict';

var
    canvas = document.getElementById('test-text-canvas'),
    ctx = canvas.getContext('2d');
ctx.clearRect(0, 0, canvas.width, canvas.height);
ctx.shadowOffsetX = 2;
ctx.shadowOffsetY = 2;
ctx.shadowBlur = 2;
ctx.shadowColor = '#660066';
ctx.font = '24px Arial';
ctx.fillStyle = '#000333';
ctx.fillText('带阴影的文字', 20, 40);
```

 Run
(no output)
Canvas除了能绘制基本的形状和文本，还可以实现动画、缩放、各种滤镜和像素转换等高级操作。如果要实现非常复杂的操作，考虑以下优化方案：

通过创建一个不可见的Canvas来绘图，然后将最终绘制结果复制到页面的可见Canvas中；

尽量使用整数坐标而不是浮点数；

可以创建多个重叠的Canvas绘制不同的层，而不是在一个Canvas中绘制非常复杂的图；

背景图片如果不变可以直接用<img>标签并放到最底层。


练习
请根据从163获取的JSON数据绘制最近30个交易日的K线图，数据已处理为包含一组对象的数组：

```javascript
'use strict';

window.loadStockData = function (r) {
    var
        NUMS = 30,
        data = r.data;
    if (data.length > NUMS) {
        data = data.slice(data.length - NUMS);
    }
    data = data.map(function (x) {
        return {
            date: x[0],
            open: x[1],
            close: x[2],
            high: x[3],
            low: x[4],
            vol: x[5],
            change: x[6]
        };
    });
    window.drawStock(data);
}

window.drawStock = function (data) {
var
  canvas = document.getElementById('stock-canvas'),
  width = canvas.width,
  height = canvas.height,
  ctx = canvas.getContext('2d');
console.log(JSON.stringify(data));
ctx.clearRect(0, 0, width, height);
ctx.fillStyle = 'black';
ctx.fillText('Test Canvas', 10, 10);

// 价格基准点
var base_price = data[0].open;
// 整K的y轴基准位置
var base_y = 100;
// k线图缩小比例
var scale = 4;
// 日K的宽度/2
var single_width_half = 3;
// 日K的宽度
var single_width_solo = single_width_half * 2;
// 日K的间隔
var single_margin = 2;
// 日K加间隔的宽度
var single_width = single_width_solo + single_margin;

for (var i in data) {
  // 收盘大于开盘，涨！红色。
  // 收盘小于开盘，跌！绿色。
  // 收盘等于开盘，横盘！灰色。
  if (data[i].close > data[i].open) {
    ctx.fillStyle = 'red';
    ctx.strokeStyle = 'red';
  } else if (data[i].close < data[i].open) {
    ctx.fillStyle = 'green';
    ctx.strokeStyle = 'green';
  } else {
    ctx.fillStyle = 'grey';
    ctx.strokeStyle = 'grey';
  }
  // 开/收高点
  var open_close_high = data[i].open > data[i].close ? data[i].open : data[i].close;
  // 开/收低点
  var open_close_low = data[i].open < data[i].close ? data[i].open : data[i].close;

  // 画开收矩形，开/收作为矩形的上下点
  var rect_start = base_y - (open_close_high - base_price) / scale;
  var rect_height = (Math.abs(data[i].open - data[i].close)) / scale;
  ctx.fillRect(20 + single_width * i, rect_start, single_width_solo, rect_height);

  // 画高直线，当高点大于开收高点，才会有高直线
  if (data[i].high > open_close_high) {
    var high_line_start = base_y - (data[i].high - base_price) / scale;
    var high_line_end = base_y - (open_close_high - base_price) / scale;
    ctx.beginPath();
    ctx.moveTo(20 + single_width_half + single_width * i, high_line_start);
    ctx.lineTo(20 + single_width_half + single_width * i, high_line_end);
    ctx.stroke();
  }

  // 画低直线，当低点大于开收低点，才会有低直线
  if(data[i].low < open_close_low) {
    var low_line_start = base_y - (open_close_high - base_price) / scale;
    var low_line_end = base_y - (data[i].low - base_price) / scale;
    ctx.beginPath();
    ctx.moveTo(20 + single_width_half + single_width * i, low_line_start);
    ctx.lineTo(20 + single_width_half + single_width * i, low_line_end);
    ctx.stroke();
  }
}
};

// 加载最近30个交易日的K线图数据:
var js = document.createElement('script');
js.src = 'http://img1.money.126.net/data/hs/kline/day/history/2015/0000001.json?callback=loadStockData&t=' + Date.now();
document.getElementsByTagName('head')[0].appendChild(js);
```


![结果图表](./pic.png)
