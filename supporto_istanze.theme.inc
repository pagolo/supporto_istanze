<?php
/**
 * @file
 * theming file.
 */

 /**
  * Implements template_preprocess() hook
  */     
function template_preprocess_supporto_istanze_views(&$variables) {
  if (empty($variables['content'])) {
    $assoc = $variables['assoc'];
    $variables['content'] = drupal_render($assoc);
  }
}
