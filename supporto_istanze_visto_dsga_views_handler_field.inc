<?php
class supporto_istanze_visto_dsga_views_handler_field extends views_handler_field {
  function render($values) {
    $editabile = property_exists($this->view, 'si_editable') ? $this->view->si_editable : FALSE;
    $value = $this->get_value($values);
    $sid = $values->webform_submissions_node_sid;
    $nid = $values->webform_submissions_node_nid;
    $tid = $values->webform_submissions_node_si_tid;
    $conc = $values->webform_submissions_node_si_concedibile_stato;
    $visto_dsga = $values->webform_submissions_node_si_visto_dsga_stato;
    $visto_referente = $values->webform_submissions_node_si_visto_referente_stato;
    $visto = $values->webform_submissions_node_si_visto_stato;
    $usa_visto_dsga = $usa_visto_referente = FALSE;
    $acquisisci = FALSE;
    $nodo = node_load($nid);
    if (isset($nodo->field_si_dsga['und'][0]['value']) && $nodo->field_si_dsga['und'][0]['value'] == 1) {
      $usa_visto_dsga = TRUE;
    }
    if (isset($nodo->field_si_referente['und'][0]['value']) && $nodo->field_si_referente['und'][0]['value'] == 1) {
      $usa_visto_referente = TRUE;
    }
    if (isset($nodo->field_si_acquisisci['und'][0]['value']) && $nodo->field_si_acquisisci['und'][0]['value'] == 1) {
      $acquisisci = TRUE;
    }
    if (!($usa_visto_dsga)) {
      return '---';
    }
    $nodata = is_null($tid);
    if (user_access('visto dsga') && $editabile && !$nodata && $conc == 1 && is_null($visto) && (!$usa_visto_referente || is_null($visto_referente))) {
      $status = 'da valutare';
      switch ($value) {
        case 1:
          $status = 'pu&ograve; procedere';
          break;
        case 2:
          $status = 'non pu&ograve; procedere';
          break;            
      }
      $a = drupal_get_destination();
      $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'node/%d/submission/%d/istanza_visto_dsga/%d?destination=%s\'>%s</a>', $nid, $sid, $tid, $a['destination'], $status);
    }
    elseif ($nodata || $value == 0) {
      $html = '---';
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = ($value == 2? 'non ' : '') . 'pu&ograve; procedere';
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    return $html;
  }
}
