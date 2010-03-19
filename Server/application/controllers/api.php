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
	if ($this->is_authorized()){
    		  print "OK";
    		  die;
    	}
		else
		  $this->not_authorized();
    }

    /*
     * Validate supplied credentials
     */
    public function is_authorized(){
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

    /*
     * Display "You're not authorized error to client
     *
     * @todo Need to create function for generally displaying errors
     */
    public function not_authorized(){
	header('HTTP/1.0 401 Unauthorized');
        print "Invalid credentials or not registered";
        die;
    }

    /*
     * Get categories list and output it as XML
     *
     */
    public function categories(){
	if ($this->is_authorized()){
		$view = new View('api/categories');
		$cat = new Category_Model();
		$view->categories=$cat->get_all();
		$view->render(true);
    	}
	else
	   $this->not_authorized();
    }

    /*
     * Get results
     *
     */
    public function results($category, $limit){
	$results = New Result_Model();
	$cat = New Category_Model();
        if ($cat->category_exists($category) AND $this->is_authorized() AND isset($limit)){
	        $view = new View('api/results');
	        $view->results = $results->get_results($category, $limit);
	        $view->render(true);
	    }
        else
            $this->not_authorized();
    }

    /*
     * Submit results to selected category
     *
     * @param string $category Category to which results are submitted
     */
    public function update($category){
	$cat = New Category_Model();
	if ($cat->category_exists($category) AND $this->is_authorized()){
		$xml = $this->get_xml();
		$result = New Result_Model();
		if ($result->insert($category,$_SERVER['PHP_AUTH_USER'], $xml['value'])){
			print "OK";
			die;
		}
		else {
			header("HTTP/1.1 400 Bad Request");
	            echo "Invalid request";
	            die;
		}
	}
	else {
            header("HTTP/1.0 404 Not Found");
            die('Category not found or not authorized');
	}

    }
}