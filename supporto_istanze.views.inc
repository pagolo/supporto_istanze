<?php
/**
 * hook for the Views module
 */
/**
 * Implements hook_views_pre_render().
 */ 
function supporto_istanze_views_pre_render(&$view) {
  $uid = $GLOBALS['user']->uid;
  if (!$uid) {
    return;
  }
  $msg = FALSE;
  foreach ($view->result as $i => $node) {
    //dsm($node);
    if (!isset($node->webform_submissions_node_sid) || !isset($node->users_webform_submissions_uid)) {
      continue;
    }
    $sid = $node->webform_submissions_node_sid;
    $uid = $node->users_webform_submissions_uid;
    $result = db_query('SELECT * FROM {supporto_istanze} WHERE user_id = :uid AND submission_id = :sid', array(':uid' => $uid, ':sid' => $sid));
    $nodata = ($result->rowCount() == 0);
    if (!$nodata) {
      $data = $result->fetchAssoc();
    }
    if (isset($node->field_field_si_protocollo)) {
      if (user_access('protocollato')) {
        $ass_array = array();
        $ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_form_'.$i, $sid, $uid, $nodata? 0 : $data['tid'], $nodata? 0 : $data['protocollo_stato'], 'protocollo');
        $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
      }
      else if ($nodata || $data['protocollo_stato'] == 0) {
        $html = '---';
      } else {
        $html = format_date($data['protocollo_data'], 'custom', 'd/m/Y');
      }
      $view->result[$i]->field_field_si_protocollo[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');                                                                                                              
    }
    if (isset($node->field_field_si_visto)) {
      if (user_access('visto')) {
        $ass_array = array();
        $ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_form_1_'.$i, $sid, $uid, $nodata? 0 : $data['tid'], $nodata? 0 : $data['visto_stato'], 'visto');
        $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
      }
      else if ($nodata || $data['visto_stato'] == 0) {
        $html = '---';
      } else {
        $html = format_date($data['visto_data'], 'custom', 'd/m/Y');
      }
      $view->result[$i]->field_field_si_visto[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');                                                                                                              
    }
    if (isset($node->field_field_si_accolto)) {
      if ($nodata || $data['accolto_stato'] == 0) {
        $view->result[$i]->field_field_si_accolto[0]['rendered'][] = array ('#markup' => '---', '#access' => '1');
      } else {
      }
    }
  }
}
