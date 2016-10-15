<?php
class supporto_istanze_protocollo_views_handler_field extends views_handler_field {
  function render($values) {
    static $i = 1;
//    $editabile = ($this->view->name != 'le_mie_istanze' && !($this->view->name == 'istanze_personale' && $this->view->current_display == 'page_1'));
    $editabile = property_exists($this->view, 'si_editable') ? $this->view->si_editable : FALSE;
    $value = $this->get_value($values);
    $nid = $values->webform_submissions_node_nid;
    $sid = $values->webform_submissions_node_sid;
    $uid = $values->users_webform_submissions_uid;
    $tid = $values->webform_submissions_node_si_tid;
    $visto_referente = property_exists($values, 'webform_submissions_node_si_visto_referente_stato') ? $values->webform_submissions_node_si_visto_referente_stato : NULL;
    $nodo = node_load($nid);
    $nodata = is_null($values->webform_submissions_node_si_tid);
    $conc = $values->webform_submissions_node_si_concedibile_stato;
    $usa_visto_referente = FALSE;
    if (isset($nodo->field_si_referente['und'][0]['value']) && $nodo->field_si_referente['und'][0]['value'] == 1) {
      $usa_visto_referente = TRUE;
    }
    if (user_access('protocollato') &&
      $editabile &&
      $conc == 0 // &&
      //(($nodata && !$usa_visto_referente) || $usa_visto_referente)
      ) {
      $ass_array = array();
      $ass_array['my_checkbox'] = drupal_get_form('supporto_istanze_form_'.$i, $sid, $uid, $nodata? 0 : $tid, $nodata? 0 : $value, 'protocollo');
      $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
    }
    elseif ($nodata || $value == 0) {
      $html = sprintf('<span id="pro%d">---</span>', $sid);
    } else {
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/si.png" alt="protocollato" title="protocollato" />'; // sostituire con icona
    }
    ++$i;
    return $html;
  }
}
