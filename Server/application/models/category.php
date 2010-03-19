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

    /*
     * Check if category exists
     *
     * @param string $category Category name (slug)
     * @return bool True if exists and False otherwise
     */
    public function category_exists($category){
	$results = $this->db->query("SELECT id FROM categories where slug = ?", $category);
    if ($results->count()>0)
            return true;
        else
            return false;
    }

    /*
     * Get category id
     *
     * @param string $category Category name (slug)
     * @return integer|bool Category id if successful or false
     */
    public function get_id($category){
	$results = $this->db->query("SELECT id FROM categories where slug = ?", $category);
    if ($results->count()>0)
            return $results[0]->id;
        else
            return false;
    }

}