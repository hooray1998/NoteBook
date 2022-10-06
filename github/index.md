# index


## gitlogs

https://juejin.cn/post/6995173310245896206

这个网站其实就是一个github项目搜索引擎，可以根据关键词搜索，支持邮箱订阅文章，每天都可以收到GitHub网站上的最新内容。

访问地址：www.gitlogs.com/

## `.github/workflow/lint_python.yml`:

	name: lint_python
	on: [pull_request, push]
	jobs:
	  lint_python:
		runs-on: ubuntu-latest
		steps:
		  - uses: actions/checkout@v2
		  - uses: actions/setup-python@v2
		  - run: pip install --upgrade pip wheel
		  - run: pip install bandit black codespell flake8 flake8-2020 flake8-bugbear
							 flake8-comprehensions isort mypy pytest pyupgrade safety
		  - run: bandit --recursive --skip B101 . || true  # B101 is assert statements
		  - run: black --check . || true
		  - run: codespell || true  # --ignore-words-list="" --skip="*.css,*.js,*.lock"
		  - run: flake8 . --count --select=E9,F63,F7,F82 --show-source --statistics
		  - run: flake8 . --count --exit-zero --max-complexity=10 --max-line-length=88
						  --show-source --statistics
		  - run: isort --check-only --profile black . || true
		  - run: pip install -r requirements.txt || pip install --editable . || true
		  - run: mkdir --parents --verbose .mypy_cache
		  - run: mypy --ignore-missing-imports --install-types --non-interactive . || true
		  - run: pytest . || pytest --doctest-modules .
		  - run: shopt -s globstar && pyupgrade --py36-plus **/*.py || true
		  - run: safety check



## Github1s

如何更快速的阅读这些github代码呢？
今年GitHub 上出现了一个叫 github1s的开源项目，可以使用户直接在 VS Code 界面读取 GitHub 项目的代码，实现了 GitHub 项目与 VS Code 的无缝衔接，阅读代码非常爽快和方便。
开源地址： github.com/conwnet/git…
使用方法非常简单，只需要在浏览器地址栏 GitHub 网址链接中的「github 」后面添加 1s ，就能用在线VS Code 打开 github 项目，即使使用国内网络并且访问速度也非常快。
