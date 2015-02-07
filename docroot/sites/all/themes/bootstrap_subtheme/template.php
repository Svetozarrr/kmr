<?php

/**
 * @file
 * Contains custom preprocess functions for current theme
 */

/**
 * Implements template_preprocess_html()
 */
function bootstrap_subtheme_preprocess_html(&$variables)
{
  $head_title = &$variables['head_title'];
  $head_title = htmlspecialchars_decode($head_title);
  $head_title = strip_tags($head_title);
}
