<?php defined('SYSPATH') OR die('No direct access allowed.');
/*
 * Configuration file for API controller
 */

/*
 * URL where to redirect if no parameters are given to API controller
 */
 $config['default_redirect'] = 'http://www.speedfreak-app.com';
 
/*
 * Salt for hashing (should always be changed on deployment!)
 */
$config['salf'] = 'klzdjkhI/&/567Û%#ÛgbnkBJHVTVjdhiuhdbmzcss-__FDHSYUWYUTUDGBZ';

/*
 * Maximum filesize for avatar images (in bytes)
 */
$config['avatar_max_filesize'] = '102400';

/*
 * Allowed image types for avatars
 */
$config['avatar_allowed_filetypes'] = array('image/jpeg');