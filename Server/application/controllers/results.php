 <?php defined('SYSPATH') OR die('No direct access allowed.');
/*
 * API controller for managing and viewing results and categories
 * 
 * @author      Artem Daniliants <artem@daniliants.com>
 * @copyright   (c) 2010 Speed Freak team
 * @license     http://opensource.org/licenses/gpl-license.php GNU Public License
 */

class Results_Controller extends Controller{
 	
 	/*
     * Get categories list and output it as XML
     *
     */
    public function categories(){
	if (apiler::is_authorized()){
		$view = new View('api/categories');
		$cat = new Category_Model();
		$view->categories=$cat->get_all();
		$view->render(true);
    	}
	else
	   apiler::not_authorized();
    }

    /*
     * Get results
     *
     */
    public function list_results($category, $limit, $show_unit=false){
	$results = New Result_Model();
	$cat = New Category_Model();
        if ($cat->category_exists($category) AND apiler::is_authorized() AND isset($limit)){
	        $view = new View('api/results');
	        $view->results = $results->get_results($category, $limit);
	        $view->show_unit=$show_unit;
	        $view->render(true);
	    }
        else
            apiler::not_authorized();
    }

    /*
     * Submit results to selected category
     *
     * @param string $category Category to which results are submitted
     */
    public function update($category){
	$cat = New Category_Model();
	if ($cat->category_exists($category) AND apiler::is_authorized()){
		$xml = apiler::get_xml();
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