<?php
class supporto_istanze_visto_views_handler_field extends views_handler_field {
  function render($values) {
    $editabile = ($this->view->name != 'le_mie_istanze');
    $value = $this->get_value($values);
    $sid = $values->webform_submissions_node_sid;
    $nid = $values->webform_submissions_node_nid;
    $tid = $values->webform_submissions_node__supporto_istanze_tid;
    $conc = $values->webform_submissions_node__supporto_istanze_concedibile_stato;
    $acquisisci = FALSE;
    $nodo = node_load($nid);
    if (isset($nodo->field_si_acquisisci['und'][0]['value']) && $nodo->field_si_acquisisci['und'][0]['value'] == 1) {
      $acquisisci = TRUE;
    }
    $nodata = is_null($tid);
    if (user_access('visto') && $editabile && !$nodata && $conc == 1 && $acquisisci == FALSE) {
      $status = 'da valutare';
      switch ($value) {
        case 1:
          $status = 'si concede';
          break;
        case 2:
          $status = 'non si concede';
          break;            
      }
      $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'%s#overlay=node/%d/submission/%d/istanza_visto/%d\'>%s</a>', current_path(), $nid, $sid, $tid,$status);
    }
    elseif ($nodata || $value == 0) {
      $html = '---';
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = ($value == 2? 'non ' : '') . 'si concede';
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    return $html;
  }
}
