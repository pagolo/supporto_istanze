<?php
/**
 * hook for the Views module
 */
/**
 * Implements hook_views_data().
 */ 
function supporto_istanze_views_data() {
  $data = array();
  $data['supporto_istanze']['table']['group'] = 'Supporto istanze';
  $data['supporto_istanze']['table']['join'] = array(
    'webform_submissions' => array(
      'left_field' => 'sid',
      'field' => 'submission_id',
    ),
  );
/*
  $data['supporto_istanze']['tid'] = array(
    'title' => 'Chiave di procedura',
    'help' => 'Relazione tra submission e procedura.',
    'relationship' => array(
      'base' => 'webform_submissions',
      'handler' => 'views_handler_relationship',
      'label' => 'Istanza',
    ),
    // There is no argument here; if you need an argument, add the relationship
    // and use the node: nid argument.
  );
*/
  $data['supporto_istanze']['tid'] = array(
    'title' => 'Chiave di istanza',
    'help' => 'Indice primario tabella supporto_istanze.',
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    // There is no argument here; if you need an argument, add the relationship
    // and use the node: nid argument.
  );
  $data['supporto_istanze']['protocollo_stato'] = array(
    'title' => 'Protocollo',
    'help' => 'Istanza protocollata.',
    'field' => array(
      'handler' => 'supporto_istanze_protocollo_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['acquisito_stato'] = array(
    'title' => 'Acquisito',
    'help' => 'Istanza acquisita.',
    'field' => array(
      'handler' => 'supporto_istanze_acquisito_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['concedibile_stato'] = array(
    'title' => 'Verifica ufficio',
    'help' => 'Istanza concedibile.',
    'field' => array(
      'handler' => 'supporto_istanze_concedibile_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['visto_stato'] = array(
    'title' => 'Visto del DS',
    'help' => 'Istanza accolta.',
    'field' => array(
      'handler' => 'supporto_istanze_visto_views_handler_field',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['evaso_data'] = array(
    'title' => 'Evaso il',
    'help' => 'Istanza evasa il...',
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => FALSE,
    ),
  );
  $data['supporto_istanze']['motivazioni'] = array(
    'title' => 'Motivazioni',
    'help' => 'Le motivazioni per il rifiuto della istanza.',
    'field' => array(
      'handler' => 'supporto_istanze_motivazioni_views_handler_field',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function supporto_istanze_views_handlers() {
  return array(
  'info' => array(
    'path' => drupal_get_path('module', 'supporto_istanze'),
    ),
  'handlers' => array(
    'supporto_istanze_protocollo_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_acquisito_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_concedibile_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_visto_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    'supporto_istanze_motivazioni_views_handler_field' => array(
      'parent' => 'views_handler_field',
     ),        
    ),
  );
}
/**
 * Implements hook_views_pre_render().
 */
function supporto_istanze_views_pre_render(&$view) {
  static $css_done = FALSE;
  if (!$css_done) {
    drupal_add_css(drupal_get_path('module', 'supporto_istanze') . '/' . 'stylesheet.css');
    $css_done = TRUE;
  }
/*
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
    if (isset($node->webform_submissions_node__supporto_istanze_motivazioni)) {
      if ($nodata) {
        $html = '---';
      } else {
        $full = str_replace(array('\'', '"'),'&#39;',$data['motivazioni']);
        $abbr = _supporto_istanze_abbrevia_testo($data['motivazioni']);
        $abbr = str_replace(array('\'', '"'),'&#39;',$abbr);
        $html = '<div id=\'tid_' . $data['tid'] . '\' style="display:none" onmouseover=\'this.innerHTML="' . $full . '"\' onmouseout=\'this.innerHTML="' . $abbr . '"\' class=\'motivazioni\'>' . $data['motivazioni'] . '</div>';
        $html .= "<script type=\"text/javascript\">\n//<![CDATA[\nvar div=document.getElementById('tid_".$data['tid']."');\ndiv.innerHTML=\"" . $abbr . "\";\ndiv.style.display='block';\n//]]>\n</script>";
      }
      //$view->result[$i]->field_field_si_motivazioni[0]['rendered'][] = array ('#markup' => $html, '#access' => '1');
      $view->result[$i]->webform_submissions_node__supporto_istanze_motivazioni = $html;
    }
  }
    */
}

