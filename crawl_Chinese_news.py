from scrapy import cmdline

cmdline.execute('scrapy crawl newsChinese -o ../newsChinese.csv'.split())
