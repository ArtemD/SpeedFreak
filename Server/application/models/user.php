<?php defined('SYSPATH') or die('No direct script access.');
/*
 * Users model for creating and manipulating user accounts
 * 
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */
 
class User_Model extends Model {
 
	/*
	 * Initialize class and register user if all parameters are supplied
	 * 
	 * @param string $username Length 3-12
	 * @param string $password Length 6-255 (stored as sha1 hash in database)
	 * @param string $email Valid email address
	 * @return bool Returns True if operation was successfull and exception otherwise
	 */
    public function __construct($username='', $password='', $email='', $description=''){
        
    	// load database library into $this->db
        parent::__construct();
        
        if ($username!='' and $password!='' and $email!=''){
        	if (strlen($username)<3)
        	   throw new Exception('Username too short');
            elseif (strlen($username)>12)
                throw new Exception('Username too long');
            elseif (strlen($password)<6)
               throw new Exception('Password too short');
            elseif (strlen($username)>255)
                throw new Exception('Password too long');
            elseif (valid::email($email) == False)
                throw new Exception('Invalid email supplied');
            elseif ($this->user_exists($username, $email))
                throw new Exception('User already exists (login or email matched)');
                
            if ($this->register($username, $password, $email, $description)->valid())
                return true;
            else
                return false;
            
        }
    }
    
    /*
     * Register new user
     * 
     * @param string $username Length 3-12
     * @param string $password Length 6-255 (stored as sha1 hash in database)
     * @param string $email Valid email address
     * @return bool Returns True if operation was successfull and exception otherwise
     */
    private function register($username, $password, $email, $description){
    	// hash password
        $password = $this->hash($password);
        
        // @todo I can't seem to get query working when password binding has '' around it like others
        if ($this->user_exists($username, $email)==false)
    	   return $this->db->query("INSERT into users SET username = '?', password = ?, description='?', last_activity=NOW(), email = '?'",
    	           $username, $password, $description, $email);
        else
            return false;
    }
    
    /*
     * Hash password supplied by user using salt stored in config file
     * 
     * @param string $password Password in plain text format
     * @return string Returns string containing hash generated from password
     */
    private function hash($password){
    	return sha1($password.Kohana::config('api.salt'));
    }
    
    /*
     * Check if user already exists in database
     * 
     * @param string $username Username
     * @param string $email Email address
     * @return bool Returns True if user exists and false otherwise
     */
    private function user_exists($username, $email){
    	if ($this->db->query("SELECT id FROM users WHERE username='?' OR email='?'",
	                   $username, $email)->count()>0)
	       return true;
	    else
	       return false;          
    }
    
    
    public function get_info($username){
    	$result = $this->db->query("SELECT * FROM users WHERE username = ?", $username);
		if ($result->count()>0)
           return $result[0];
        else
           return false;
    }
    
    
    /*
     * Get user id
     *
     * @param string $username Username
     * @return integer|bool User id if successful or false
     */
    public function get_id($username){
        $result = $this->db->query("SELECT id FROM users WHERE username=?", $username);
		if ($result->count()>0)
           return $result[0]->id;
        else
           return false;
    }
    
    /**
     * List all users found in database
     * 
     * @access public
     * @return boolean|object Returns object containing all users or false
     */
    public function list_all_users(){
        $result = $this->db->query("SELECT * FROM users");
		if ($result->count()>0)
           return $result;
        else
           return false;
    }

    /*
     * Check if supplied credentials are valid
     * 
     * @param string $username Username
     * @param string $password Password in plain text format
     * @return bool True if credentials match and false if supplied credentials are invalid
     */
    public function login($username, $password){
        // hash password
        $password = $this->hash($password);
        
        if ($this->db->query("SELECT id FROM users WHERE username = ? AND password = ?",
                             $username, $password)->count()>0)
            return true;
        else
            return false;
    }
 
}