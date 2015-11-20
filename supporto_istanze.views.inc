<?php
/**
 * hook for the Views module
 */
/**
 * Implements hook_views_pre_render().
 */ 
function supporto_istanze_views_pre_render(&$view) {
  static $css_done = FALSE;
  if (!$css_done) {
    drupal_add_css(drupal_get_path('module', 'supporto_istanze') . '/' . 'stylesheet.css');
    $css_done = TRUE;
  }
  $uid = $GLOBALS['user']->uid;
  if (!$uid) {
    return;
  }
  $msg = FALSE;
  foreach ($view->result as $i => $node) {
    if (!isset($node->webform_submissions_node_sid) || !isset($node->users_webform_submissions_uid)) {
      continue;
    }
    $nid = $node->webform_submissions_node_nid;
    $sid = $node->webform_submissions_node_sid;
    $uid = $node->users_webform_submissions_uid;
    $result = db_query('SELECT * FROM {supporto_istanze} WHERE user_id = :uid AND submission_id = :sid', array(':uid' => $uid, ':sid' => $sid));
    $nodata = ($result->rowCount() == 0);
    if (!$nodata) {
      $data = $result->fetchAssoc();
    }
    if (isset($node->field_field_si_protocollo)) {
      if (user_access('protocollato') && ($nodata || ((isset($node->field_field_si_acquisita) && is_null($data['acquisito_stato'])) || (isset($node->field_field_si_concedibile) && is_null($data['concedibile_stato']))))) {
        $ass_array = array();
        $ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_form_'.$i, $sid, $uid, $nodata? 0 : $data['tid'], $nodata? 0 : $data['protocollo_stato'], 'protocollo');
        $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
      }
      elseif ($nodata || $data['protocollo_stato'] == 0) {
        $html = '---';
      } else {
        $html = format_date($data['protocollo_data'], 'custom', 'd/m/Y');
      }
      $view->result[$i]->field_field_si_protocollo[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');                                                                                                              
    }
    if (isset($node->field_field_si_acquisita)) {
      if (user_access('acquisito') && !$nodata && $data['protocollo_stato'] == 1) {
        switch ($data['acquisito_stato']) {
          case 0:
            $status = 'da valutare';
            break;
          case 1:
            $status = 'acquisita';
            break;
          case 2:
            $status = 'non acquisita';
            break;            
        }
        $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'%s#overlay=node/%d/submission/%d/istanza_acquisisci/%d\'>%s</a>', current_path(), $nid, $sid, $data['tid'],$status);
      }
      elseif ($nodata || $data['acquisito_stato'] == 0) {
        $html = '---';
      } else {
        $html = ($data['acquisito_stato'] == 1 ? 's&igrave; ' : 'no ') . '(' . format_date($data['acquisito_data'], 'custom', 'd/m/Y') . ')';
      }
      $view->result[$i]->field_field_si_acquisita[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');
    }
    if (isset($node->field_field_si_concedibile)) {
      if (user_access('acquisito') && !$nodata && $data['protocollo_stato'] == 1 && is_null($data['visto_stato'])) {
        switch ($data['concedibile_stato']) {
          case 0:
            $status = 'da valutare';
            break;
          case 1:
            $status = 'concedibile';
            break;
          case 2:
            $status = 'non concedibile';
            break;            
        }
        $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'%s#overlay=node/%d/submission/%d/istanza_concedi/%d\'>%s</a>', current_path(), $nid, $sid, $data['tid'],$status);
      }
      elseif ($nodata || $data['concedibile_stato'] == 0) {
        $html = '---';
      } else {
        $html = ($data['concedibile_stato'] == 1 ? 's&igrave; ' : 'no ') . '(' . format_date($data['concedibile_data'], 'custom', 'd/m/Y') . ')';
      }
      $view->result[$i]->field_field_si_concedibile[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');
    }
    if (isset($node->field_field_si_visto)) {
     if (user_access('visto') && !$nodata && $data['protocollo_stato'] == 1 && $data['concedibile_stato'] == 1) {
        switch ($data['visto_stato']) {
          case 0:
            $status = 'da valutare';
            break;
          case 1:
            $status = 'si concede';
            break;
          case 2:
            $status = 'non si concede';
            break;            
        }
        $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'%s#overlay=node/%d/submission/%d/istanza_visto/%d\'>%s</a>', current_path(), $nid, $sid, $data['tid'],$status);
      }
      elseif ($nodata || $data['visto_stato'] == 0) {
        $html = '---';
      } else {
        $html = ($data['visto_stato'] == 1 ? 'Si concede' : 'Non si concede') . '(' . format_date($data['visto_data'], 'custom', 'd/m/Y') . ')';
      }
      $view->result[$i]->field_field_si_visto[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');
    }
    if (isset($node->field_field_si_motivazioni)) {
      if ($nodata) {
        $html = '---';
      } else {
        $full = str_replace(array('\'', '"'),'&#39;',$data['motivazioni']);
        $abbr = _supporto_istanze_abbrevia_testo($data['motivazioni']);
        $abbr = str_replace(array('\'', '"'),'&#39;',$abbr);
        $html = '<div id=\'tid_' . $data['tid'] . '\' style="display:none" onmouseover=\'this.innerHTML="' . $full . '"\' onmouseout=\'this.innerHTML="' . $abbr . '"\' class=\'motivazioni\'>' . $data['motivazioni'] . '</div>';
        $html .= "<script type=\"text/javascript\">\n//<![CDATA[\nvar div=document.getElementById('tid_".$data['tid']."');\ndiv.innerHTML=\"" . $abbr . "\";\ndiv.style.display='block';\n//]]>\n</script>";
      }
      $view->result[$i]->field_field_si_motivazioni[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');
    }
  }
}

function _supporto_istanze_abbrevia_testo($text) {
  return substr($text, 0, 8) . (strlen($text) > 8 ? '...(segue)' : '');
}
