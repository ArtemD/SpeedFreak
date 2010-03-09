<?php defined('SYSPATH') or die('No direct script access.');
/*
 * API controller for communicating with mobile clients
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
    public function __construct($username='', $password='', $email=''){
        
    	// load database library into $this->db
        parent::__construct();
        
        if (isset($username, $password, $email)){
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
                
            if ($this->register($username, $password, $email)->valid())
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
    private function register($username, $password, $email){
    	return $this->db->query('INSERT into users SET username = ?, password = ?, email = ?',
    	           $this->db->escape($username), $this->db->escape($password), $this->db->escape($email));
    }
    
    /*
     * Check if user already exists in database
     * 
     * @param string $username Username
     * @param string $email Email address
     * @return bool Returns True if user exists and false otherwise
     */
    private function user_exists($username, $email){
        if ($this->db->query('SELECT id FROM users WHERE username = ? OR email = ?',
                   $this->db->escape($username), $this->db->escape($email))->count()>0)
            return true;
        else
            return false;
    }
 
}