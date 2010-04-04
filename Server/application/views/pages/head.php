<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
<title><?php echo $title; ?> - SpeedFreak</title>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link href="<?php echo url::base(); ?>static/css/style.css" rel="stylesheet" type="text/css" />
<link href="<?php echo url::base(); ?>static/css/layout.css" rel="stylesheet" type="text/css" />
<link href="<?php echo url::base(); ?>static/css/custom.css" rel="stylesheet" type="text/css" />
<script src="<?php echo url::base(); ?>static/js/jquery-1.3.2.min.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/cufon-yui.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/cufon-replace.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/Myriad_Pro_700.font.js" type="text/javascript"></script>
<script src="<?php echo url::base(); ?>static/js/Myriad_Pro_BC_700.font.js" type="text/javascript"></script>
<?php echo $head; ?>
<?php echo View::factory('pages/tracking_analytics')->render(); ?>
</head>