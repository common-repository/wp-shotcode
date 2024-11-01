<?php

/*
 * Copyright (c) 2007 ShotCode.com
 * All rights reserved.
 * Based on original work by Anthony Wong ( http://blog.anthonywong.net/qr-code-wordpress-plugin/). Original copyright follows:
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

define("DEFAULT_IMAGE_PATH", "/wp-content/shotcode");
add_option("shotcode_lib_path", "");
add_option("shotcode_image_path", DEFAULT_IMAGE_PATH);
add_option("shotcode_encoded_data_options", array("title", "posttime", "url"));
add_option("shotcode_version", "0");
add_option("shotcode_ecc_level", "M");
add_option("shotcode_module_size", "5");
//add_option("shotcode_quietzone", "5");

// Process forms
if (isset($_POST["update_lib_path"])) {
	update_option("shotcode_lib_path", $_POST["shotcode_lib_path"]);
}

if (isset($_POST["update_image_path"])) {
	update_option("shotcode_image_path", $_POST["shotcode_image_path"]);
}

if (isset($_POST["update_options"])) {
	if (empty($_POST["shotcode_image_height"])) {
		update_option("shotcode_image_height", "");
	} else {
		update_option("shotcode_image_height", $_POST["shotcode_image_height"]);
	}
}

if (isset($_POST["update_params"])) {
	update_option("shotcode_version", $_POST["shotcode_version"]);
	update_option("shotcode_ecc_level", $_POST["shotcode_ecc_level"]);
	update_option("shotcode_module_size", $_POST["shotcode_module_size"]);
//	update_option("shotcode_quietzone", $_POST["shotcode_quietzone"]);
	shotcode_wp_plugin::generate_test_shotcode_img();
}

if (isset($_POST["re-generate"])) {
	shotcode_wp_plugin::generate_test_shotcode_img();
}

// Initialization
$shotcode_lib_path = get_option("shotcode_lib_path");
$shotcode_image_path = get_option("shotcode_image_path");
$shotcode_encoded_data_options = get_option("shotcode_encoded_data_options");
$shotcode_image_height = get_option("shotcode_image_height");
$shotcode_version = get_option("shotcode_version");
$shotcode_ecc_level = get_option("shotcode_ecc_level");
$shotcode_module_size = get_option("shotcode_module_size");
//$shotcode_quietzone = get_option("shotcode_quietzone");

if (empty($shotcode_image_path)) {
	$shotcode_image_path = DEFAULT_IMAGE_PATH;
}
if (empty($shotcode_version)) {
	$shotcode_version = "0";
}
if (empty($shotcode_ecc_level)) {
	$shotcode_ecc_level = "M";
}
if (empty($shotcode_module_size)) {
	$shotcode_module_size = "5";
}
//if (empty($shotcode_quietzone)) {
//	$shotcode_quietzone = "5";
//}

?>

<div class="wrap">
	<h2>ShotCode for Wordpress options</h2>

    <p>
	To make ShotCode plugin work for your blog, you have to modify your theme to show the generated ShotCode for each of your blog articles. 
	Open your layout files (usually under Presentation/Theme Editor. e.g: <code>index.php</code>) and identify where you want to place the ShotCode image, then insert this PHP code snippet:<br/><br/><strong>
				<code>&lt;?php shotcode_wp_plugin::get_shotcode_img_link(); ?&gt;</code></strong>
			</li>
		</ol>
	</p>


	<form method="post">
		<fieldset class="options">
			<legend>Options</legend>

			<p>If you think the output image is too big or too small, you can resize it by putting the height of
			the image you wish below. As ShotCodes are circular, the height and width are the same, so you just
			need to supply the height (the minimum recomended size is 80, and the maximum is 400).
			<p>
			<table class="editform optiontable">
				<tr>
					<th width="33%" valign="top"><label for="shotcode_image_height">Image height:</label></th>
					<td>
						<input class="code" type="text" id="shotcode_image_height" name="shotcode_image_height" size="5" value="<?php echo $shotcode_image_height ; ?>" /><br />
					</td>
				</tr>
			</table>
			
		</fieldset>

		<p class="submit">
			<input name="update_options" value="Update Options &raquo;" type="submit" />
		</p>
	</form>


	<form method="post">
		<fieldset class="options">
			<legend>Test Image</legend>
			<div>
				<div style="float: left; padding: 5px; margin: 5px; border: 1px solid #ccc; text-align: center;">
					<?php shotcode_wp_plugin::get_test_shotcode_img_link(); ?>
					<br/>
					<b>Sample image (resized)</b>
				</div>
				<div style="float: left; padding: 5px; margin: 5px; border: 1px solid #ccc; text-align: center;">
					<?php shotcode_wp_plugin::get_test_shotcode_img_link(0); ?>
					<br/>
					<b>Sample image (original size)</b>
				</div>
			</div>
			<div style="clear: both">
				<p><b>URL in the image:</b> <?php echo shotcode_wp_plugin::get_test_shotcode_data(); ?>
				</p>
			</div>
		</fieldset>
	</form>
</div>
