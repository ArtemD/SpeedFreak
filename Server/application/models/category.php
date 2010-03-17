<?php defined('SYSPATH') or die('No direct script access.');
/*
 * Categories model for creating and manipulating categories
 *
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

class Category_Model extends Model {

    public function __construct(){

        // load database library into $this->db
        parent::__construct();
    }

    /*
     * Fetch all categories
     *
     * @return object|bool Returns object containing results if everything is ok and false otherwise
     */
    public function get_all(){
        $results = $this->db->query("SELECT slug,description,unit FROM categories");
	if ($results->count()>0)
            return $results;
        else
            return false;
    }

}