# -*- coding:utf-8 -*-

# 很多机器学习的例子, 建议都运行一遍 https://riverml.xyz/dev/introduction/getting-started/regression/

from river import datasets

dataset = datasets.ImageSegments()
print(dataset)

x, y = next(iter(dataset))
print("x=", x)
print("y=", y)

from river import tree

model = tree.HoeffdingTreeClassifier()
result = model.predict_proba_one(x)

print(result)

print(model.predict_one(x))

model.learn_one(x, y)

print(model.predict_proba_one(x))
print(model.predict_one(x))


from river import metrics

model = tree.HoeffdingTreeClassifier()

metric = metrics.ClassificationReport()

for x, y in dataset:
    # 这句话放在后面就是先学习再预测，放前面就是先预测再学习
    y_pred = model.predict_one(x)
    # 先学习再预测， 和先预测再学习， 结果是不一样的
    model.learn_one(x, y)
    if y_pred is not None:
        metric.update(y, y_pred)

print(metric)

# 方式二: evaluate.progressive_val_score 这个函数专门用来计算这个的

from river import evaluate

model = tree.HoeffdingTreeClassifier()
metric = metrics.ClassificationReport()

evaluate.progressive_val_score(dataset, model, metric)

print(metric)
