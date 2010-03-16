<?php defined('SYSPATH') OR die('No direct access allowed.');
/*
 * API controller for communicating with mobile clients
 * 
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
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
    public function register(){
    	$xml = $this->get_xml();
    	try {
    	   $user = new User_Model($xml->login, $xml->password, $xml->email);
    	   echo "OK";
    	}
        catch (Exception $e) {
            echo $e->getMessage() . "\n";
            die;
        } 
    }
    
    /*
     * Returns XML file supplied by client
     */
    private function get_xml(){
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
    
    /*
     * Check that supplied credentials are valid using basic authentication
     *
     */
    public function login(){
    	if (isset($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW'])){
    		$user = new User_Model();
    		if ($user->login($_SERVER['PHP_AUTH_USER'], $_SERVER['PHP_AUTH_PW']))
    		  print "OK";
    		else {
    		  header('HTTP/1.0 401 Unauthorized');
    		  print "Invalid credentials";
    		  die;
    		} 
    	}
    	else {
    		header('HTTP/1.0 401 Unauthorized');
            print "No credentials supplied";
            die;
    	}
    	   
    }
}