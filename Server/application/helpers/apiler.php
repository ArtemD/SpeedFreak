<?php defined('SYSPATH') or die('No direct script access.');
/*
 * Helper class mainly for API controllers
 * 
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

class apiler_Core {

    /**
     * Get XML either from POST variable or FILES variable
     * 
     * @access private
     * @static
     * @return mixed Returns either SimpleXml object or outputs error along with HTTP 400 error
     */
    public static function get_xml(){
        if (isset($_POST['xml'])){
            $xml = simplexml_load_string($_POST['xml']);
        }
        elseif (isset($_FILES['xml'])){
            $xml = simplexml_load_file($_FILES['xml']['tmp_name']);
        }
        else{
            header("HTTP/1.1 400 Bad Request");
            echo "Please supply required parameters";
            die;
        }
        return $xml;
    }
    
    
    /**
     * Check if user is authorized
     * 
     * @access public
     * @static
     * @return boolean Returns TRUE if authorized and FALSE otherwise
     */
    public static function is_authorized(){
		if (isset($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW'])){
	            $user = new User_Model();
	            if ($user->login($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']))
	                return true;
	            else
	                return false;
		}
	        else
	            return false;

    }
    
    
    /**
     * Display "Unauthorized error"
     * 
     * @access public
     * @static
     * @return string Prints error text
     */
    public static function not_authorized(){
		header('HTTP/1.0 401 Unauthorized');
        print "Invalid credentials or not registered";
        die;
    }
    
    /**
     * Verify user's credentials
     *  
     * @access public
     * @return string Outputs "OK" or error
     */
    public function login(){
		if ($this->is_authorized()){
	    	print "OK";
	    	die;
	    }else
			$this->not_authorized();
     }
    
}