<?php
class Page_Controller extends Template_Controller {

	public $template = 'pages/base'; //defaults to template but you can set your own view file

	public $auto_render = TRUE; //defaults to true, renders the template after the controller method is done

	public function __construct()
	{
		parent::__construct(); //necessary
	}

	public function index()
	{
		$this->template->content= 'to be replaced';
	}
}