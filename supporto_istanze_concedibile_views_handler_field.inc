<?php
class supporto_istanze_concedibile_views_handler_field extends views_handler_field {
  function render($values) {
    $editabile = ($this->view->name != 'le_mie_istanze' && !($this->view->name == 'istanze_personale' && $this->view->current_display == 'page_1'));
    $value = $this->get_value($values);
    $sid = $values->webform_submissions_node_sid;
    $nid = $values->webform_submissions_node_nid;
    $tid = $values->webform_submissions_node_si_tid;
    $protoc = $values->webform_submissions_node_si_protocollo_stato;
    $visto = $values->webform_submissions_node_si_visto_stato;
    $acquisisci = FALSE;
    $nodo = node_load($nid);
    if (isset($nodo->field_si_acquisisci['und'][0]['value']) && $nodo->field_si_acquisisci['und'][0]['value'] == 1) {
      $acquisisci = TRUE;
    }
    $nodata = is_null($tid);
    if (user_access('acquisito') && $editabile && !$nodata && $protoc == 1 && is_null($visto)) {
      $status = 'da valutare';
      switch ($value) {
        case 1:
          $status = $acquisisci? 'acquisito' : 'concedibile';
          break;
        case 2:
          $status = $acquisisci? 'non acquisito' : 'non concedibile';
          break;            
      }
      $a = drupal_get_destination();
      $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'node/%d/submission/%d/istanza_%s/%d?destination=%s\'>%s</a>', $nid, $sid, $acquisisci? 'acquisisci' : 'concedi', $tid, $a['destination'], $status);
    }
    elseif ($nodata || $value == 0) {
      $html = '---';
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = ($value == 2? 'non ' : '') . ($acquisisci? 'acquisito' : 'concedibile');
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    return $html;
  }
}
