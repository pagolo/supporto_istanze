<?php
class supporto_istanze_visto_referente_views_handler_field extends views_handler_field {
  function right_user($comp_uid) {
    global $user;
    $current_user = user_load($user->uid);
    $comp_user = user_load($comp_uid);
    return ($comp_user->field_scuola['und']['0']['value'] == $current_user->field_scuola['und']['0']['value']);
  }
  function render($values) {
    global $user;
    $editabile = property_exists($this->view, 'si_editable') ? $this->view->si_editable : FALSE;
    $value = $this->get_value($values);
    $uid = $values->users_webform_submissions_uid;
    $sid = $values->webform_submissions_node_sid;
    $nid = $values->webform_submissions_node_nid;
    $tid = $values->webform_submissions_node_si_tid;
    $conc = $values->webform_submissions_node_si_concedibile_stato;
    $visto_dsga = property_exists($values, 'webform_submissions_node_si_visto_dsga_stato') ? $values->webform_submissions_node_si_visto_dsga_stato : NULL;
    $visto_referente = property_exists($values, 'webform_submissions_node_si_visto_referente_stato') ? $values->webform_submissions_node_si_visto_referente_stato : NULL;
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
    if (!($usa_visto_referente)) {
      return '---';
    }
    $nodata = is_null($tid);
    if (user_access('visto referente') && ($user->uid == 1 || $this->right_user($uid)) && $editabile && !$nodata && $conc == 0 && is_null($visto)) {
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
      $html = sprintf('<a title=\'clic qui per valutare o modificare\' href=\'node/%d/submission/%d/istanza_visto_referente/%d?destination=%s\'>%s</a>', $nid, $sid, $tid, $a['destination'], $status);
    }
    elseif ($nodata || $value == 0) {
      if (!($usa_visto_referente && user_access('visto referente')))
        $html = '---';
      else
        $html = sprintf('<span id="sid%d">---</span>', $sid);
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = ($value == 2? 'non ' : '') . 'pu&ograve; procedere';
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    return $html;
  }
}
