<?php
class supporto_istanze_concedibile_views_handler_field extends views_handler_field {
  function render($values) {
//  dsm($values);
    $value = $this->get_value($values);
    $sid = $values->webform_submissions_node_sid;
    $nid = $values->webform_submissions_node_nid;
    $tid = $values->webform_submissions_node__supporto_istanze_tid;
    $protoc = $values->webform_submissions_node__supporto_istanze_protocollo_stato;
    $visto = $values->webform_submissions_node__supporto_istanze_visto_stato;
    $nodata = is_null($tid);
    if (user_access('acquisito') && !$nodata && $protoc == 1 && is_null($visto)) {
      $status = 'da valutare';
      switch ($value) {
        case 1:
          $status = 'concedibile';
          break;
        case 2:
          $status = 'non concedibile';
          break;            
      }
      $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'%s#overlay=node/%d/submission/%d/istanza_concedi/%d\'>%s</a>', current_path(), $nid, $sid, $tid, $status);
    }
    elseif ($nodata || $value == 0) {
      $html = '---';
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = ($value == 2? 'non ' : '') . 'concedibile';
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    return $html;
  }
}
