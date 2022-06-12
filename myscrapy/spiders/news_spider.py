import scrapy

class NewsSpiderCHN(scrapy.Spider):
    name = "newsChinese"

    start_urls = [
        'http://opinion.people.com.cn/n1/2022/0612/c223228-32444286.html',
        'http://edu.people.com.cn/n1/2022/0610/c1006-32443127.html',
        'http://society.people.com.cn/n1/2022/0610/c1008-32442758.html'
    ]
    def parse(self, response):
        for news in response.css('div.col-1'):
            if news.css('h1::text').get() is not None:
                yield {
                    'url': response.url,
                    'title': news.css('h1::text').get(),
                    'abstract': ' '.join(news.css('p::text').getall()),
                }
        #anchors_a = response.css('li.ranking_key')
       # yield from response.follow_all(anchors_a, callback=self.parse)
        yield from response.follow_all(css='ul.rm_ranking_list a', callback=self.parse)
pass

class NewsSpider(scrapy.Spider):
    name = "news"

    start_urls = [
        'http://en.people.cn/n3/2022/0524/c90000-10100455.html'
    ]

    def parse(self, response):
        for news in response.css('div.main'):
            if news.css('h1::text').get() is not None:
                yield {
                    'url': response.url,
                    'title': news.css('h1::text').get(),
                    'news_content': ' '.join(news.css('p::text').getall()),
                }
        anchors_a = response.css('div.relevant_news a')
        yield from response.follow_all(anchors_a, callback=self.parse)
pass

