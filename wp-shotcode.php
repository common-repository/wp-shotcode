<?php
/*
Plugin Name: ShotCode
Plugin URI: http://www.shotcode.org/wordpress
Description: Shows ShotCode mobile links code for your blog articles.
Author: Herval Freire
Author URI: http://hervalicio.us/blog
Version: 0.1
*/ 

/*
* Copyright (c) 2007, ShotCode.com.
* Based on original work by Anthony Wong's plugin QR-code ( http://blog.anthonywong.net/qr-code-wordpress-plugin/). Original copyright follows:
* 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
add_action('admin_menu', array('shotcode_wp_plugin', 'add_options_submenu'));

class shotcode_wp_plugin {

	function add_options_submenu() {
		if (!current_user_can('manage_options'))
			return;

		$minUserLevel = 1; // doesn't look like the function actually uses this
		                   // see code in admin-functions.php

		if (function_exists('add_options_page')) {
			add_options_page('ShotCode plugin options', 'ShotCode', $minUserLevel,
			                 basename(__FILE__), array('shotcode_wp_plugin', 'admin_options_subpanel'));
		}
	}

	function admin_options_subpanel() {
		include_once('wp-shotcode_options_subpanel.inc');
	}

	function get_shotcode_img_link() {
		global $id;

		echo '<a border="0" href="http://www.shotcode.org/about"><img border="0" src="http://www.shotcode.org/code.png?';
		
		$height = get_option("shotcode_image_height");
		if ($height != "") {
			echo 's=' . $height . '&';
		}
		$url = apply_filters('the_permalink', get_permalink());
		echo 'url=' . $url .'" ';
		
		if ($height != "") {
			echo 'width="' . $height . '" height="' . $height . '"';
		}
		echo '" alt="Use this link to access this content from your mobile phone" /></a>';
	}

	function get_test_shotcode_data() {
		return "http://www.google.com";
	}

	function get_test_shotcode_img_link($resize = 1) {
		$url = "http://www.shotcode.org/code.png?url=www.google.com";
        $height = get_option("shotcode_image_height");
		if ($resize == 1 && $height != "") {
			$url .= "&s=". $height;
		}
		echo '<img src="' . $url . '" ';
		if ($resize == 1 &&  $height != "") {
			echo 'width="' . $height . '" height="' . $height . '"';
		}
		echo '/>';
	}

}

?>
