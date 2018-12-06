<?php namespace UserCenter\Controller;

use Think\Model;
use Think\Controller;

header("Content-Type: text/html; charset=utf-8");

class HaaaaaaaaaaaaaaaaController extends Controller
{
    public function gettoken()
    {
        $time = time();
        $appid = C('WX_APPID');
        $secret = C('WX_SECRET');
        $lasttime = S("weixin.token.lasttime");
        $lasttoken = S("weixin.token.lasttoken");
        $res = S("weixin.token.lasttime", $time);
        $apiUrl = 'https://api.weixin.qq.com/cgi-bin/token';
        $agent = 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.1 Safari/537.11';

        if ($time - $lasttime < 3600 && $lasttoken != '') {
            //echo $lasttoken;
            return;
        }

        $url = "$apiUrl?grant_type=client_credential&" . "appid=" . $appid . "&secret=" . $secret;
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_HEADER, false);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_USERAGENT, $agent);

        $res = curl_exec($ch);
        $rescode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
        curl_close($ch);

        $arr = json_decode($res);
        $curtoken = $arr->access_token;
        S("weixin.token.lasttime", $time);
        S("weixin.token.lasttoken", $curtoken);
        // echo $curtoken;
    }
    public function uploadImage()
    {
        //类型
        $type = "image";

        //得到token
        $this->gettoken();
        $lastToken = S("weixin.token.lasttoken");
        echo $lastToken ."\r\n";

        //请求url
//        $url = "https://api.weixin.qq.com/cgi-bin/material/add_material?access_token=$lastToken&type=$type";
//        //$url = "https://api.weixin.qq.com/cgi-bin/media/uploadimg?access_token=$lastToken";
//
//        //图片位置
//        $filepath = dirname(__FILE__)."/../../../Public/image/gouwuka.jpg";
//        $filedata = array("media"=>"@".$filepath);
//        $data = '{"media":"@' . $filepath . '"}';
//
//
//        echo $url."\r\n";
//        echo $data."\r\n";
//
//        //上传图片
//        $ch1 = curl_init ();
//        curl_setopt ( $ch1, CURLOPT_URL, $url );
//        curl_setopt ( $ch1, CURLOPT_POST, 1 );
//        curl_setopt ( $ch1, CURLOPT_RETURNTRANSFER, 1 );
//        curl_setopt ( $ch1, CURLOPT_CONNECTTIMEOUT, 5 );
//        curl_setopt ( $ch1, CURLOPT_SSL_VERIFYPEER, FALSE );
//        curl_setopt ( $ch1, CURLOPT_SSL_VERIFYHOST, false );
//        curl_setopt ( $ch1, CURLOPT_POSTFIELDS, $jsdata );
//        $result = curl_exec ( $ch1 );
//        curl_close ( $ch1 );
//        echo $result."\r\n";
//
//
//
//
//            $ch = curl_init();
//            curl_setopt($ch, CURLOPT_URL, $url);
//            curl_setopt($ch, CURLOPT_HEADER, false);
//            curl_setopt($ch, CURLOPT_POST, true);
//            curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
//            curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
//            curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
//            $res = curl_exec($ch);
//            $rescode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
//            curl_close($ch) ;
//            echo $res."\r\n";
        }

    public function creatMenu()
    {
        $this->gettoken();
        $lasttoken = S("weixin.token.lasttoken");
        $delurl = 'https://api.weixin.qq.com/cgi-bin/menu/delete?access_token=' . $lasttoken;

        $delres = getHttpsCurl($delurl);
        $base = C('BMSAPIURL');

        //$first[0]['type'] = 'view';
        //$first[0]['name'] = '游戏中心';
        //$first[0]['url'] = 'http://h.play.cn/inner/10074/cantv/index.html';
        //$first[0]['type'] = 'view';
        //$first[0]['name'] = '推荐';
        //$first[0]['url'] = $base . '/api/Wap/Index/carouselPic?typeID=1';
        //$first[1]['type'] = 'view';
        //$first[1]['name'] = '电影';
        //$first[1]['url'] = $base . '/api/Wap/Index/moviesList/typeID/1/topicID/0';
        //$first[2]['type'] = 'view';
        //$first[2]['name'] = '电视剧';
        //$first[2]['url'] = $base . '/api/Wap/Index/moviesList/typeID/2/topicID/0';


        //$sencond[0]['type'] = 'view';
        //$sencond[0]['name'] = '甜橙视频下载';
        //$sencond[0]['url'] = 'http://www.cibnvideo.com/download/tiancheng.html';
        //$sencond[1]['type'] = 'view';
        //$sencond[1]['name'] = '购买会员';
        //$sencond[1]['url'] = $base . '/api/Wap/WxpayMemberBuy/member_login';
        //$sencond[1]['type'] = 'view';
        //$sencond[1]['name'] = '流量直充';
        //$sencond[1]['url'] = 'http://w.url.cn/s/AQMba6O';
        //$sencond[1]['type'] = 'view';
        //$sencond[1]['name'] = '玩游戏';
        //$sencond[1]['url'] = 'http://h.play.cn/inner/10074/cantv/index.html';
        //$sencond[2]['type'] = 'view';
        //$sencond[2]['name'] = '我的账户';
        //$sencond[2]['url'] = $base . '/api/Wap/Index/userinfo';

        $sencond[0]['type'] = 'view';
        $sencond[0]['name'] = '照片教程';
        $sencond[0]['url'] = $base . '/api/Wap/Wxphoto/photoGuide';
        $sencond[1]['type'] = 'pic_weixin';
        $sencond[1]['name'] = '发照片';
        $sencond[1]['key'] = 'WXPIC';
        $sencond[2]['type'] = 'view';
        $sencond[2]['name'] = '购买会员';
        $sencond[2]['url'] = $base . '/api/Wap/WxpayMemberBuy/member_login';
        $sencond[3]['type'] = 'view';
        $sencond[3]['name'] = '我的账户';
        $sencond[3]['url'] = $base . '/api/Wap/Index/userinfo';

        //$three[0]['type'] = 'view';
        //$three[0]['name'] = '看尚商城';
        //$three[0]['url'] = 'https://shop13314621.wxrrd.com/feature/10195391';
        $three[0]['type'] = 'view';
        $three[0]['name'] = '企业介绍';
        $three[0]['url'] = 'https://mp.weixin.qq.com/s/ThX6py3wSfwrw7KGuxG3tg';
        $three[1]['type'] = 'view';
        $three[1]['name'] = '产品介绍';
        $three[1]['url'] = 'https://mp.weixin.qq.com/s/paXH-hO_Lf_L6aFB4dqqLA';
        $three[2]['type'] = 'view';
        $three[2]['name'] = '联系方式';
        $three[2]['url'] = 'https://mp.weixin.qq.com/s/1fwbl8-FD8btmxrepI2rUw';


        $button[0]['type'] = 'view';
        $button[0]['name'] = '天成动态';
        $button[0]['url'] = 'http://www.cibnvideo.com/historical_news.php';
        //$button[0]['sub_button'] = $first;
        $button[1]['name'] = '关于天成';
        $button[1]['sub_button'] = $three;
        $button[2]['name'] = '会员服务';
        $button[2]['sub_button'] = $sencond;
        $menu['button'] = $button;

        $str = str_replace("\\/", "/", encode_json($menu));
        $creatusrl = 'https://api.weixin.qq.com/cgi-bin/menu/create?access_token=' . $lasttoken;
        echo postHttpsCurl($creatusrl, $str);
    }

    public function getMenu()
    {
        $res = $this->selfGetMenu();
        echo $res;
    }

    public function selfGetMenu()
    {
        $lasttoken = S("weixin.token.lasttoken");
        //echo $lasttoken;
        $geturl = 'https://api.weixin.qq.com/cgi-bin/menu/get?access_token=' . $lasttoken;
        $res = getHttpsCurl($geturl);
        return $res;
    }
}
