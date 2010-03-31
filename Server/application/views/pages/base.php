<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title><?php echo $title; ?> - SpeedFreak</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link href="<?php echo url::base(); ?>static/css/style.css" rel="stylesheet" type="text/css" />
<link href="<?php echo url::base(); ?>static/css/layout.css" rel="stylesheet" type="text/css" />
<script src="<?php echo url::base(); ?>static/js/jquery-1.3.2.min.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/cufon-yui.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/cufon-replace.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/Myriad_Pro_700.font.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/Myriad_Pro_BC_700.font.js" type="text/javascript"></script>
<?php echo View::factory('pages/tracking_analytics')->render(); ?>
</head>

<body id="index">
    <div class="top-bg">
    <div id="main">
        <!-- Header -->
        <div id="header">
            <div class="menu">
                <div class="left-bg">
                    <div class="right-bg">
                        <a href="<?php echo url::base(); ?>" class="home-link" title="SpeedFreak homepage"><img src="<?php echo url::base(); ?>static/img/home-link.gif" alt="Home icon" /></a>
                        <ul>
                            <li><a href="<?php echo url::base(); ?>" title="SpeedFreak Homepage">Home</a></li>
                            <li><a href="<?php echo url::site('pages/screenshot'); ?>" title="SpeedFreak screenshots">Screenshots</a></li>
                            <li><a href="<?php echo url::base('pages/community'); ?>" title="SpeedFreak community">Community</a></li>
                            <li><a href="<?php echo url::base('pages/credits'); ?>" title="SpeedFreak developers and contributors">Credits</a></li>
                            <li><a href="<?php echo url::base('pages/about'); ?>" title="SpeedFreak about">About</a></li>
                        </ul>
                    </div>
                </div>
            </div>
            <div class="logo"><a href="<?php echo url::base(); ?>"><img src="<?php echo url::base(); ?>static/img/logo.jpg" alt="" /></a></div>
        </div>
        <!-- /Header -->
        <div id="content">
            <div class="box1">
                <div class="left-border">
                    <div class="right-border">
                        <div class="top-border">
                            <div class="left-bot">
                                <div class="right-bot">
                                    <div class="left-top">
                                        <div class="right-top">
                                            <div class="indent1 line1">
                                                <div class="container">
                                                    <div class="col-1">
                                                        <h3><?php echo $header; ?></h3>
                                                        <?php echo $content; ?>
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
         </div>
        <!-- Footer -->
        <div id="footer">
            <p><a href="/">SpeedFreak-app.com</a> &copy; 2010</p>
        </div>
        <!-- /Footer -->
    </div>
    </div>
    <script type="text/javascript"> Cufon.now(); </script>
<?php echo View::factory('pages/tracking')->render(); ?>
</body>

</html>
