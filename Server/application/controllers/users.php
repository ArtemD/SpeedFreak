<?php defined('SYSPATH') OR die('No direct access allowed.');
/*
 * API for registering users and updating profile information
 * 
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

class Users_Controller extends Controller{
    
    
	/**
	 * When no parameters are supplied visitor is redirected to project's website
	 * 
	 * @access public
	 * @return void
	 */
	public function index(){
        url::redirect(Kohana::config('api.default_redirect'),301);
    }
    
    
    /**
     * Register new user
     * 
     * @access public
     * @return string Returns "OK" string upon succession and error message otherwise
     */
    public function register(){
    	$xml = apiler::get_xml();
    	try {
    	   $user = new User_Model($xml->login, $xml->password, $xml->email, $xml->description);
    	   $this->store_avatar($user->get_id($xml->login));
    	   echo "OK";
    	}
        catch (Exception $e) {
            echo $e->getMessage() . "\n";
            die;
        } 
    }
    
    
    /**
     * Display user's information
     * 
     * @access public
     * @param string Username that we wish to get information for
     * @return string Returns information as XML or error message
     */
    public function info($username){
    	if (apiler::is_authorized()){
			$view = new View('api/user_info');
			$user = new User_Model();
			$view->user=$user->get_info($username);
			if ($view->user==false)
				die('User not found');
			if (file_exists(Kohana::config('upload.directory').'/'.$view->user->id.'.jpg'))
				$view->avatar=url::site('static/uploads/avatars/'.$view->user->id.'.jpg', 'http');
			$view->render(true);
    	}
		else
	   		apiler::not_authorized();
    }
    
    
    /**
     * View all registered users
     * 
     * @access public
     * @return string Returns XML containing list of all users or error message
     */
    public function list_all(){
    	if (apiler::is_authorized()){
	    	$users = new User_Model();
	    	$list = $users->list_all_users();
	    	$view = new View('api/user_list');
	    	$view->list = $list;
	    	$view->render(true);
	    }
	    else
	    	apiler::not_authorized();
    }
    
    /**
    * Verify credentials
    *
    * @return string Returns string "OK" if login is successful and error otherwise
    */
    public function login(){
    	if (apiler::is_authorized()){
        	print "OK";
            die;
    	}
        else
        	apiler::not_authorized();
    }
    
    
    /**
     * Check that supplied avatar is valid and store it
     * 
     * @access private
     * @param array $image Uploaded item found in $_FILES array
     * @param integer $id User id that will be used as filename
     * @return boolean Returns TRUE upon succession and FALSE otherwise
     */
    private function store_avatar($id){
    	if (isset($_FILES['avatar'])){
    		$info = getimagesize($_FILES['avatar']['tmp_name']);
	 
			if ($_FILES['avatar']['size']<=Kohana::config('api.avatar_max_filesize') AND in_array($info['mime'], Kohana::config('api.avatar_allowed_filetypes')))
			{
				if (upload::save('avatar', $id.'.jpg'))
					return True;
				else
					return False;
			}
			else
				return False;
		}
    }
   
}