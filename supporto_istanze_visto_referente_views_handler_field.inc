<?php
class supporto_istanze_visto_referente_views_handler_field extends views_handler_field {
  function right_user($comp_uid) {
    global $user;
    $current_user = user_load($user->uid);
    $comp_user = user_load($comp_uid);
    foreach ($comp_user->field_scuola['und'] as $item1) {
      foreach ($current_user->field_scuola['und'] as $item2) {
        if ($item1['value'] == $item2['value']) {
          return TRUE;
        }
      }
    }
    return FALSE; 
  }
  function render($values) {
    global $user;
    static $i = 1;
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
    if (user_access('visto referente') && (user_has_role(user_role_load_by_name('administrator')->rid) || $this->right_user($uid)) && $editabile && $value == 0) {
      $ass_array = array();
      $ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_ref_form_'.$i, $sid, $uid, $nodata? 0 : $tid, $nodata? 0 : $value, 'visto_referente');
      $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array))."<span id='ref1$sid'><span><span id='ref2$sid'><span>";
    }
    elseif ($nodata || $value == 0) {
      if ($usa_visto_referente)
        $html = 'Nessun visto';
      else
        $html = '---';
    } else {
      $si_no = ($value == 1 ? 'si' : 'no');
      $msg = 'visto ' . ($value == 2? 'negativo' : 'positivo');
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/' . $si_no . '.png" alt="' . $msg . '" title="' . $msg . '" />';
    }
    ++$i;
    return $html;
  }
}
