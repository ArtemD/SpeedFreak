<?php defined('SYSPATH') OR die('No direct access allowed.');
/*
 * API controller for communicating with mobile clients
 * 
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright  (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

class Api_Controller extends Controller{
    
	/*
	 * Default action when no parameters are given to controller
	 */
	public function index(){
        url::redirect(Kohana::config('api.default_redirect'),301);
    }
    
    /*
     * New user registration
     */
}