数据通信产品线
软件开发






# 如何使Siri成为您完美的家庭伴侣，而设备不受Apple HomeKit支持

### 为什么要homekit？

homekit是一个由苹果公司开发的家庭配件管理框架。

它允许苹果设备的所有者使用一个接口控制来自不同制造商的连接对象。它增强了Siri解释这些设备的命令的能力。

如果你拥有一部iPhone和一部AppleTV，那么在其他连接对象协议（如家庭帮助）上，家庭工具包尤其有趣。homekit是iPhone自带的，允许通过家庭应用程序和快速访问选项卡轻松控制您的设备。苹果电视将作为一个枢纽，允许您设置自动化任务，并从您的家庭网络之外控制您的家。

### 它是如何工作的？

家庭套件附件协议
homekit为您的家和连接的对象定义布局。
家：一个家代表一个拥有一个配件网络的单一住宅。
房间：每个房间可以添加多个房间和附件。
平台：一组附件。
附件：附件是一个物理家庭自动化设备。
桥接器：桥接器是一种特殊类型的附件，允许您与无法直接与家庭套件通信的附件进行通信。例如，一个网桥可能是多个灯的集线器，这些灯使用的通信协议不是HomeKit附件协议。
服务：与附件功能相对应的服务。车库门可能有打开和关闭车门的服务，以及打开和关闭车库灯的其他服务。
特征：每个服务都有一组称为特征的属性。车库门具有当前门状态和目标门状态布尔值。服务的每个特征都标识其当前状态。每个特性有三个权限级别：读、写和通知。您可以在这里找到服务和相关特性的列表。

---------------------------------------------
使用iOS设备家庭应用程序或Siri发出的每个请求都将使用此布局来了解要对哪个对象执行操作以及要触发什么操作。
然而，截至今天，市场上只有少数支持家庭套件的设备可用。对于其他设备，您需要在HomeKit和设备之间使用代理。大多数连接的对象制造商都定义了自己与设备（API和协议）交互的方式。您的代理将收到homekit请求，并根据您的设备界面进行转换。
故桥
本文使用的代理是一个名为homebridge的node js服务器，它使用hap-node.js编写。home bridge实例化一个Bridge homekit对象，您可以通过iOS设备上的家庭应用程序添加该对象。然后，它支持插件，这些插件是社区贡献的模块，提供了从家庭工具包到各种“智能家居”设备的基本桥梁。
许多家庭自动化设备插件已经由社区开发（如Nest、Lifx甚至所有与家庭助手兼容的设备）。
如果您的对象现在没有可用的插件，那么本教程将为您编写。


### 编写自己的插件

#### 先决条件
您需要在局域网的任何设备上安装和运行HomeBridge。您可以按照这些说明操作。
您需要将HomeBridge作为iOS上家庭应用程序的附件添加。

#### 指令
让我们为一个假的开关编写一个插件。

创建一个包含package.json文件的新存储库来管理我们的依赖关系，以及一个包含插件核心逻辑的index.js文件。

我们将对交换机API做出以下假设：
- 它可以通过局域网上HTTP协议上的RESTfulAPI进行控制。
- 我们局域网上的交换机IP地址是192.168.0.10
- GET请求/api/status返回一个表示开关当前状态的布尔值。这样做将读取开关的接通特性
- 向/api/order发出的包含表示开关目标状态的布尔值的POST请求将触发相应的操作。这样做将设置开关的接通特性

我们将创建一个homebridge插件，用两个服务注册一个新附件：
- 附件信息服务，每个附件都需要，无论是哪种类型，广播与设备本身相关的信息
- 开关服务，与我们的实际开关相对应。此类服务具有单对布尔要求特性（检查服务列表和相应特性）

首先，我们需要在homebridge中注入插件。
myswitch是包含我们的控制逻辑的javascript对象。

```javascript
const Service, Characteristic;
 
module.exports = function (homebridge) {
  Service = homebridge.hap.Service;
  Characteristic = homebridge.hap.Characteristic;
  homebridge.registerAccessory("switch-plugin", "MyAwesomeSwitch", mySwitch);
};
```

在hap-node.js和homebridge中构建的核心逻辑位于myswitch对象的getservices原型函数中。
我们将在此功能中说明我们的服务。我们还将定义每个服务的每个特性的哪个`getter和setter`，它将调用从homekit收到的每个请求。
我们需要声明：
- 包含以下内容的访问器信息服务：
	- 制造商特征Characteristic.Manufacturer,
	- 模型特征  Characteristic.Model,
	- 序列号特征Characteristic.SerialNumber,
- 包含以下内容的交换服务：
	- 开启特性— —这项服务唯一需要的特性

不像accessoryInformation服务的特性是可读的，可以在插件初始化时设置，on特性是可写的，需要getter和setter。

```javascript
mySwitch.prototype = {
  getServices: function () {
    let informationService = new Service.AccessoryInformation();
    informationService
      .setCharacteristic(Characteristic.Manufacturer, "My switch manufacturer")
      .setCharacteristic(Characteristic.Model, "My switch model")
      .setCharacteristic(Characteristic.SerialNumber, "123-456-789");
 
    let switchService = new Service.Switch("My switch");
    switchService
      .getCharacteristic(Characteristic.On)
        .on('get', this.getSwitchOnCharacteristic.bind(this))
        .on('set', this.setSwitchOnCharacteristic.bind(this));
 
    this.informationService = informationService;
    this.switchService = switchService;
    return [informationService, switchService];
  }
};
```

现在我们将在myswitch对象的专用原型函数中编写on characteristic getter和setter的逻辑。
对于交换机提供的RESTful API，我们将做出以下假设：

- http://192.168.0.10/api/status上的get请求返回一个当前状态：反映开关当前状态
- 在http://192.168.0.10/api/order上发布请求发送a target state:反映所需目标状态设置开关状态

我们将使用请求和URL模块来执行HTTP请求。
我们的配置对象（在HomeBridge全局配置JSON中定义）将包含上述两个URL。


```javascript
const request = require('request');
const url = require('url');
 
function mySwitch(log, config) {
  this.log = log;
  this.getUrl = url.parse(config['getUrl']);
  this.postUrl = url.parse(config['postUrl']);
}
 
mySwitch.prototype = {
 
  getSwitchOnCharacteristic: function (next) {
    const me = this;
    request({
        url: me.getUrl,
        method: 'GET',
    }, 
    function (error, response, body) {
      if (error) {
        me.log('STATUS: ' + response.statusCode);
        me.log(error.message);
        return next(error);
      }
      return next(null, body.currentState);
    });
  },
   
  setSwitchOnCharacteristic: function (on, next) {
    const me = this;
    request({
      url: me.postUrl,
      body: {'targetState': on},
      method: 'POST',
      headers: {'Content-type': 'application/json'}
    },
    function (error, response) {
      if (error) {
        me.log('STATUS: ' + response.statusCode);
        me.log(error.message);
        return next(error);
      }
      return next();
    });
  }
};
```
我们现在可以通过全局安装将新创建的插件添加到homebridge：

`npm install -g switch-plugin`

在您最喜欢的文本编辑器中打开homebridge目录中的config.json文件。在附件部分，向阵列添加信息：
```json
{
  "accessory": "MyAwesomeSwitch",
  "getUrl": "http://192.168.0.10/api/status",
  "postUrl": "http://192.168.0.10/api/order"
}
```
重新启动homebridge，您现在可以通过iOS设备上的home app打开和关闭这个假开关。

